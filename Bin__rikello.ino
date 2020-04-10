// Arduino Binary Clock with Millis and Buttons

int ledPinsMin[] = {13, 12, 11, 10, 9, 8};   //minuutti ledit

int ledPinsHr[] = {14, 15, 16, 17, 18};   // tunti ledit

int statusLed = 7;            // status ledi
int statusMode = LOW;

int button1 = 2;              //nappi 1, jolla vaihdetaan statusta
int buttonRead1 = HIGH;
long button1time = 0;         // viimeinen napinpaino aika
long debounce = 200;          // häiriö jutun odotusaika

int button2= 3;               // nappi 2, ajan muuttamista varten
int buttonRead2 = HIGH;
long button2time = 0;         // viimeinen napinpaino aika


int countS = 0;   // Seconds
int countM = 30;  // Minutes
int countH = 8;  // Hours

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
  pinMode(2, INPUT_PULLUP);       //Napit on pull_uppeina
  pinMode(3, INPUT_PULLUP);
  pinMode(statusLed, OUTPUT);
  
  for (byte i = 0; i < nBitsMin; i++) {
    pinMode(ledPinsMin[i], OUTPUT);
  }

  for (byte i = 0; i < nBitsHr; i++) {
    pinMode(ledPinsHr[i], OUTPUT);
  }
  Serial.begin(9600);             //vianetsintää varten
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

readButton1();  //katotaan nappi 1

if(statusMode == HIGH) {   // jos ollaan konfiguraatiossa, katotaan nappi 2
  readButton2();
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
}

void readButton1() {   // toggle buttonit on vaikeita!!!
  
if(digitalRead(button1) != buttonRead1 && millis() - button1time > debounce) {
  
  statusMode = !statusMode;
  digitalWrite(statusLed, statusMode);
  button1time = millis();
  }
}

void readButton2() {   // toggle buttonit on vaikeita!!!
  
if(digitalRead(button2) != buttonRead2 && millis() - button2time > debounce) {
  
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
  button2time = millis();
  }
}
