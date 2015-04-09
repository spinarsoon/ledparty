/*
  Analog Input
 Demonstrates analog input by reading an analog sensor on analog pin 0 and
 turning on and off a light emitting diode(LED)  connected to digital pin 13.
 The amount of time the LED will be on and off depends on
 the value obtained by analogRead().

 The circuit:
 * Potentiometer attached to analog input 0
 * center pin of the potentiometer to the analog pin
 * one side pin (either one) to ground
 * the other side pin to +5V
 * LED anode (long leg) attached to digital output 13
 * LED cathode (short leg) attached to ground

 * Note: because most Arduinos have a built-in LED attached
 to pin 13 on the board, the LED is optional.


 Created by David Cuartielles
 modified 30 Aug 2011
 By Tom Igoe

 This example code is in the public domain.

 http://arduino.cc/en/Tutorial/AnalogInput

 */

int sensorPin = A0;    // select the input pin for the potentiometer
int mosfetPin = 3;      // select the pin for PWMing mosfet
int sensorValue = 0;  // variable to store the value coming from the sensor
int dimmValue=0;
void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(mosfetPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  
  dimmValue = map(sensorValue, 0, 1023, 0, 255);
  if(Serial.available())
  {
    int mode = Serial.parseInt();
    Serial.print("Frequency mode:");
    Serial.println(mode);
    if(mode==1)
    {
      setPwmFrequency(mosfetPin,1);
    }
    else if(mode==2){
      setPwmFrequency(mosfetPin,8);
    }
    else if(mode==3){
      setPwmFrequency(mosfetPin,32);
    }
    else if(mode==4){
      setPwmFrequency(mosfetPin,64);
    }
    else if(mode==5){
      setPwmFrequency(mosfetPin,128);
    }
    else if(mode==6){
      setPwmFrequency(mosfetPin,256);
    }
    else if(mode==7){
      setPwmFrequency(mosfetPin,1024);
    }
  }

  analogWrite(mosfetPin,dimmValue);
}

void setPwmFrequency(int pin, int divisor) {
  byte mode;
  if(pin == 5 || pin == 6 || pin == 9 || pin == 10) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }
    if(pin == 5 || pin == 6) {
      TCCR0B = TCCR0B & 0b11111000 | mode;
    } else {
      TCCR1B = TCCR1B & 0b11111000 | mode;
    }
  } else if(pin == 3 || pin == 11) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 32: mode = 0x03; break;
      case 64: mode = 0x04; break;
      case 128: mode = 0x05; break;
      case 256: mode = 0x06; break;
      case 1024: mode = 0x7; break;
      default: return;
    }
    TCCR2B = TCCR2B & 0b11111000 | mode;
  }
}
