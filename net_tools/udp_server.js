//node udp_sender.js --ip=localhost --port=6009 --content read-config
const dgram = require("dgram");
const server = dgram.createSocket("udp4");
const yargs = require('yargs').argv;

let localPort = yargs.port

server.on("message", function (msg, rinfo) {

    // remote_client = rinfo;

    console.log(rinfo);

    let header = msg.readInt32LE(0)

    // console.log("header : " + header )
    console.log(`header ${header} , length ${msg.length}`)

    if (header == 99) {
        console.log(`header : ${header} `);
        console.log(`code : ${msg.readUInt8(4)} `);
        console.log(`m_index : ${msg.readInt16LE(6)} `);
        console.log(`m_iSensorData : ${msg.readFloatLE(8)} `);

        let resBuf = Buffer.alloc(10)
        resBuf.writeUInt32LE(77, 0);
        
        resBuf.writeUInt8(49, 4);
        resBuf.writeUInt8(36, 5); //m_status

        resBuf.writeUInt16LE(18, 6); //m_extra
        resBuf.writeInt16LE(516, 8)

        console.log(` ${rinfo.address}:${rinfo.port}`  )
        console.log(resBuf)

        server.send(
            resBuf, 0, 10,
            rinfo.port, rinfo.address); // added missing bracket
    }
    else {
        
        let message = new Buffer.from(`ok : ${msg}`);
        server.send(message, 0, message.length, rinfo.port, rinfo.address)

        console.log(msg.toString());
    }




});

server.bind(localPort)

console.log(`server bind at : ${localPort}`)
