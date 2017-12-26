enum State {
  dot,
  dash,
  gap,      //between dots and dashes in morse code
  between,  //between characters
  space,
  off,
};

#include"MorseCodes.h"

const int led = 13;
const unsigned long unit = 500;

unsigned long nextTime = 0;
unsigned long delta = 0;

String morse = "";

bool readyForNextState = false;
bool isBetween = true;
int i = 0;

// Argument: Any character
// Return Value: Either:
//                  1) If the character is a letter, the upper case equivalent.  
//                  2) If the character is not a letter, the original value.
char toUpper(char c) {
  if ((c > 0x60) && (c < 0x7B))
    return c-0x20;
  return c;
}

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

State currentState = space;

State nextState (State state) {
   currentState = state;
  
  switch (currentState) {

    case dot:
      digitalWrite(led, LOW); //
      delta = unit;
      Serial.println("switch working dot");
      

      if (readyForNextState) {
        currentState = between;
        digitalWrite(led, HIGH);  //
        readyForNextState = false;
        isBetween = false;
      }
      
      break;

    case dash:
      digitalWrite(led, LOW); //
      delta = unit*3;
      Serial.println("switch working dash");

      if (readyForNextState) { 
        currentState = between;
        digitalWrite(led, HIGH);  //
        readyForNextState = false;
        isBetween = false;
      }

      break;

    case gap:
      isBetween = true;
      digitalWrite(led, HIGH);
      delta = unit;
      Serial.println("switch working gap");

      ++i;
      break;
      
    case between:
      isBetween = true;
      digitalWrite(led, HIGH);  //
      delta = unit*3;
      Serial.println("switch working between");
      
      ++i;
      break;

    case space:
      digitalWrite(led, HIGH);  //
      delta = unit;
      Serial.println("switch working space");

      ++i;
      break;

    case off:
      digitalWrite(led, LOW);

      break;
      
  }
  return currentState;
  
}

void convertIncomingCharsToMorseCode() {
  // TODO
  
  if (Serial.available() > 0) {
    
    morse = morseEncode(Serial.read());

    Serial.println(morse);

    i = 0;
    while (i < morse.length()) {
      Serial.println(i);
      
      if (isBetween) {
        if (morse[i] == '.') {
          digitalWrite(led, LOW); //
          currentState = dot;
          Serial.println("dot");
        }
        
        if (morse[i] == '-') {
          digitalWrite(led, LOW); //
          currentState = dash;
          Serial.println("dash");
        }
        
        if (morse[i] == ' ') {
          currentState = space;
          Serial.println("space");
        }
      }

      if (millis()-nextTime > delta) { 
        readyForNextState = true;   
        currentState = nextState(currentState);
        nextTime = millis();
      }

    }
   
  }
  
  else {

    currentState = off;
    nextState(currentState);
  }
  
}

void loop() {
  // No Need to Modify this.  Put most of your code in "convertIncomingCharsToMorseCode()"
  convertIncomingCharsToMorseCode();
}
