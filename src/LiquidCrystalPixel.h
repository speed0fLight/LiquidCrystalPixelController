// not done (10/9/2025)

#ifndef LiquidCrystalPixel_h
#define LiquidCrystalPixel_h

#include <inttypes.h>

// preset commands from LiquidCrystal and datasheet
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

const SLOT_WIDTH = 5;
const SLOT_HEIGHT = 8;

// Type definitions
typedef uint8_t BYTE;

typedef struct RenderSlot
{ // Holds two dimensional data for a character slot.
  // 8 vertical.
  // 5 horizontal.
  // Empty
  BYTE rows[8];

  RenderSlot()
  {
    for (int i = 0; i < 8; i++)
    {
      rows[i] = 0b00000;
    }
  }
};

typedef struct RenderMatrix_16x2
{
  RenderSlot grid[16][2];

  RenderMatrix_16x2()
  {
  }
};

class LiquidCrystalPixel
{
public:
// Different types of constructors to allow for compatability with LiquidCrystal
  LiquidCrystalPixel(uint8_t rs, uint8_t enable,
                     uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
                     uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);
  LiquidCrystalPixel(uint8_t rs, uint8_t rw, uint8_t enable,
                     uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
                     uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);
  LiquidCrystalPixel(uint8_t rs, uint8_t rw, uint8_t enable,
                     uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3);
  LiquidCrystalPixel(uint8_t rs, uint8_t enable,
                     uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3);

  void init(uint8_t fourbitmode, uint8_t rs, uint8_t rw, uint8_t enable,
            uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
            uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7); // Creates the LCD Object from LiquidCrystal
  // This library is for rendering onto a lcd with a graphical-like interface.

  void WritePixel(int x, int y, bool STATE); // Should use cursor. Find the slot with divison of x against the max. math.floor it
  void ReadPixel(int x, int y);              // x is about 80 pixels wide, combining all of the slots into one.

private:
  void RenderMap(const RenderMatrix_16x2 &map); // This takes a 16x2 map of individual character slots, each with their own custom char.

  // Variables
  RenderMatrix_16x2 map; // Stores characters as arr[16][2] to be accessed.
  LiquidCrystal *lcd;
};

#endif