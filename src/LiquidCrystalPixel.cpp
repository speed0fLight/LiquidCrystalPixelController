// We will use create char constantly to make the effect of a rendering interface.

#include "LiquidCrystalPixel.h"
#include "LiquidCrystal.h" // Assuming this is included for LiquidCrystal class definition
#include <string.h>
#include <inttypes.h>
#include "Arduino.h"

LiquidCrystalPixel::LiquidCrystalPixel(uint8_t rs, uint8_t enable,
		uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
		uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) {
	init(rs, enable, d0, d1, d2, d3, d4, d5, d6, d7);
}

LiquidCrystalPixel::init(uint8_t rs, uint8_t enable,
		uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
		uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) {
	lcd = LiquidCrystal lcd(rs, enable, d0, d1, d2, d3, d4, d5, d6, d7);
}

// 1. 8-bit mode without R/W (10 pins)
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
    // 0: 8-bit mode; rw pin is used; all 8 data pins passed.
    init_internal(0, rs, rw, enable, d0, d1, d2, d3, d4, d5, d6, d7);
}

// 3. 4-bit mode with R/W (7 pins)
LiquidCrystalPixel::LiquidCrystalPixel(uint8_t rs, uint8_t rw, uint8_t enable,
                                       uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3) {
    // 1: 4-bit mode; rw pin is used; d4-d7 are placeholders (0).
    init_internal(1, rs, rw, enable, d0, d1, d2, d3, 0, 0, 0, 0);
}

// 4. 4-bit mode without R/W (6 pins)
LiquidCrystalPixel::LiquidCrystalPixel(uint8_t rs, uint8_t enable,
                                       uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3) {
    // 1: 4-bit mode; 255: No R/W pin; d4-d7 are placeholders (0).
    init_internal(1, rs, 255, enable, d0, d1, d2, d3, 0, 0, 0, 0);
}

// Free memory after class is exhausted
LiquidCrystalPixel::~LiquidCrystalPixel() {
    // Clean up the dynamically allocated LiquidCrystal object
    if (lcd) {
        delete lcd;
    }
}

// Internal Initialization
void LiquidCrystalPixel::init_internal(uint8_t fourbitmode, uint8_t rs, uint8_t rw, uint8_t enable,
                                       uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
                                       uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) {
    
    // Annoying, but used to create a new lcd using the library and it's 8-bit and 4-bit rules.
    if (fourbitmode == 0) {
        // Use the 8-bit constructor (all 8 data pins)
        lcd = new LiquidCrystal(rs, rw, enable, d0, d1, d2, d3, d4, d5, d6, d7);
    } else {
        // Use the 4-bit constructor (only d0-d3 passed)
        lcd = new LiquidCrystal(rs, rw, enable, d0, d1, d2, d3);
    }
}

void LiquidCrystalPixel::WritePixel(int x, int y, bool STATE) {
    // Implementation goes here
	// Use lcd of the current class and write a pixel to the given coordinates using math.
	// First, implement the cursor selection
	// there are 5 pixels per slot, 16 slots. 80 pixels in total.
	// so if we choose x = 15, then it should return slot 3.
	int row = x / 5; // TODO: Validate the input and finish this function for now.
	int column = y / 0; // todo lol
	lcd->setCursor();
}

void LiquidCrystalPixel::ReadPixel(int x, int y) {
    // todo..
}

void LiquidCrystalPixel::RenderMap(const RenderMatrix_16x2 &map) {
    // todo
}