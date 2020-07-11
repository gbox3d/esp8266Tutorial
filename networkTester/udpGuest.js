
// usage ex) : node udpGuest.js 2390 localhost

const dgram = require( "dgram" );
const udp_socket = dgram.createSocket( "udp4" );

_port = process.argv[2]
_ip = process.argv[3]

udp_socket.on( "message", function( msg, rinfo ) {

    console.log( rinfo.address + ':' + rinfo.port + ' - ' + msg );
});


function _loop()
{
    console.log('send udp')
    udp_socket.send( Buffer('hello'), 0, 6, _port,_ip ); // added missing bracket

    setTimeout(_loop,1000)
}

_loop()
