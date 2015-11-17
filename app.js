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

var mongo = require('mongodb');
var client = mongo.MongoClient;
var mongoLink = "mongodb://localhost:27017/idenator"

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

app.get('/createEntries', function(req, res, next){

  client.connect(mongoLink, function(err, db){
    if (!err){
      console.log("Connected");
      console.log(req.query);
      var ids = req.query.ids.split(' ');

      ids.forEach(function(e, i){
        db.collection('entries').insert({
          author : req.query.author,
          isbn : req.query.isbn,
          title : req.query.title,
          print : req.query.print,
          edition : req.query.edition,
          entry : e
        });
      })
      
    } else {
      console.log("Connection failed.");
    }

    db.close();
  });

  res.send({
    res: 'ok'
  })
});

var generateFileId = function(len) {
  var arr = new Uint8Array((len || 40) / 2);
  window.crypto.getRandomValues(arr);
  return [].map.call(arr, function(n) { return n.toString(16); }).join("");
}

app.post('/uploadSheet/', nodefu(), function(req, res, next){

  for ( file in req.files) {
    req.files[file].toFile(path.join(__dirname, 'images/temp_uploaded/'), function(err, uploadedPath){
      if (!err){
        var names = alignator.getIdentifiersOnSheet(uploadedPath);
        
        res.send({res: 'ok', names : names});

      } else {
        console.log(err);
      }
    })
  }
});


app.post('/uploadOriginal/', nodefu(), function(req, res, next){

  var queries =[];
  var fails = [];
  var id;
  for ( file in req.files) {
    req.files[file].toFile(path.join(__dirname, 'images/temp_uploaded/'), function(err, uploadedPath){
      if (!err){
        id = alignator.getWarpedLabelFromPath(uploadedPath, path.join(__dirname, 'images/groundtruths/'));

        if(id.search(/error/) != -1){
          fails.push(path.basename((id.split("|"))[0]));
        } else {
          queries.push(id);
        }

      } else {
        console.log(err);
      }
    })
  }

  client.connect(mongoLink, function(err, db){
    if (!err){

      db.collection('entries')
        .find({"entry": {$in: queries}})
        .toArray(function(err, results){
          console.log(results);
          res.send({res: 'ok', result : results, failed : fails});
        });

    } else {
      console.log("Connection failed.");
    }
  });

});

app.post('/uploadTobeTest/', nodefu(), function(req, res, next){
  req.files.file_data.toFile(path.join(__dirname, 'images/temp_uploaded/'), function(err, uploadedPath){
      if(!err){

        var id = alignator.getWarpedLabelFromPath(uploadedPath, path.join(__dirname, 'images/tests/'));

        if(id.search(/error/) != -1){

          res.send({
            res : 'ok',
            status : "404"
          });            

        } else {

          client.connect(mongoLink, function(err, db){
            if (!err){

              db.collection('entries').findOne({"entry": id}, function(err, doc){
                var score = alignator.match(
                  path.join(__dirname, 'images/tests/') + id + ".png",
                  path.join(__dirname, "images/groundtruths/") + id + ".png",
                  path.join(__dirname, "public/images/"+id+'.png')
                  );

                res.send({
                  res : 'ok',
                  doc : doc,
                  score : score,
                  file : 'images/'+id+'.png'
                });            

              })

            } else {
              console.log("Connection failed.");
            }
          });

        }

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
