var local = {
    port : 1471
}

var remote = {
    address : '192.168.9.20',
    port : 1471
}


var dgram = require( "dgram" );
var udp_socket = dgram.createSocket( "udp4" );

//var remote_client;
/*

 udp 는 리스하는 과정이 없다. 연결시작 종료 개념이 없이 바로 데이터 보내고 받는식이다.

 open , close 개념이 없다.

 * */

udp_socket.on( "message", function( msg, rinfo ) {

    console.log( 'remote :' + rinfo.address + ':' + rinfo.port + ' - ' + msg );

    remote.address = rinfo.address;
    //remote.port =  rinfo.port;
    //remote_client = rinfo;
    //udp_socket.send( Buffer([0x02,0x03]), 0,2, rinfo.port, rinfo.address ); // added missing bracket
    //udp_socket.send( Buffer('hello'), 0,5, remote.port ,remote.address); // added missing bracket
});
udp_socket.bind( local.port );

console.log('local : bind udp port :' +  local.port );

////////////------------------//////////////////////
var    repl = require('repl')

var theApp = {
    testMsg : 'hello repl',
    udp_socket : udp_socket
}
theApp.sendTest = function() {
    udp_socket.send( Buffer('hello'), 0,5, remote.port ,remote.address);
}



var repl_context = repl.start({
    prompt: 'Node.js via stdin> ',
    input: process.stdin,
    output: process.stdout
}).context;

//콘텍스트객체 설정
//theApp을 repl에서 볼수있다
repl_context.theApp = theApp;