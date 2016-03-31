#include <Arduino.h>

// Talkie library
// Copyright 2011 Peter Knight
// This code is released under GPLv2 license.
//
// These soundbites come from SPROW's custom BBC Micro phrase ROM

#include <Talkie.h>

Talkie voice;

const uint8_t spWHAT_IS_THY_BIDDING[] PROGMEM = {0x41,0x89,0xaa,0x32,0x3c,0x2a,0x1F,0x25,0xea,0xee,0x10,0x8d,0x73,0xe6,0x64,0x66,0x5c,0xac,0xc9,0x99,0xb3,0x9d,0x51,0x89,0xb4,0x67,0x4e,0x7e,0x5a,0x35,0x6b,0xaF,0x35,0xa9,0x8a,0x12,0x73,0xd2,0xd6,0xa2,0x2b,0xd5,0xdc,0x76,0x6a,0xb3,0x9F,0x92,0xc8,0x38,0xa9,0x2d,0x6e,0xda,0xc2,0x64,0x8F,0xb6,0xba,0x96,0x0e,0x8F,0xbc,0xda,0xa4,0x9d,0xaa,0xb2,0xca,0xd9,0x8b,0x32,0x6a,0xcF,0xd9,0x67,0xcF,0xd2,0x69,0x3c,0x67,0x9F,0x23,0xab,0xa0,0xc8,0xac,0x7d,0xae,0xa2,0x82,0xdd,0xa3,0xF6,0xba,0x8a,0x0a,0x51,0xcF,0x26,0xa3,0x69,0xca,0xd5,0xc4,0x92,0x8c,0xa6,0xbb,0x34,0x15,0x4d,0x3c,0xe2,0xae,0xdd,0x5c,0xcd,0x71,0x8a,0x8b,0xe9,0x20,0x31,0x27,0x2e,0x2e,0xb6,0x5d,0x54,0x55,0x43,0x8a,0xab,0x6b,0xab,0x70,0xdb,0xa9,0xad,0xb6,0x2c,0xc2,0x95,0x9c,0x36,0x9b,0x2e,0x8e,0xaa,0x72,0x8e,0xe4,0xa6,0xd4,0x33,0xF6,0x39,0x93,0xeb,0xd0,0xac,0xc8,0xe7,0x2a,0xb6,0x34,0x32,0x6b,0x9F,0xab,0xb9,0xa4,0x8a,0xa8,0x7c,0xae,0xe6,0x02,0x3a,0x32,0xF6,0xb9,0x9a,0x76,0x48,0xaF,0x3a,0xe7,0xaa,0xc2,0xa8,0x23,0xeb,0x8e,0x2b,0x09,0x97,0x89,0x48,0x92,0xFa,0xa4,0x53,0xd4,0x3c,0x49,0x5a,0xb2,0x29,0x67,0x73,0xdb,0x61,0xc9,0xb6,0x8c,0xcd,0x93,0x00,0x38,0xaa,0x98,0x14,0x73,0x4F,0x72,0x8e,0x2c,0x4c,0x26,0xb3,0xF1,0x39,0x8a,0x30,0x9a,0xa8,0xda,0xe7,0xc8,0xc2,0xb8,0xb3,0xaa,0x8c,0x23,0x2b,0x97,0xF0,0x88,0x93,0x8e,0xa8,0x53,0xd5,0x3c,0xcd,0x39,0x9a,0x6d,0xcF,0x4c,0x5a,0xeb,0xa8,0xd2,0x28,0xbc,0xe2,0x9c,0xa3,0x0a,0xe5,0x88,0x5a,0x7a,0xae,0xcc,0x54,0xa6,0xba,0xcd,0xb9,0x33,0x57,0x99,0xee,0x34,0xe7,0xce,0x4c,0x65,0xab,0x92,0xac,0xb7,0x72,0xe1,0xae,0x4a,0xb2,0xde,0x26,0x04,0x27,0xbd,0xc9,0x7a,0x2b,0x57,0xda,0xF4,0x34,0xe3,0x09,0x2c,0x6d,0x32,0x6a,0x8F,0x27,0xF0,0xd4,0x75,0x6F,0x32,0x9e,0xc0,0xc3,0x26,0xbc,0x49,0x7b,0x02,0x0b,0xdd,0x88,0x25,0xed,0x0e,0x3c,0x6d,0xc3,0x9b,0xb4,0x3b,0xF0,0xb4,0x35,0x6F,0xd3,0xee,0xc0,0xd3,0x36,0xbc,0x4e,0xb9,0x03,0x0F,0x5b,0xF7,0x25,0xed,0x0e,0x3c,0xad,0xcd,0xdb,0x94,0x3b,0xF2,0xd0,0xF1,0xa8,0x53,0xee,0x20,0x52,0xdb,0xa2,0x4d,0xb9,0x02,0x4F,0x6d,0xF3,0x26,0xe5,0x0a,0x3c,0xb4,0x3d,0x9a,0xa4,0x3b,0xca,0x54,0x57,0x6F,0x12,0xee,0xa8,0x52,0x42,0xa3,0x4d,0xba,0xa3,0x4c,0x75,0x8d,0xd6,0xe9,0x4e,0x2a,0x55,0xc5,0xFb,0x84,0x3b,0xaa,0x54,0xd7,0x68,0x9d,0xee,0x28,0x53,0xc3,0xb3,0x49,0xba,0x03,0x4F,0x5b,0xF3,0x36,0xe9,0x8e,0x22,0x2d,0x2c,0xba,0xa4,0x27,0xF2,0xd0,0xF2,0x68,0x12,0x9e,0xa4,0x53,0x45,0x23,0x0b,0x00,0xc0,0x03};
const uint8_t spHASTA_LA_VISTA[]      PROGMEM = {0x0e,0xe0,0x3e,0x62,0x6d,0xc9,0x78,0xa8,0x89,0xed,0xd5,0x27,0xe9,0xae,0x61,0x71,0x03,0x00,0x6a,0x45,0x00,0x40,0x72,0x2F,0x80,0xa9,0x6c,0x0d,0xF0,0x55,0xe2,0x34,0xa9,0x47,0x68,0x65,0xed,0xd3,0xa4,0x9a,0x61,0xe5,0x8b,0x4F,0x93,0x7a,0x98,0x77,0x2c,0x3e,0x4d,0x6e,0x9e,0x52,0xd9,0xF8,0xb4,0x39,0x44,0x9a,0x67,0x95,0x00,0xF0,0x10,0x9e,0x00,0x62,0x3c,0x12,0x00,0x65,0x67,0x02,0xb4,0xec,0x48,0x00,0x94,0x11,0x2b,0xc9,0x22,0xd2,0x82,0x2d,0xad,0x24,0x4b,0x0d,0x0d,0x4d,0xec,0x00,0xec,0x33,0x1d,0x00,0x5c,0xc6,0x0a,0xaa,0x36,0xd7,0x50,0x3b,0xc7,0x8F,0x4a,0x2b,0xc2,0xeb,0x9c,0x2c,0x6b,0x0b,0x77,0x9b,0x73,0xea,0x94,0xcc,0x28,0xb3,0x76,0x02,0x50,0x0F,0x73,0x00,0x68,0xe1,0x0e,0x80,0x35,0x3d,0x00,0xbc,0xb2,0x9d,0x3e,0x56,0x33,0xa9,0xaa,0x73,0xFa,0x54,0xdc,0x29,0xa2,0xF6,0x19,0x62,0x0c,0xa3,0xca,0xc6,0xab,0x08,0xde,0xdd,0x3c,0x66,0x1b,0x00,0xe6,0x74,0x07,0x80,0x92,0x69,0x00,0x90,0x2b,0x57,0x9F,0x2c,0xbb,0x55,0x34,0x39,0x7d,0xd6,0x1c,0x3e,0x11,0xFb,0x74,0x41,0x6a,0xc6,0x78,0xe4,0xd5,0x17,0x45,0xe1,0x13,0xb1,0xcF,0x90,0x94,0x44,0x94,0x27,0x39,0x43,0x91,0x6a,0x5a,0x3e,0x33,0x00,0x40,0x66,0x26,0x40,0x93,0xc8,0x04,0x30,0x5e,0x15,0x00,0xc6,0xb3,0x1c,0x00,0x4c,0x47,0x00,0x40,0xa8,0x70,0x00,0x48,0x15,0x06,0xc0,0x31,0xc3,0x00,0xc0,0x67,0x38,0x00,0x7a,0xF7,0x00,0xe0,0xe6,0x71,0x86,0xe0,0x22,0xad,0xb2,0xd2,0x1a,0x82,0x8b,0x88,0x8a,0x5a,0x6b,0xc9,0xc6,0xc3,0x42,0x1b,0x3b,0x00,0x65,0x77,0x07,0x80,0x10,0x65,0x00,0x92,0x22,0x1c,0x20,0x8d,0xa5,0x03,0x98,0x33,0x33,0x00,0xb4,0xe1,0x06,0x00,0x31,0xd3,0x00,0x20,0x54,0xb5,0x2e,0x33,0x49,0x4b,0x8F,0x33,0x96,0x22,0x34,0x24,0xdc,0x8a,0x01,0x80,0x8F,0x30,0x00,0xF0,0x95,0x0a,0xc0,0xbd,0xca,0x00,0x20,0x67,0xb5,0x26,0x4a,0xc9,0x4c,0x4d,0xd2,0x9a,0xcc,0x35,0xcc,0x3d,0x6e,0x9b,0x32,0xb3,0xF0,0xb0,0x38,0x2d,0xcb,0x42,0xc2,0x52,0x6d,0xb7,0x2c,0x73,0x73,0xcb,0x48,0xda,0xca,0xc2,0x24,0x2c,0xb4,0x6e,0x2b,0x33,0x97,0x8c,0xF4,0x38,0x2d,0x2b,0x4c,0x43,0xc2,0xe3,0x2a,0x00,0xb8,0x2a,0x05,0x80,0x54,0xa1,0x00,0x10,0x32,0x1d,0x80,0x9c,0xd4,0xa9,0x6b,0x66,0x97,0x8c,0xb9,0xa7,0xae,0x99,0x5d,0x2a,0x97,0x9e,0xb6,0x15,0x76,0x8d,0x9c,0x7a,0x86,0x12,0x28,0xa2,0x6b,0x4a,0x01,0xa2,0xa5,0x0a,0x80,0xF4,0x3e,0x01,0x90,0xd6,0x66,0x8d,0x55,0x61,0x46,0x67,0xd4,0x35,0x66,0xc9,0x19,0x13,0x93,0xdb,0x98,0xa5,0xba,0x76,0x26,0x69,0x5b,0xd5,0x6a,0x14,0x11,0x47,0x00,0xc0,0x66,0x29,0x00,0x78,0xeb,0x33,0x55,0xcF,0xaa,0x1d,0xb3,0xd7,0x5c,0x2d,0xb9,0x74,0x57,0x5d,0x53,0x31,0x64,0x3a,0x55,0x65,0x2d,0xcd,0xb1,0x4a,0xe7,0xd4,0xb5,0x14,0x4d,0x11,0x53,0x55,0xd7,0x9a,0x0d,0xb9,0x6F,0x55,0x19,0x5b,0x52,0x12,0xb9,0x59,0xd6,0x01,0xcc,0x7b,0x3b,0x80,0x2b,0x6b,0x03,0x00,0xa9,0x6d,0x00,0xa4,0xbc,0x0c,0xc0,0xb4,0xa7,0x02,0xa0,0xF1,0x54,0x00,0xd0,0x11,0x02,0x80,0xce,0x43,0x01,0xc0,0x66,0x29,0x00,0xb8,0x4c,0x01,0x00,0x9F,0xa5,0x00,0xe0,0x23,0x05,0x00,0x9c,0xa7,0x00,0x80,0x8b,0x12,0x00,0x30,0x9e,0x02,0x00,0x36,0x12,0x08,0xdd,0x65,0x98,0x9b,0xd9,0x7e};
const uint8_t spONE_SMALL_STEP[]      PROGMEM = {0x06,0x88,0x11,0x75,0x00,0xb9,0x52,0x37,0x20,0x16,0x9a,0x02,0xa4,0x82,0x13,0x80,0x90,0xb1,0x15,0x60,0x02,0x99,0x01,0x52,0x82,0x70,0x40,0xe9,0x94,0x01,0x28,0x93,0x3b,0x00,0x65,0xcb,0x3a,0x20,0x77,0x4e,0x05,0x84,0xcc,0xee,0x00,0x77,0x78,0x02,0xe0,0x27,0x6F,0x02,0xFc,0x96,0x3d,0x4b,0x1c,0xb6,0x16,0x96,0xF4,0x2c,0xb1,0xd9,0x68,0x5a,0xdb,0x33,0xc7,0xa1,0x2d,0x95,0xcb,0xce,0x94,0xba,0xb4,0x56,0x2d,0x3d,0x53,0x5e,0x12,0xd1,0xd9,0xe6,0x8c,0xe5,0x48,0x5a,0x76,0xdd,0x33,0x96,0x25,0xa5,0x9d,0x4d,0xcF,0x58,0x9e,0x95,0xa4,0x27,0x75,0x40,0xee,0x94,0x0e,0x28,0x89,0xd2,0x01,0x25,0x52,0x05,0xa0,0x24,0xae,0x00,0xe4,0x2c,0xe5,0x80,0x14,0xb9,0x0c,0x10,0x3d,0x87,0x01,0x4a,0xa6,0x30,0x40,0x8e,0x1c,0x06,0xc8,0x85,0xc3,0x01,0xa5,0x50,0x38,0xa0,0x14,0x72,0x05,0xc4,0x40,0x26,0x80,0xe0,0x49,0x15,0x90,0x02,0x99,0x01,0x52,0x96,0x30,0x40,0xaa,0x52,0x0e,0x08,0x5b,0xF7,0xcc,0xb1,0xeb,0x66,0x69,0x9c,0x33,0xc7,0x6e,0x13,0xad,0x49,0xce,0x14,0x9b,0x4e,0x94,0x56,0x3d,0x73,0x6c,0x3a,0x56,0x96,0xF4,0x4c,0xb1,0x5b,0x5b,0x5a,0xb3,0x33,0xc5,0xa6,0xed,0xe9,0x75,0xcF,0x14,0x9b,0xb6,0x87,0xd5,0x3d,0x53,0xec,0x3a,0x16,0x5e,0xF7,0x4c,0x71,0x68,0x7b,0x5a,0xdd,0x33,0xc7,0xa1,0x6d,0xe9,0x49,0xcF,0x1c,0x87,0xb6,0x87,0x25,0x3d,0x73,0x1c,0xda,0x91,0xd2,0xF4,0x2c,0xb1,0xeb,0x64,0x9a,0xd5,0x00,0x84,0x2d,0xed,0x80,0x9c,0xb9,0x0c,0x50,0x2a,0x87,0x01,0x4a,0x23,0x73,0x40,0x99,0x52,0x0e,0x28,0x93,0x4b,0x01,0xd1,0xb1,0x1a,0x20,0x0d,0x09,0x07,0xe4,0x26,0x95,0x80,0xb2,0xa9,0x0b,0x90,0x3b,0xF6,0x99,0xea,0x96,0xd4,0x91,0x24,0x67,0xae,0x4F,0x52,0x46,0x2b,0x9F,0xb9,0x3e,0x0d,0x69,0x8F,0x73,0xe6,0x7a,0x24,0x74,0xbc,0xee,0x99,0xcb,0x90,0xb4,0xF6,0x66,0x67,0xc9,0x5b,0xc3,0x32,0x9a,0x25,0x20,0x4e,0x6a,0x03,0xc4,0x46,0x65,0x80,0xd8,0xb8,0x04,0x60,0x9c,0x98,0x00,0x94,0x61,0x15,0x80,0xb2,0xac,0x02,0x50,0x9a,0x54,0x00,0x4a,0xb3,0x0b,0xc0,0x59,0x32,0x05,0xc4,0x80,0x16,0x80,0xd2,0xb9,0xce,0x92,0xae,0x66,0x97,0x55,0x39,0x63,0x7e,0x16,0x51,0x16,0x26,0x01,0xe9,0x50,0x25,0x20,0x1d,0xaa,0x00,0xc4,0x45,0xed,0x80,0xd4,0xa8,0x1d,0x10,0x3b,0x4F,0x00,0x62,0xe3,0x4e,0x40,0x3e,0xd4,0x09,0xc8,0x0b,0xbb,0x00,0x65,0x61,0x9F,0xb9,0x3e,0x49,0xa9,0x68,0x7a,0xe6,0xFa,0xac,0xa4,0x2c,0xe9,0x99,0xdb,0xF3,0xe6,0xb6,0xa4,0x67,0x6e,0xcF,0x4b,0xc6,0xe2,0x34,0xa0,0x76,0xae,0x06,0x94,0xc2,0xdd,0x80,0x52,0xa9,0x1b,0x90,0x2b,0xF5,0x59,0xea,0xd5,0xd0,0xF6,0xa4,0x67,0x2e,0x43,0xca,0x3b,0x92,0x9e,0x39,0x2F,0x29,0xab,0x68,0x7b,0xa6,0xFc,0x24,0x3d,0xbd,0x5d,0x00,0xd2,0xa0,0x72,0x40,0xee,0xe4,0x06,0x48,0x0d,0xcd,0x00,0xa9,0x91,0x1b,0x20,0x56,0x72,0x05,0xc4,0x40,0xa1,0x80,0x14,0x29,0x14,0x10,0x3d,0xb9,0x02,0x82,0x27,0x55,0x40,0x70,0x6c,0x02,0x88,0x96,0x4c,0x00,0xc1,0xb1,0x09,0x20,0x78,0x56,0x05,0xa4,0x28,0xe6,0x80,0x34,0xb8,0x1d,0x10,0x1b,0xb7,0x01,0x62,0x97,0x76,0x40,0x1c,0x3c,0x0a,0x08,0x45,0xd2,0x00,0xa9,0x70,0x28,0x20,0x46,0x72,0x05,0x84,0xc8,0xae,0x80,0x98,0x48,0x15,0xe0,0x3d,0x9b,0x00,0x7c,0x60,0x15,0x80,0xb2,0x22,0x02,0xF0,0x96,0x4d,0x01,0xde,0xb3,0x09,0xc0,0x7b,0x76,0x01,0x04,0xcF,0xa6,0x80,0xe0,0x44,0x15,0x10,0x1d,0x9b,0x01,0x52,0xe1,0x74,0x40,0xea,0xdc,0x0a,0x48,0x95,0xc3,0x00,0xa9,0x4b,0x1a,0x20,0x36,0x2e,0x03,0xc4,0x22,0xa9,0x80,0xe0,0xd8,0x04,0x60,0x8c,0xa8,0x00,0x9c,0x11,0x13,0x80,0xF7,0x24,0x0a,0xF0,0x4e,0x4c,0x01,0xde,0x8a,0x2b,0x20,0x38,0x56,0x01,0x78,0x2b,0x26,0x00,0x6F,0xd9,0x04,0xe0,0xac,0x98,0x02,0xa2,0x67,0x53,0x80,0xb1,0xac,0x02,0xd0,0x86,0x5d,0x01,0xd6,0xb1,0x0b,0x40,0x1b,0x71,0x05,0x58,0xcb,0xa6,0x00,0x6b,0xc5,0x14,0xe0,0x8d,0x98,0x00,0xbc,0x65,0x13,0x80,0x35,0x62,0x02,0xF0,0x96,0x55,0x01,0xce,0x89,0x29,0xc0,0x3b,0x36,0x05,0x78,0x2b,0x66,0x80,0x54,0xd9,0x0a,0x10,0x36,0x4F,0x01,0xc2,0x93,0x3a,0x6b,0x9c,0x5e,0xd6,0x5a,0xF7,0x2c,0x71,0x59,0x69,0x5b,0xbb,0xb3,0xc4,0xa9,0xa5,0x65,0x5d,0xcF,0x9c,0x9a,0xb4,0x67,0xb4,0x3d,0x73,0xee,0x5c,0xd1,0xd6,0x2e,0x01,0xa9,0xe1,0x18,0x20,0x66,0x4c,0x03,0xe4,0x4c,0x61,0x80,0x9c,0x39,0x0c,0x90,0x13,0xa5,0x01,0x52,0xe2,0x32,0x40,0x0a,0x9c,0x06,0x48,0x91,0x52,0x01,0x31,0x72,0x28,0x20,0x27,0x76,0x05,0xa4,0x28,0xa1,0x80,0x14,0xd8,0x15,0x90,0xa2,0xba,0x02,0x62,0x14,0x53,0x40,0x8e,0xe4,0x0a,0x88,0x51,0x5c,0x00,0xc1,0xb3,0x0a,0x20,0x46,0x36,0x01,0xc4,0xc0,0xa6,0x80,0xe8,0xd4,0x04,0x10,0x3d,0x9b,0x02,0xa2,0x17,0x53,0x40,0x0c,0xa2,0x0a,0x88,0x4e,0x4c,0x01,0xd1,0x8b,0x2a,0x20,0x06,0x56,0x01,0x04,0xcF,0xae,0x80,0x14,0xc4,0x14,0x10,0xbd,0x9a,0x02,0x52,0x60,0x13,0x40,0x0c,0xec,0x02,0x08,0x5e,0x54,0x00,0xde,0xb0,0x29,0x20,0x58,0x51,0x01,0x04,0x2F,0x2a,0x00,0xeF,0xc4,0x04,0x10,0xac,0x98,0x00,0xbc,0x15,0x53,0x40,0xb4,0xac,0x0a,0x88,0x5e,0x54,0x01,0xc1,0xb1,0x09,0x20,0x38,0x31,0x05,0xc4,0x20,0x2a,0x80,0x60,0xc5,0x04,0x10,0x9c,0xba,0x03,0xd2,0xe0,0x3e,0x7d,0x1e,0x92,0xd6,0xde,0xF4,0x2c,0x69,0x68,0x6b,0xF9,0x9c,0xb3,0xc4,0xa9,0xe9,0x15,0x75,0xcF,0x92,0xa6,0x56,0x54,0xd6,0x39,0x4b,0x59,0x5c,0x5e,0x91,0xec,0x2c,0xF5,0x6b,0x4a,0x7b,0xd6,0x33,0xd7,0x27,0xa1,0x63,0x6d,0xcF,0x50,0xaF,0xa4,0x8c,0xb7,0x3d,0x4b,0xdd,0x9c,0x3a,0xde,0xF6,0xac,0x75,0x73,0x7a,0x5b,0xd3,0xb3,0xe6,0xc9,0x15,0x99,0x4d,0xcF,0x9a,0xb6,0x44,0x56,0xd4,0x35,0x40,0xe8,0x9c,0x06,0x48,0x5d,0xd2,0x01,0xb1,0x53,0x3b,0x20,0x75,0x6e,0x07,0xa4,0x41,0x63,0x80,0x30,0x35,0x1c,0x10,0x87,0x64,0x02,0xd2,0xc4,0x3e,0x53,0x99,0x5c,0x1a,0xda,0xF4,0xcc,0x75,0x4a,0x48,0x6b,0xd2,0xb3,0xd4,0x21,0x29,0xad,0x49,0x0b,0x90,0x03,0x55,0x01,0x4a,0xe4,0x2a,0x40,0xc9,0xdc,0x01,0xc8,0x19,0xdb,0x00,0x29,0x89,0x1b,0x20,0x45,0x31,0x05,0xa4,0xc8,0x26,0x80,0x10,0xc5,0x15,0x10,0xbc,0x98,0x00,0xa2,0x67,0x15,0x40,0x0c,0x62,0x0a,0x48,0x59,0x2c,0x00,0x69,0xF0,0x04,0x20,0x75,0x9e,0x04,0xa4,0x49,0x1d,0x80,0x38,0xb1,0xcF,0x98,0x9F,0x44,0x84,0xc6,0x5d,0x6b,0x9a,0x96,0x96,0x16,0x57,0x01,0xb1,0x71,0x28,0x20,0x66,0x72,0x03,0xe4,0xc6,0x15,0x80,0x3c,0x71,0x0a,0x50,0x26,0x76,0x01,0xea,0xc0,0x2e,0x40,0x6d,0x38,0x05,0xc8,0x85,0xb7,0x00,0xa5,0x60,0x17,0x20,0x17,0x9a,0x04,0xe4,0x8e,0x93,0x80,0xd4,0x69,0x02,0x90,0x3a,0x4d,0x02,0x52,0xa7,0x71,0x40,0x68,0xbc,0x0e,0x48,0x8d,0x2b,0x01,0xb9,0xd1,0x24,0x20,0x77,0x9a,0x02,0xa4,0x4e,0x73,0xba,0x3c,0xb9,0xbc,0x3d,0xdd,0x59,0x72,0xe7,0xF2,0x89,0xa4,0x09,0x88,0x8d,0xa7,0x00,0x71,0xF0,0x14,0x20,0x76,0x9e,0x04,0xc4,0x4a,0x13,0x80,0x54,0x68,0x03,0x10,0x2b,0xaF,0x03,0x52,0xa5,0x09,0x40,0xec,0x3c,0x0e,0x88,0x95,0xdb,0x01,0xa5,0x53,0x05,0x20,0x76,0x1e,0x07,0xc4,0x46,0x6d,0x80,0x54,0xc8,0x0d,0x90,0x1a,0x97,0x01,0x52,0xa5,0x12,0x80,0xF7,0x12,0x02,0x08,0x81,0x4d,0x01,0xb1,0x48,0x38,0x20,0x4d,0x2e,0x07,0xa4,0x4e,0x9d,0x80,0x3c,0xa9,0x0b,0x10,0x3b,0x8F,0x01,0x54,0xd3,0x52,0x40,0x4a,0x1c,0x0a,0x88,0x81,0x43,0x01,0x29,0xb2,0x09,0x20,0x79,0x72,0x05,0xa4,0xc0,0xae,0x80,0x68,0x45,0x05,0x10,0x03,0xab,0x02,0x62,0x64,0x77,0x40,0x1a,0xd2,0x09,0x48,0x83,0xdb,0x01,0xb1,0xF2,0x38,0x20,0x76,0x6e,0x07,0xc4,0xc6,0x6d,0x80,0x58,0x39,0x05,0x10,0x1c,0xa9,0x00,0x9c,0x65,0x13,0x80,0x77,0x6c,0x02,0x08,0x8e,0x4d,0x01,0xc1,0xb1,0x09,0x20,0x05,0x56,0x02,0x00,0x87,0x0a,0x00,0x40,0xba,0xae,0xc2,0xdc,0xcc,0xF6,0x03};
const uint8_t spHMMM_BEER[]           PROGMEM = {0x00,0x50,0x9a,0x42,0xc2,0x5c,0xc3,0xc9,0xe8,0x1a,0x53,0x35,0x73,0x27,0xa5,0x8F,0xcc,0x3c,0x3c,0x12,0xa5,0xde,0x2b,0x0b,0x77,0x73,0xd3,0xFa,0x44,0xcd,0xc3,0xc2,0x71,0xeb,0x32,0x51,0x0F,0x0F,0x27,0xad,0x4b,0x2c,0xcc,0xdc,0x9d,0x94,0xd6,0x2b,0x4b,0x0d,0x77,0xdc,0x9a,0x20,0x3c,0xd4,0x22,0xF6,0x68,0x32,0x93,0x48,0x09,0x27,0xa3,0xc9,0x9c,0xc3,0xdc,0x6d,0xb7,0x26,0x73,0x6a,0x49,0x8d,0x3b,0x9a,0x2a,0xb0,0x3c,0xdc,0xce,0x6a,0x9a,0xc4,0x74,0x77,0x3b,0xab,0x69,0x02,0xd3,0xdd,0xec,0x8c,0xa6,0x08,0x2a,0x8d,0xb0,0x33,0x9a,0x22,0xa8,0x34,0x5c,0xc9,0x6a,0x9a,0x20,0x4b,0x77,0xbb,0xab,0xa9,0x9c,0xd2,0xdd,0x9d,0x8c,0x26,0x71,0x2e,0x4d,0xb7,0xdb,0xea,0xc4,0xb9,0x2d,0xdc,0xc9,0x68,0x32,0xe3,0x4a,0x73,0x27,0xa3,0x49,0x4c,0x32,0x25,0x1c,0xb7,0x26,0x08,0x2d,0x73,0x73,0xdb,0x1a,0x2F,0x2d,0x2d,0xc2,0x49,0x6b,0x02,0x09,0x0F,0x0F,0x3b,0xad,0x09,0x2c,0x3c,0x2c,0x1c,0x97,0xc6,0xc8,0x88,0x74,0x77,0x5d,0x5a,0xa5,0x2d,0x22,0x22,0x49,0x69,0x03,0xF1,0x28,0x8F,0xc4,0xad,0x8b,0xd4,0xc2,0x23,0xe3,0x8c,0xae,0x50,0x53,0xF3,0x70,0x92,0x3a,0x23,0x2d,0xbc,0x3c,0x4e,0xe9,0x23,0x35,0xcb,0x8c,0x38,0xa5,0x2F,0xc4,0x38,0x3d,0x92,0x94,0x21,0x51,0xd3,0xca,0x88,0x5d,0xc6,0x24,0xc4,0xdd,0x3c,0x71,0x19,0x92,0x50,0x09,0x0F,0xd5,0x6d,0xac,0xd4,0x55,0xdc,0x1d,0x97,0xb1,0x10,0xd1,0x34,0x77,0x95,0xc6,0x24,0xc4,0xd5,0x3d,0x4e,0x9a,0x0a,0x13,0x31,0x0d,0x3b,0x65,0xea,0x5c,0x59,0xd4,0x1c,0xa7,0xa9,0x52,0x13,0x35,0xb7,0x9d,0xe6,0x2c,0xd5,0xd4,0x4c,0x71,0x9a,0xab,0x70,0x16,0x31,0xc5,0x65,0xea,0xc2,0xcd,0xdc,0xe5,0x08,0x40,0x49,0x37,0x05,0x04,0x2b,0xd6,0xda,0x24,0xd5,0x62,0x22,0xce,0xea,0x1a,0x67,0xb3,0xae,0x5a,0xa7,0x1b,0x9a,0x8d,0x2b,0x67,0x9F,0xae,0x3b,0x36,0xaa,0xae,0x7d,0xda,0xee,0xc8,0xa9,0xbb,0xF6,0x69,0x47,0x64,0x23,0x9F,0x56,0xa7,0x1d,0x85,0x0d,0xbd,0x5b,0x9F,0x76,0x64,0x36,0xac,0x6e,0x7c,0xda,0x5e,0xd8,0xb0,0x6b,0xF6,0x69,0x47,0x13,0xc3,0xa8,0xd6,0xa7,0x1d,0xc3,0x1c,0x35,0x5b,0x9F,0xb6,0x0F,0x35,0x88,0xec,0x7c,0xda,0x3e,0xc4,0x28,0xb3,0xc9,0x69,0xFb,0x50,0x07,0x8F,0xd6,0xa7,0x1b,0xc3,0x1d,0xc5,0xbb,0x9c,0xae,0x4F,0x73,0xb0,0x68,0x73,0xba,0x3e,0xd8,0x30,0x63,0xce,0xe9,0xFa,0x14,0x25,0x8F,0x25,0xa7,0xeb,0xd3,0x94,0xcd,0xd6,0x9c,0xae,0x4F,0x55,0x72,0x5F,0xbd,0xba,0x36,0xc9,0x38,0xb3,0xd1,0xe9,0xda,0x10,0x51,0xb7,0x39,0xa7,0x6F,0x43,0x44,0xdd,0x5b,0x9F,0xbe,0x75,0x16,0x8d,0xe8,0x3c,0xFa,0x52,0xd0,0x22,0xb3,0x51,0xeb,0x4b,0x42,0xaF,0xc8,0x9a,0xa3,0x2F,0x91,0x24,0x3a,0x52,0x8d,0x3e,0x5b,0xe1,0xec,0x4c,0xdc,0x86,0x64,0x54,0xb3,0xcb,0x76,0x19,0x93,0x23,0xcb,0xF6,0x58,0x65,0x2c,0xc2,0xc9,0xa2,0x12,0xb7,0xa9,0xa9,0x60,0xd6,0x4c,0x5c,0xa6,0x2a,0x4d,0x24,0xc2,0x55,0x99,0xaa,0x57,0x16,0x37,0x25,0x65,0x69,0xca,0x59,0xd4,0x63,0xb7,0xa5,0xab,0x10,0x56,0x77,0x94,0xb6,0x6e,0x43,0x54,0x4d,0x0e,0xa4,0x6d,0xb8,0x08,0xb7,0x70,0x4c,0x80,0x28,0xcc,0x00,0x00,0x1e};

void setup() {
  voice.say(spWHAT_IS_THY_BIDDING);
  voice.say(spHASTA_LA_VISTA);
  voice.say(spONE_SMALL_STEP);
  voice.say(spHMMM_BEER);
}
void loop() {
}
