#include <Arduino.h>
#include <string.h>
#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>
#include <Adafruit_TFTLCD.h>
#include "SparkFun_APDS9960.h"
#include <Wire.h>

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF
#define ORANGE 0xFD20
#define GREENYELLOW 0xAFE5
#define NAVY 0x000F
#define DARKGREEN 0x03E0
#define DARKCYAN 0x03EF
#define MAROON 0x7800
#define PURPLE 0x780F
#define OLIVE 0x7BE0
#define LIGHTGREY 0xC618
#define DARKGREY 0x7BEF
#define BRANCO 0xFFFF
String textoLCD = "";
//CS, CD, WR, RD, RESET
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

SparkFun_APDS9960 apds = SparkFun_APDS9960();
void handleGesture();
void escreveTexto(uint16_t color, const char str[], uint8_t s);
void setup()
{
  // Wire.begin();
  Serial.begin(115200);
  Serial.println();
  Serial.println(F("--------------------------------"));
  Serial.println(F("SparkFun APDS-9960 - GestureTest"));
  Serial.println(F("--------------------------------"));

  if (apds.init())
  {
    Serial.println(F("APDS-9960 initialization complete"));
    textoLCD = "APDS-9960 initialization complete";
  }
  else
  {
    Serial.println(F("Something went wrong during APDS-9960 init!"));
    textoLCD = "Something went wrong during APDS-9960 init!";
  }

  // Start running the APDS-9960 gesture sensor engine
  if (apds.enableGestureSensor(true))
  {
    Serial.println(F("Gesture sensor is now running"));
    textoLCD = "Gesture sensor is now running";
  }
  else
  {
    Serial.println(F("Something went wrong during gesture sensor init!"));
    textoLCD = "Something went wrong during gesture sensor init!";
  }

  Serial.println(F("TFT LCD test"));
#ifdef USE_ADAFRUIT_SHIELD_PINOUT
  Serial.println(F("Using Adafruit 2.4\" TFT Arduino Shield Pinout"));
#else
  Serial.println(F("Using Adafruit 2.4\" TFT Breakout Board Pinout"));
#endif
  Serial.print("TFT size is ");
  Serial.print(tft.width());
  Serial.print("x");
  Serial.println(tft.height());
  tft.reset();
  uint16_t identifier = tft.readID();
  if (identifier == 0x9325)
  {
    Serial.println(F("Found ILI9325 LCD driver"));
  }
  else if (identifier == 0x9328)
  {
    Serial.println(F("Found ILI9328 LCD driver"));
  }
  else if (identifier == 0x7575)
  {
    Serial.println(F("Found HX8347G LCD driver"));
  }
  else if (identifier == 0x9341)
  {
    Serial.println(F("Found ILI9341 LCD driver"));
  }
  else if (identifier == 0x8357)
  {
    Serial.println(F("Found HX8357D LCD driver"));
  }
  else
  {
    Serial.print(F("Unknown LCD driver chip: "));
    Serial.println(identifier, HEX);
    Serial.println(F("If using the Adafruit 2.4\" TFT Arduino shield, the line:"));
    Serial.println(F("  #define USE_ADAFRUIT_SHIELD_PINOUT"));
    Serial.println(F("should appear in the library header (Adafruit_TFT.h)."));
    Serial.println(F("If using the breakout board, it should NOT be #defined!"));
    Serial.println(F("Also if using the breakout, double-check that all wiring"));
    Serial.println(F("matches the tutorial."));
    return;
  }
  tft.begin(identifier);
  escreveTexto(BLACK, "Ricardo", 4);
}

int proximity = 0;
int r = 0, g = 0, b = 0;
unsigned long lastUpdate = 0;

void escreveTexto(uint16_t color, const char str[], uint8_t s)
{
  tft.fillScreen(WHITE);
  tft.setRotation(90);
  tft.setTextColor(color);
  tft.setCursor(10, 180);
  tft.setTextSize(s);
  tft.println(str);
  delay(200);
}

void loop()
{
  handleGesture();
  int n_textoLCD = textoLCD.length();
  char textToWrite[n_textoLCD + 1];
  strcpy(textToWrite, textoLCD.c_str());
  // escreveTexto(BLACK, textToWrite, 4);
  Serial.println(textToWrite);
  delay(500);
}

void handleGesture()
{
  if (apds.isGestureAvailable())
  {
    switch (apds.readGesture())
    {
    case DIR_UP:
      textoLCD = "UP";
      // Serial.println(textoLCD);
      delay(500);
      break;
    case DIR_DOWN:
      textoLCD = "DOWN";
      // Serial.println(textoLCD);
      delay(500);
      break;
    case DIR_LEFT:
       textoLCD = "LEFT";
      // Serial.println(textoLCD);
      delay(500);
      break;
    case DIR_RIGHT:
       textoLCD = "RIGHT";
      // Serial.println(textoLCD);
      delay(500);
      break;
    case DIR_NEAR:
      textoLCD = "NEAR";
      Serial.println(textoLCD);
      delay(500);
      break;
    case DIR_FAR:
      textoLCD = "FAR";
      Serial.println(textoLCD);
      delay(500);
      break;
    default:
      textoLCD = "NONE";
      Serial.println(textoLCD);
      delay(500);
    }
  }
 
}