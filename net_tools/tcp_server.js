const net = require('net');
const yargs = require('yargs').argv;

//현제 할당받은 주소를 써준다..
//var HOST = '192.168.0.7';
var PORT = yargs.port;

// Create a server instance, and chain the listen function to it
// The function passed to net.createServer() becomes the event handler for the 'connection' event
// The sock object the callback function receives UNIQUE for each connection
net.createServer(function(socket) {

    // We have a connection - a socket object is assigned to the connection automatically
    console.log('CONNECTED: ' + socket.remoteAddress +':'+ socket.remotePort);

    // Add a 'data' event handler to this instance of socket
    socket.on('data', function(data) {

        console.log('DATA ' + socket.remoteAddress + ': ' + data);
        console.log(data);
        // Write the data back to the socket, the client will receive it as data from the server
        socket.write('You said "' + data + '"' + "\n");

    });

    // Add a 'close' event handler to this instance of socket
    socket.on('close', function(data) {
        console.log('CLOSED: ');
        //console.log(JSON.stringify(socket.getConnection()));
    });

}).listen(PORT);

//console.log('Server listening on ' + HOST +':'+ PORT);
console.log('Server listening on ' + ':'+ PORT);