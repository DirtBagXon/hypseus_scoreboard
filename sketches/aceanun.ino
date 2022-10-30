/*
 * ____ HYPSEUS COPYRIGHT NOTICE ____
 *
 * Copyright (C) 2022 DirtBagXon, Rumblebelly5
 *
 * Space Ace Scoreboard & Annunciator - Arduino Sketch
 *
 * https://www.youtube.com/watch?v=LukUfrBfwL8
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
 *  - 3 x 8x7 segment display modules (lc1 - lc3)
 *  - 1 x 8x8 matrix module (lc4)
 *
 */

#include <LedControl.h>

#define BYTE_SIZE 3

typedef struct
{
    char unit;
    char digit;
    char value;
} DigitStruct;

const uint64_t ANNUNCIATOR[] PROGMEM = {
    0xc366667e66663c18,
    0x000042663c180000,
    0x42663c1842663c18,
    0x0000000000000000
};

char buffer[BYTE_SIZE];
uint64_t image = 0;
DigitStruct ds;

LedControl lc1 = LedControl(7, 6, 5, 1);    // player 1
LedControl lc2 = LedControl(8, 9, 10, 1);   // player 2
LedControl lc3 = LedControl(4, 3, 2, 1);    // credits
LedControl lc4 = LedControl(11, 12, 13, 1); // 8x8 matrix

void setup() {

    lc1.shutdown(0, false);
    lc2.shutdown(0, false);
    lc3.shutdown(0, false);
    lc4.shutdown(0, false);

    lc1.setIntensity(0, 8);
    lc2.setIntensity(0, 8);
    lc3.setIntensity(0, 8);
    lc4.setIntensity(0, 8);

    lc1.clearDisplay(0);
    lc2.clearDisplay(0);
    lc3.clearDisplay(0);
    lc4.clearDisplay(0);

    Serial.begin(19200);

    Serial.println("Hello Dirk!");
}

void displayRank(uint64_t image) {
    for (int i = 0; i < 8; i++) {
         byte row = (image >> i * 8) & 0xFF;
         for (int j = 0; j < 8; j++) {
              lc4.setLed(0, i, j, bitRead(row, j));
         }
    }
}

void loop() {

  if (Serial.available() >= BYTE_SIZE) {

      Serial.readBytes(buffer, BYTE_SIZE);

      memcpy(&ds, &buffer, BYTE_SIZE);

      if (ds.unit == 0) { // scoreboard

        switch(ds.digit) {
        case 0x0:
            // PLAYER1_0
            lc1.setChar(0, 7, (byte)ds.value, false);
            break;
        case 0x1:
            // PLAYER1_1
            lc1.setChar(0, 6, (byte)ds.value, false);
            break;
        case 0x2:
            // PLAYER1_2
            lc1.setChar(0, 5, (byte)ds.value, false);
            break;
        case 0x3:
            // PLAYER1_3
            lc1.setChar(0, 4, (byte)ds.value, false);
            break;
        case 0x4:
            // PLAYER1_4
            lc1.setChar(0, 3, (byte)ds.value, false);
            break;
        case 0x5:
            // PLAYER1_5
            lc1.setChar(0, 2, (byte)ds.value, false);
            break;
        case 0x6:
            // PLAYER2_0
            lc2.setChar(0, 7, (byte)ds.value, false);
            break;
        case 0x7:
            // PLAYER2_1
            lc2.setChar(0, 6, (byte)ds.value, false);
            break;
        case 0x8:
            // PLAYER2_2
            lc2.setChar(0, 5, (byte)ds.value, false);
            break;
        case 0x9:
            // PLAYER2_3
            lc2.setChar(0, 4, (byte)ds.value, false);
            break;
        case 0xa:
            // PLAYER2_4
            lc2.setChar(0, 3, (byte)ds.value, false);
            break;
        case 0xb:
            // PLAYER2_5
            lc2.setChar(0, 2, (byte)ds.value, false);
            break;
        case 0xc:
            // LIVES0
            lc1.setChar(0, 0, (byte)ds.value, false);
            break;
        case 0xd:
            // LIVES1
            lc2.setChar(0, 0, (byte)ds.value, false);
            break;
        case 0xe:
            // CREDITS1_0
            lc3.setChar(0, 4, (byte)ds.value, false);
            break;
        case 0xf:
            // CREDITS1_1
            lc3.setChar(0, 3, (byte)ds.value, false);
            break;
        }

      } else if (ds.unit == 1) { //annunciator

        switch(ds.value) {
        case 0x1:
            // Ace
            memcpy_P(&image, &ANNUNCIATOR[0], 8);
            break;
        case 0x2:
            // Cadet
            memcpy_P(&image, &ANNUNCIATOR[1], 8);
            break;
        case 0x4:
            // Captain
            memcpy_P(&image, &ANNUNCIATOR[2], 8);
            break;
        default:
            // Blank
            memcpy_P(&image, &ANNUNCIATOR[3], 8);
            break;
       }
       displayRank(image);
    }
  }
}
