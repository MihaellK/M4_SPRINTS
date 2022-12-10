var express = require("express");
var app = express();
var bodyParser = require("body-parser");
var port = process.env.PORT || 3000;
const { json } = require("express/lib/response");
const sqlite3 = require('sqlite3').verbose();
const DBPATH = 'db.db';
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));

app.use(express.static("./"));

app.get("/get", function (req, res) {
    res.header("Access-Control-Allow-Origin", "*");
    res.send("Get Aqui");
});




app.listen(port, () => {
    console.log(`Server running at: http://localhost:${port}/`);
});













/* Definição dos endpoints */

/******** CRUD ************/

// app.use(express.json());


//Get

//The url we want is: 'www.random.org/integers/?num=1&min=1&max=10&col=1&base=10&format=plain&rnd=new'
// var options = {
//   host: 'www.random.org',
//   path: '/integers/?num=1&min=1&max=10&col=1&base=10&format=plain&rnd=new'
// };

// callback = function(response) {
//   var str = '';

//   //another chunk of data has been received, so append it to `str`
//   response.on('data', function (chunk) {
//     str += chunk;
//   });

//   //the whole response has been received, so we just print it out here
//   response.on('end', function () {
//     console.log(str);
//   });
// }

// http.request(options, callback).end();


//Post 


// //The url we want is `www.nodejitsu.com:1337/`
// var options = {
//   host: 'www.nodejitsu.com',
//   path: '/',
//   //since we are listening on a custom port, we need to specify it by hand
//   port: '1337',
//   //This is what changes the request to a POST request
//   method: 'POST'
// };

// callback = function(response) {
//   var str = ''
//   response.on('data', function (chunk) {
//     str += chunk;
//   });

//   response.on('end', function () {
//     console.log(str);
//   });
// }

// var req = http.request(options, callback);
// //This is the data we are posting, it needs to be a string or a buffer
// req.write("hello world!");
// req.end();


// app.listen(port, hostname, () => {
//     console.log(`Page server running at http://${hostname}:${port}/`);
//   });

