import serial
import argparse
import time

ap = argparse.ArgumentParser()
ap.add_argument("-p", "--port", required=True, help="device port")
ap.add_argument("-i", "--inputfile", required=True, help="input file")

args = vars(ap.parse_args())

ser = serial.Serial(port=args['port'],baudrate=115200)

ser.write(b'<save>\n')
ser.flush()
# time.sleep(.5)

print(ser.readline())
# time.sleep(.5)

ser.write(b'config.json\n')
ser.flush()
# time.sleep(.5)

print(ser.readline())
# time.sleep(.5)

# ser.write(b'config.json\n')
# ser.flush()
# time.sleep(.5)


fd = open(args['inputfile'],"r")
data = fd.read()
# print(data)
fd.close()
#time.sleep(.5)

ser.write( data.encode())
# ser.write(b'\n')
ser.flush()
time.sleep(.5)

print(ser.readline())
# time.sleep(.5)

ser.close()

print('done.');