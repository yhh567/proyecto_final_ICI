/*
* ssd1306.h
*
*  Created on: 20 oct. 2017
*  Author: Miguel Angel Rodriguez Jodar
*
* Based upon Adafruit library.
* GPL licensed.
* 
*/

#include "ssd1306.h"
#include "mbed.h"

/* I believe this charset was taken from the compilation from Joseph Gil years ago
 * when I needed a charset for a different (FPGA) project, but I cannot remember 
 * exactly the website I took it from.
 * What I do remember is that the owner of the website claimed that this charset
 * is in the public domain.
 * This a complete (256 ASCII codes) 8x8 charset, using the 437 page code (original IBM)
 * so you can use its graphic blocks to build decent text based GUIs without the need
 * to use plot, line and circle primitives
 */
static const char charset[2048] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7E, 0x81,
    0x95, 0xB1, 0xB1, 0x95, 0x81, 0x7E, 0x7E, 0xFF, 0xEB, 0xCF,
    0xCF, 0xEB, 0xFF, 0x7E, 0x0E, 0x1F, 0x3F, 0x7E, 0x3F, 0x1F,
    0x0E, 0x00, 0x08, 0x1C, 0x3E, 0x7F, 0x3E, 0x1C, 0x08, 0x00,
    0x38, 0x3A, 0x9F, 0xFF, 0x9F, 0x3A, 0x38, 0x00, 0x18, 0x3C,
    0xBE, 0xFF, 0xBE, 0x3C, 0x18, 0x00, 0x00, 0x00, 0x18, 0x3C,
    0x3C, 0x18, 0x00, 0x00, 0xFF, 0xFF, 0xE7, 0xC3, 0xC3, 0xE7,
    0xFF, 0xFF, 0x00, 0x3C, 0x66, 0x42, 0x42, 0x66, 0x3C, 0x00,
    0xFF, 0xC3, 0x99, 0xBD, 0xBD, 0x99, 0xC3, 0xFF, 0x70, 0xF8,
    0x88, 0x88, 0xFD, 0x7F, 0x07, 0x0F, 0x00, 0x4E, 0x5F, 0xF1,
    0xF1, 0x5F, 0x4E, 0x00, 0xC0, 0xE0, 0xFF, 0x7F, 0x05, 0x05,
    0x07, 0x07, 0xC0, 0xFF, 0x7F, 0x05, 0x05, 0x65, 0x7F, 0x3F,
    0x5A, 0x5A, 0x3C, 0xE7, 0xE7, 0x3C, 0x5A, 0x5A, 0x7F, 0x3E,
    0x3E, 0x1C, 0x1C, 0x08, 0x08, 0x00, 0x08, 0x08, 0x1C, 0x1C,
    0x3E, 0x3E, 0x7F, 0x00, 0x00, 0x24, 0x66, 0xFF, 0xFF, 0x66,
    0x24, 0x00, 0x00, 0x5F, 0x5F, 0x00, 0x00, 0x5F, 0x5F, 0x00,
    0x06, 0x0F, 0x09, 0x7F, 0x7F, 0x01, 0x7F, 0x7F, 0x40, 0x9A,
    0xBF, 0xA5, 0xA5, 0xFD, 0x59, 0x02, 0x00, 0x70, 0x70, 0x70,
    0x70, 0x70, 0x70, 0x00, 0x80, 0x94, 0xB6, 0xFF, 0xFF, 0xB6,
    0x94, 0x80, 0x00, 0x04, 0x06, 0x7F, 0x7F, 0x06, 0x04, 0x00,
    0x00, 0x10, 0x30, 0x7F, 0x7F, 0x30, 0x10, 0x00, 0x08, 0x08,
    0x08, 0x2A, 0x3E, 0x1C, 0x08, 0x00, 0x08, 0x1C, 0x3E, 0x2A,
    0x08, 0x08, 0x08, 0x00, 0x3C, 0x3C, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x00, 0x08, 0x1C, 0x3E, 0x08, 0x08, 0x3E, 0x1C, 0x08,
    0x30, 0x38, 0x3C, 0x3E, 0x3E, 0x3C, 0x38, 0x30, 0x06, 0x0E,
    0x1E, 0x3E, 0x3E, 0x1E, 0x0E, 0x06, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x5F, 0x5F, 0x06,
    0x00, 0x00, 0x00, 0x03, 0x07, 0x00, 0x00, 0x07, 0x03, 0x00,
    0x14, 0x7F, 0x7F, 0x14, 0x7F, 0x7F, 0x14, 0x00, 0x00, 0x24,
    0x2E, 0x6B, 0x6B, 0x3A, 0x12, 0x00, 0x46, 0x66, 0x30, 0x18,
    0x0C, 0x66, 0x62, 0x00, 0x30, 0x7A, 0x4F, 0x5D, 0x37, 0x7A,
    0x48, 0x00, 0x00, 0x00, 0x04, 0x07, 0x03, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x1C, 0x3E, 0x63, 0x41, 0x00, 0x00, 0x00, 0x00,
    0x41, 0x63, 0x3E, 0x1C, 0x00, 0x00, 0x08, 0x2A, 0x3E, 0x1C,
    0x1C, 0x3E, 0x2A, 0x08, 0x00, 0x08, 0x08, 0x3E, 0x3E, 0x08,
    0x08, 0x00, 0x00, 0x00, 0x80, 0xE0, 0x60, 0x00, 0x00, 0x00,
    0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00,
    0x00, 0x60, 0x60, 0x00, 0x00, 0x00, 0x60, 0x30, 0x18, 0x0C,
    0x06, 0x03, 0x01, 0x00, 0x1C, 0x3E, 0x63, 0x49, 0x63, 0x3E,
    0x1C, 0x00, 0x00, 0x40, 0x42, 0x7F, 0x7F, 0x40, 0x40, 0x00,
    0x42, 0x63, 0x71, 0x59, 0x49, 0x6F, 0x66, 0x00, 0x22, 0x63,
    0x49, 0x49, 0x49, 0x7F, 0x36, 0x00, 0x18, 0x1C, 0x16, 0x53,
    0x7F, 0x7F, 0x50, 0x00, 0x2F, 0x6F, 0x49, 0x49, 0x49, 0x79,
    0x31, 0x00, 0x3C, 0x7E, 0x4B, 0x49, 0x49, 0x78, 0x30, 0x00,
    0x03, 0x03, 0x71, 0x79, 0x0D, 0x07, 0x03, 0x00, 0x36, 0x7F,
    0x49, 0x49, 0x49, 0x7F, 0x36, 0x00, 0x06, 0x4F, 0x49, 0x49,
    0x69, 0x3F, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x66, 0x66, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x80, 0xE6, 0x66, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x08, 0x1C, 0x36, 0x63, 0x41, 0x00, 0x00, 0x24,
    0x24, 0x24, 0x24, 0x24, 0x24, 0x00, 0x00, 0x41, 0x63, 0x36,
    0x1C, 0x08, 0x00, 0x00, 0x02, 0x03, 0x01, 0x59, 0x5D, 0x07,
    0x02, 0x00, 0x3E, 0x7F, 0x41, 0x5D, 0x5D, 0x1F, 0x1E, 0x00,
    0x7C, 0x7E, 0x0B, 0x09, 0x0B, 0x7E, 0x7C, 0x00, 0x41, 0x7F,
    0x7F, 0x49, 0x49, 0x7F, 0x36, 0x00, 0x1C, 0x3E, 0x63, 0x41,
    0x41, 0x63, 0x22, 0x00, 0x41, 0x7F, 0x7F, 0x41, 0x63, 0x3E,
    0x1C, 0x00, 0x41, 0x7F, 0x7F, 0x49, 0x5D, 0x41, 0x63, 0x00,
    0x41, 0x7F, 0x7F, 0x49, 0x1D, 0x01, 0x03, 0x00, 0x1C, 0x3E,
    0x63, 0x41, 0x51, 0x33, 0x72, 0x00, 0x7F, 0x7F, 0x08, 0x08,
    0x08, 0x7F, 0x7F, 0x00, 0x00, 0x00, 0x41, 0x7F, 0x7F, 0x41,
    0x00, 0x00, 0x30, 0x70, 0x40, 0x41, 0x7F, 0x3F, 0x01, 0x00,
    0x41, 0x7F, 0x7F, 0x08, 0x1C, 0x77, 0x63, 0x00, 0x41, 0x7F,
    0x7F, 0x41, 0x40, 0x60, 0x70, 0x00, 0x7F, 0x7F, 0x0E, 0x1C,
    0x0E, 0x7F, 0x7F, 0x00, 0x7F, 0x7F, 0x06, 0x0C, 0x18, 0x7F,
    0x7F, 0x00, 0x3E, 0x7F, 0x41, 0x41, 0x41, 0x7F, 0x3E, 0x00,
    0x41, 0x7F, 0x7F, 0x49, 0x09, 0x0F, 0x06, 0x00, 0x3E, 0x7F,
    0x41, 0x41, 0xE1, 0xFF, 0xBE, 0x00, 0x41, 0x7F, 0x7F, 0x09,
    0x19, 0x7F, 0x66, 0x00, 0x00, 0x22, 0x67, 0x4D, 0x59, 0x73,
    0x22, 0x00, 0x00, 0x07, 0x43, 0x7F, 0x7F, 0x43, 0x07, 0x00,
    0x3F, 0x7F, 0x40, 0x40, 0x40, 0x7F, 0x3F, 0x00, 0x1F, 0x3F,
    0x60, 0x40, 0x60, 0x3F, 0x1F, 0x00, 0x3F, 0x7F, 0x60, 0x38,
    0x60, 0x7F, 0x3F, 0x00, 0x63, 0x77, 0x1C, 0x08, 0x1C, 0x77,
    0x63, 0x00, 0x00, 0x07, 0x4F, 0x78, 0x78, 0x4F, 0x07, 0x00,
    0x47, 0x63, 0x71, 0x59, 0x4D, 0x67, 0x73, 0x00, 0x00, 0x00,
    0x7F, 0x7F, 0x41, 0x41, 0x00, 0x00, 0x01, 0x03, 0x06, 0x0C,
    0x18, 0x30, 0x60, 0x00, 0x00, 0x00, 0x41, 0x41, 0x7F, 0x7F,
    0x00, 0x00, 0x08, 0x0C, 0x06, 0x03, 0x06, 0x0C, 0x08, 0x00,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00,
    0x01, 0x03, 0x06, 0x04, 0x00, 0x00, 0x20, 0x74, 0x54, 0x54,
    0x3C, 0x78, 0x40, 0x00, 0x41, 0x7F, 0x3F, 0x44, 0x44, 0x7C,
    0x38, 0x00, 0x38, 0x7C, 0x44, 0x44, 0x44, 0x6C, 0x28, 0x00,
    0x38, 0x7C, 0x44, 0x45, 0x3F, 0x7F, 0x40, 0x00, 0x38, 0x7C,
    0x54, 0x54, 0x54, 0x5C, 0x18, 0x00, 0x48, 0x7E, 0x7F, 0x49,
    0x09, 0x03, 0x02, 0x00, 0x98, 0xBC, 0xA4, 0xA4, 0xF8, 0x7C,
    0x04, 0x00, 0x41, 0x7F, 0x7F, 0x08, 0x04, 0x7C, 0x78, 0x00,
    0x00, 0x00, 0x44, 0x7D, 0x7D, 0x40, 0x00, 0x00, 0x00, 0x60,
    0xE0, 0x80, 0x80, 0xFD, 0x7D, 0x00, 0x41, 0x7F, 0x7F, 0x10,
    0x38, 0x6C, 0x44, 0x00, 0x00, 0x00, 0x41, 0x7F, 0x7F, 0x40,
    0x00, 0x00, 0x7C, 0x7C, 0x0C, 0x78, 0x0C, 0x7C, 0x78, 0x00,
    0x04, 0x7C, 0x78, 0x04, 0x04, 0x7C, 0x78, 0x00, 0x38, 0x7C,
    0x44, 0x44, 0x44, 0x7C, 0x38, 0x00, 0x84, 0xFC, 0xF8, 0xA4,
    0x24, 0x3C, 0x18, 0x00, 0x18, 0x3C, 0x24, 0xA4, 0xF8, 0xFC,
    0x84, 0x00, 0x44, 0x7C, 0x78, 0x4C, 0x04, 0x0C, 0x08, 0x00,
    0x48, 0x5C, 0x54, 0x54, 0x54, 0x74, 0x24, 0x00, 0x04, 0x04,
    0x3F, 0x7F, 0x44, 0x64, 0x20, 0x00, 0x3C, 0x7C, 0x40, 0x40,
    0x3C, 0x7C, 0x40, 0x00, 0x1C, 0x3C, 0x60, 0x40, 0x60, 0x3C,
    0x1C, 0x00, 0x3C, 0x7C, 0x60, 0x38, 0x60, 0x7C, 0x3C, 0x00,
    0x44, 0x6C, 0x38, 0x10, 0x38, 0x6C, 0x44, 0x00, 0x9C, 0xBC,
    0xA0, 0xA0, 0xA0, 0xFC, 0x7C, 0x00, 0x00, 0x4C, 0x64, 0x74,
    0x5C, 0x4C, 0x64, 0x00, 0x00, 0x08, 0x08, 0x3E, 0x77, 0x41,
    0x41, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x00, 0x00, 0x00,
    0x00, 0x41, 0x41, 0x77, 0x3E, 0x08, 0x08, 0x00, 0x02, 0x03,
    0x01, 0x03, 0x02, 0x03, 0x01, 0x00, 0x70, 0x78, 0x4C, 0x46,
    0x4C, 0x78, 0x70, 0x00, 0x1E, 0xBF, 0xA1, 0xA1, 0xE1, 0x73,
    0x12, 0x00, 0x3D, 0x7D, 0x40, 0x40, 0x3D, 0x7D, 0x40, 0x00,
    0x38, 0x7C, 0x54, 0x56, 0x57, 0x5D, 0x18, 0x00, 0x22, 0x75,
    0x55, 0x55, 0x3D, 0x79, 0x42, 0x00, 0x21, 0x75, 0x54, 0x54,
    0x3C, 0x79, 0x41, 0x00, 0x20, 0x74, 0x55, 0x57, 0x3E, 0x78,
    0x40, 0x00, 0x20, 0x74, 0x57, 0x57, 0x3C, 0x78, 0x40, 0x00,
    0x18, 0x3C, 0xA4, 0xA4, 0xE4, 0x64, 0x24, 0x00, 0x3A, 0x7D,
    0x55, 0x55, 0x55, 0x5D, 0x1A, 0x00, 0x39, 0x7D, 0x54, 0x54,
    0x54, 0x5D, 0x19, 0x00, 0x38, 0x7C, 0x55, 0x57, 0x56, 0x5C,
    0x18, 0x00, 0x00, 0x01, 0x45, 0x7C, 0x7C, 0x41, 0x01, 0x00,
    0x02, 0x01, 0x45, 0x7D, 0x7D, 0x41, 0x02, 0x00, 0x00, 0x00,
    0x49, 0x7B, 0x7A, 0x40, 0x00, 0x00, 0x79, 0x7D, 0x16, 0x12,
    0x16, 0x7D, 0x79, 0x00, 0x78, 0x7E, 0x17, 0x15, 0x17, 0x7E,
    0x78, 0x00, 0x7C, 0x7C, 0x56, 0x57, 0x55, 0x44, 0x44, 0x00,
    0x20, 0x74, 0x54, 0x7C, 0x7C, 0x54, 0x54, 0x00, 0x7C, 0x7E,
    0x0B, 0x09, 0x7F, 0x7F, 0x49, 0x00, 0x3A, 0x7D, 0x45, 0x45,
    0x45, 0x7D, 0x3A, 0x00, 0x39, 0x7D, 0x44, 0x44, 0x44, 0x7D,
    0x39, 0x00, 0x38, 0x7C, 0x45, 0x47, 0x46, 0x7C, 0x38, 0x00,
    0x3A, 0x79, 0x41, 0x41, 0x39, 0x7A, 0x40, 0x00, 0x3C, 0x7D,
    0x43, 0x42, 0x3C, 0x7C, 0x40, 0x00, 0x9D, 0xBD, 0xA0, 0xA0,
    0xA0, 0xFD, 0x7D, 0x00, 0x19, 0x3D, 0x66, 0x42, 0x66, 0x3D,
    0x19, 0x00, 0x3D, 0x7D, 0x40, 0x40, 0x40, 0x7D, 0x3D, 0x00,
    0x18, 0x3C, 0x24, 0xE7, 0xE7, 0x24, 0x24, 0x00, 0x48, 0x7E,
    0x7F, 0x49, 0x43, 0x66, 0x20, 0x00, 0x00, 0x2B, 0x2F, 0xFC,
    0xFC, 0x2F, 0x2B, 0x00, 0xFF, 0xFF, 0x09, 0x09, 0x2F, 0xF6,
    0xF8, 0xA0, 0x20, 0x60, 0x48, 0x7E, 0x3F, 0x09, 0x03, 0x02,
    0x20, 0x74, 0x56, 0x57, 0x3D, 0x78, 0x40, 0x00, 0x00, 0x00,
    0x48, 0x7A, 0x7B, 0x41, 0x00, 0x00, 0x38, 0x7C, 0x44, 0x46,
    0x47, 0x7D, 0x38, 0x00, 0x3C, 0x7C, 0x42, 0x43, 0x3D, 0x7C,
    0x40, 0x00, 0x0A, 0x7B, 0x71, 0x0B, 0x0A, 0x7B, 0x71, 0x00,
    0x7A, 0x7B, 0x19, 0x33, 0x62, 0x7B, 0x79, 0x00, 0x00, 0x26,
    0x2F, 0x29, 0x2F, 0x2F, 0x28, 0x00, 0x00, 0x26, 0x2F, 0x29,
    0x2F, 0x26, 0x00, 0x00, 0x00, 0x20, 0x70, 0x5D, 0x4D, 0x40,
    0x60, 0x20, 0x38, 0x38, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00,
    0x08, 0x08, 0x08, 0x08, 0x08, 0x38, 0x38, 0x00, 0x42, 0x6F,
    0x3F, 0x18, 0xCC, 0xEE, 0xBB, 0x91, 0x42, 0x6F, 0x3F, 0x58,
    0x6C, 0xD6, 0xFB, 0x41, 0x00, 0x00, 0x30, 0x7D, 0x7D, 0x30,
    0x00, 0x00, 0x08, 0x1C, 0x36, 0x22, 0x08, 0x1C, 0x36, 0x22,
    0x22, 0x36, 0x1C, 0x08, 0x22, 0x36, 0x1C, 0x08, 0xAA, 0x00,
    0x55, 0x00, 0xAA, 0x00, 0x55, 0x00, 0xAA, 0x55, 0xAA, 0x55,
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0xFF, 0x55, 0xFF, 0xAA, 0xFF,
    0x55, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00,
    0x10, 0x10, 0x10, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x14, 0x14,
    0x14, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x10, 0x10, 0xFF, 0xFF,
    0x00, 0xFF, 0xFF, 0x00, 0x10, 0x10, 0xF0, 0xF0, 0x10, 0xF0,
    0xF0, 0x00, 0x14, 0x14, 0x14, 0xFC, 0xFC, 0x00, 0x00, 0x00,
    0x14, 0x14, 0xF7, 0xF7, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x14, 0x14, 0xF4, 0xF4,
    0x04, 0xFC, 0xFC, 0x00, 0x14, 0x14, 0x17, 0x17, 0x10, 0x1F,
    0x1F, 0x00, 0x10, 0x10, 0x1F, 0x1F, 0x10, 0x1F, 0x1F, 0x00,
    0x14, 0x14, 0x14, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x10, 0x10,
    0x10, 0xF0, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F,
    0x1F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F, 0x1F, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0xF0, 0xF0, 0x10, 0x10, 0x10,
    0x00, 0x00, 0x00, 0xFF, 0xFF, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0xFF,
    0xFF, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x14,
    0x14, 0x14, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x10,
    0x00, 0x00, 0x1F, 0x1F, 0x10, 0x17, 0x17, 0x14, 0x00, 0x00,
    0xFC, 0xFC, 0x04, 0xF4, 0xF4, 0x14, 0x14, 0x14, 0x17, 0x17,
    0x10, 0x17, 0x17, 0x14, 0x14, 0x14, 0xF4, 0xF4, 0x04, 0xF4,
    0xF4, 0x14, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xF7, 0xF7, 0x14,
    0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,
    0xF7, 0xF7, 0x00, 0xF7, 0xF7, 0x14, 0x14, 0x14, 0x14, 0x17,
    0x17, 0x14, 0x14, 0x14, 0x10, 0x10, 0x1F, 0x1F, 0x10, 0x1F,
    0x1F, 0x10, 0x14, 0x14, 0x14, 0xF4, 0xF4, 0x14, 0x14, 0x14,
    0x10, 0x10, 0xF0, 0xF0, 0x10, 0xF0, 0xF0, 0x10, 0x00, 0x00,
    0x1F, 0x1F, 0x10, 0x1F, 0x1F, 0x10, 0x00, 0x00, 0x00, 0x1F,
    0x1F, 0x14, 0x14, 0x14, 0x00, 0x00, 0x00, 0xFC, 0xFC, 0x14,
    0x14, 0x14, 0x00, 0x00, 0xF0, 0xF0, 0x10, 0xF0, 0xF0, 0x10,
    0x10, 0x10, 0xFF, 0xFF, 0x10, 0xFF, 0xFF, 0x10, 0x14, 0x14,
    0x14, 0xFF, 0xFF, 0x14, 0x14, 0x14, 0x10, 0x10, 0x10, 0x1F,
    0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xF0, 0x10,
    0x10, 0x10, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xFF, 0xFF,
    0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
    0x0F, 0x0F, 0x38, 0x7C, 0x44, 0x6C, 0x38, 0x6C, 0x44, 0x00,
    0x7E, 0x7F, 0x01, 0x09, 0x5F, 0x76, 0x20, 0x00, 0x7F, 0x7F,
    0x01, 0x01, 0x01, 0x03, 0x03, 0x00, 0x04, 0x7C, 0x7C, 0x04,
    0x7C, 0x7C, 0x04, 0x00, 0x63, 0x77, 0x5D, 0x49, 0x41, 0x63,
    0x63, 0x00, 0x38, 0x7C, 0x44, 0x7C, 0x3C, 0x04, 0x04, 0x00,
    0x80, 0xFC, 0x7C, 0x40, 0x40, 0x7C, 0x3C, 0x00, 0x04, 0x06,
    0x02, 0x7E, 0x7C, 0x06, 0x02, 0x00, 0x00, 0x99, 0xBD, 0xE7,
    0xE7, 0xBD, 0x99, 0x00, 0x1C, 0x3E, 0x6B, 0x49, 0x6B, 0x3E,
    0x1C, 0x00, 0x4C, 0x7E, 0x73, 0x01, 0x73, 0x7E, 0x4C, 0x00,
    0x00, 0x30, 0x78, 0x4A, 0x4F, 0x7D, 0x39, 0x00, 0x18, 0x3C,
    0x24, 0x3C, 0x3C, 0x24, 0x3C, 0x18, 0x98, 0xFC, 0x64, 0x3C,
    0x3E, 0x27, 0x3D, 0x18, 0x00, 0x1C, 0x3E, 0x6B, 0x49, 0x49,
    0x49, 0x00, 0x7C, 0x7E, 0x02, 0x02, 0x02, 0x7E, 0x7C, 0x00,
    0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x00, 0x00, 0x44,
    0x44, 0x5F, 0x5F, 0x44, 0x44, 0x00, 0x00, 0x40, 0x51, 0x5B,
    0x4E, 0x44, 0x40, 0x00, 0x00, 0x40, 0x44, 0x4E, 0x5B, 0x51,
    0x40, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0x01, 0x07, 0x06,
    0x60, 0xE0, 0x80, 0xFF, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x08, 0x2A, 0x2A, 0x08, 0x08, 0x00, 0x24, 0x36, 0x12, 0x36,
    0x24, 0x36, 0x12, 0x00, 0x00, 0x06, 0x0F, 0x09, 0x0F, 0x06,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x00, 0x10, 0x30,
    0x70, 0xC0, 0xFF, 0xFF, 0x01, 0x01, 0x00, 0x01, 0x1F, 0x1E,
    0x01, 0x1F, 0x1E, 0x00, 0x00, 0x11, 0x19, 0x1D, 0x17, 0x12,
    0x00, 0x00, 0x00, 0x00, 0x3C, 0x3C, 0x3C, 0x3C, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


SSD1306::SSD1306 (PinName sda, PinName scl, char ssd1306_addr)
{
    idxfb = 0;
    fb = new char[1024];
    if (!fb) {
        printf ("SSD1306: Framebuffer allocation failed!\r\n");
        for (;;) { }
    }

    bus = new I2C (sda, scl);
    ssd1306_i2c_addr = ssd1306_addr;
    do_not_delete_bus = 0;
#ifdef SSD1306_DEBUG
    printf ("SSD1306 debug: fb = 0x%08.8X\r\n", fb);
#endif
}

SSD1306::SSD1306 (I2C &busi2c, char ssd1306_addr)
{
    bus = &busi2c;
    idxfb = 0;
    fb = new char[1024];
    if (!fb) {
        printf ("SSD1306: Framebuffer allocation failed!\r\n");
        for (;;) { }
    }
    ssd1306_i2c_addr = ssd1306_addr;
    do_not_delete_bus = 1;
}

void SSD1306::speed (I2CSpeed spd)
{
    switch (spd) {
        case Slow:
            bus->frequency(100000);
            break;
        case Medium:
            bus->frequency(400000);
            break;
        case Fast:
            bus->frequency(1000000);
            break;
    }
}

char SSD1306::scan (void)
{
    int addr;
    int res;
    char i2caddr = 0;

    for (addr=0; addr<256; addr++) {
        res = bus->write (addr, NULL, 0);
        if (res == 0)
            i2caddr = addr & 0xFE;
    }
    return i2caddr;
}

int SSD1306::command_data (char c, char c_or_d, char lastitem)
{
    int res;

    bus->start();
    res = bus->write(ssd1306_i2c_addr);
    if (!res) goto terminate_transaction;
    res = bus->write(c_or_d | lastitem);
    if (!res) goto terminate_transaction;
    res = bus->write(c);
    if (!res) goto terminate_transaction;

terminate_transaction:
    bus->stop();
    return res;
}

int SSD1306::command (char c)
{
    return command_data (c, SSD1306_IS_COMMAND, SSD1306_IS_LAST);
}

int SSD1306::data (char d)
{
    return command_data (d, SSD1306_IS_DATA, SSD1306_IS_LAST);
}

int SSD1306::init (void)
{
    static const char comando[] = {0x80, SSD1306_DISPLAYOFF, 
                                         0x80, SSD1306_CHARGEPUMP, 
                                         0x80, 0x14, 
                                                                     0x80, SSD1306_MEMORYMODE, 
                                         0x80, 0x00, 
                                         0x80, SSD1306_SEGREMAP | 0x1,
                                   0x80, SSD1306_COMSCANDEC, 
                                         0x80, SSD1306_SETCONTRAST, 
                                         0x80, 0x7F, 
                                         0x00, SSD1306_DISPLAYON
                                  };

    return bus->write (ssd1306_i2c_addr, comando, sizeof comando);
}

void SSD1306::scroll (bool refresh)
{
    int i;

    for (i=128; i<1024; i++)
        fb[i-128] = fb[i];
    for (i=896; i<1024; i++)
        fb[i] = 0;
    if (refresh)
        redraw();
}

void SSD1306::locate (char row, char column)
{
    idxfb = row*128+column*8;
}

void SSD1306::putchar (char c, bool refresh)
{
    int idx,i;

    idx = c*8;
    if (idxfb == 1024) {
        scroll(refresh);
        idxfb = 896;
    }
    for (i=0; i<8; i++) {
        fb[idxfb] = charset[idx+i];
        idxfb++;
    }
    if (refresh)
        redraw();
}

void SSD1306::puts (char *s, bool refresh)
{
    while (*s) putchar (*s++, refresh);
}

void SSD1306::printf (const char *fmt,...)
{
    char *s = new char[129];
    va_list args;
    
    va_start (args, fmt);
    vsnprintf (s, 128, fmt, args);
    puts (s, false);
    delete[] s;
    va_end (args);
}


void SSD1306::redraw (void)
{
    int i;

    command (0xb0);
    command (SSD1306_SETLOWCOLUMN | 0x0);  // low col = 0
    command (SSD1306_SETHIGHCOLUMN | 0x0);  // hi col = 0
    command (SSD1306_SETSTARTLINE | 0x0); // line #0

    bus->start();
    bus->write (ssd1306_i2c_addr);
    bus->write (0x40);
    for (i=0; i<1024; i++) {
        bus->write (fb[i]);
    }
    bus->stop();
}

void SSD1306::display (void)
{
    redraw();
}

void SSD1306::set_contrast (char v)
{
    command (SSD1306_SETCONTRAST);
    command (v);
}

void SSD1306::cls (char *bkground, bool refresh)
{
    int i;

    if (!bkground) {
        for (i=0; i<1024; i++)
            fb[i] = 0;
    } else {
        for (i=0; i<1024; i++)
            fb[i] = bkground[i];
    }
    idxfb = 0;
    if (refresh)
        redraw();
}

void SSD1306::plot (char x, char y, PlotStyle mode, bool refresh)
{
    x = x % 128;
    y = y % 64;
    
    switch (mode) {
        case Normal:
            fb[(y/8)*128+x] |=  (1<<(y%8));
            break;
        case Inverse:
            fb[(y/8)*128+x] &= ~(1<<(y%8));
            break;
        case Xor:
            fb[(y/8)*128+x] ^=  (1<<(y%8));
            break;
    }
    if (refresh)
        redraw();
}

bool SSD1306::point (char x, char y)
{
    x = x % 128;
    y = y % 64;
    
    if ( fb[(y/8)*128+x] & (1<<(y%8)) )
        return true;
    else
        return false;
}

void SSD1306::line (char x0, char y0, char x1, char y1, PlotStyle mode, bool refresh)
{
    int dx =  abs (x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs (y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2; /* error value e_xy */

    for (;;) {
        /* loop */
        plot (x0, y0, mode, false);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) {
            err += dy;    /* e_xy+e_x > 0 */
            x0 += sx;
        }
        if (e2 <= dx) {
            err += dx;    /* e_xy+e_y < 0 */
            y0 += sy;
        }
    }
    if (refresh)
        redraw();
}

void SSD1306::circle (char x0, char y0, char r, PlotStyle mode, bool refresh)
{
    int x = r-1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - 2*r;

    while (x >= y)
    {
        plot (x0 + x, y0 + y, mode);
        plot (x0 + y, y0 + x, mode);
        plot (x0 - y, y0 + x, mode);
        plot (x0 - x, y0 + y, mode);
        plot (x0 - x, y0 - y, mode);
        plot (x0 - y, y0 - x, mode);
        plot (x0 + y, y0 - x, mode);
        plot (x0 + x, y0 - y, mode);

        if (err <= 0)
        {
            y++;
            err += dy;
            dy += 2;
        }
        if (err > 0)
        {
            x--;
            dx += 2;
            err += dx - 2*r;
        }
    }
    if (refresh)
        redraw();
}

void SSD1306::fill (char x, char y, bool refresh)
{
    unsigned char rqueue = 0, wqueue = 1;
    char *qpixel_x = new char[256];
    char *qpixel_y = new char[256];
    
    if (!qpixel_x || !qpixel_y)
    {
        if (qpixel_x) delete[] qpixel_x;
        if (qpixel_y) delete[] qpixel_y;
        printf ("SSD1306::fill ERROR. Not enough memory\r\n");
        return;
    }
    
    qpixel_x[0] = x;
    qpixel_y[0] = y;    
    plot (x, y, SSD1306::Normal);
    while (wqueue != rqueue)
    {
        x = qpixel_x[rqueue];
        y = qpixel_y[rqueue];
        rqueue++;
        
        if (x!=127 && !point (x+1,y))
        {
            plot (x+1, y, SSD1306::Normal);
            qpixel_x[wqueue] = x+1;
            qpixel_y[wqueue] = y;
            wqueue++;
        }
        
        if (x!=0 && !point (x-1,y))
        {
            plot (x-1, y, SSD1306::Normal);
            qpixel_x[wqueue] = x-1;
            qpixel_y[wqueue] = y;
            wqueue++;
        }
        
        if (y!=63 && !point (x,y+1))
        {
            plot (x, y+1, SSD1306::Normal);
            qpixel_x[wqueue] = x;
            qpixel_y[wqueue] = y+1;
            wqueue++;
        }
        
        if (y!=0 && !point (x,y-1))
        {
            plot (x, y-1, SSD1306::Normal);
            qpixel_x[wqueue] = x;
            qpixel_y[wqueue] = y-1;
            wqueue++;
        }
    }
    delete[] qpixel_x;
    delete[] qpixel_y;
    
    if (refresh)
        redraw();
}
