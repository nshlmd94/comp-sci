import requests

from flask import Flask, session, redirect, render_template
from functools import wraps

import yfinance as yf

def error(message, code=400):
    
    def escape(s):
        # escape special characters
        
        for old, new in [
            ("-", "--"),
            (" ", "-"),
            ("_", "__"),
            ("?", "~q"),
            ("%", "~p"),
            ("#", "~h"),
            ("/", "~s"),
            ('"', "''"),
        ]:
            s = s.replace(old, new)
        
        return s
    
    return render_template("error.html", top=code, bottom=escape(message)), code


def loginRequired(func):
    
    @wraps(func)
    def wrapper(*args, **kwargs):
        if session.get("user_id") is None:
            return redirect("/login")
        else:
            return func(*args, **kwargs)
        
    return wrapper
            
def lookupData(inputTicker):
    try:
        stock = yf.Ticker(inputTicker)
        price = stock.fast_info["lastPrice"]
        currency = stock.fast_info["currency"]
        stockName = stock.info["longName"]
        if price is None:
            return None
        else:
            return {
                "Name": stockName,
                "Price": price, 
                "Currency": currency, 
                }
    except Exception as e:
        exceptionName = type(e).__name__
        errorMessage = str(e)
        print(f"{exceptionName}, {errorMessage}")
        return None