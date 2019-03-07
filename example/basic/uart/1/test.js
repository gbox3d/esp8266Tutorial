/**
 * Created by gbox3d on 15. 7. 20..
 */
//
// var serialport = require("serialport");
//
// //ls /dev | grep usb
// var serialPort = new serialport(
//   // "/dev/tty.usbserial",
//   "/dev/tty.wchusbserial1460",
//   {
//       baudRate: 115200
//       //parser: serialport.parsers.readline("\r\n") //개행문자기준으로 마샬링해주기
//   }
// );
//
// serialPort.on("open", function () {
//     console.log('open at baudrate :' + baudrate);
//
//     // setInterval(function() {
//     //     console.log('send data');
//     //     var buf = Buffer([0x01,0x02,0x03,0x8,0x81]);
//     //     serialPort.write(buf);
//     //     console.log(buf);
//     //
//     // },3000);
//
// });
//
// //데이터 읽기
// serialPort.on('data', function(data) {
//
//     console.log('rev data :');
//     console.log(data );
// });

const SerialPort = require('serialport')
const port = new SerialPort("/dev/tty.wchusbserial1460", {
    baudRate: 115200
})

port.on("open", function () {
    console.log('open  port')

    setTimeout( ()=> {
        port.write(`{"c":"cs"}\r\n`)

    },3000)

});


port.on('data', function(data) {

    console.log('rev data :');
    console.log( data.toString() );
});
