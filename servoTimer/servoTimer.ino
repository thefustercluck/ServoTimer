#include <ESP32Servo.h>
#include <esp_wifi.h>
#include <WiFi.h>
#include <time.h>
#include <ESP32Time.h>

ESP32Time rtc(0);

const char *ssid = "SSID HERE";
const char *password = "PASS HERE";
const char *ntpServer1 = "pool.ntp.org";
const char *ntpServer2 = "time.nist.gov";
boolean timeinterval= false;
Servo myServo;

// short pos= 0;
// short angle = Serial.parseInt(); // Read the angle from the serial monitor

const long  gmtOffset_sec = -18000;
const int   daylightOffset_sec = 3600;

void initWifi()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.print("Connecting..");
    while (WiFi.status() != WL_CONNECTED)
    {
      Serial.print('.');
      delay(1000);
    }
  Serial.println(WiFi.localIP());
}


void setup() 
{
    Serial.begin(115200);
    myServo.attach(22); // Attach the servo to pin 1 (TX)
    initWifi();
    delay(1000);
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer1);    
}

void loop() 
{
    delay(2000);
    struct tm timeinfo = rtc.getTimeStruct();
    short hour = timeinfo.tm_hour;
    short minute = timeinfo.tm_min;
    
    if (hour == 7 && minute == 45 && timeinterval==false)
      {
        myServo.write(40);
        delay(2000);
        myServo.write(0);
        timeinterval=true;
      }
    else
      {
        myServo.write(0);
        delay(60000);
        timeinterval=false;
      }
      //for debugging
    // if (Serial.available() > 0) 
    // {
    //     int angle = Serial.parseInt(); // Read the angle from the serial monitor
    //     if (angle >= 0 && angle <= 180) {
    //         myServo.write(angle); // Set the servo to the specified angle
    //         Serial.print("Servo angle set to: ");
    //         Serial.println(angle);
    //     } else {
    //         Serial.println("Invalid angle. Please enter a value between 0 and 180.");
    //     }
    // }
}
