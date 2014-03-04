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

//modes could be 0 - 8
uint8_t currentMode = 0; 

//current sensor value, regardless of human or not
int currentVal = 0; 

//setup neopixel strip
#define numStripLEDs 10//how many LEDs long
Adafruit_NeoPixel strip = Adafruit_NeoPixel(numStripLEDs, ledStrip, NEO_GRB + NEO_KHZ800);

//define sound
//////////////////////////////////////////////////////////////
//windFish
int melody1[] = {
  NOTE_D5, NOTE_E5, NOTE_F5, NOTE_D5, NOTE_E5, NOTE_F5, 
  NOTE_E5, NOTE_D5, NOTE_A4, NOTE_C5, NOTE_D5
};
int noteDurations1[] = {
  400, 400, 1400, 400, 400, 1400,
  400, 400, 400, 800, 1000
};

//songOfStorms
int melody2[] = {
  NOTE_D4, NOTE_F4, NOTE_D5, NOTE_D4, NOTE_F4, NOTE_D5, 
  NOTE_E5, NOTE_F5, NOTE_E5, NOTE_F5, NOTE_E5, NOTE_C5, NOTE_A4
};
int noteDurations2[] = {
  200, 200, 600, 200, 200, 600, 
  600, 200, 200, 200, 200, 200, 600
};

//overWorld
int melody3[] = {
  NOTE_A4, NOTE_E4, NOTE_A4, 
  NOTE_A4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5
};
int noteDurations3[] = {
  400, 800, 150,
  150, 150, 150, 150, 800
};

int count = 0;
int thisNote = 0;
//////////////////////////////////////////////////////////////

void setup(){
  pinMode(buttonMode, INPUT);
  pinMode(buttonRange, INPUT);
  pinMode(ledMode, OUTPUT);
  pinMode(ledOnboard, OUTPUT);
  pinMode(audioOut, OUTPUT);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  Serial.begin(57600);
}

void loop(){

  /* update buttons and mode LEDs */
  updateButtons();
  updateModeLeds();
  updateSounds();
  Serial.println(thisNote);
  Serial.println(count);

  switch(currentMode){

  case 0: //--- REGULAR GADGIT MODE ---
    digitalWrite(ledOnboard, HIGH);
    currentVal = analogRead(gadgitCircuitIn);      
    //TODO: map currentVal to 0-1000 or 0-100 or something even

      colorWipe(100, currentVal);

    Serial.print("GADGIT currentVal:\t");
    Serial.println(currentVal);

    break;

  case 1: //--- HUMAN CIRCUIT MODE ---
    digitalWrite(ledOnboard, LOW);
    currentVal = analogRead(humanCircuitIn);
    //TODO: map currentVal to 0-1000 or 0-100 or something even

      colorWipe(127, currentVal);

    Serial.print("HUMAN currentVal:\t");
    Serial.println(currentVal);

    break;   
  }
}

void updateButtons(){
  /* check both buttons, set the global currentMode to
   * whichever button has last been pressed   */

  int currModeBut = digitalRead(buttonMode); 
  if(currModeBut) currentMode = 1;

  int currRangeBut = digitalRead(buttonRange); 
  if(currRangeBut) {
    currentMode = 0;
    count = (count + 1) % 3;
    thisNote = 0;
    delay(1000);
  }
}


void updateModeLeds(){
  /* check current mode and turn on correct modeLED */
  if(currentMode == 0)  digitalWrite(ledMode, HIGH);
  else digitalWrite(ledMode, LOW);
}

void updateSounds(){
  if(currentMode == 0) {
    switch(count){
    case 0:
      windFish();
      break;
    case 1:
      songOfStorms();
      break;
    case 2:
      overWorld();
      break;
    }
  }
  else {
    noTone(audioOut);
  }
}

void windFish(){
  int noteDuration = noteDurations1[thisNote];
  tone(audioOut, melody1[thisNote], noteDuration);
  int pauseBetweenNotes = noteDuration * 1.30;
  delay(pauseBetweenNotes);
  thisNote = (thisNote + 1) % 11; 
}

void songOfStorms(){
  int noteDuration = noteDurations2[thisNote];
  tone(audioOut, melody2[thisNote], noteDuration);
  int pauseBetweenNotes = noteDuration * 1.30;
  delay(pauseBetweenNotes);
  thisNote = (thisNote + 1) % 13;
}

void overWorld(){
  int noteDuration = noteDurations3[thisNote];
  tone(audioOut, melody3[thisNote], noteDuration);
  int pauseBetweenNotes = noteDuration * 1.30;
  delay(pauseBetweenNotes);
  thisNote = (thisNote + 1) % 8;
}
