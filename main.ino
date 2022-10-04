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

#define RED_ledPin 2      // pin D2
#define LDR_sensorPin A0  // pin A0
#define IR_sensorPin A1   // pin A1

// variables

float NDVI = 0;             //  the ndvi value
float IR_sensorValue = 0;   // ir sensor value
float RED_sensorValue = 0;  // ldr sensor value

const int IR_sensorMax = 0;   // maximum reflectance value of IR sensor  (calibration value)
const int RED_sensorMax = 0;  // maximum reflectance value of LDR sensor (calibration value)


void setup() {

  // Debug console
  Serial.begin(9600);  // at 9600 baud rate

  //Dislay begin
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);  // Display type, I2C address
  display.clearDisplay();                               // clear

  // I/O declaration
  pinMode(RED_ledPin, OUTPUT);
  pinMode(LDR_sensorPin, INPUT);
  pinMode(IR_sensorPin, INPUT);

  Serial.println("NDVI-GO begin successfully !");  // print initialization message
  Serial.println("");
  Serial.println("Getting data........");
  Serial.println("");

  // print message to display
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(15, 15);  // (x,y)
  display.println("NDVI-GO");
  display.display();

  delay(1000);
}

void loop() {


  // read the sensor:

  IR_sensorValue = abs(analogRead(IR_sensorPin) - 1023);  // get reading for IR
  delay(200);

  digitalWrite(RED_ledPin, HIGH);  // turn on RED lED
  delay(200);

  RED_sensorValue = abs(analogRead(LDR_sensorPin) - 1023);  // get reading for RED/LDR
  delay(200);

  digitalWrite(RED_ledPin, LOW);


  // print on console
  Serial.println(" ");
  Serial.println("IR sensor Value :");
  Serial.print(IR_sensorValue);
  Serial.println("RED sensor Value :");
  Serial.print(RED_sensorValue);



  // apply the calibration to the sensor reading:

  IR_sensorValue = map(IR_sensorValue, 0, IR_sensorMax, 0, 100);  // (0 - 100)

  // in case the sensor value is outside the range seen during calibration
  IR_sensorValue = constrain(IR_sensorValue, 0, 100);

  RED_sensorValue = map(RED_sensorValue, 0, RED_sensorMax, 0, 100);  // (0 - 100)

  // in case the sensor value is outside the range seen during calibration
  RED_sensorValue = constrain(RED_sensorValue, 0, 100);



  // calculate NDVI using the calibrated value:

  NDVI = float((float(IR_sensorValue / 100) - float(RED_sensorValue)) / (float(IR_sensorValue) + float(RED_sensorValue)));  // NDVI expression

  // print on console
  Serial.println("");
  Serial.println("NDVI Value :");
  Serial.print(NDVI);


  // print to display
  display.clearDisplay();  // clear
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 15);
  display.println("NDVI:");
  display.setCursor(65, 15);
  display.println(NDVI);
  display.display();

  /*
  // Remarks :

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

  else if (NDVI >= 0.66 && NDVI <= 0.33) {  // (0.66 to 1)
    Serial.println("Very healthy plant !");
    Serial.println(" ");
  }
*/

  // delay a little bit
  delay(1000);  // delay
}
