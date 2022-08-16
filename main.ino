

// GPIO

#define IR_led 2 // pin D2
#define RED_led 3
#define LDR A0 // pin A0

//Variables

float IR = 0;
float RED = 0;
float NDVI = 0;

void setup() {

  // Debug console
  Serial.begin(9600); // at 9600 baud rate

  pinMode(IR_led, OUTPUT);
  pinMode(RED_led, OUTPUT);
  pinMode(LDR, INPUT);


}

void loop() {

  // get reading for RED:
  digitalWrite(3, HIGH);
  delay(200);   //wait

  RED = analogRead(A0);   //read the LDR sensor
  digitalWrite(3, LOW); // turn off RED led
  delay(500);

  // get reading for IR:
  digitalWrite(2, HIGH);
  delay(200);//wait

  IR = analogRead(A0);  //read the LDR sensor
  digitalWrite(2, LOW);
  delay(500);

  //NDVI calculation:
  NDVI = float((float(IR) - float(RED)) / (float(IR) + float(RED)));


  // Send data to serial console

  Serial.print("IR analog Value: ");
  Serial.print(IR);
  Serial.print(", RED analog Value: ");
  Serial.print(RED);
  Serial.print(", NDVI value: ");
  Serial.print(NDVI);
  Serial.println(" ");
  Serial.println("-----------------------------------------------------------");

  delay(1000); // delay

}
