#pragma once

typedef unsigned char CHIP_TYPE;

const unsigned char CHIP_TYPE_NONE       = 0x00; 
const unsigned char CHIP_TYPE_LINE       = 0x10; 
const unsigned char CHIP_TYPE_ROOT		 = 0x11;
const unsigned char CHIP_TYPE_FACILITY   = 0x20; 
const unsigned char CHIP_TYPE_POWERPLANT = 0x21;
const unsigned char CHIP_TYPE_CHARGER    = 0x22;
const unsigned char CHIP_TYPE_BASE       = 0x23;
const unsigned char CHIP_TYPE_REFINERY   = 0x24;
const unsigned char CHIP_TYPE_BULLETIN   = 0x25;
const unsigned char CHIP_TYPE_MATERIAL	 = 0x30;
const unsigned char CHIP_TYPE_FOREST	 = 0x31;
const unsigned char CHIP_TYPE_GOLD_MINE	 = 0x32;