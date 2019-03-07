# Hardware

## Materials

* [Adafruit Metro Mini 328](https://www.adafruit.com/product/2590)
* [Adafruit 12-Key Capacitive Touch Sensor Breakout - MPR121](https://www.adafruit.com/product/1982)
* [OLED Breakout Board - 16-bit Color 0.96" w/microSD holder](https://www.adafruit.com/product/684)

## Connections

To the Arduino:

* **D8** to **OLED D/C**
* **D9** to **OLED RST**
* **D10** to **OLED OCS**
* **D11** to **OLED MOSI**
* **D13** to **OLED SCK**
* **A4** to **Cap Sense SDA**
* **A5** to **Cap Sense SCL**

To the fabric:

* **Upper left conductive panel** to **capacitive sense pin 5**
* **Upper right conductive panel** to **capacitive sense pin 2**
* **Lower left conductive panel** to **capacitive sense pin 11**
* **Lower right conductive panel** to **capacitive sense pin 0**

