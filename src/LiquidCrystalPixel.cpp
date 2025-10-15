// LiquidCrystalPixel.cpp

#include "LiquidCrystalPixel.h"
#include <LiquidCrystal.h>
#include <string.h>
#include <inttypes.h>
#include <Arduino.h>

// Initializers from LiquidCrystal
// 1. 8-bit mode without R/W (10 pins) - This was duplicated, removed the first.
LiquidCrystalPixel::LiquidCrystalPixel(uint8_t rs, uint8_t enable,
                                       uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
                                       uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) {
    // 0: 8-bit mode; 255: No R/W pin; all 8 data pins passed.
    init_internal(0, rs, 255, enable, d0, d1, d2, d3, d4, d5, d6, d7);
}

// 2. 8-bit mode with R/W (11 pins)
LiquidCrystalPixel::LiquidCrystalPixel(uint8_t rs, uint8_t rw, uint8_t enable,
                                       uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
                                       uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) {
    init_internal(0, rs, rw, enable, d0, d1, d2, d3, d4, d5, d6, d7);
}

// 3. 4-bit mode with R/W (7 pins)
LiquidCrystalPixel::LiquidCrystalPixel(uint8_t rs, uint8_t rw, uint8_t enable,
                                       uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3) {
    init_internal(1, rs, rw, enable, d0, d1, d2, d3, 0, 0, 0, 0);
}

// 4. 4-bit mode without R/W (6 pins)
LiquidCrystalPixel::LiquidCrystalPixel(uint8_t rs, uint8_t enable,
                                       uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3) {
    init_internal(1, rs, 255, enable, d0, d1, d2, d3, 0, 0, 0, 0);
}

LiquidCrystalPixel::~LiquidCrystalPixel() {
    if (lcd) {
        delete lcd;
    }
}


void LiquidCrystalPixel::init_internal(uint8_t fourbitmode, uint8_t rs, uint8_t rw, uint8_t enable,
                                       uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
                                       uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) {
    
    if (fourbitmode == 0) {
        lcd = new LiquidCrystal(rs, rw, enable, d0, d1, d2, d3, d4, d5, d6, d7);
    } else {
        lcd = new LiquidCrystal(rs, rw, enable, d0, d1, d2, d3);
    }
    
    // Initialize the LCD display size
    if (lcd) {
        lcd->begin(16, 2); 
    }
}

// Write pixles individually
void LiquidCrystalPixel::WritePixel(int x, int y, bool STATE) {
    // 80 pixels wide
    // 16 pixels high
    if (x < 1 || x > 80 || y < 1 || y > 16 || !lcd) {
        return; // Out of bounds or LCD not initialized
    }
    
    // Slot Calculation
    int cursorRow = (x + SLOT_WIDTH - 1) / SLOT_WIDTH; // Corrected: (x+4)/5
    int cursorColumn = (y - 1) / SLOT_HEIGHT; 
    
    // Pixel Slot Calculation 0 index
    int row = (y - 1) % SLOT_HEIGHT; 
    
    // index (0-4): The horizontal pixel column within the 8x5 character slot.
    int index = (x - 1) % SLOT_WIDTH;
    int bit_position = 4 - index;
    BYTE& pixel_byte = map.grid[cursorRow - 1][cursorColumn].rows[row];

    if (STATE == true) {
        // Pixel turns ON
        pixel_byte |= (1 << bit_position); 
    } else {
        // Pixel turns OFF
        pixel_byte &= ~(1 << bit_position);
    }
    
    // 1. Define the custom character (slot 0 is used for every update)
    // custom char definition expects a pointer to an 8-byte array.
    lcd->createChar(0, map.grid[cursorRow - 1][cursorColumn].rows);
    
    // 2. Move the cursor to the character slot
    lcd->setCursor(cursorRow - 1, cursorColumn); // cursorRow-1 for 0-based column
    
    // 3. Write the custom character (ID 0)
    lcd->write((BYTE)0);
}

bool LiquidCrystalPixel::ReadPixel(int x, int y) {
    if (x < 1 || x > 80 || y < 1 || y > 16) {
        return false; // Out of bounds
    }

    // Slot Calculation (1-based index)
    int cursorRow = (x + SLOT_WIDTH - 1) / SLOT_WIDTH;
    int cursorColumn = (y - 1) / SLOT_HEIGHT;

    // Pixel-in-Slot Calculation (0-based index)
    int row = (y - 1) % SLOT_HEIGHT;
    int index = (x - 1) % SLOT_WIDTH;

    int bit_position = 4 - index; // Bit position for the specific pixel (0-4)

    // Check if the bit is set in the stored pattern
    BYTE pixel_byte = map.grid[cursorRow - 1][cursorColumn].rows[row];
    
    // Check the specific bit
    return (pixel_byte & (1 << bit_position)) != 0;
}

void LiquidCrystalPixel::RenderMap(const RenderMatrix_16x2 &map) {
    // This function is meant to render the map matrix.
    
    for (int col = 0; col < 2; col++) { // 2 rows
        for (int row = 0; row < 16; row++) { // 16 columns
            // 1. Temporarily define custom character 0 with the character data
            lcd->createChar(0, map.grid[row][col].rows);
            
            // 2. Set cursor to the slot position
            lcd->setCursor(row, col);
            
            // 3. Write custom character 0
            lcd->write((uint8_t)0);
        }
    }
}