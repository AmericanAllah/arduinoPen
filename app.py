import serial
import pyautogui
import time

def process_data(data):
    # Process the data received from the Arduino
    # You can implement your sensor fusion algorithm here and calculate cursor position
    ax, ay, az, gx, gy, gz, mx, my, mz = map(float, data.split(','))
    
    # Calculate the cursor position based on sensor data (e.g., using the gyroscope)
    cursor_x = int(gx * 100)
    cursor_y = int(gy * 100)
    
    return cursor_x, cursor_y

def main():
    # Set up the serial connection with the Arduino
    ser = serial.Serial('COM_PORT', 115200)
    time.sleep(2)

    # Set the drawing flag
    drawing = False

    while True:
        if ser.inWaiting():
            data = ser.readline().decode().strip()
            cursor_x, cursor_y = process_data(data)
            
            # If drawing is enabled, move the cursor and perform the drawing action
            if drawing:
                pyautogui.move(cursor_x, cursor_y, duration=0.1)
                # Add any other actions for drawing (e.g., mouse clicks) using pyautogui library

            # If drawing is not enabled, just move the cursor
            else:
                pyautogui.move(cursor_x, cursor_y, duration=0.1)

            # Update the drawing flag based on specific conditions (e.g., a button press or a gesture)
            # drawing = True or False

if __name__ == "__main__":
    main()
