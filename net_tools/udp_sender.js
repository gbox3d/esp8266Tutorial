//node udp_sender.js --ip=192.168.4.2 --port 2012 --content
//node udp_sender.js --ip=192.168.4.2 --port=6009 --content read-config
var dgram = require("dgram");
const yargs = require('yargs').argv;

var client = dgram.createSocket("udp4");

client.on("message", function (msg, rinfo) {
    console.log(rinfo)
    console.log("The packet came back");
    console.log(msg);

    let _header = msg.readInt32LE(0) 
    let _code = msg.readUInt8(8)
    
    if (_code === 0x21 && _header == 20200519)  
    {
        let _headerSize = 16
        console.log( msg.slice(_headerSize, msg.length).toString('utf-8') )
    }
    

    client.close()
});

// client listens on a port as well in order to receive ping
client.bind(); //포트를 특정하지 않으면 모든 포트의 데이터를 받는다.

_ip = yargs.ip
_port = yargs.port
console.log(yargs.content)

if (yargs.content === 'read-config') {
    let resBuf = Buffer.alloc(8)
    resBuf.writeInt32LE(20200519, 0);
    resBuf.writeUInt8(0x21, 4);
    resBuf.writeUInt8(0x1, 5); // 1 이면 요청한주소로 응답요청 ,0 이면 지정된 원격서버로 전달
    resBuf.writeUInt8(0x0, 6);

    console.log(`send : ${_ip}, ${_port}`)
    console.log(resBuf)
    client.send(resBuf, 0, resBuf.length, _port, _ip)
}
else {
    var message = new Buffer.from(yargs.content);
    console.log(`send : ${_ip}, ${_port}`)
    client.send(
        message, 0,
        message.length,
        _port,_ip);
}
