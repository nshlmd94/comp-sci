from flask import Flask, session, render_template, redirect, request
from flask_session import Session
import os
from dotenv import load_dotenv
import sqlite3

from werkzeug.security import check_password_hash, generate_password_hash

from helpers import error, loginRequired, lookupData

load_dotenv()

# Configure application
app = Flask(__name__)

app.secret_key = os.getenv("SECRET_KEY")

app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

sqliteConnection = sqlite3.connect("finance.db")
sqliteConnection.row_factory = sqlite3.Row
db = sqliteConnection.cursor()
db.execute("CREATE TABLE IF NOT EXISTS purchases (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, user_id INTEGER NOT NULL, ticker TEXT NOT NULL, quantity INTEGER NOT NULL, price REAL NOT NULL, timestamp DATETIME DEFAULT CURRENT_TIMESTAMP NOT NULL)")
sqliteConnection.commit()
sqliteConnection.close()

@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/login", methods=["GET", "POST"])
def login():
    
    session.clear()
    
    if request.method == "POST":
        
        username = request.form.get("username")
        password = request.form.get("password")
        
        if not username:
            return error("must provide username", 403)
        
        if not password:
            return error("must provide password", 403)
        
        sqliteConnection = sqlite3.connect("finance.db")
        sqliteConnection.row_factory = sqlite3.Row
        db = sqliteConnection.cursor()
        rows = db.execute("SELECT * FROM users WHERE username = ?", [username]).fetchall()
        sqliteConnection.close()
        
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], password):
            return error("invalid username or password", 403)
        
        session["user_id"] = rows[0]["id"]
        
        return redirect("/")
            
    elif request.method == "GET":
        return render_template("login.html")
        

@app.route("/", methods=["GET"])
@loginRequired
def index():
    user_id = session["user_id"]
    
    sqliteConnection = sqlite3.connect("finance.db")
    sqliteConnection.row_factory = sqlite3.Row
    db = sqliteConnection.cursor()
    rows = db.execute("SELECT ticker, sum(quantity) as quantity FROM purchases WHERE user_id = ? GROUP BY UPPER(ticker) HAVING sum(quantity) > 0", [user_id]).fetchall()
    cash = db.execute("SELECT cash FROM users WHERE id = ?", [user_id]).fetchone()
    
    holdings = []
    
    for row in rows:
        name = row["ticker"]
        quantity = row["quantity"]
        output = lookupData(name)
        
        if output is None:
            continue
        
        currentPrice = output["Price"]
        total = int(quantity) * currentPrice
        holdings.append({
            "Ticker": name, 
            "Quantity": quantity, 
            "Price": currentPrice,
            "Total": total,
        })
        
    finalTotal = 0
    for holding in holdings:
        finalTotal += holding["Total"]
    finalTotal = finalTotal + cash["cash"]
    
    sqliteConnection.close()
    
    return render_template("index.html", holdings=holdings, cash=cash, total=finalTotal)


@app.route("/register", methods=["GET", "POST"])
def register():
    
    session.clear()
    
    if request.method == "POST":
        
        username = request.form.get("username")
        password = request.form.get("password")
        confirmPassword = request.form.get("confirm_password")
        
        if not username:
            return error("must provide username", 403)
            
        if not password:
            return error("must provide password", 403)
            
        if not confirmPassword or confirmPassword != password:
            return error("passwords don't match", 403)
        
        sqliteConnection = sqlite3.connect("finance.db")
        sqliteConnection.row_factory = sqlite3.Row
        db = sqliteConnection.cursor()
        
        hashedPassword = generate_password_hash(password)
        
        try:
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", (username, hashedPassword))
            sqliteConnection.commit()
        except sqlite3.IntegrityError:
            sqliteConnection.close()
            return error("that username already exists, choose another one", 403)
        
        #gives the id of the last row inserted, other option would be to rerun the select query
        session["user_id"] = db.lastrowid  
        
        sqliteConnection.close()
        
        return redirect("/")
    
    elif request.method == "GET":
        return render_template("register.html")
    
    
@app.route("/quote", methods=["GET", "POST"])
@loginRequired
def quote():
    if request.method == "POST":
        name = request.form.get("ticker")
        result = lookupData(name)
        if result is None:
            return error("Invalid ticker", 400)
        return render_template("quote.html", result=result)
    else:
        return render_template("quote.html", result=None)
    
    
@app.route("/buy", methods=["GET", "POST"])
@loginRequired
def buy():
    if request.method == "POST":
        user_id = session["user_id"]
        name = request.form.get("ticker")
        quantity = request.form.get("quantity")
        
        if not name:
            return error("Ticker can't be blank", 400)
        
        if not quantity:
            return error("Quantity can't be blank", 400)
        
        output = lookupData(name)
        
        if output is None:
            return error("Invalid ticker", 400)
        
        price = output["Price"]
        
        sqliteConnection = sqlite3.connect("finance.db")
        sqliteConnection.row_factory = sqlite3.Row
        db = sqliteConnection.cursor()
        
        rows = db.execute("SELECT cash FROM users WHERE id = ?", [user_id]).fetchone()
        cash = rows["cash"]
        
        total = price * int(quantity)
        amount = cash
        
        if cash < total:
            sqliteConnection.close()
            return error("Insufficient funds", 400)
        
        remainder = amount - total
        
        result = {
            "ticker": name,
            "price": price,
            "quantity": quantity,
            "total": total,
            "amount": amount,
            "remainder": remainder,
        }

        db.execute("INSERT INTO purchases (user_id, ticker, quantity, price) VALUES (?, ?, ?, ?)", (user_id, name, quantity, price))
        sqliteConnection.commit()
        
        db.execute("UPDATE users SET cash = ? WHERE id = ?", (remainder, user_id))
        sqliteConnection.commit()
        
        sqliteConnection.close()
        
        return render_template("buy.html", result=result)
    
    else:
        return render_template("buy.html", result=None)
    

@app.route("/sell", methods=["GET", "POST"])
@loginRequired
def sell():
    if request.method == "POST":
        user_id = session["user_id"]
        name = request.form.get("ticker")
        quantity = request.form.get("quantity")
        
        if not name:
            return error("Ticker is required", 400)
        
        if not quantity:
            return error("Quantity is required", 400)
        
        output = lookupData(name)
        saleQuantity = int(quantity)
        
        if output is None:
            return error("Invalid ticker", 400)
        
        price = output["Price"]
        
        # Open the SQL Connection and copy the database using the cursor object
        sqliteConnection = sqlite3.connect("finance.db")
        sqliteConnection.row_factory = sqlite3.Row
        db = sqliteConnection.cursor()
        
        # Figure out what the base price of each entry with a loop and calculate the profit (Try doing it with FIFO - it'll be a nice challenge)
        rows = db.execute("SELECT * FROM purchases WHERE ticker = ? AND user_id = ? and quantity > 0 ORDER BY timestamp ASC", (name, user_id)).fetchall()
        profit = 0
        remainderShares = saleQuantity
        
        totalBuys = db.execute("SELECT SUM(quantity) FROM purchases WHERE ticker = ? AND user_id = ? AND quantity > 0", (name, user_id)).fetchone()
        totalSale = db.execute("SELECT SUM(quantity) FROM purchases WHERE ticker = ? AND user_id = ? AND quantity < 0", (name, user_id)).fetchone()
        totalSold = totalSale[0] if totalSale[0] else 0
        totalLeft = totalBuys[0] + totalSold
                
        if totalLeft >= saleQuantity and -totalSold > 0:
            runningCount = 0
            lowerRange = 0
            pendingInLowerRange = 0
            
            for i in range(len(rows)):
                runningCount = rows[i]["quantity"] + runningCount
                if runningCount >= -totalSold:
                    lowerRange = i
                    pendingInLowerRange = runningCount + totalSold
                    profitLowerRange = ((price - rows[lowerRange]["price"]) * pendingInLowerRange)
                    break
            
            if remainderShares <= pendingInLowerRange and pendingInLowerRange > 0:
                profit = ((price - rows[lowerRange]["price"]) * remainderShares) + profit
                pendingInLowerRange = pendingInLowerRange - remainderShares
            else:
                remainderShares = remainderShares - pendingInLowerRange
                for j in range(lowerRange+1, len(rows)):
                    shares = min(remainderShares, rows[j]["quantity"])
                    profit = ((price - rows[j]["price"]) * shares) + profit
                    remainderShares = remainderShares - shares
                    if remainderShares == 0:
                        profit = profit + profitLowerRange
                        break
        
        elif totalLeft >= saleQuantity and totalSold == 0:
            for j in range(len(rows)):
                shares = min(remainderShares, rows[j]["quantity"])
                profit = ((price - rows[j]["price"]) * shares) + profit
                remainderShares = remainderShares - shares
                if remainderShares == 0:
                    break
                    
        else:
            return error("Can't sell more than you own", 400)
        
        db.execute("INSERT INTO purchases (user_id, ticker, quantity, price) VALUES (?, ?, ?, ?)", (user_id, name, -saleQuantity, price))
        sqliteConnection.commit()
        
        cashValue = db.execute("SELECT cash FROM users WHERE id = ?", [user_id]).fetchone()
        cash = cashValue["cash"]
        
        # When displaying the sale profit, only showcase the one for the current ticker
        total = price * saleQuantity
        amount = cash 
        
        remainder = amount + total
        
        result = {
            "ticker": name,
            "price": price,
            "quantity": quantity,
            "total": total,
            "amount": amount,
            "profit": profit,
            "remainder": remainder,
        }
        
        db.execute("UPDATE users SET cash = ? WHERE id = ?", (remainder, user_id))
        sqliteConnection.commit()
        
        sqliteConnection.close()
        
        return render_template("sell.html", result=result)
        
    else:
        return render_template("sell.html", result=None)


@app.route("/history", methods=["GET"])
@loginRequired
def history():
    user_id = session["user_id"]
    
    sqliteConnection = sqlite3.connect("finance.db")
    sqliteConnection.row_factory = sqlite3.Row
    db = sqliteConnection.cursor()
    rows = db.execute("SELECT * FROM purchases WHERE user_id = ?", [user_id]).fetchall()
    
    sqliteConnection.close()
    
    return render_template("history.html", rows=rows)
    

@app.route("/logout", methods=["GET"])
@loginRequired
def logout():
    
    session.clear()
    
    return redirect("/")
    