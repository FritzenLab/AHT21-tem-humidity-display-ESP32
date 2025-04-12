#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
//#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>
#include <Adafruit_AHTX0.h>

Adafruit_AHTX0 aht;

// For the breakout board, you can use any 2 or 3 pins.
// These pins will also work for the 1.8" TFT shield.
#define TFT_CS        7
#define TFT_RST        10 // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC         0


// OPTION 1 (recommended) is to use the HARDWARE SPI pins, which are unique
// to each board and not reassignable. For Arduino Uno: MOSI = pin 11 and
// SCLK = pin 13. This is the fastest mode of operation and is required if
// using the breakout board's microSD card.

// For 1.44" and 1.8" TFT with ST7735 use:
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);


void setup(void) {
  Serial.begin(115200);
  Serial.print(F("Hello! ST77xx TFT Test"));
  

  // Use this initializer if using a 1.8" TFT screen:
  tft.initR(INITR_BLACKTAB);      // Init ST7735S chip, black tab

  Serial.println(F("Initialized"));

  uint16_t time = millis();
  tft.fillScreen(ST77XX_BLACK);
  

  // large block of text
  tft.setTextSize(1);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(5, 30);
  tft.setTextColor(ST77XX_GREEN);
  tft.println("Electronics-Lab");
  delay(1000);
  tft.setCursor(5, 60);
  Serial.println("Adafruit AHT10/AHT20 demo!");

  if (! aht.begin()) {
    Serial.println("Could not find AHT? Check wiring");
    while (1) delay(10);
  }
  Serial.println("AHT10 or AHT20/21 found");

}

void loop() {
  
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data
  
  tft.setTextSize(2);
  tft.setCursor(20, 60);
  tft.setTextColor(ST77XX_WHITE);
  //tft.println("     ");
  //tft.setTextColor(39321);
  tft.print(millis() / 1000);
  tft.setTextSize(1);
  tft.println(" seconds");
  tft.setCursor(20, 80);
  tft.print("AHT21 = ");
  tft.setTextSize(1);
  tft.print(temp.temperature);
  tft.println(" oC");
  tft.setCursor(20, 100);
  tft.print("RH = ");
  tft.setCursor(60, 100);
  tft.print(humidity.relative_humidity);
  tft.println(" %");
  delay(1000);
  testdrawrects(ST77XX_BLACK);
  //delay(5);
}

void testdrawrects(uint16_t color) {
  
  tft.fillRect(5, 50, 100, 60, color);
  tft.drawRect(5, 50, 100, 60, color);
  
}