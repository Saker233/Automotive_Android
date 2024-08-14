
import RPi.GPIO as GPIO
import subprocess
import time

# Define GPIO pins
LED_RED_PIN = 2
LED_GREEN_PIN = 3

# Setup GPIO
GPIO.setmode(GPIO.BCM)
GPIO.setup(LED_RED_PIN, GPIO.OUT)
GPIO.setup(LED_GREEN_PIN, GPIO.OUT)

# Get the IP address from user input
IP_ADDRESS = input("Enter the IP address to ping: ")

def ping(ip):
    try:
        # Run the ping command
        output = subprocess.run(['ping', '-c', '1', ip], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        if output.returncode == 0:
            return True
        else:
            return False
    except Exception as e:
        print(f"An error occurred: {e}")
        return False

def control_leds(success):
    if success:
        GPIO.output(LED_GREEN_PIN, GPIO.HIGH)
        GPIO.output(LED_RED_PIN, GPIO.LOW)
    else:
        GPIO.output(LED_GREEN_PIN, GPIO.LOW)
        GPIO.output(LED_RED_PIN, GPIO.HIGH)

try:
    while True:
        success = ping(IP_ADDRESS)
        control_leds(success)
        time.sleep(10)  # Wait for 10 seconds before the next ping
except KeyboardInterrupt:
    print("Script terminated by user.")
finally:
    GPIO.cleanup()

