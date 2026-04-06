from flask import Flask, session, render_template, redirect, request
#from flask_session import Session
import sqlite3

app = Flask(__name__)

sqliteConnection = sqlite3.connect("birthdays.db")
cursor = sqliteConnection.cursor()
# cursor creates a cursor object, which is used to interact with the database and execute SQL queries

query = "CREATE TABLE IF NOT EXISTS birthdays (id INTEGER PRIMARY KEY, name TEXT NOT NULL, month INTEGER NOT NULL, day INTEGER NOT NULL);"
cursor.execute(query)
sqliteConnection.commit()

sqliteConnection.close()

@app.route("/", methods=['GET','POST'])
def layout():
    if request.method == 'GET':
        birthdays = getBirthdays()
        return render_template("index.html", birthdays=birthdays)
    
    elif request.method == 'POST':
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")
        
        birthdays = getBirthdays()
        
        if not name:
            return render_template("index.html", birthdays=birthdays, error="Name is required!")
        
        if not month:
            return render_template("index.html", birthdays=birthdays, error="Month is required!")
        try:
            month = int(month)
        except ValueError:
            return redirect("/")
        if month < 1 or month > 12:
            return redirect("/")
        
        if not day:
            return render_template("index.html", birthdays=birthdays, error="Day is required!")
        try:
            day = int(day)
        except ValueError:
            return redirect("/")
        if month < 1 or month > 31:
            return redirect("/")
            
        insertBirthdays(name, month, day)
        return redirect("/")
    
@app.route("/delete", methods=['POST'])
def remove():
    id = request.form.get("id")
    deleteBirthdays(id)
    return redirect("/")

@app.route("/update", methods=['POST'])
def edit():
    name = request.form.get("name")
    month = request.form.get("month")
    day = request.form.get("day")
    id = request.form.get("id")
    
    updateBirthdays(name, month, day, id)
    return redirect("/")
    
def getBirthdays():
    sqliteConnection = sqlite3.connect("birthdays.db")
    sqliteConnection.row_factory = sqlite3.Row
    cursor = sqliteConnection.cursor()
    birthdays = cursor.execute("SELECT * FROM birthdays").fetchall()
    sqliteConnection.close()
    return birthdays
    
def insertBirthdays(name, month, day):
    sqliteConnection = sqlite3.connect("birthdays.db")
    cursor = sqliteConnection.cursor()
    cursor.execute("INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)", (name, month, day))
    sqliteConnection.commit()
    sqliteConnection.close()
    
def deleteBirthdays(id):
    sqliteConnection = sqlite3.connect("birthdays.db")
    cursor = sqliteConnection.cursor()
    cursor.execute("DELETE FROM birthdays WHERE id = ?", [id])
    sqliteConnection.commit()
    sqliteConnection.close()
    
def updateBirthdays(name, month, day, id):
    sqliteConnection = sqlite3.connect("birthdays.db")
    cursor = sqliteConnection.cursor()
    cursor.execute("UPDATE birthdays  SET name = ?, month = ?, day = ? WHERE id = ?", [name, month, day, id])
    sqliteConnection.commit()
    sqliteConnection.close()