import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Ensure environment variable is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    return apology("Show Portfolio of Stocks")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide symbol", 403)

        # Ensure number of shares was submitted
        if not request.form.get("shares"):
            return apology("must provide number of shares you want to buy", 403)

        # Ensure number of shares is a positive integer
        if not request.form.get("shares"):
            return apology("must provide positive number of shares you want to buy", 403)

        # look up a stock’s current price
        quote = lookup(symbol)
        # lookup returns dict with dict with three keys:
        # !! deprecated specs!! name no longer returned by lookup function!!! #
        # price, whose value is a float;
        # symbol, whose value is a str, a uppercase version of a stock’s symbol
        price = usd(quote['price'])
        symbol = quote['symbol']

        # SELECT how much cash the user currently has in users

        # Query database for current cash of user
        rows = db.execute("SELECT cash FROM users WHERE id = 1")

        # Is cash less than price * shares?
            # Error message

        # Is cash more than price * shares?
            # Add shares of symbol to portfolio

        # Portfolio
        # Add one or more new tables to finance.db via which to keep track of the purchase.
        # Store enough information so that you know who bought what at what price and when.
        # Use appropriate SQLite types.
        # Define UNIQUE indexes on any fields that should be unique.
        # Define (non-UNIQUE) indexes on any fields via which you will search (as via SELECT with WHERE).


     # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


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
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
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
#@login_required
def quote():
    """Get stock quote."""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide symbol", 403)

        # Lookup symbol
        symbol = request.form.get("symbol")
        quote = lookup(symbol)
        # lookup returns dict with dict with three keys:
        # !! deprecated specs!! name no longer returned by lookup function!!! #
        # price, whose value is a float;
        # symbol, whose value is a str, a uppercase version of a stock’s symbol
        price = usd(quote['price'])
        symbol = quote['symbol']

        return render_template("quoted.html", price = price, symbol = symbol) # template embedding within it one or more values from lookup.

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")


@app.route("/quoted", methods=["GET", "POST"])
#@login_required
def quoted():
    """Display stock quote."""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        return render_template("quoted.html", price = price, symbol = symbol)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure username is not already taken
        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username does not exist
        if len(rows) == 1:
            return apology("sorry, username already taken", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Ensure password confirmation was submitted
        elif not request.form.get("confirm_password"):
            return apology("must provide password confirmation", 403)

        # Ensure password and confirmation match
        elif not (request.form.get("password")) == (request.form.get("confirm_password")):
            return apology("Password and confirmation didn't match", 403)

        # Encrypt password
        # source given by CS50: http://werkzeug.pocoo.org/docs/0.12/utils/#werkzeug.security.generate_password_hash
        hash = generate_password_hash(request.form.get("password"), method='pbkdf2:sha256', salt_length=8)

        # Query database to INSERT username
        rows = db.execute("INSERT INTO users(username, hash) VALUES(:username, :hash)",
                          username=request.form.get("username"), hash=hash)

        # Remember which user has registered and log them in => Didn't work like this, here! ???
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    return apology("TODO")


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
