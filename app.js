var express = require('express');

var fs = require('fs');
var path = require('path');
var nodefu  = require('nodefu');

var bindings = require('bindings');
var alignator = bindings('alignator');

var favicon = require('serve-favicon');
var logger = require('morgan');
var cookieParser = require('cookie-parser');
var bodyParser = require('body-parser');

var routes = require('./routes/index');
var users = require('./routes/users');

var app = express();

// view engine setup
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'jade');

// uncomment after placing your favicon in /public
//app.use(favicon(__dirname + '/public/favicon.ico'));
app.use(logger('dev'));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/', routes);
app.use('/users', users);

app.post('/uploadOriginal/', nodefu(), function(req, res, next){
  req.files.file_data.toFile(path.join(__dirname, 'images/groundtruths/'),
    function(err, uploadedPath){
      if(!err){
        alignator.getWarpedLabelFromPath(uploadedPath, uploadedPath);

        res.send({
          res: 'ok'
        })
      }
  })
});

app.post('/uploadTobeTest/', nodefu(), function(req, res, next){
  req.files.file_data.toFile(path.join(__dirname, 'public/images/'),
    function(err, uploadedPath){
      if(!err){
        alignator.getWarpedLabelFromPath(uploadedPath, uploadedPath);

        var max_score = 0,
        max_id;        
        fs.readdirSync("./images/scanned transformed").forEach(function(im){
          var score = alignator.match(
            uploadedPath,
            path.join(__dirname, "images/scanned transformed/")+im,
            path.join(__dirname, "public/images/"+im.split('.')[0]+'.jpg')
            );
          if (score >= max_score){
            max_score = score;
            max_id = im.split('.')[0];
          }
        });

        res.send({
          res : 'ok',
          score : max_score,
          file : path.basename(max_id+'.jpg')
        });            
      }
    })
});


// catch 404 and forward to error handler
app.use(function(req, res, next) {
  var err = new Error('Not Found');
  err.status = 404;
  next(err);
});

// error handlers

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
