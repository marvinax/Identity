var Db = require('./node_modules/mongodb').Db,
    Server = require('mongodb').Server;

module.exports = new Db('wine', new Server('localhost',  1337, {}), {safe: false});