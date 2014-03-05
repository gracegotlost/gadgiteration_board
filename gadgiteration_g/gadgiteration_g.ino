#include <Adafruit_NeoPixel.h>
#include "pitches.h"

/* still in progress */

//define all pins
#define buttonMode   2
#define buttonRange  4
#define ledStrip     6
#define ledMode      7
#define audioOut     8
#define ledOnboard   13
#define gadgitCircuitIn A0
#define humanCircuitIn  A1
#define sensorInput1    A2
#define sensorInput2    A3
#define sensorInput3    A4

//modes could be 0 - 8
uint8_t currentMode = 0;
uint8_t currentCheck = 0;
uint8_t tempMode = 0;

//current values
int thisNote = 0;
int currentVal = 0; 
int sensorState1 = 0;
int sensorState2 = 0;
int sensorState3 = 0;

//setup neopixel strip
#define numStripLEDs 10//how many LEDs long
Adafruit_NeoPixel strip = Adafruit_NeoPixel(numStripLEDs, ledStrip, NEO_GRB + NEO_KHZ800);

//////////////////////////////////////////////////////////////
/*
 Functions to add:
 Control Button Light
 Three inputs to add
 */
//////////////////////////////////////////////////////////////

void setup(){
  pinMode(buttonMode, INPUT);
  pinMode(buttonRange, INPUT);
  pinMode(sensorInput1, INPUT);
  pinMode(sensorInput2, INPUT);
  pinMode(sensorInput3, INPUT);

  pinMode(ledStrip, OUTPUT);
  pinMode(ledMode, OUTPUT);
  pinMode(ledOnboard, OUTPUT);
  pinMode(audioOut, OUTPUT);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  Serial.begin(57600);
}

void loop(){

  /* update buttons and mode LEDs and sounds*/
  updateButtons();
  updateInputs();

  //--- HUMAN CIRCUIT MODE ---
  digitalWrite(ledOnboard, LOW);
  currentVal = analogRead(humanCircuitIn);
  //TODO: map currentVal to 0-1000 or 0-100 or something even
  colorWipe(127, currentVal);
  tone(audioOut, currentVal);
  Serial.print("HUMAN currentVal:\t");
  Serial.println(currentVal);

  //--- REGULAR GADGIT MODE ---
  switch(currentMode){
    /* select modes with different sounds/lights */
  case 0:
    noTone(audioOut);
    digitalWrite(ledMode, LOW);//need to check
    break;
  case 1:
    windFish();
    rainbow(20);
    break;
  case 2:
    songOfStorms();
    rainbowCycle(20);
    break;
  case 3:
    overWorld();
    theaterChaseRainbow(50);
    break;
  }
}

void updateButtons(){
  /* check both buttons, buttonMode loops through all sounds;
   buttonRange confirms which song to choose  */

  int currModeBut = digitalRead(buttonMode);
  if(currModeBut) {
    currentMode = (currentMode + 1) % 4;
    thisNote = 0;
    delay(1000);
  }

  int currRangeBut = digitalRead(buttonRange); 
  if(currRangeBut) {
    currentCheck = 1 - currentCheck;

    if(currentCheck) {
      tempMode = currentMode;
      currentMode = 0;
      digitalWrite(ledOnboard, LOW);
    }
    else {
      currentMode = tempMode;
      digitalWrite(ledOnboard, HIGH);
    }
  }
}

void updateInputs(){
  sensorState1 = digitalRead(sensorInput1);
  sensorState2 = digitalRead(sensorInput2);
  sensorState3 = digitalRead(sensorInput3);
  if((sensorState1&sensorState2) || (sensorState2&sensorState3)
    || (sensorState3&sensorState1) || (sensorState1&sensorState2&sensorState3)){
    tone(audioOut, 400);
  }
  else if(sensorState1 || sensorState2 || sensorState3){
    currentMode = tempMode;
  }
}












