//Define sound arrays and note durations

//windFish
int melody1[] = {
  NOTE_D5, NOTE_E5, NOTE_F5, 
  NOTE_D5, NOTE_E5, NOTE_F5, 
  NOTE_E5, NOTE_D5, NOTE_A4,
  NOTE_C5, NOTE_D5
};
int noteDurations1[] = {
  400, 400, 1400, 
  400, 400, 1400,
  400, 400, 400, 
  800, 1000
};

//songOfStorms
int melody2[] = {
  NOTE_D4, NOTE_F4, NOTE_D5, 
  NOTE_D4, NOTE_F4, NOTE_D5, 
  NOTE_E5, NOTE_F5, NOTE_E5, 
  NOTE_F5, NOTE_E5, NOTE_C5, 
  NOTE_A4
};
int noteDurations2[] = {
  200, 200, 600, 
  200, 200, 600, 
  600, 200, 200, 
  200, 200, 200, 
  600
};

//overWorld
int melody3[] = {
  NOTE_A4, NOTE_E4, NOTE_A4, 
  NOTE_A4, NOTE_B4, NOTE_C5, 
  NOTE_D5, NOTE_E5
};
int noteDurations3[] = {
  400, 800, 150,
  150, 150, 150, 
  150, 800
};

//song of windFish
void windFish(){
  int noteDuration = noteDurations1[thisNote];
  tone(audioOut, melody1[thisNote], noteDuration);
  int pauseBetweenNotes = noteDuration * 1.30;
  delay(pauseBetweenNotes);
  thisNote = (thisNote + 1) % 11; 
}

//song of songOfStorms
void songOfStorms(){
  int noteDuration = noteDurations2[thisNote];
  tone(audioOut, melody2[thisNote], noteDuration);
  int pauseBetweenNotes = noteDuration * 1.30;
  delay(pauseBetweenNotes);
  thisNote = (thisNote + 1) % 13;
}

//song of overWorld
void overWorld(){
  int noteDuration = noteDurations3[thisNote];
  tone(audioOut, melody3[thisNote], noteDuration);
  int pauseBetweenNotes = noteDuration * 1.30;
  delay(pauseBetweenNotes);
  thisNote = (thisNote + 1) % 8;
}
