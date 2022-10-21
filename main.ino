/*
  This sketch demonstrates a technique for measuring NDVI (Normalized Difference Vegetation Index).
  It has a red LED (630 nm) with Infra-red (tx, rx) and LDR sensor inputs.

  Minimum and maximum reflectance value of both the sensors attached to the sensor pins
  are also required in the sketch, for calibration purpose.

  These values can be obtained by sampling the most healthy leaf/plant and an unhealthy leaf, use minimum
  and maximum relectane value of Infra-red and Red.
  Initially, the values are set to 1023 & 0 (default), replace those values with the mminimum and maximum value.

  Finally the sensor readings are between 0 to 1, which is then passed into an NDVI expression.

  The circuit:
   Analog sensors (LDR and IR) attached to analog input channel A0  & A1
   RED LED attached from digital pin 10 to ground and IR LED attached from digital pin 9 to ground.

  created on Aug 15 2022
  By Abhijeet Kumar

  https://github.com/Abhijeetbyte/NDVI-GO

  This code is in the public domain.

*/


// Libraries
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Display setup
#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
#define OLED_RESET -1        // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C  ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// GPIO
#define IR_ledPin 9      // pin D9
#define RED_ledPin 10      // pin D10
#define LDR_sensorPin A0  // pin A0
#define IR_sensorPin A1   // pin A1

// variables
float NDVI = 0;             //  the ndvi value
float IR_sensorValue = 0;   // ir sensor value
float RED_sensorValue = 0;  // ldr sensor value

const int IR_sensorMax = 1023;   // maximum reflectance value of IR sensor  (calibration value)
const int RED_sensorMax = 1023;  // maximum reflectance value of LDR sensor (calibration value)
const int IR_sensorMin = 0;  // minimum reflectance value of IR sensor  (calibration value)
const int RED_sensorMin = 0;  // minimum reflectance value of LDR sensor (calibration value)



void setup() {

  // Debug console
  Serial.begin(9600);  // at 9600 baud rate

  //Dislay begin
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);  // Display type, I2C address
  display.clearDisplay(); // clear

  // I/O declaration
  pinMode(IR_ledPin, OUTPUT);
  pinMode(RED_ledPin, OUTPUT);
  pinMode(LDR_sensorPin, INPUT);
  pinMode(IR_sensorPin, INPUT);

  Serial.println("NDVI-GO begin successfully");  // print initialization message
  Serial.println("");

  // print message to display
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(15, 15);  // (x,y)
  display.println("NDVI-GO");
  display.display();
  Serial.println("Getting data........");  // print message
  Serial.println("");

  delay(1000);
}



void loop() {

  // Read the sensors:

  // get reading for IR:
  digitalWrite(IR_ledPin, HIGH);  // turn on IR led
  delay(200); //wait for IR sensor to stabalize
  IR_sensorValue = analogRead(IR_sensorPin); //read the IR sensor
  delay(200);
  digitalWrite(IR_ledPin, LOW);  // turn off IR led
  delay(200);

  // get reading for RED:
  digitalWrite(RED_ledPin, HIGH);  // turn on RED led
  delay(200); //wait for LDR sensor to stabalize
  RED_sensorValue = analogRead(LDR_sensorPin); //read the LDR sensor
  delay(200);
  digitalWrite(RED_ledPin, LOW);  // turn off IR led

  // send data to serial
  Serial.print("IR sensor Value :");
  Serial.print(IR_sensorValue);
  Serial.print(", RED sensor Value :");
  Serial.println(RED_sensorValue);


  // Apply the calibration to the sensor reading:

  IR_sensorValue = map(IR_sensorValue, IR_sensorMin, IR_sensorMax, 0, 100);  // (0 - 100)
  IR_sensorValue = constrain(IR_sensorValue, 0, 100);  // in case the sensor value is outside the range seen during calibration
  IR_sensorValue = IR_sensorValue / 100; // (0 - 1)

  RED_sensorValue = map(RED_sensorValue, RED_sensorMin, RED_sensorMax, 0, 100);
  RED_sensorValue = constrain(RED_sensorValue, 0, 100);
  RED_sensorValue = RED_sensorValue / 100;

  //debug value
  //Serial.println("");
  //Serial.print("NIR :");
  //Serial.print(IR_sensorValue);
  // Serial.print(" , RED :");
  // Serial.print(RED_sensorValue);
  // Serial.println("");


  // Calculate NDVI using the calibrated value:

  NDVI = (IR_sensorValue) - (RED_sensorValue) / (IR_sensorValue) + (RED_sensorValue); // NDVI expression

  //send to serial
  Serial.println("");
  Serial.print("NDVI Value :");
  Serial.println(NDVI);
  Serial.println("");

  // print to display
  display.clearDisplay();  // clear
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 15);
  display.println("NIR:");
  display.setCursor(65, 15);
  display.println(IR_sensorValue);
  display.display();
  delay(3000); // wait 3 sec

  display.clearDisplay();  // clear
  display.setCursor(0, 15);
  display.println("RED:");
  display.setCursor(65, 15);
  display.println(RED_sensorValue);
  display.display();
  delay(3000);

  display.clearDisplay();  // clear
  display.setCursor(0, 15);
  display.println("NDVI:");
  display.setCursor(65, 15);
  display.println(NDVI);
  display.display();
  delay(3000);


  // remarks :

  if (NDVI >= -1 && NDVI <= 0) {  // (-1 to 0)
    Serial.println("Dead plant or Inanimate object !");
    Serial.println(" ");
  }
  else if (NDVI >= 0 && NDVI <= 0.33) {  // (0 to 0.33)
    Serial.println("Unhealthy plant !");
    Serial.println(" ");
  }
  else if (NDVI >= 0.33 && NDVI <= 0.66) {  // (0.33 to 0.66)
    Serial.println("Moderatly healthy plant !");
    Serial.println(" ");
  }
  else if (NDVI >= 0.66 && NDVI <= 1.00) {  // (0.66 to 1)
    Serial.println("Very healthy plant !");
    Serial.println(" ");
  }

  Serial.println("---------------------------------------------------------"); // end line

  delay(1000); // delay a little bit

}
