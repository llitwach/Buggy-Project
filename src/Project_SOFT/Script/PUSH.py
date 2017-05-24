
import time
import RPi.GPIO as GPIO
import httplib, urllib
import os
import serial

# Check if Arduino is connected
connected = False
# Define the port for the Arduino
Arduino = serial.Serial('/dev/ttyACM0',57600, timeout=.1)

# setup GPIO using Broadcom SOC channel numbering
GPIO.setmode(GPIO.BCM)

# define the GPIO port you will use for the motion detector
PIR_SENSOR = 7 



# number of seconds to delay between alarms
DELAY = 10

# set to pull-up (normally closed position for a PIR sensor dry contact)
GPIO.setup(PIR_SENSOR, GPIO.IN, pull_up_down=GPIO.PUD_UP)




# Pushover API setup
PUSH_TOKEN = "a5ngxxdhyfdz628ccdtzsgkxih68ez" # API Token/Key
PUSH_USER = "utsy974qmfxm54cstwv9aj4sj28p99" # Your User Key
PUSH_MSG = "Motion detected!" # Push Message you want sent

# This function sends the push message using Pushover.
# Pass in the message that you want sent
def sendPush( msg ):
        conn = httplib.HTTPSConnection("api.pushover.net:443")
        conn.request("POST", "/1/messages.json",
                urllib.urlencode({
                        "token": PUSH_TOKEN,
                        "user": PUSH_USER,
                        "message": msg,
                }), { "Content-type": "application/x-www-form-urlencoded" })

        conn.getresponse()
        return

try:    # loop here until Arduino is connected
        while not connected:
                serin = Arduino.read()
                connected = True
        # setup an indefinite loop that looks for the PIR sensor to be triggered
        while True:
                # motion is detected
                GPIO.wait_for_edge(PIR_SENSOR, GPIO.RISING)

               
                
                # webcam take the picture       
                os.system('fswebcam -r 320x240 -S 3 --jpeg 50 --save /home/pi/www/html/Image/%H%M%S.jpg')
                print('PIC CAPTURED')

                # Send '1' to Arduino
                Arduino.write("1")
                
                # print and push message
                print(PUSH_MSG)
                sendPush(PUSH_MSG)

                # do you want a time delay in between alarms?
                time.sleep(DELAY)
                

except KeyboardInterrupt:
        # cleanup GPIOs on keyboard exit
        GPIO.cleanup()

# cleanup GPIOs when program exits
GPIO.cleanup()
