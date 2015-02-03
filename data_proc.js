var fs = require('fs');

data = fs.readFileSync("winedata.txt").toString();
data_to_write = (data.split('\n,\n').map(function(e){
    var obj = {};
    var kvps = e.split(',\n').map(function(e){
        var kvp = e.split(": "); 
        obj[kvp[0]] = kvp[1];
    });
    obj.access = [];
    return obj;
}));
console.log(data_to_write);

var Db = require('./node_modules/mongodb').Db,
    Server = require('mongodb').Server;

var mongoDB = new Db('wine', new Server('localhost',  1337, {}), {safe: false});

mongoDB.open(function(err, db){
    if(err){
        return callback(err);
    }
    
    db.collection('wine', function(err, collection){
        if(err){
            mongoDB.close();
            console.log(err);
        }
        // Insert the new user profile into the collection
        collection.insert(data_to_write, {safe: true}, function(err, user){
            mongoDB.close();
        });
    });
});
