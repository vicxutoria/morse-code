#include"MorseCodes.h"

const int ledPin = 13;
const int buttonPin = 3;
const int unit = 1000;
unsigned long currentTimeButtonChanged = 0;
unsigned long prevTimeButtonChanged = 0;
unsigned long currentTime = 0;
int buttonState = 0;
int dot = unit;
int dash = unit*3;
int dotDashGap = unit;
int morseCodeGap = unit*3;
int space = unit*7;
int morseCodeCount = 0;
char morseCodes[7];

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonPressed, CHANGE);
}

void buttonPressed() {
  currentTimeButtonChanged = millis();
  buttonState = 1 - buttonState;
}

void convertIncomingMorseCodeToChars() {
  int timer = millis() - prevTimeButtonChanged;
  int partialWord = 0;
  if(currentTimeButtonChanged != prevTimeButtonChanged) {
    prevTimeButtonChanged = currentTimeButtonChanged;
    if(buttonState == 0) {
      if(timer < dot*0.66) {
        Serial.println("#Too short for a dot! Ignored!#");
      }
      else if(timer > dash*1.33) {
        Serial.println("#Too long for a dash! Ignored!#");
      }
      else if(timer >= dot*0.66 && timer <= dot*1.33) {
        Serial.println("#.#");
        morseCodes[morseCodeCount] = '.';
        morseCodeCount++;
      }
      else if(timer >= dash*0.66 && timer <= dash*1.33) {
        Serial.println("#-#");
        morseCodes[morseCodeCount] = '-';
        morseCodeCount++;
      }
      else {
        Serial.println("#Too long for a dot, but too short for a dash! Ignored!#");
        
      } 
    }
    else if(morseCodeCount > 0) {
      if(timer < dotDashGap*0.66) {
        Serial.println("#Too short of a gap between dot/dash!#");
      }
      else if(timer >= morseCodeGap*0.66) {
        if(morseCodeCount > 6) {
          Serial.println("#Code too lont to be valid! Dropping all!#");
        }
        else {
          morseCodes[morseCodeCount] = '\0';
          char anChar = morseDecode(morseCodes);
          if(anChar == 0) {
            Serial.println("#Not a valid Morse Code!#");
          }
          else {
            Serial.print("#Letter: ");
            Serial.print(anChar);
            Serial.println("#");
            partialWord = 1;
          }
        }
        morseCodeCount = 0;
        if(timer >= space*0.66 && partialWord > 0) {
          Serial.println("#space#");
          partialWord = 0;
        }
      }
    }
  }
  else if(morseCodeCount > 0 && buttonState == 0) {
    if(timer >= space*0.66) {
      if(morseCodeCount > 6) {
        Serial.println("#Code too long to be valid! Dropping all!#");
      }
      else {
        morseCodes[morseCodeCount] = '\0';
        char anChar = morseDecode(morseCodes);
        if(anChar == 0) {
          Serial.println("#Not a valid Morse Code!#");
        }
        else {
          Serial.print("#Letter: ");
          Serial.print(anChar);
          Serial.println("#");
          partialWord = 1;
        }
      }
      morseCodeCount = 0;
      if(partialWord > 0) {
        Serial.println("#space#");
        partialWord = 0;
      }
    }
  }
}

void updateLED() {
  boolean readLed = digitalRead(ledPin);
  if(millis() - currentTime > unit*0.5) {
    digitalWrite(ledPin, !readLed);
    currentTime = millis();
  }
}

void loop() {
  // No Need to Modify this.  Put most of your code in "convertIncomingMorseCodeToChars()" and "updateLED()"
  updateLED();
  convertIncomingMorseCodeToChars();

  // Extra credit: Merge in your convertIncomingCharsToMorseCode() to have a 
  // complete encoder/decoder
}
