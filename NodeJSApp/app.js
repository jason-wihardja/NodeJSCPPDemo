var express = require('express');
var bodyParser = require('body-parser');
var morgan = require('morgan');
var chalk = require('chalk');
var path = require('path');

// EXPRESS
var app = express();

// APP CONFIGURATION
if (app.get('env') === 'development') {
    morgan.token('pid', function (request, response) { return process.pid; });
    app.use(morgan(function (tokens, request, response) {
        var logString = tokens['method'](request, response) + ' ' + tokens['url'](request, response) + ' ';
        
        if (response.statusCode >= 500) logString += chalk.red(tokens['status'](request, response));
        else if (response.statusCode >= 400) logString += chalk.yellow(tokens['status'](request, response));
        else if (response.statusCode >= 300) logString += chalk.cyan(tokens['status'](request, response));
        else logString += chalk.green(tokens['status'](request, response));
        
        logString += ' ' + tokens['response-time'](request, response) + ' ms - PID: ' + tokens['pid'](request, response);
        
        return logString;
    }));
}
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: false }));

app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'jade');
app.use(express.static(path.join(__dirname)));

// ROUTES
app.get('/', function (request, response, next) {
    response.render('IndexView', {
        title: "Express",
        content1: "Welcome to Express!"
    });
});

app.use('/api', require('./routes/api')(express));

// 404 NOT FOUND
app.use(function (request, response, next) {
    var error = new Error('Not Found');
    error.status = 404;
    next(error);
});

// 500 SERVER ERROR
if (app.get('env') === 'development') {
    // Development error handler (will print stacktrace)
    app.use(function (error, request, response, next) {
        response.status(error.status || 500);
        response.render('ErrorView', {
            message: error.message,
            error: error
        });
    });
} else {
    // Production error handler (no stacktraces leaked to user)
    app.use(function (error, request, response, next) {
        response.status(error.status || 500);
        response.render('ErrorView', {
            message: error.message,
            error: {}
        });
    });
}

// CREATE SERVER
var server = app.listen(3000, function () {
    var host = server.address().address;
    var port = server.address().port;
    console.log("Server listening at http://%s:%s", host, port);
});