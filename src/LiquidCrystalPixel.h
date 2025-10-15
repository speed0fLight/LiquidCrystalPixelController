#ifndef LiquidCrystalPixel_h
#define LiquidCrystalPixel_h

#include <inttypes.h>
#include <LiquidCrystal.h> // Include the type definition for LiquidCrystal

// preset commands from LiquidCrystal and datasheet
#define LCD_CLEARDISPLAY 0x01
#define LCD_5x8DOTS 0x00

// Constants 
const int SLOT_WIDTH = 5;
const int SLOT_HEIGHT = 8;

// Type definitions
typedef uint8_t BYTE;

typedef struct RenderSlot
{ // Holds two dimensional data for a character slot.
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
  // Destructor
  ~LiquidCrystalPixel();

  // Different types of constructors to allow for compatibility with LiquidCrystal
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

  void WritePixel(int x, int y, bool STATE);
  bool ReadPixel(int x, int y);

private:
  // Internal function to create the LCD Object from LiquidCrystal
  void init_internal(uint8_t fourbitmode, uint8_t rs, uint8_t rw, uint8_t enable,
                     uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
                     uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);
  
  void RenderMap(const RenderMatrix_16x2 &map);

  // Variables
  RenderMatrix_16x2 map; // Stores characters as arr[16][2] to be accessed.
  LiquidCrystal *lcd;
};

#endif