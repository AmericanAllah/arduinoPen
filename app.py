import socket
import struct
import pyautogui
from pythonosc import dispatcher
from pythonosc import osc_server
import argparse


# Set up the socket connection
HOST = '0.0.0.0'  # IP address of the MPU6050 sensor
PORT = 5444  # Port number used by ArduinoOSC
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((HOST, PORT))

# Define the range of motion for the mouse
SCREEN_WIDTH, SCREEN_HEIGHT = pyautogui.size()

# Define the sensitivity of the mouse movement
SENSITIVITY_X = .5
SENSITIVITY_Y = .5

# Define the previous acceleration and gyro values
prev_accX = 0
prev_accY = 0
prev_gyroX = 0
prev_gyroY = 0
prev_gyroZ = 0


def data_handler(unused_addr, dx, dy, dz, dAccX, dAccY, dGyroX, dGyroY, dGyroZ):
    global prev_accX, prev_accY, prev_gyroX, prev_gyroY, prev_gyroZ
    
    # Calculate the new position of the mouse based on the change in acceleration and gyro values
    new_x = pyautogui.position().x + (dAccX + dGyroY - prev_accX - prev_gyroY) * SENSITIVITY_X
    new_y = pyautogui.position().y + (dAccY + dGyroX - prev_accY - prev_gyroX) * SENSITIVITY_Y

    # Clamp the mouse position to the screen boundaries
    new_x = min(max(new_x, 0), SCREEN_WIDTH)
    new_y = min(max(new_y, 0), SCREEN_HEIGHT)

    # Update the previous acceleration and gyro values
    prev_accX += dAccX
    prev_accY += dAccY
    prev_gyroX += dGyroX
    prev_gyroY += dGyroY
    prev_gyroZ += dGyroZ
    
    # Move the mouse to the new position
    pyautogui.moveTo(new_x, new_y, duration=0)


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--ip", default="0.0.0.0", help="The IP to listen on")
    parser.add_argument("--port", type=int, default=54445, help="The port to listen on")
    args = parser.parse_args()

    disp = dispatcher.Dispatcher()
    #disp.map("/quat", quat_handler)
    #disp.map("/euler", euler_handler)
    disp.map("/data", data_handler)

    server = osc_server.ThreadingOSCUDPServer((args.ip, args.port), disp)
    print(f"Serving on {server.server_address}")

    try:
        server.serve_forever()
    except KeyboardInterrupt:
        server.server_close()
