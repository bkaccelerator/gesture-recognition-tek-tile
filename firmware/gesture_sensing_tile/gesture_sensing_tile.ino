#include <Wire.h>
#include "Adafruit_MPR121.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1331.h>
#include <SPI.h>

#include "colors.h"

// OLED screen: https://www.adafruit.com/product/684
const int SCREEN_WIDTH = 96;
const int SCREEN_HEIGHT = 64;

// Time within which a touch must be completed
const int TOUCH_RESET_TIME = 3000;

// OLED display
const int PIN_OLED_SCLK = 13;
const int PIN_OLED_MOSI = 11;
const int PIN_OLED_CS = 10;
const int PIN_OLED_RESET = 9;
const int PIN_OLED_DC = 8;

// MPR121 cap sense pins that correspond to each conductive knit panel
const int PIN_TOP_LEFT = 5;
const int PIN_TOP_RIGHT = 2;
const int PIN_BOTTOM_LEFT = 11;
const int PIN_BOTTOM_RIGHT = 0;

Adafruit_SSD1331 display = Adafruit_SSD1331(PIN_OLED_CS, PIN_OLED_DC, PIN_OLED_MOSI, PIN_OLED_SCLK, PIN_OLED_RESET);
Adafruit_MPR121 cap = Adafruit_MPR121();

typedef struct Touch {
  int x;
  int y;
} Touch;

int gestureStage = 0;
Touch gesture[2];

void setup() {
  Serial.begin(115200);

  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    // TODO display error symbol & message on display
    while (1);
  }

  Serial.println("Demo setup, starting...");
}

// Returns true if there is a single touch, and false otherwise
// If there is a touch then the touch struct passed in is filled with its info
bool getTouch(Touch& theTouch) {
  uint16_t capState = cap.touched();

  bool topLeftTouched = (1 << PIN_TOP_LEFT) & capState > 0;
  bool topRightTouched = (1 << PIN_TOP_RIGHT) & capState > 0;
  bool bottomLeftTouched = (1 << PIN_BOTTOM_LEFT) & capState > 0;
  bool bottomRightTouched = (1 << PIN_BOTTOM_RIGHT) & capState > 0;

  int touchCount = 0;

  touchCount += topLeftTouched ? 1 : 0;
  touchCount += topRightTouched ? 1 : 0;
  touchCount += bottomLeftTouched ? 1 : 0;
  touchCount += bottomRightTouched ? 1 : 0;

  if (touchCount == 0) {
    // No touch
    return false;
  } else if (touchCount == 1) {
    if (topLeftTouched) {
      theTouch.x = -1;
      theTouch.y = -1;
    } else if (topRightTouched) {
      theTouch.x = 1;
      theTouch.y = -1;
    } else if (bottomLeftTouched) {
      theTouch.x = -1;
      theTouch.y = 1;
    } else if (bottomRightTouched) {
      theTouch.x = 1;
      theTouch.y = 1;
    }

    return true;
  } else {
    return false;
  }
}

void drawArrow(int x1, int y1, int x2, int y2) {
  // TODO draw arrow from (x1, y1) to (x2, y2)
}

void handleGesture(Touch first, Touch second) {
  int tileSize = (SCREEN_HEIGHT - 4) / 4;
  int gridSize = tileSize * 2;

  int gridLeft = SCREEN_WIDTH / 2 - gridSize / 2;
  int gridTop = SCREEN_HEIGHT / 2 - gridSize / 2;
  int gridRight = gridLeft + gridSize;
  int gridBottom = gridTop + gridSize;

  display.fillScreen(BLACK);

  // Draw the grid outline
  display.drawLine(gridLeft, gridTop, gridRight, gridTop, WHITE); // top
  display.drawLine(gridRight, gridTop, gridRight, gridBottom, WHITE); // right
  display.drawLine(gridRight, gridBottom, gridLeft, gridBottom, WHITE); // bottom
  display.drawLine(gridLeft, gridBottom, gridLeft, gridTop, WHITE); // left

  // Draw grid lines
  display.drawLine(gridLeft + tileSize, gridTop, gridLeft + tileSize, gridBottom, WHITE); // vertical
  display.drawLine(gridLeft, gridTop + tileSize, gridRight, gridTop + tileSize, WHITE); // horizontal

  // Draw gesture
  int gridCenterX = gridLeft + tileSize;
  int gridCenterY = gridTop + tileSize;

  int arrowStartX = gridCenterX + first.x * tileSize / 2;
  int arrowStartY = gridCenterY + first.y * tileSize / 2;
  int arrowEndX = gridCenterX + second.x * tileSize / 2;
  int arrowEndY = gridCenterY + second.y * tileSize / 2;

  drawArrow(arrowStartX, arrowStartY, arrowEndX, arrowEndY);
}

void loop() {
  static Touch firstTouch;
  static bool gestureStarted = false;
  static long gestureStartedTime;

  // Sense touches
  Touch touch;
  bool isTouched = getTouch(touch);

  // Manage gesture state
  if (isTouched && !gestureStarted) {
    if (!gestureStarted) {
      // Start the gesture
      gestureStarted = true;
      gestureStartedTime = millis();
      firstTouch = touch;
    } else {
      if (firstTouch.x == touch.x && firstTouch.y == touch.y) {
        // Still touching the same panel, ignore
      } else {
        // Gesture completed!
        handleGesture(firstTouch, touch);
      }
    }
  }

  // If enough time passes without the gesture being completed then consider it
  // incomplete and reset
  if (gestureStarted && (millis() - gestureStartedTime > TOUCH_RESET_TIME)) {
    gestureStarted = false;
  }

  delay(10);
}
