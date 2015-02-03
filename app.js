var express = require('express');
var path = require('path');
var favicon = require('static-favicon');
var logger = require('morgan');
var cookieParser = require('cookie-parser');
var bodyParser = require('body-parser');

var MongoDB = require('./db');

var routes = require('./routes/index');
var users = require('./routes/users');

var app = express();

// view engine setup
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'jade');

app.use(favicon());
app.use(logger('dev'));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded());
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/', routes);
app.use('/users', users);

app.get('/editor', function(req,res){
    res.render('editor');
});

app.get('/wine', function(req, res){
    console.log(req.query);
    var pages = parseInt(req.query.page),
        range = parseInt(req.query.range);
    if(req.query.page){
        MongoDB.open(function(err, db){
            if(err){
                res.send(err);
                return;
            }
            // Fetches the users collection
            db.collection('wine', function(err, collection){
                if(err){
                    console.log(err);
                    MongoDB.close();
                    res.send(err);
                    return;
                }
                // Insert the new user profile into the collection
                collection.find().skip((pages -1) * range).limit(range).toArray(function(err, result){
                    err && res.send(err);
                    res.render('catalog', {data: result});
                    MongoDB.close();
                });
            });
        });
    }
})

/// catch 404 and forward to error handler
app.use(function(req, res, next) {
    var err = new Error('Not Found');
    err.status = 404;
    next(err);
});

/// error handlers

// development error handler
// will print stacktrace
if (app.get('env') === 'development') {
    app.use(function(err, req, res, next) {
        res.status(err.status || 500);
        res.render('error', {
            message: err.message,
            error: err
        });
    });
}

// production error handler
// no stacktraces leaked to user
app.use(function(err, req, res, next) {
    res.status(err.status || 500);
    res.render('error', {
        message: err.message,
        error: {}
    });
});


module.exports = app;
