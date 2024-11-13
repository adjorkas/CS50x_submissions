import os
import re

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd


# Define global username
def define_username(input_string):
    global username
    username = input_string


# Check if password is strong enough
def is_password_strong(password):
    return (
        bool(re.search(r"[!@#$%^&*(),.?\":{}|<>]", password))
        and bool(re.search(r"[A-Z]", password))
        and bool(re.search(r"[a-z]", password))
        and len(password) >= 8
    )


# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    try:
        data = db.execute(
            "SELECT company_symbol, price, SUM(amount) AS totalsum FROM transactions JOIN users ON transactions.user_id = users.id WHERE users.id = ? GROUP BY company_symbol;",
            session["user_id"],
        )
        cash = usd(
            (db.execute("SELECT cash FROM users WHERE id = ?;", session["user_id"]))[0][
                "cash"
            ]
        )
        total = usd(
            db.execute(
                "SELECT SUM(total+cash) AS TOTAL FROM (SELECT SUM(price * totalsum) AS total, cash FROM (SELECT company_symbol, price, SUM(amount) AS totalsum, cash FROM transactions JOIN users ON transactions.user_id = users.id WHERE users.id = ? GROUP BY company_symbol));",
                session["user_id"],
            )[0]["TOTAL"]
        )
        return render_template("index.html", data=data, usd=usd, cash=cash, total=total)
    except:
        return render_template("index.html")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        # Remember username
        define_username(
            (db.execute("SELECT username FROM users WHERE id = ?", session["user_id"]))[
                0
            ]["username"]
        )

        # Ensure symbol is valid
        in_symbol = request.form.get("symbol")
        if not in_symbol or lookup(in_symbol) == None:
            return apology("Invalid or missing symbol", 400)

        # Ensure shares are positive int
        try:
            in_shares = int(request.form.get("shares"))
        except ValueError:
            return apology("Invalid share input", 400)
        if not in_shares or in_shares < 1:
            return apology("Shares should be a positive number!", 400)

        # Ensure user has enough money for the transaction
        result = lookup(in_symbol)
        stocks_price = in_shares * (result["price"])
        user_capital = (
            db.execute("SELECT cash FROM users WHERE username = ?;", username)
        )[0]["cash"]
        if stocks_price > user_capital:
            return apology("Sorry... not enough money", 400)

        # Case OK:

        # Add company-symbol pair if not in DB
        if (
            db.execute(
                "SELECT COUNT(*) FROM companies WHERE symbol = ? LIMIT 1;",
                result["symbol"],
            )[0]["COUNT(*)"]
        ) == 0:
            db.execute(
                "INSERT INTO companies (symbol, name) VALUES (?, ?);",
                result["symbol"],
                result["name"],
            )

        # Add transactions to DB
        db.execute(
            "INSERT INTO transactions (user_id, company_symbol, time_of_purchase, price, amount) VALUES (?, ?, ?, ?, ?);",
            session["user_id"],
            result["symbol"],
            datetime.now(),
            result["price"],
            in_shares,
        )

        # Update user capital in DB
        db.execute(
            "UPDATE users SET cash = ? WHERE username = ?;",
            (user_capital - stocks_price),
            username,
        )

        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    rows = db.execute(
        "SELECT company_symbol, amount, price, time_of_purchase FROM transactions WHERE user_id = ?;",
        session["user_id"],
    )
    return render_template("history.html", rows=rows, usd=usd)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        in_symbol = request.form.get("symbol")
        if not in_symbol or lookup(in_symbol) == None:
            return apology("Invalid or missing symbol", 400)
        else:
            result = lookup(in_symbol)
            return render_template(
                "quoted.html", result=result, price=usd(result["price"])
            )
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        in_username = request.form.get("username")
        in_password = request.form.get("password")
        in_confirmation = request.form.get("confirmation")
        if not in_username:
            return apology("Username required", 400)
        elif (
            db.execute(
                "SELECT COUNT(*) FROM users WHERE username = ? LIMIT 1;", in_username
            )[0]["COUNT(*)"]
        ) != 0:
            return apology("Username already exists", 400)
        elif not in_password or not in_confirmation:
            return apology("Password and confirmation required", 400)
        elif in_password != in_confirmation:
            return apology("Password and confirmation don't match", 400)
        elif not is_password_strong(in_password):
            return apology(
                "Password must be 8+ characters long and include one symbol, one capital letter, and one non-capital letter",
                400,
            )
        else:
            define_username(in_username)
            db.execute(
                "INSERT INTO users (username, hash) VALUES (?, ?);",
                username,
                generate_password_hash(in_password),
            )
            session["user_id"] = db.execute(
                "SELECT id FROM users WHERE username = ?;", username
            )[0][
                "id"
            ]  # [{'id': 1}]
            return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # Save user stocks and amounts (> 0) in dict
    rows = db.execute(
        "SELECT company_symbol, SUM(amount) FROM transactions WHERE user_id = ? GROUP BY company_symbol HAVING SUM(amount) > 0;",
        session["user_id"],
    )
    stocks = {}
    for row in rows:
        stocks[row["company_symbol"]] = row[
            "SUM(amount)"
        ]  # Example: {'MSFN': 3, 'MSFT': 3, 'NFLX': 2, 'TSLA': 3}

    # When form is submitted
    if request.method == "POST":
        in_symbol = request.form.get("symbol")

        # Ensure in_symbol exists and is in dict
        if not in_symbol or in_symbol not in stocks:
            return apology("Lacking or invalid symbol", 400)

        # Ensure valid share number, not empty
        try:
            in_shares = int(request.form.get("shares"))
        except:
            return apology("Invalid or missing share number", 400)

        # Ensure in_shares isn't less than 1 or more than available stocks
        if in_shares < 1 or in_shares > stocks[in_symbol]:
            return apology("Invalid number of shares to sell", 400)

        # If user can sell the stocks, update database
        if not in_symbol or lookup(in_symbol) == None:
            return apology("Invalid or missing symbol", 400)
        else:
            # Add cash
            new_cash = (lookup(in_symbol))["price"] * in_shares
            db.execute(
                "UPDATE users SET cash = cash + ? WHERE id = ?",
                new_cash,
                session["user_id"],
            )

            # Add transaction
            db.execute(
                "INSERT INTO transactions(user_id, company_symbol, time_of_purchase, price, amount) VALUES (?, ?, ?, ?, ?)",
                session["user_id"],
                in_symbol,
                datetime.now(),
                (lookup(in_symbol))["price"],
                -in_shares,
            )

            # Redirect to index page
            return redirect("/")

    else:  # Through "GET"
        return render_template("sell.html", stocks=stocks)
