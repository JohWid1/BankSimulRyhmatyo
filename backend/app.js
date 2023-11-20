var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');

var indexRouter = require('./routes/index');
var customerRouter = require('./routes/customer');
var card_has_accountRouter = require('./routes/card_has_account');
var accountRouter = require('./routes/account');
var cardRouter = require('./routes/card');
var transactionRouter = require('./routes/transaction');
var loginRouter = require('./routes/login');

var app = express();

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/', indexRouter);
app.use('/customer', customerRouter);
app.use('/account', accountRouter);
app.use('/card', cardRouter);
app.use ('/transaction', transactionRouter);
app.use('/card_has_account', card_has_accountRouter);
app.use('/login', loginRouter);

module.exports = app;
