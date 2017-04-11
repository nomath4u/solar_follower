import argparse
import serial
import matplotlib.pyplot as plt
import signal
import sys
import time

s = 0
x = []
y = []
#ser = serial.Serial('/dev/tty.usbserial', 9600)

def sig_int_handler(signum, frame):
    #global s
    #plt.plot(x,y, 'ro')
    #plt.show()
    s = s + 1
#    sys.exit(0)
def tilt_range(device):
    print """Make sure the tilt_range sketch has been loaded to your arduino.
 press enter to continue when you have done so."""
    input("Press Enter to continue...")

    print """In this step we are going to be finding the ranges that we want
to calibrate the servo to move. The max and min values that are gotten will be
displayed. To move on press Ctrl+C. Make sure that you move the servo as far as
it can go in both directions because the arduino sketch takes a safety buffer 
out for you"""
    ser = serial.Serial(device) #TODO: put the arg parse thing in here
    minimum = 0
    maximum = 0
    while s == 0:
    	val = ser.readline();
	minimum = min(minimum, val)
	maximum = max(maximum, val)
	sys.stdout.write("\rMax: %d Min:%d" % (maximum, minimum))
	sys.stdout.flush()

    print """ Your values are displayed below. Please enter them into the main
    arduino sketch for proper functioning"""
    print "MAX: ", maximum
    print "MIN: ", minimum

def calibration_stage():
    i = 0
    while s == 0:
        #split =  ser.readline().split(':');
        #x.append(split[0])
        #y.append(split[1])
        y.append(i)
        x.append(i)
        i = i + 1
        sys.stdout.write("\rNum: %d State: %d" % (i,  s))
        sys.stdout.flush()
        time.sleep(1)
def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("serial_port", help="Path to the serial device for your arduino")
    args = parser.parse_args()
    return args

def main():
    args = parse_args()
    signal.signal(signal.SIGINT, sig_int_handler)
    tilt_range(args.serial) 
#	calibration_stage():
if __name__ == '__main__':
	main()
	sys.exit(0)
