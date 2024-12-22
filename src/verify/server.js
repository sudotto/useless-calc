const express = require('express');
const fs = require('fs');
const url = require('url');
const bodyParser = require('body-parser');

const app = express();

var code = null;

app.use(bodyParser.urlencoded({ extended: true }));

app.get("/", (req, res) => {
	fs.readFile("verify/index.html", "utf8", (err, data) => {
		res.send(data);
	});
	var q = url.parse(req.url, true).query;
	code = q.c;
});

server = app.listen(7777, () => {});

app.post("/submit", (req, res) => {
	const input = req.body.input_box;
	if(input == code){
		res.send("<script>alert('all set! you can continue using the calculator now')</script>");
		console.log(0);
	} 
	if(input != code){
		res.send("<script>alert('incorrect! killing server for maximum annoyance...')</script>");
		console.log(1);
	}
	server.close();
});
