

// GPIO

#define IR_led 2 // pin D2
#define RED_led 3 // pin D3
#define LDR A0 // pin A0


//Variables

float NDVI = 0;

const int IR_Max = 1023; // Put Max Value of IR reflectance (Calibration Value)
const int RED_Max = 1023 ; // Put Max Value of RED reflectance (Calibration Value)


void setup() {

  // Debug console
  Serial.begin(9600); // at 9600 baud rate

  // I/O declaration

  pinMode(IR_led, OUTPUT);
  pinMode(RED_led, OUTPUT);
  pinMode(LDR, INPUT); // delared as input


  Serial.println("NDVI-GO begin successfully !"); // print initialization message
  Serial.println("");
  delay(1000);

}

void loop() {


  //  ***************** Measure analog value using cahnnel A0 & A1 ******************

  Serial.print("Getting data........"); // print a message

  float ADC_ir = 0;
  float ADC_red = 0;

  for (int i = 0; i < 10; i++) {

    // get reading for IR:
    
    digitalWrite(2, HIGH); // turn on IR lED

    delay(200);//wait
    ADC_ir = ADC_ir + analogRead(A0);  //reads the value of the IR sensor

    digitalWrite(2, LOW);
    delay(100);


    // get reading for RED:

    digitalWrite(3, HIGH); // turn on RED led

    delay(200);//wait
    ADC_red = ADC_red + analogRead(A0);  // reads the value of the LDR (value between 0 and 1023)

    digitalWrite(3, LOW); //turn off RED led
    delay(100);

    Serial.print(".");
  }

  ADC_ir = ADC_ir / 10; // getting average of 10 ADC readings
  ADC_red =  ADC_red / 10;



  //  *************** Calculate NDVI ******************

  float IR =  0; 
  float RED = 0;


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

  /*

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

  */

  delay(500); // delay

}
