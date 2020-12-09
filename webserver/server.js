// server.js
//
// A simple visualisation server for the driag processor visualiser
//
// author: stf


// for accessing server-side files
var http = require('http');
var https = require('https');
var fs = require('fs');

var path = require('path');
var cdir = process.cwd();

const WebSocket = require('ws');

// the express webserver
const express = require('express');
const app = express();

console.log(process.argv);

// The files that the webserver hosts
app.get('/', (req, res) => res.sendFile(path.join(cdir+"/"+process.argv[3])));

var vis_libdir = process.argv[2] + '/';
console.log("Visualisation library: "+vis_libdir);

// All the library include files
app.get('/hdlvis/position.js', (req, res) => res.sendFile(path.join(vis_libdir+'/hdlvis/position.js')));
app.get('/hdlvis/wire.js', (req, res) => res.sendFile(path.join(vis_libdir+'/hdlvis/wire.js')));
app.get('/hdlvis/wireGroup.js', (req, res) => res.sendFile(path.join(vis_libdir+'/hdlvis/wireGroup.js')));
app.get('/hdlvis/ram.js', (req, res) => res.sendFile(path.join(vis_libdir+'/hdlvis/ram.js')));
app.get('/hdlvis/reg.js', (req, res) => res.sendFile(path.join(vis_libdir+'/hdlvis/reg.js')));
app.get('/hdlvis/regN.js', (req, res) => res.sendFile(path.join(vis_libdir+'/hdlvis/regN.js')));
app.get('/hdlvis/regArray.js', (req, res) => res.sendFile(path.join(vis_libdir+'/hdlvis/regArray.js')));
app.get('/hdlvis/regFile.js', (req, res) => res.sendFile(path.join(vis_libdir+'/hdlvis/regFile.js')));
app.get('/hdlvis/twoMux.js', (req, res) => res.sendFile(path.join(vis_libdir+'/hdlvis/twoMux.js')));
app.get('/hdlvis/riscvInst.js', (req, res) => res.sendFile(path.join(vis_libdir+'/hdlvis/riscvInst.js')));
app.get('/hdlvis/programCounter.js', (req, res) => res.sendFile(path.join(vis_libdir+'/hdlvis/programCounter.js')));
app.get('/hdlvis/colourScheme.js', (req, res) => res.sendFile(path.join(vis_libdir+'/hdlvis/colourScheme.js')));
app.get('/hdlvis/onLED.js', (req, res) => res.sendFile(path.join(vis_libdir+'/hdlvis/onLED.js')));
app.get('/hdlvis/bootLED.js', (req, res) => res.sendFile(path.join(vis_libdir+'/hdlvis/bootLED.js')));
app.get('/hdlvis/imem_out.js', (req, res) => res.sendFile(path.join(vis_libdir+'/hdlvis/imem_out.js')));
app.get('/hdlvis/commandParser.js', (req, res) => res.sendFile(path.join(vis_libdir+'/hdlvis/commandParser.js')));
app.get('/clientside_modules/terminaljs/terminal.js', (req, res) => res.sendFile(path.join(vis_libdir+'/clientside_modules/terminaljs/terminal.js')));

var httpServer = http.createServer(app);
httpServer.listen(4000);

// backend websocket server -- the cpp client running in verilator connects here
const be_wss = new WebSocket.Server({port: 1234});

// frontend websocket server -- the visualiser webpage connects here
const fe_wss = new WebSocket.Server({port: 1235});

// current default -- pass all messages from the backend to the frontend
// backend server logic
be_wss.on('connection', function connection(be_ws) {
    console.log('backend connection established');
    be_ws.on('message', function incoming(message) {
        console.log('received BE message %s', message);

        // forward the message onto all frontends
        fe_wss.clients.forEach(function each(client) {
            if(client !== fe_wss && client.readyState == WebSocket.OPEN){
                client.send(message);
            }
        });
    });
});

// Frontend messages to be sent to the simulation
fe_wss.on('connection', function connection(fe_ws) {
    console.log('frontend connection established');
    fe_ws.on('message', function incoming(message) {
        console.log('received FE message %s', message);

        // forward the message onto all frontends
        be_wss.clients.forEach(function each(client) {
            if(client !== be_wss && client.readyState == WebSocket.OPEN){
                client.send(message);
            }
        });
    });
});

console.log("Server is running: http://localhost:4000");
