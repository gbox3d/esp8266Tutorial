//node udp_sender.js --ip=192.168.4.2 --port 2012 --content
var dgram = require( "dgram" );
const yargs = require('yargs').argv;

var client = dgram.createSocket( "udp4" );

client.on( "message", function( msg, rinfo ) {
    console.log(rinfo)
    console.log( "The packet came back" );
    console.log(msg.toString());

    client.close()
});

// client listens on a port as well in order to receive ping
client.bind(); //포트를 특정하지 않으면 모든 포트의 데이터를 받는다.

var message = new Buffer.from( yargs.content );
client.send(
    message, 0,
    message.length,
    yargs.port,yargs.ip);

console.log('send data');