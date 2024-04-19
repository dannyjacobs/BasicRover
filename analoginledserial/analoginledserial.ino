/*
  Analog input, analog output, serial output

  Reads an analog input pin, maps the result to a range from 0 to 255 and uses
  the result to set the pulse width modulation (PWM) of an output pin.
  Also prints the results to the Serial Monitor.

  The circuit:
  - potentiometer connected to analog pin 0.
    Center pin of the potentiometer goes to the analog pin.
    side pins of the potentiometer go to +5V and ground
  - LED connected from digital pin 9 to ground through 220 ohm resistor

  created 29 Dec. 2008
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/AnalogInOutSerial
*/

// These constants won't change. They're used to give names to the pins used:
// const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
// const int analogOutPin = 9;  // Analog output pin that the LED is attached to

int sensorValue = 0;  // value read from the pot
int outputValue = 0;  // value output to the PWM (analog out)
int PWMValue = 0;
int ledPins[] = {
  2, 3, 4, 5, 6, 7, 8.
};                 // an array of pin numbers to which LEDs are attached
int pinCount = 6;  // the number of pins (i.e. the length of the array)
int ADCchans[] = {
  A2, A3, A4, A5, A6, A7, A8  //ADC channels, sorted to match PWM pins
};
int ADCvals[] = {
  -1, -1, -1, -1, -1, -1, -1, -1
};
void setup() {
  // the array elements are numbered from 0 to (pinCount - 1).
  // use a for loop to initialize each pin as an output:
  for (int thisPin = 0; thisPin < pinCount; thisPin++) {
    pinMode(ledPins[thisPin], OUTPUT);
  }
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void readADCs() {
  for (int thisPin = 0; thisPin <  pinCount; thisPin++){
    ADCvals[thisPin] = analogRead(ADCchans[thisPin]);
  }

}

void loop() {
  // read the analog in value:
  //sensorValue = analogRead(analogInPin);
  readADCs();
  for (int thisPin=0; thisPin < pinCount; thisPin++){
    Serial.print(ADCvals[thisPin]); //write the output to the serial port
    if (thisPin==(pinCount-1)) { //clean up the end of the line
      Serial.println();
      }
    else {
        Serial.print(',');
      }    
    PWMValue = map(ADCvals[thisPin], 0, 1023, 0, 255); //write an appropriately scaled value to a PWM pin for LED indication
    analogWrite(ledPins[thisPin], PWMValue);
  }
  
  // map it to the range of the analog out:
  //outputValue = map(sensorValue, 0, 1023, 0, 255);
  // change the analog out value:
  //analogWrite(analogOutPin, outputValue);

  // print the results to the Serial Monitor:
  // Serial.print("sensor = ");
  // Serial.print(sensorValue);
  // Serial.print("\t output = ");
  // Serial.println(outputValue);

  // wait 20 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(500);
  
}
