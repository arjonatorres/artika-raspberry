import serial
import time
import sys

arduino=serial.Serial('/dev/ttyUSB0',baudrate=9600, timeout = 3.0)

arduino.write(sys.argv[1])
txt = ''
time.sleep(0.1)
while arduino.inWaiting() > 0:
            txt += arduino.read(1)
sys.stdout.write(txt)
sys.stdout.flush()

arduino.close()
