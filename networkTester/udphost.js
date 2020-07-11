const dgram = require( "dgram" );
const udp_socket = dgram.createSocket( "udp4" );

const port = 33333
udp_socket.on( "message", function( msg, rinfo ) {

    console.log( rinfo.address + ':' + rinfo.port + ' - ' + msg );

    udp_socket.send( Buffer('ok'), 0, 3, rinfo.port,rinfo.address );
    
});
udp_socket.bind( port );


// ////////////////
// //
// process.stdin.resume();
// process.stdin.setEncoding('utf8');
// const util = require('util');

// process.stdin.on('data', function (text) {
//     var strText = text;
//     udp_socket.send( Buffer(text), 0, text.length, remote.port, remote.address ); // added missing bracket

// });

console.log("start p2p(udp) tester at :" + port);