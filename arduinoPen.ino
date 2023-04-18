/* Get all possible data from MPU6050
 * Accelerometer values are given as multiple of the gravity [1g = 9.81 m/s²]
 * Gyro values are given in deg/s
 * Angles are given in degrees
 * Note that X and Y are tilt angles and not pitch/roll.
 *
 * License: MIT
 */

#include <Wire.h>
#include <ESP8266WiFi.h>
#include <MPU6050_light.h>
#include "ArduinoOSCWiFi.h"

const char* ssid = "Supreme-2.4";
const char* pwd = "thomas03";
const IPAddress ip(10, 1, 10, 201);
const IPAddress gateway(10, 1, 10, 1);
const IPAddress subnet(255, 255, 255, 0);

// for ArduinoOSC
const char* host = "10.1.10.20";
const int publish_port = 54445;

MPU6050 mpu(Wire);

void setup() {
  Serial.begin(115200);
  Wire.begin(4, 5);
  
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status!=0){ } // stop everything if could not connect to MPU6050
  
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  mpu.calcOffsets(true,true); // gyro and accelero
  Serial.println("Done!\n");
  
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, pwd);
  WiFi.config(ip, gateway, subnet);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.print("WiFi connected, IP = ");
  Serial.println(WiFi.localIP());
}

void loop() {
  mpu.update();
  float x = mpu.getAngleX();
  float y = mpu.getAngleY();
  float z = mpu.getAngleZ();
  float accX = mpu.getAccAngleX();
  float accY = mpu.getAccAngleY();
  float gyroX = mpu.getGyroX();
  float gyroY = mpu.getGyroY();
  float gyroZ = mpu.getGyroZ();
  
  // Send data via OSC
  OscWiFi.update();
  OscWiFi.publish(host, publish_port, "/data", x, y, z, accX, accY, gyroX, gyroY, gyroZ);
  
  delay(10);
}
