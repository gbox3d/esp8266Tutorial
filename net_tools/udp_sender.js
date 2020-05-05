
var dgram = require( "dgram" );

var client = dgram.createSocket( "udp4" );

client.on( "message", function( msg, rinfo ) {
    console.log( "The packet came back" );
    console.log(msg.toString());
    console.log(rinfo)
});

// client listens on a port as well in order to receive ping
client.bind(); //포트를 특정하지 않으면 모든 포트의 데이터를 받는다.

var message = new Buffer.from( "hello udp!" );
client.send(
    message, 0,
    message.length,
    4210,"192.168.4.14" );

console.log('send data');