/*
 * ____ HYPSEUS COPYRIGHT NOTICE ____
 *
 * Copyright (C) 2024 DirtBagXon, Rumblebelly5, Dariociceri
 *
 * Dragon's Lair Scoreboard - Esp32 Sketch
 *
 * https://www.youtube.com/watch?v=gd5kwp7HdSc
 *
 * This file is part of HYPSEUS SCOREBOARD
 *
 * HYPSEUS SCOREBOARD is licensed under a Creative Commons 
 * Attribution-NonCommercial-ShareAlike 4.0 International License.
 *
 * You should have received a copy of the license along with this
 * work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.
 *
 * This sketch requires LedControl for the MAX7219 and MAX7221
 *         7-Segment Displays - Author Eberhard Fahle 
 *
 * Hardware:
 *  - 5 x 8x7 segment display (lc1 - lc5)
 */

#include <LedControl.h>

#define BYTE_SIZE 3

typedef struct
{
  char unit;
  char digit;
  char value;
} DigitStruct;

char buffer[BYTE_SIZE];
DigitStruct ds;

LedControl lc1 = LedControl(23, 19, 13, 1); //Punteggio P1
LedControl lc2 = LedControl(23, 19, 12, 1); //Vite P1
LedControl lc3 = LedControl(23, 19, 14, 1); //Punteggio P2
LedControl lc4 = LedControl(23, 19, 27, 1); //Vite P2
LedControl lc5 = LedControl(23, 19, 26, 1); //Crediti

void setup() {
  pinMode(2, OUTPUT);
  digitalWrite(2, 1);

  lc1.shutdown(0, false);
  lc2.shutdown(0, false);
  lc3.shutdown(0, false);
  lc4.shutdown(0, false);
  lc5.shutdown(0, false);

  lc1.setIntensity(0, 8);
  lc2.setIntensity(0, 8);
  lc3.setIntensity(0, 8);
  lc4.setIntensity(0, 8);
  lc5.setIntensity(0, 8);

  //while (true) {
  for (int i = 0; i < 8; i++) {
    lc1.setDigit(0, i, i, false);
    lc2.setDigit(0, i, i + 1, false);
    lc3.setDigit(0, i, i + 2, false);
    lc4.setDigit(0, i, i + 3, false);
    lc5.setDigit(0, i, i + 4, false);
    delay(100);
  }
  delay(1000);
  lc1.clearDisplay(0);
  lc2.clearDisplay(0);
  lc3.clearDisplay(0);
  lc4.clearDisplay(0);
  lc5.clearDisplay(0);
  delay(1000);
  //}

  lc1.clearDisplay(0);
  lc2.clearDisplay(0);
  lc3.clearDisplay(0);
  lc4.clearDisplay(0);
  lc5.clearDisplay(0);

  Serial.begin(115200);

  while (!Serial) {
    digitalWrite(2, 1);
    delay(500);
    digitalWrite(2, 0);
    delay(500);
  }

  Serial.println("Hello Dirk!");
  digitalWrite(2, 0);
}

void loop() {


  if (Serial.available() >= BYTE_SIZE) {
    digitalWrite(2, 1);

    Serial.readBytes(buffer, BYTE_SIZE);

    memcpy(&ds, &buffer, BYTE_SIZE);

    if (ds.unit == 0) {

      switch (ds.digit) {
        case 0x0:
          // PLAYER1_0
          lc1.setChar(0, 6, (byte)ds.value, false);
          break;
        case 0x1:
          // PLAYER1_1
          lc1.setChar(0, 5, (byte)ds.value, false);
          break;
        case 0x2:
          // PLAYER1_2
          lc1.setChar(0, 4, (byte)ds.value, false);
          break;
        case 0x3:
          // PLAYER1_3
          lc1.setChar(0, 3, (byte)ds.value, false);
          break;
        case 0x4:
          // PLAYER1_4
          lc1.setChar(0, 2, (byte)ds.value, false);
          break;
        case 0x5:
          // PLAYER1_5
          lc1.setChar(0, 1, (byte)ds.value, false);
          break;

        case 0x6:
          // PLAYER2_0
          lc3.setChar(0, 6, (byte)ds.value, false);
          break;
        case 0x7:
          // PLAYER2_1
          lc3.setChar(0, 5, (byte)ds.value, false);
          break;
        case 0x8:
          // PLAYER2_2
          lc3.setChar(0, 4, (byte)ds.value, false);
          break;
        case 0x9:
          // PLAYER2_3
          lc3.setChar(0, 3, (byte)ds.value, false);
          break;
        case 0xa:
          // PLAYER2_4
          lc3.setChar(0, 2, (byte)ds.value, false);
          break;
        case 0xb:
          // PLAYER2_5
          lc3.setChar(0, 1, (byte)ds.value, false);
          break;

        case 0xc:
          // LIVES0
          lc2.setChar(0, 3, (byte)ds.value, false);
          break;
        case 0xd:
          // LIVES1
          lc4.setChar(0, 3, (byte)ds.value, false);
          break;

        case 0xe:
          // CREDITS1_0
          lc5.setChar(0, 4, (byte)ds.value, false);
          break;
        case 0xf:
          // CREDITS1_1
          lc5.setChar(0, 3, (byte)ds.value, false);
          break;
      }
    }
  }
  digitalWrite(2, 0);
}
