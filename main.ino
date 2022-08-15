

// GPIO

#define IR_led 2 // pin D1
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
  delay(25);            //wait

  RED = analogRead(A0);   //read the LDR sensor
  digitalWrite(3, LOW); // turn off RED led
  delay(200);

  // get reading for IR:
  digitalWrite(2, HIGH);
  delay(25);//wait

  IR = analogRead(A0);  //read the LDR sensor
  digitalWrite(2, LOW);
  delay(200);

  //NDVI calculation:
  NDVI = (IR - RED ) / (IR + RED);

  Serial.print("NDVI value: ");  // Send data to serial console
  Serial.println(NDVI);

  delay(500); // delay

}
