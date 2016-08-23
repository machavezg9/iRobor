#try requesting if on and if not on then return not on or if on return on
#but push the question and request the answer.
#need to add code to check for valid signal coming from 0x04
import smbus
import time
# for RPI version 1, use "bus = smbus.SMBus(0)"
bus = smbus.SMBus(1)

# This is the address we setup in the Arduino Program
address = 0x04

#need to figure out the send data code
#place that code below these comments
#def writeNumber(value):
#  bus.write_byte(address, value)
## bus.write_byte_data(address, 0, value) dont use yet
#  return -1

def readNumber():
  number = bus.read_byte(address)
  # number = bus.read_byte_data(address, 1)
  return number

while True:
    if readNumber() == 1:
        print "Yes I am on\n"
        print
    elif readNumber() == 0:
        print "No, I am not on\n"
        print
    # sleep one second
    time.sleep(.05)

#number = readNumber()
#print "Arduino: Hey RPI, I received a digit ", number
#print
#
