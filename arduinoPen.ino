#include <Wire.h>
#include "YourGyroscopeLibrary.h"

YourGyroscopeClass gyro;

void setup() {
  Serial.begin(115200);
  Wire.begin();

  if (!gyro.begin()) {
    Serial.println("Failed to initialize gyroscope!");
    while (1);
  }

  // Set gyroscope settings (e.g., range, bandwidth, etc.)
}

void loop() {
  gyro.read(); // Read gyroscope data

  float ax = gyro.getAccelX_mss(); // Acceleration in X-axis (m/s^2)
  float ay = gyro.getAccelY_mss(); // Acceleration in Y-axis (m/s^2)
  float az = gyro.getAccelZ_mss(); // Acceleration in Z-axis (m/s^2)

  float gx = gyro.getGyroX_rad();  // Angular velocity in X-axis (rad/s)
  float gy = gyro.getGyroY_rad();  // Angular velocity in Y-axis (rad/s)
  float gz = gyro.getGyroZ_rad();  // Angular velocity in Z-axis (rad/s)

  float mx = gyro.getMagX_uT();    // Magnetic field strength in X-axis (microteslas)
  float my = gyro.getMagY_uT();    // Magnetic field strength in Y-axis (microteslas)
  float mz = gyro.getMagZ_uT();    // Magnetic field strength in Z-axis (microteslas)

  // Perform calculations to determine the position, orientation, or motion of the finger using the sensor data.
  // You can use sensor fusion algorithms like Madgwick or Mahony to estimate the orientation (roll, pitch, yaw) of the finger.

  // Print the results to the Serial Monitor
  Serial.print("Accel (m/s^2): ");
  Serial.print(ax); Serial.print(", ");
  Serial.print(ay); Serial.print(", ");
  Serial.println(az);

  Serial.print("Gyro (rad/s): ");
  Serial.print(gx); Serial.print(", ");
  Serial.print(gy); Serial.print(", ");
  Serial.println(gz);

  Serial.print("Mag (uT): ");
  Serial.print(mx); Serial.print(", ");
  Serial.print(my); Serial.print(", ");
  Serial.println(mz);

  Serial.println();

  delay(100);
}
