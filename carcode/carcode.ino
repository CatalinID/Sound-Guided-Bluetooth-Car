#define  SOUND_PIN1  A1
#define  SOUND_PIN2    A2
#define  SOUND_PIN3    A3
//L293 Connection
const int motorA1  = 5;  // Pin  2 of L293
const int motorA2  = 6;  // Pin  7 of L293
const int motorB1  = 10; // Pin 10 of L293
const int motorB2  = 9;  // Pin 14 of L293
//Bluetooth (HC-06 JY-MCU) State pin on pin 2 of Arduino
const int BTState = 2;
//Calculate Battery Level

//Useful Variables
int st;
int i = 0;
int j = 0;
int state;
int vSpeed = 180;
float avr = 0;
// Default speed, from 0 to 255
float soundValue1, soundValue2, soundValue3;
void setup() {

  pinMode(SOUND_PIN1, INPUT);
  pinMode(SOUND_PIN2, INPUT);
  pinMode(SOUND_PIN3, INPUT);
  // Set pins as outputs:
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  pinMode(BTState, INPUT);
  pinMode(BTState, OUTPUT);
  // Initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

void loop() {


  //Stop car when connection lost or bluetooth disconnected
  if (digitalRead(BTState) == LOW) {
    state = 'S';
  }
  //Save income data to variable 'state'
  
     if((st=Serial.read() ) == 'A' ){ 
  //Send data from microphones
        state='S';
        avr=0;
       for (int i = 0 ; i < 100 ; i++) {
        avr=avr+analogRead(SOUND_PIN1);
        
     }
     Serial.println(avr/100);
    avr =0;
    for(int i = 0 ; i < 100 ; i++){
      avr=avr +analogRead(SOUND_PIN2);
      }
      
    Serial.println(avr/100);
    avr = 0;
    for(int i = 0 ; i < 100 ; i++){
     avr = avr + analogRead(SOUND_PIN3);
     }
     Serial.println(avr/100);
     Serial.println("Done");
     Serial.flush();
  delay(1000);
 // Serial.begin(9600);
  
  if (Serial.available() > 0) {
    state = Serial.read();
  }
    


  /***********************Forward****************************/
  //If state is equal with letter 'F', car will go forward!
  if (state == 'F') {
    analogWrite(motorA1, 120); analogWrite(motorA2, 0);
    analogWrite(motorB1, 0);      analogWrite(motorB2, 0);
  }
  /**********************Forward Left************************/
  //If state is equal with letter 'G', car will go forward left
  else if (state == 'G') {
    analogWrite(motorA1, vSpeed); analogWrite(motorA2, 0);
    analogWrite(motorB1, 255);    analogWrite(motorB2, 0);
  }
  /**********************Forward Right************************/
  //If state is equal with letter 'I', car will go forward right
  else if (state == 'I') {
    analogWrite(motorA1, vSpeed); analogWrite(motorA2, 0);
    analogWrite(motorB1, 0);      analogWrite(motorB2, 255);
  }
  /***********************Backward****************************/
  //If state is equal with letter 'B', car will go backward
  else if (state == 'B') {
    analogWrite(motorA1, 0);   analogWrite(motorA2, vSpeed);
    analogWrite(motorB1, 0);   analogWrite(motorB2, 0);
  }
  /**********************Backward Left************************/
  //If state is equal with letter 'H', car will go backward left
  else if (state == 'H') {
    analogWrite(motorA1, 0);   analogWrite(motorA2, vSpeed);
    analogWrite(motorB1, 255); analogWrite(motorB2, 0);
  }
  /**********************Backward Right************************/
  //If state is equal with letter 'J', car will go backward right
  else if (state == 'J') {
    analogWrite(motorA1, 0);   analogWrite(motorA2, vSpeed);
    analogWrite(motorB1, 0);   analogWrite(motorB2, 255);
  }
  /***************************Left*****************************/
  //If state is equal with letter 'L', wheels will turn left
  else if (state == 'L') {
    analogWrite(motorA1, 0);   analogWrite(motorA2, 0);
    analogWrite(motorB1, 255); analogWrite(motorB2, 0);
  }
  /***************************Right*****************************/
  //If state is equal with letter 'R', wheels will turn right
  else if (state == 'R') {
    analogWrite(motorA1, 0);   analogWrite(motorA2, 0);
    analogWrite(motorB1, 0);   analogWrite(motorB2, 255);
  }
 
  /************************Stop*****************************/
  //If state is equal with letter 'S', stop the car
  else if (state == 'S') {
    analogWrite(motorA1, 0);  analogWrite(motorA2, 0);
    analogWrite(motorB1, 0);  analogWrite(motorB2, 0);
  }
 
      delay(500);
     }
    
}



