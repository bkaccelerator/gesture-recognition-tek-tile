
///cap sensor setup
#include <Wire.h>
#include "Adafruit_MPR121.h"

Adafruit_MPR121 cap = Adafruit_MPR121();

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;

int pinTopLeft = 5;
int pinTopRight = 2;
int pinBottomLeft = 11;
int pinBottomRight = 0;

//gesture checking
int gestureArray[10] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int gestureCounter = 0;
bool timerState = 0;
long timer = 0;
int TIMER_THRESHOLD = 700;

//samples
int topLeftToRight[2] = {pinTopLeft, pinTopRight};
int bottomLeftToRight[2] = {pinBottomLeft, pinBottomRight};


//OLED setup
// You can use any (4 or) 5 pins
#define sclk 13
#define mosi 11
#define cs   10
#define rst  9
#define dc   8


// Color definitions
#define  BLACK           0x0000
#define BLUE            0x001F
#define RED             0xF800
#define GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0
#define WHITE           0xFFFF

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1331.h>
#include <SPI.h>

// Option 1: use any pins but a little slower
Adafruit_SSD1331 display = Adafruit_SSD1331(cs, dc, mosi, sclk, rst);

float p = 3.1415926;


void setup() {
  Serial.begin(9600);
  //display.begin();
  //  display.fillScreen(BLACK);
  //
  //  display.setCursor(0, 0);
  //  display.print("Begin");
  //  delay(50);

  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    display.print("MPR121 not found, check wiring?");
    while (1);
  }

  Serial.println("MPR121 found!");
  //display.print("MPR121 found!");

}

void loop() {
  checkGuesture();
}

void checkGuesture() {
  // Get the currently touched pads
  currtouched = cap.touched();

  for (uint8_t i = 0; i < 12; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      //Serial.print(i); Serial.println(" touched");
      String t = i + " touched";
      timerState = 0;
      timer = 0;
    }

    // if it *was* touched and now *isnt*, alert!
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
      //Serial.print(i); Serial.println(" released");
      String t = i + " released";

      //if it's not the first pad touched
      if (gestureArray > 0) {
        if (gestureArray[gestureCounter - 1] != i) {
          gestureArray[gestureCounter] = i;
          gestureCounter ++;
        }
      } else {
        gestureArray[gestureCounter] = i;
        gestureCounter ++;
      }

      timerState = 1;
    }
  }

  if (timerState) {
    timer ++;
  }

  if (timer > TIMER_THRESHOLD && gestureCounter > 0) {

    //compare the gesture 
    if (compareArray(gestureArray, topLeftToRight, gestureCounter)) {
      Serial.println("top left to right");
    }else if (compareArray(gestureArray, bottomLeftToRight, gestureCounter)) {
      Serial.println("bottom left to right");
    }


    //reset the gesture array
    for (int i = 0; i < gestureCounter; i ++) {
      gestureArray[i] = -1;
    }
    gestureCounter = 0;
    timer = 0;
  }
  // reset our state
  lasttouched = currtouched;

  // comment out this line for detailed data from the sensor!
  return;

  // debugging info, what
  Serial.print("\t\t\t\t\t\t\t\t\t\t\t\t\t 0x"); Serial.println(cap.touched(), HEX);
  Serial.print("Filt: ");
  for (uint8_t i = 0; i < 12; i++) {
    Serial.print(cap.filteredData(i)); Serial.print("\t");
  }
  Serial.println();
  Serial.print("Base: ");
  for (uint8_t i = 0; i < 12; i++) {
    Serial.print(cap.baselineData(i)); Serial.print("\t");
  }
  Serial.println();

  // put a delay so it isn't overwhelming
  //delay(100);
}

bool compareArray(int a[], int b[], int n) {
  if(sizeof(b) != n){
    return false;
  }
  for (int i = 0; i < n; i ++) {
    if (a[i] ==  b[i]) {
      //match
    } else {
      //not matching
      return false;
    }
  }
  return true;
}

void displayText(String input) {
  //display.fillScreen(BLACK);
  //display.setCursor(0, 0);
  //display.fillRect(0,0,display.width(),display.height(), BLACK);
  display.println(input);
  //delay(50);
}


