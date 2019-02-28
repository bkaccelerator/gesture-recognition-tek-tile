void displayText(String input) {
  //display.fillScreen(BLACK);
  //display.setCursor(0, 0);
  //display.fillRect(0,0,display.width(),display.height(), BLACK);
  display.println(input);
  //delay(50);
}

void displayArrow(int x1, int y1, int x2, int y2, int d, uint16_t color) {
  //direction: 0>>right, 1>>left,2>>up,3>>down, 4>>up&right, 5>>down&left,6>>up&left, 7>>down&right, 8>>down&left&up&right
  switch (d) {
    case 0:
      display.drawLine(x1, y1, x2, y2, color);
      display.drawTriangle(x2, y2 + triangleSize, x2, y2 - triangleSize, x2 + triangleSize * 2, y2, color);
      break;
    case 1:
      display.drawLine(x1, y1, x2, y2, color);
      display.drawTriangle(x1, y1 + triangleSize, x1, y1 - triangleSize, x1 - triangleSize * 2, y1, color);
      break;
    case 2:
      display.drawLine(x1, y1, x2, y2, color);
      display.drawTriangle(x1 + triangleSize, y1, x1 - triangleSize, y1, x1, y1 - triangleSize, color);
      break;
    case 3:
      display.drawLine(x1, y1, x2, y2, color);
      display.drawTriangle(x2 + triangleSize, y2, x2 - triangleSize, y2, x2, y2 + triangleSize, color);
      break;
    case 4:
      display.drawLine(x1, y1, x2, y2, color);
      display.drawTriangle(x2 + triangleSize, y2 + triangleSize, x2 - triangleSize, y2 - triangleSize, x2 + triangleSize, y2 - triangleSize, color);
      break;
    case 5:
      display.drawLine(x1, y1, x2, y2, color);
      display.drawTriangle(x2 + triangleSize, y2 + triangleSize, x2 - triangleSize, y2 - triangleSize, x2 - triangleSize, y2 + triangleSize, color);
      break;
    case 6:
      display.drawLine(x1, y1, x2, y2, color);
      display.drawTriangle(x2 + triangleSize, y2 - triangleSize, x2 - triangleSize, y2 + triangleSize, x2 - triangleSize, y2 - triangleSize, color);
      break;
    case 7:
      display.drawLine(x1, y1, x2, y2, color);
      display.drawTriangle(x2 + triangleSize, y2 - triangleSize, x2 - triangleSize, y2 + triangleSize, x2 + triangleSize, y2 + triangleSize, color);
      break;
    case 8:
      display.drawLine(x1, y1, x2, y1, color);
      display.drawLine(x2, y2, x2, y1, color);
      display.drawTriangle(x2 + triangleSize, y2, x2, y2 - triangleSize, x2 - triangleSize, y2, color);
      break;
    default:
      // if nothing else matches, do the default
      // default is optional
      break;
  }

}
void clearArrow(int x1, int y1, int x2, int y2, int d) {
  displayArrow(x1, y1, x2, y2, d, BLACK);
}

void displayGesture(int prev[], int current[],  uint16_t color) {
  clearArrow(prev[0], prev[1], prev[2], prev[3], prev[4]);
  displayArrow(current[0], current[1], current[2], current[3], current[4], color);
}

void changeDisplay(int g) {
  //main function to change different animations according to the gesture
  switch (g) {
    case 0:
      //top left to right
      currentGesture[0] = display.width() / 4;
      currentGesture[1] = display.height() / 4;
      currentGesture[2] = display.width() / 4 * 3;
      currentGesture[3] = display.height() / 4;
      currentGesture[4] = 0;
      displayGesture(prevGesture, currentGesture, GREEN);
      break;
    case 1:
      //top right to left
      currentGesture[0] = display.width() / 4 ;
      currentGesture[1] = display.height() / 4;
      currentGesture[2] = display.width() / 4 * 3 ;
      currentGesture[3] = display.height() / 4;
      currentGesture[4] = 1;
      displayGesture(prevGesture, currentGesture, GREEN);
      break;
    case 2:
      //bottom left to right
      currentGesture[0] = display.width() / 4;
      currentGesture[1] = display.height() / 4 * 3;
      currentGesture[2] = display.width() / 4 * 3;
      currentGesture[3] = display.height() / 4 * 3;
      currentGesture[4] = 0;
      displayGesture(prevGesture, currentGesture, YELLOW);
      break;
    case 3:
      //bottom right to left
      currentGesture[0] = display.width() / 4 ;
      currentGesture[1] = display.height() / 4 * 3;
      currentGesture[2] = display.width() / 4 * 3 ;
      currentGesture[3] = display.height() / 4 * 3;
      currentGesture[4] = 1;
      displayGesture(prevGesture, currentGesture, YELLOW);
      break;
    case 4:
      //left top to bottom
      currentGesture[0] = display.width() / 4 ;
      currentGesture[1] = display.height() / 4 ;
      currentGesture[2] = display.width() / 4  ;
      currentGesture[3] = display.height() / 4 * 3;
      currentGesture[4] = 3;
      displayGesture(prevGesture, currentGesture, RED);
      break;
    case 5:
      //left bottom to top
      currentGesture[0] = display.width() / 4 ;
      currentGesture[1] = display.height() / 4 ;
      currentGesture[2] = display.width() / 4  ;
      currentGesture[3] = display.height() / 4 * 3;
      currentGesture[4] = 2;
      displayGesture(prevGesture, currentGesture, RED);
      break;
    case 6:
      //left top to bottom
      currentGesture[0] = display.width() / 4 * 3 ;
      currentGesture[1] = display.height() / 4 ;
      currentGesture[2] = display.width() / 4 * 3 ;
      currentGesture[3] = display.height() / 4 * 3;
      currentGesture[4] = 3;
      displayGesture(prevGesture, currentGesture, BLUE);
      break;
    case 7:
      //left bottom to top
      currentGesture[0] = display.width() / 4 * 3;
      currentGesture[1] = display.height() / 4 ;
      currentGesture[2] = display.width() / 4  * 3;
      currentGesture[3] = display.height() / 4 * 3;
      currentGesture[4] = 2;
      displayGesture(prevGesture, currentGesture, BLUE);
      break;
    case 8:
      //left bottom to right top
      currentGesture[0] = display.height() / 4 + (display.width() - display.height()) / 2;
      currentGesture[1] = display.height() / 4 * 3 ;
      currentGesture[2] = display.height() / 4  * 3  + (display.width() - display.height()) / 2;
      currentGesture[3] = display.height() / 4 ;
      currentGesture[4] = 4;
      displayGesture(prevGesture, currentGesture, CYAN);
      break;
    case 9:
      //left bottom to right top
      currentGesture[0] = display.height() / 4  * 3  + (display.width() - display.height()) / 2;
      currentGesture[1] = display.height() / 4 ;
      currentGesture[2] = display.height() / 4 + (display.width() - display.height()) / 2;
      currentGesture[3] = display.height() / 4 * 3 ;
      currentGesture[4] = 5;
      displayGesture(prevGesture, currentGesture, CYAN);
      break;
    case 10:
      //right bottom to left top
      currentGesture[0] = display.height() / 4  * 3  + (display.width() - display.height()) / 2;
      currentGesture[1] = display.height() / 4 * 3 ;
      currentGesture[2] = display.height() / 4 + (display.width() - display.height()) / 2;
      currentGesture[3] = display.height() / 4  ;
      currentGesture[4] = 6;
      displayGesture(prevGesture, currentGesture, CYAN);
      break;
    case 11:
      //right bottom to left top
      currentGesture[0] = display.height() / 4 + (display.width() - display.height()) / 2;
      currentGesture[1] = display.height() / 4  ;
      currentGesture[2] = display.height() / 4  * 3  + (display.width() - display.height()) / 2;
      currentGesture[3] = display.height() / 4 * 3 ;
      currentGesture[4] = 7;
      displayGesture(prevGesture, currentGesture, CYAN);
      break;
    case 12:
      //clockwise
      displayLineSwipeA();
      break;
    case 13:
      //counterclockwise
      displayLineSwipeB();
      break;
    case 14:
      HorizontalStripes(WHITE);
      break;
    case 15:
      HorizontalStripes(MAGENTA);
      break;
    case 16:
      HorizontalStripes(CYAN);
      break;
    case 17:
      HorizontalStripes(YELLOW);
      break;
    case 18:
      VerticalArrows(10, WHITE);
      break;
    case 19:
      VerticalArrows(10, MAGENTA);
      break;
    case 20:
      diagonalCircles(12, WHITE);
      break;
    case 22:
      //bottom left to right to top right
      currentGesture[0] = display.width() / 4;
      currentGesture[1] = display.height() / 4 * 3;
      currentGesture[2] = display.width() / 4 * 3;
      currentGesture[3] = display.height() / 4 ;
      currentGesture[4] = 8;
      displayGesture(prevGesture, currentGesture, YELLOW);
      break;
    case 100:
      //full circle
      displayFullCircle();
      break;
    default:
      // if nothing else matches, do the default
      // default is optional
      break;

  }

  prevGesture[0] = currentGesture[0];
  prevGesture[1] = currentGesture[1];
  prevGesture[2] = currentGesture[2];
  prevGesture[3] = currentGesture[3];
  prevGesture[4] = currentGesture[4];
}

void displayAllTouched(uint16_t color1, uint16_t color2) {
  testfastlines(color1, color2);
  delay(500);
  display.fillScreen(BLACK);
}


void displayFullCircle() {
  testroundrects();
  delay(500);
  display.fillScreen(BLACK);
}

void testroundrects() {

  int color = 100;
  int i;
  int t;
  for (t = 0 ; t <= 4; t += 1) {
    int x = 0;
    int y = 0;
    int w = display.width();
    int h = display.height();
    for (i = 0 ; i <= 24; i += 1) {
      display.drawRoundRect(x, y, w, h, 5, color);
      x += 2;
      y += 3;
      w -= 4;
      h -= 6;
      color += 1100;
    }
    color += 100;
  }
}

void diagonalCircles(uint8_t radius, uint16_t color) {
  for (int16_t x = radius; x < display.width() - 3 * radius; x += radius * 1.5) {
    int y = x;
    display.drawCircle(x + 1.5 * radius, y, radius, color);
    y = x - radius;
    delay(25);
  }
  delay(1500);
  display.fillScreen(BLACK);
}

void HorizontalStripes(uint16_t color) {
  for (int16_t x = 0; x < display.width(); x += 5) {
    display.drawFastVLine(x, (display.height() - 1) / 2, 50, color);
  }
  delay(1500);
  display.fillScreen(BLACK);
}

void VerticalArrows(uint8_t sideSize, uint16_t color) {
  int y = sideSize;
  for (int16_t y = sideSize; y < display.height() + sideSize / 2; y += sideSize) {
    for (int16_t x = sideSize; x < display.width() - sideSize * 2; x = x + 2 * sideSize + 5) {
      int z = y - sideSize + 5;
      display.drawTriangle(x, z, x + sideSize * 2, z, x + sideSize, y, color);
      delay(25);
    }
  }
  delay(1500);
  display.fillScreen(BLACK);
}

void displayLineSwipeA() {
  testfastlines(RED, BLUE);
  delay(500);
  display.fillScreen(BLACK);
}

void displayLineSwipeB() {
  testfastlines(GREEN, YELLOW);
  delay(500);
  display.fillScreen(BLACK);
}

void testfastlines(uint16_t color1, uint16_t color2) {

  for (int16_t y = 0; y < display.height() - 1; y += 5) {
    display.drawFastHLine(0, y, display.width() - 1, color1);
  }
  for (int16_t x = 0; x < display.width() - 1; x += 5) {
    display.drawFastVLine(x, 0, display.height() - 1, color2);
  }
}

