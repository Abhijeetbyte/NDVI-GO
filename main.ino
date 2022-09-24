
// Libraries

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Display setup

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);



// GPIO

#define RED_led 2 // pin D2
#define LDR A0 // pin A0
#define Ir A1 // pin A1


//Variables

float NDVI = 0;
float ADC_ir = 0;
float ADC_red = 0;
float IR =  0;
float RED = 0;

const int IR_Max = 1023; // Put Max Value of IR reflectance (Calibration Value)
const int RED_Max = 1023 ; // Put Max Value of RED reflectance (Calibration Value)


void setup() {

  // Debug console
  Serial.begin(9600); // at 9600 baud rate


  //Dislay begin

  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS); // Display type, I2C address
  display.clearDisplay();  // clear


  // I/O declaration

  pinMode(RED_led, OUTPUT); // delared as output
  pinMode(LDR, INPUT); // delared as input
  pinMode(Ir, INPUT);


  Serial.println("NDVI-GO begin successfully !"); // print initialization message
  Serial.println("");

  // print message to display

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(15, 15); // (x,y)
  display.println("NDVI-GO");
  display.display();

  delay(1000);


}

void loop() {


  //  ***************** Measure analog value using cahnnel A0 & A1 ******************


  Serial.print("Getting data........"); // print a message
  delay(500);


  // get reading for IR:
  ADC_ir = abs(analogRead(A0) - 1023); //reads the value of the IR sensor (value between 0 and 1023)
  delay(1000);


  // get reading for RED:
  digitalWrite(RED_led, HIGH); // turn on RED lED

  delay(200);//wait
  ADC_red = abs(analogRead(A1) - 1023); // reads the value of the LDR
  delay(1000);

  digitalWrite(RED_led, LOW); // turn off RED lED



  //  *************** Calculate NDVI ******************


  IR = map(ADC_ir, 0, IR_Max, 0, 100); // scale it for use (value between 0 and 100)
  IR /= 100;

  RED = map(ADC_red, 0, RED_Max, 0, 100);
  RED /= 100;

  NDVI = float((float(IR) - float(RED)) / (float(IR) + float(RED)));  // NDVI expression



  //  ***************** Print analog values & NDVI to console ******************

  Serial.println("");
  Serial.println("");
  Serial.print("ADC ir Value: "); // debug data
  Serial.print(ADC_ir);
  Serial.print(", ADC red Value: ");
  Serial.print(ADC_red);

  Serial.print(", IR Value : ");
  Serial.print(IR);
  Serial.print(", RED Value: ");
  Serial.print(RED);
  Serial.print(", NDVI Value: ");
  Serial.println(NDVI);
  Serial.println("");

  // print to display

  display.clearDisplay();  // clear
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 15);
  display.println("NDVI:");
  display.setCursor(65, 15);
  display.println(NDVI);
  display.display();


  // Remarks

  if (NDVI >= -1 && NDVI <= 0 ) { // (-1 to 0)
    Serial.println("Dead plant or Inanimate object !");
    Serial.println(" ");
  }

  else if (NDVI >= 0 && NDVI <= 0.33 ) { // (0 to 0.33)
    Serial.println("Unhealthy plant !");
    Serial.println(" ");
  }

  else if (NDVI >= 0.33 && NDVI <= 0.66) { // (0.33 to 0.66)
    Serial.println("Moderatly healthy plant !");
    Serial.println(" ");
  }

  else if (NDVI >= 0.66 && NDVI <= 0.33) { // (0.66 to 1)
    Serial.println("Very healthy plant !");
    Serial.println(" ");
  }


  delay(1000); // delay

}
