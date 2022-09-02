

// GPIO

#define IR_led 2 // pin D2
#define RED_led 3
#define LDR A0 // pin A0

//Variables

//float IR = 0;
//float RED = 0;
float NDVI = 0;

const int IR_Max = 0; // Put Max Value of IR reflectance (Calibration Value)
const int RED_Max = 0 ; // Put Max Value of RED reflectance (Calibration Value)

void setup() {

  // Debug console
  Serial.begin(9600); // at 9600 baud rate

  pinMode(IR_led, OUTPUT);
  pinMode(RED_led, OUTPUT);
  pinMode(LDR, INPUT);

  Serial.println("NDVI-GO begin successfully !"); // print initialization message
  delay(2000);
  Serial.println(" ");
  Serial.println("Initializing Calibration....");
  delay(2000);

  if (RED_Max == 0 && IR_Max == 0) {

    Serial.println(" ");
    Serial.println("Calibration data not found !");
    Serial.println("Insert Calibration, data to ( IR_Max, RED_Max )");
    delay(5000);
    Serial.println(" ");

  } else {
    Serial.println("Calibration check 'OK'");
    delay(1000);
    Serial.println(" ");
  }


}

void loop() {

  // get reading for RED:

  Serial.print("Getting data........"); // print a message



  float RED = 0;

  for (int i = 0; i < 10; i++) {

    digitalWrite(3, HIGH);  // turn on RED led
    delay(200);   //wait

    RED = RED + analogRead(A0);  //read the LDR sensor (value between 0 and 1023)
    digitalWrite(3, LOW); // turn off RED led
    delay(500);

    Serial.print(".");
  }
  RED = RED / 10;  // getting average of 10 readings



  // get reading for IR:

  float IR = 0;

  for (int i = 0; i < 10; i++) {

    digitalWrite(2, HIGH); // turn on IR lED
    delay(200);//wait

    IR = IR + analogRead(A0);  //read the LDR sensor (value between 0 and 1023)
    digitalWrite(2, LOW);
    delay(500);

    Serial.print(".");
  }
  IR = IR / 10;  // getting average of 10 readings




  // Preparing raw data

  RED = map(RED, 0, RED_Max, 0, 100);  // scale it for use (value between 0 and 100)

  RED /= 100;

  IR = map(IR, 0, IR_Max, 0, 100);

  IR /= 100;




  //NDVI calculation:
  NDVI = float((float(IR) - float(RED)) / (float(IR) + float(RED)));


  // Send data to serial console
  Serial.println(" ");
  Serial.println(" ");
  Serial.println("-----------------------------------------------------------"); // end line formet
  Serial.println(" ");
  Serial.print("IR analog Value: ");
  Serial.print(IR);
  Serial.print(", RED analog Value: ");
  Serial.print(RED);
  Serial.print(", NDVI value: ");
  Serial.println(NDVI);
  Serial.println(" ");
  Serial.println("-----------------------------------------------------------");
  Serial.println(" ");


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
