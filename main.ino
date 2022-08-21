

// GPIO

#define IR_led 2 // pin D2
#define RED_led 3
#define LDR A0 // pin A0

//Variables

//float IR = 0;
//float RED = 0;
float NDVI = 0;

void setup() {

  // Debug console
  Serial.begin(9600); // at 9600 baud rate

  pinMode(IR_led, OUTPUT);
  pinMode(RED_led, OUTPUT);
  pinMode(LDR, INPUT);

  Serial.println("NDVI-GO begin successfully !"); // print initialization message
  Serial.println(" ");



}

void loop() {

  // get reading for RED:

  float RED = 0;

  for (int i = 0; i < 10; i++) {

    digitalWrite(3, HIGH);  // turn on RED led
    delay(200);   //wait

    RED = RED + analogRead(A0);   //read the LDR sensor
    digitalWrite(3, LOW); // turn off RED led
    delay(500);
  }
  RED = RED / 10;  // getting average of 10 readings



  // get reading for IR:

  float IR = 0;

  for (int i = 0; i < 10; i++) {

    digitalWrite(2, HIGH); // turn on IR lED
    delay(200);//wait

    IR = IR + analogRead(A0);  //read the LDR sensor
    digitalWrite(2, LOW);
    delay(500);
  }
  IR = IR / 10;  // getting average of 10 readings



  //NDVI calculation:
  NDVI = float((float(IR) - float(RED)) / (float(IR) + float(RED)));


  // Send data to serial console

  Serial.print("IR analog Value: ");
  Serial.print(IR);
  Serial.print(", RED analog Value: ");
  Serial.print(RED);
  Serial.print(", NDVI value: ");
  Serial.println(NDVI);
  Serial.println(" ");
  Serial.println("-----------------------------------------------------------");

  delay(1000); // delay

}
