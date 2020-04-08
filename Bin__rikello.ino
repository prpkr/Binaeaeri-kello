// Arduino Binary Clock with Millis

// Code mostly from Mr. Lunk : https://www.hackster.io/peter-lunk/arduino-24h-binary-clock-with-seconds-17-leds-total-2c2374


int ledPinsMin[] = {2, 3, 4, 5, 6, 7};

int ledPinsHr[] = {8, 9, 10, 11, 12};

// Start time
int countS = 0;   // Seconds
int countM = 50;  // Minutes
int countH = 14;  // Hours

byte countSec;
byte countMin;
byte countHr;
#define nBitsSec sizeof(ledPinsSec)/sizeof(ledPinsSec[0])
#define nBitsMin sizeof(ledPinsMin)/sizeof(ledPinsMin[0])
#define nBitsHr sizeof(ledPinsHr)/sizeof(ledPinsHr[0])


// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store

unsigned long previousMillis = 0;

// constants won't change:
const long interval = 1000;


void setup(void)
{
  for (byte i = 0; i < nBitsMin; i++) {
    pinMode(ledPinsMin[i], OUTPUT);
  }

  for (byte i = 0; i < nBitsHr; i++) {
    pinMode(ledPinsHr[i], OUTPUT);
  }
}

// ----- Main Routine -------------------------------------------------

void loop(void){

unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
  
  countS = (countS + 1);
  if (countS > 59)
  {
    countS = 0;
    countM = (countM + 1);
    if (countM > 59)
    {
      countM = 0;
      countH = (countH + 1);
      if (countH > 23)
      {
        countH = 0;
        countM = 0;
        countS = 0;
      }
    }
  }
}

  dispBinaryMin(countM);
  dispBinaryHr(countH);
}

void dispBinaryMin(byte nMin)
{
  for (byte i = 0; i < nBitsMin; i++) {
    digitalWrite(ledPinsMin[i], nMin & 1);
    nMin /= 2;
  }
}

void dispBinaryHr(byte nHr)
{
  for (byte i = 0; i < nBitsHr; i++) {
    digitalWrite(ledPinsHr[i], nHr & 1);
    nHr /= 2;
  }
}}
