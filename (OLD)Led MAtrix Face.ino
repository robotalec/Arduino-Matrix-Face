#include <FastLED.h>        //https://github.com/FastLED/FastLED
#include <LEDMatrix.h>      //https://github.com/Jorgen-VikingGod/LEDMatrix
//#include "SR04.h"
//#define TRIG_PIN 12
//#define ECHO_PIN 11
//SR04 sr04 = SR04(ECHO_PIN, TRIG_PIN);
//long a;

const int SW_pin = 2; // digital pin connected to switch output
const int X_pin = 0; // analog pin connected to X output
const int Y_pin = 1; // analog pin connected to Y output

// Change the next defines to match your matrix type and size
#define DATA_PIN            6

#define COLOR_ORDER         GRB
#define CHIPSET             WS2812B

// initial matrix layout (to get led strip index by x/y)
#define MATRIX_WIDTH        32
#define MATRIX_HEIGHT       8
#define MATRIX_TYPE         VERTICAL_ZIGZAG_MATRIX
#define MATRIX_SIZE         (MATRIX_WIDTH*MATRIX_HEIGHT)
#define NUMPIXELS           MATRIX_SIZE

// create our matrix based on matrix definition
cLEDMatrix<MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_TYPE> leds;
int buttonApin = 9;
int buttonBpin = 8;
int buttonCpin = 7;
int buttonDpin = 10;
int testcounter;

uint8_t hue;
int16_t counter;
bool eyeMove = true;
int countermax = 20;
void setup()
{
  pinMode(buttonApin, INPUT_PULLUP);
  pinMode(buttonBpin, INPUT_PULLUP);
  pinMode(buttonCpin, INPUT_PULLUP);
  pinMode(buttonDpin, INPUT_PULLUP);
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  // initial LEDs
  FastLED.addLeds<CHIPSET, DATA_PIN, COLOR_ORDER>(leds[0], leds.Size()).setCorrection(TypicalSMD5050);
  FastLED.setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(8);
  FastLED.clear(true);
  delay(500);
  FastLED.showColor(CRGB::Red);
  delay(1000);
  FastLED.showColor(CRGB::Green);
  delay(1000);
  FastLED.showColor(CRGB::Blue);
  delay(1000);
  FastLED.showColor(CRGB::White);
  delay(1000);
  FastLED.clear(true);
  Serial.begin(9600);

  hue = 0;
  counter = 0;

}
int brightness = 12;
int lookDir = 7;
//up0
//down1
//left2
//right3
//upleft4
//upright5
//downleft6
//downright7
//center8
int mouthState = 0;
int counterMouth = 0;
int lastStateC = HIGH;
int currentStateC;
int lastStateD = HIGH;
int currentStateD;
int browState = 0;
int pupilCount = 0;
int pupilMax = 20;
int pupilDefaultCounter;



void loop()
{

  if (testcounter == 10000){
      FastLED.setBrightness(brightness);
  FastLED.clear(true);
  delay(500);
  FastLED.showColor(CRGB::Red);
  delay(1000);
  FastLED.showColor(CRGB::Green);
  delay(1000);
  FastLED.showColor(CRGB::Blue);
  delay(1000);
  FastLED.showColor(CRGB::White);
  delay(1000);
  FastLED.clear(true);
  testcounter = 0;
  }
  

testcounter++;
  int16_t sx, sy, x, y;
  uint8_t h;

  FastLED.clear();
  pupilCount++;
  counter++;
  pupilDefaultCounter++;
  h = hue;
  //FastLED.showColor(CRGB(153,153,255));
  //leds.DrawFilledRectangle(0,0,32,8,CRGB(0,0,255));
  currentStateC = digitalRead(buttonCpin);
  currentStateD = digitalRead(buttonDpin);
  leds.DrawCircle(3, 5, 2, CHSV(h, 255, 255));
  // leds.DrawLine(3, 5, 3, 5, CRGB::Purple);
  eyeL(lookDir);
  leds.DrawCircle(28, 5, 2, CHSV(h, 255, 255));
  //leds.DrawLine(28, 5, 28, 5, CRGB(255, 0, 255));
  eyeR(lookDir);
  mouth(mouthState);
  eyebrows(browState);

  //delay(400);

  if (counter >= countermax) {
    //lookDir = "center";
    leds.DrawCircle(3, 5, 2, CHSV(0, 0, 0));
    leds.DrawLine(3, 5, 3, 5, CRGB::Black);
    leds.DrawLine(1, 5, 5, 5, CRGB::Red);
    leds.DrawCircle(28, 5, 2, CHSV(0, 0, 0));
    leds.DrawLine(28, 5, 28, 5, CRGB(0, 0, 0));
    leds.DrawLine(26, 5, 30, 5, CRGB::Red);
    delay(50);
    counter = 0;
    countermax = random(10, 50);
  }
  if (pupilCount >= pupilMax){
    pupilMax = random(50,300);
    pupilCount = 0;
    pupilDefaultCounter = 0;
    lookDir = random(0,9);
    
  }
  if(pupilDefaultCounter >= 10){
    lookDir = 8;
  }
  


  if (digitalRead(buttonApin) == LOW) {
    Serial.print(brightness);
    brightness--;
    FastLED.setBrightness(brightness);
    delay(30);


  }
  if (digitalRead(buttonBpin) == LOW) {
    Serial.print(brightness);
    brightness++;
    FastLED.setBrightness(brightness);
    delay(30);


  }
  if (currentStateC == LOW && lastStateC == HIGH ) {


    if (counterMouth <= 3) {
      mouthState++;
      counterMouth++;
      Serial.print(mouthState);
    } else {
      counterMouth = 0;
      mouthState = 0;
    }

  }
    if (currentStateD == LOW && lastStateD == HIGH ) {


    if (browState < 3) {
        browState++;
      Serial.print(mouthState);
    } else {
      browState = 0;
    }

  }

  lastStateC = currentStateC;
  lastStateD = currentStateD;
  FastLED.show();
}

void eyeL(int leftLook) {
  if (leftLook == 0) {
    leds.DrawLine(3, 5, 3, 5, CRGB::Black);
    leds.DrawLine(3, 4, 3, 4, CRGB::Purple);
  } else if (leftLook == 1) {
    leds.DrawLine(3, 5, 3, 5, CRGB::Black);
    leds.DrawLine(3, 6, 3, 6, CRGB::Purple);
  } else if (leftLook == 2) {
    leds.DrawLine(3, 5, 3, 5, CRGB::Black);
    leds.DrawLine(2, 5, 2, 5, CRGB::Purple);
  } else   if (leftLook == 3) {
    leds.DrawLine(3, 5, 3, 5, CRGB::Black);
    leds.DrawLine(4, 5, 4, 5, CRGB::Purple);
  } else   if (leftLook == 4) {
    leds.DrawLine(3, 5, 3, 5, CRGB::Black);
    leds.DrawLine(2, 4, 2, 4, CRGB::Purple);
  } else   if (leftLook == 5) {
    leds.DrawLine(3, 5, 3, 5, CRGB::Black);
    leds.DrawLine(4, 4, 4, 4, CRGB::Purple);
  } else  if (leftLook == 6) {
    leds.DrawLine(3, 5, 3, 5, CRGB::Black);
    leds.DrawLine(2, 6, 2,6, CRGB::Purple);
  } else   if (leftLook == 7) {
    leds.DrawLine(3, 5, 3, 5, CRGB::Black);
    leds.DrawLine(4, 6, 4, 6, CRGB::Purple);
  } else if (leftLook == 8) {
    leds.DrawLine(3, 5, 3, 5, CRGB::Purple);
  }
}
void eyeR(int rightLook) {
  if (rightLook==0) {
    leds.DrawLine(28, 4, 28, 4, CRGB::Purple);
    leds.DrawLine(28, 5, 28, 5, CRGB(0, 0, 0));
  } else if (rightLook==1) {
    leds.DrawLine(28, 6, 28, 6, CRGB::Purple);
    leds.DrawLine(28, 5, 28, 5, CRGB(0, 0, 0));
  } else if (rightLook==2) {
    leds.DrawLine(27, 5, 27, 5, CRGB::Purple);
    leds.DrawLine(28, 5, 28, 5, CRGB(0, 0, 0));
  } else if (rightLook==3) {
    leds.DrawLine(29, 5, 29, 5, CRGB::Purple);
    leds.DrawLine(28, 5, 28, 5, CRGB(0, 0, 0));
  } else if (rightLook==4) {
    leds.DrawLine(27, 4, 27, 4, CRGB::Purple);
    leds.DrawLine(28, 5, 28, 5, CRGB(0, 0, 0));
  } else if (rightLook==5) {
    leds.DrawLine(29, 4, 29, 4, CRGB::Purple);
    leds.DrawLine(28, 5, 28, 5, CRGB(0, 0, 0));
  } else if (rightLook==6) {
    leds.DrawLine(27, 6, 27, 6, CRGB::Purple);
    leds.DrawLine(28, 5, 28, 5, CRGB(0, 0, 0));
  } else if (rightLook==7) {
    leds.DrawLine(29, 6, 29, 6, CRGB::Purple);
    leds.DrawLine(28, 5, 28, 5, CRGB(0, 0, 0));
  } else if (rightLook==8) {
    leds.DrawLine(28, 5, 28, 5, CRGB::Purple);
  }

}
void mouth(int state) {

  if (state == 0) {
    leds.DrawLine(9, 7, 22, 7, CRGB::White);
    leds.DrawLine(7, 5, 9, 7, CRGB::White);

  } else if (state == 1) {
    leds.DrawCircle(16, 5, 2, CRGB::White);
  } else if (state == 2) {
    leds.DrawCircle(16, 8, 5, CRGB::White);
  } else if (state == 3) {
    leds.DrawLine(14, 7, 18, 7, CRGB::White);
    leds.DrawLine(12, 4, 12, 5, CRGB::White);
    leds.DrawLine(12, 5, 14, 7, CRGB::White);
    leds.DrawLine(20, 4, 20, 5, CRGB::White);
    leds.DrawLine(20, 5, 18, 7, CRGB::White);
  }
  else{
    leds.DrawLine(9, 7, 22, 7, CRGB::White);
  }

}
void eyebrows(int state) {
  if (state == 0) {
    leds.DrawLine(26, 1, 30, 1, CRGB::White);
    leds.DrawLine(1, 1, 5, 1, CRGB(255, 255, 255));
    delay(200);

  } else if (state == 1) {
        if (eyeMove == true) {
      delay(200);
      leds.DrawLine(1, 1, 5, 1, CRGB(0, 0, 0));
      leds.DrawLine(1, 2, 5, 2, CRGB(255, 255, 255));
      leds.DrawLine(26, 1, 30, 1, CRGB::White);
      leds.DrawLine(26, 2, 30, 2, CRGB::Black);
  
      eyeMove = false;
    } else {
      delay(200);
      leds.DrawLine(1, 2, 5, 2, CRGB(0, 0, 0));
      leds.DrawLine(1, 1, 5, 1, CRGB(255, 255, 255));
      leds.DrawLine(26, 2, 30, 2, CRGB::White);
      leds.DrawLine(26, 1, 30, 1, CRGB::Black);
  
      eyeMove = true;
    }

  } else if (state == 2) {
    delay(200);
    leds.DrawLine(1,0,5,2,CRGB::White);
    leds.DrawLine(30,0,26,2,CRGB::White);

  }
  else{
    delay(200);
  leds.DrawLine(1,2,5,0,CRGB::White);
  leds.DrawLine(30,2,26,0,CRGB::White);
  }
}
