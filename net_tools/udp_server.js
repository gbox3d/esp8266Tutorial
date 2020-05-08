const dgram = require( "dgram" );
const server = dgram.createSocket( "udp4" );
const yargs = require('yargs').argv;

const localPort = yargs.port

server.on( "message", function( msg, rinfo ) {

    // remote_client = rinfo;

    console.log(rinfo);
    console.log(msg);

    let message = new Buffer.from(`ok : ${msg}`);

    server.send(message,0,message.length,rinfo.port,rinfo.address)

    // console.log(`header : ${msg.readUInt8(0) } `);
    // console.log(`ceode : ${msg.readUInt8(1) } `);
    // console.log(`m_index : ${msg.readInt16LE(4) } `);
    // console.log(`m_iSensorData : ${msg.readFloatLE(8) } `);

    // let resBuf = Buffer.alloc(8)
    // resBuf.writeUInt8(77,0);
    // resBuf.writeUInt8(49,1); 
    // resBuf.writeUInt8(36,2); //m_status
    // resBuf.writeUInt8(18,3); //m_extra

    // resBuf.writeInt16LE(516,4)

    // console.log(resBuf)

    // server.send(
    //     resBuf, 0, 8,
    //     rinfo.port, rinfo.address ); // added missing bracket
});

server.bind(localPort)

console.log(`server bind at : ${localPort}`)
