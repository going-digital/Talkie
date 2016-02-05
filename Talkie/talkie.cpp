// Talkie library
// Copyright 2011 Peter Knight
// This code is released under GPLv2 license.

#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include <avr/io.h>
 #include "WProgram.h"
#endif
#include "talkie.h"

#define FS 8000 // Speech engine sample rate
#define OUTPUT_PIN 11 // Only 3 or 11 supported at the moment

#if OUTPUT_PIN == 3
	#define OUTPUT_BIT COM2B1
	#define LIMITING_REG OCR2B
#else
	#define OUTPUT_BIT COM2A1
	#define LIMITING_REG OCR2A
#endif

Talkie* lastInstance;

const uint8_t tmsEnergyPgm[]    PROGMEM = {0x00,0x02,0x03,0x04,0x05,0x07,0x0a,0x0f,0x14,0x20,0x29,0x39,0x51,0x72,0xa1,0xff};
const uint8_t tmsPeriodPgm[] 	PROGMEM = {0x00,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2D,0x2F,0x31,0x33,0x35,0x36,0x39,0x3B,0x3D,0x3F,0x42,0x45,0x47,0x49,0x4D,0x4F,0x51,0x55,0x57,0x5C,0x5F,0x63,0x66,0x6A,0x6E,0x73,0x77,0x7B,0x80,0x85,0x8A,0x8F,0x95,0x9A,0xA0};
const int16_t tmsK1Pgm[]   	 	PROGMEM = {0x82C0,0x8380,0x83C0,0x8440,0x84C0,0x8540,0x8600,0x8780,0x8880,0x8980,0x8AC0,0x8C00,0x8D40,0x8F00,0x90C0,0x92C0,0x9900,0xA140,0xAB80,0xB840,0xC740,0xD8C0,0xEBC0,0x0000,0x1440,0x2740,0x38C0,0x47C0,0x5480,0x5EC0,0x6700,0x6D40};
const int16_t tmsK2Pgm[]     	PROGMEM = {0xAE00,0xB480,0xBB80,0xC340,0xCB80,0xD440,0xDDC0,0xE780,0xF180,0xFBC0,0x0600,0x1040,0x1A40,0x2400,0x2D40,0x3600,0x3E40,0x45C0,0x4CC0,0x5300,0x5880,0x5DC0,0x6240,0x6640,0x69C0,0x6CC0,0x6F80,0x71C0,0x73C0,0x7580,0x7700,0x7E80};
const int8_t tmsK3Pgm[]      	PROGMEM = {0x92,0x9F,0xAD,0xBA,0xC8,0xD5,0xE3,0xF0,0xFE,0x0B,0x19,0x26,0x34,0x41,0x4F,0x5C};
const int8_t tmsK4Pgm[]      	PROGMEM = {0xAE,0xBC,0xCA,0xD8,0xE6,0xF4,0x01,0x0F,0x1D,0x2B,0x39,0x47,0x55,0x63,0x71,0x7E};
const int8_t tmsK5Pgm[]      	PROGMEM = {0xAE,0xBA,0xC5,0xD1,0xDD,0xE8,0xF4,0xFF,0x0B,0x17,0x22,0x2E,0x39,0x45,0x51,0x5C};
const int8_t tmsK6Pgm[]      	PROGMEM = {0xC0,0xCB,0xD6,0xE1,0xEC,0xF7,0x03,0x0E,0x19,0x24,0x2F,0x3A,0x45,0x50,0x5B,0x66};
const int8_t tmsK7Pgm[]      	PROGMEM = {0xB3,0xBF,0xCB,0xD7,0xE3,0xEF,0xFB,0x07,0x13,0x1F,0x2B,0x37,0x43,0x4F,0x5A,0x66};
const int8_t tmsK8Pgm[]      	PROGMEM = {0xC0,0xD8,0xF0,0x07,0x1F,0x37,0x4F,0x66};
const int8_t tmsK9Pgm[]      	PROGMEM = {0xC0,0xD4,0xE8,0xFC,0x10,0x25,0x39,0x4D};
const int8_t tmsK10Pgm[]     	PROGMEM = {0xCD,0xDF,0xF1,0x04,0x16,0x20,0x3B,0x4D};
const int8_t chirpPgm[]			PROGMEM = {0x00,0x2a,0xd4,0x32,0xb2,0x12,0x25,0x14,0x02,0xe1,0xc5,0x02,0x5f,0x5a,0x05,0x0f,0x26,0xfc,0xa5,0xa5,0xd6,0xdd,0xdc,0xfc,0x25,0x2b,0x22,0x21,0x0f,0xff,0xf8,0xee,0xed,0xef,0xf7,0xf6,0xfa,0x00,0x03,0x02,0x01};

Talkie::Talkie() {
	//TODO: Record normal register values here
	readPgmArrayU(tmsEnergy, tmsEnergyPgm, 0x10);
	readPgmArrayU(tmsPeriod, tmsPeriodPgm, 0x40);
	readPgmArrayW(tmsK1, tmsK1Pgm, 0x20);
	readPgmArrayW(tmsK2, tmsK2Pgm, 0x20);
	readPgmArray(tmsK3, tmsK3Pgm, 0x10);
	readPgmArray(tmsK4, tmsK4Pgm, 0x10);
	readPgmArray(tmsK5, tmsK5Pgm, 0x10);
	readPgmArray(tmsK6, tmsK6Pgm, 0x10);
	readPgmArray(tmsK7, tmsK7Pgm, 0x10);
	readPgmArray(tmsK8, tmsK8Pgm, 0x08);
	readPgmArray(tmsK9, tmsK9Pgm, 0x08);
	readPgmArray(tmsK10, tmsK10Pgm, 0x08);
	readPgmArray(chirp, chirpPgm, CHIRP_SIZE);
	lastInstance = this;
}

Talkie::~Talkie() {
	lastInstance = NULL;
	end();
}

void Talkie::readPgmArrayU(uint8_t* array, const uint8_t* ptr, int size) {
	for (int i=0; i<size; i++) {
		array[i] = pgm_read_byte(ptr + i);
	}
}

void Talkie::readPgmArrayW(int16_t* array, const int16_t* ptr, int size) {
	for (int i=0; i<size; i++) {
		array[i] = pgm_read_word_near(ptr + i);
	}
}

void Talkie::readPgmArray(int8_t* array, const int8_t* ptr, int size) {
	for (int i=0; i<size; i++) {
		array[i] = pgm_read_byte(ptr + i);
	}
}

void Talkie::begin() {
	// Record old timer values for later restoration 
	R_TCCR2A = TCCR2A;
	R_TCCR2B = TCCR2B; 
	R_TIMSK2=TIMSK2; 
	R_TCCR1A=TCCR1A; 
	R_TCCR1B=TCCR1B; 
	R_TCNT1=TCNT1; 
	R_OCR1A=OCR1A; 
	R_TIMSK1=TIMSK1; 
	R_LIMITING_REG = LIMITING_REG;


	pinMode(OUTPUT_PIN, OUTPUT);
	// Timer 2 set up as a 62500Hz PWM.
	//
	// The PWM 'buzz' is well above human hearing range and is
	// very easy to filter out.
	//
	TCCR2A = _BV(OUTPUT_BIT) | _BV(WGM21) | _BV(WGM20);
	TCCR2B = _BV(CS20);
	TIMSK2 = 0;

	// Unfortunately we can't calculate the next sample every PWM cycle
	// as the routine is too slow. So use Timer 1 to trigger that.
	
	// Timer 1 set up as a 8000Hz sample interrupt
	TCCR1A = 0;
	TCCR1B = _BV(WGM12) | _BV(CS10);
	TCNT1 = 0;
	OCR1A = F_CPU / FS;
	TIMSK1 = _BV(OCIE1A);
}

void Talkie::end() {
	// Restore old timer register values
	TCCR2A = R_TCCR2A ;
	TCCR2B = R_TCCR2B; 
	TIMSK2 = R_TIMSK2; 
	TCCR1A = R_TCCR1A; 
	TCCR1B = R_TCCR1B; 
	TCNT1 = R_TCNT1; 
	OCR1A = R_OCR1A; 
	TIMSK1 = R_TIMSK1; 
	LIMITING_REG = R_LIMITING_REG;
}

void Talkie::setPtr(const uint8_t* addr) {
	ptrAddr = addr;
	ptrBit = 0;
}

// The ROMs used with the TI speech were serial, not byte wide.
// Here's a handy routine to flip ROM data which is usually reversed.
uint8_t Talkie::rev(uint8_t a) {
	// 76543210
	a = (a>>4) | (a<<4); // Swap in groups of 4
	// 32107654
	a = ((a & 0xcc)>>2) | ((a & 0x33)<<2); // Swap in groups of 2
	// 10325476
	a = ((a & 0xaa)>>1) | ((a & 0x55)<<1); // Swap bit pairs
	// 01234567
	return a;
}

uint8_t Talkie::getBits(uint8_t bits) {
	uint8_t value;
	uint16_t data;
	data = rev(pgm_read_byte(ptrAddr))<<8;
	if (ptrBit+bits > 8) {
		data |= rev(pgm_read_byte(ptrAddr+1));
	}
	data <<= ptrBit;
	value = data >> (16-bits);
	ptrBit += bits;
	if (ptrBit >= 8) {
		ptrBit -= 8;
		ptrAddr++;
	}
	return value;
}

void Talkie::say(const uint8_t* addr) {
	uint8_t energy;
	setPtr(addr);
	do {
		uint8_t repeat;

		// Read speech data, processing the variable size frames.
		
		energy = getBits(4);
		if (energy == 0) {
			// Energy = 0: rest frame
			synthEnergy = 0;
		} else if (energy == 0xf) {
			// Energy = 15: stop frame. Silence the synthesiser.
			synthEnergy = 0;
			synthK1 = 0;
			synthK2 = 0;
			synthK3 = 0;
			synthK4 = 0;
			synthK5 = 0;
			synthK6 = 0;
			synthK7 = 0;
			synthK8 = 0;
			synthK9 = 0;
			synthK10 = 0;
		} else {
			synthEnergy = tmsEnergy[energy];
			repeat = getBits(1);
			synthPeriod = tmsPeriod[getBits(6)];
			// A repeat frame uses the last coefficients
			if (!repeat) {
				// All frames use the first 4 coefficients
				synthK1 = tmsK1[getBits(5)];
				synthK2 = tmsK2[getBits(5)];
				synthK3 = tmsK3[getBits(4)];
				synthK4 = tmsK4[getBits(4)];
				if (synthPeriod) {
					// Voiced frames use 6 extra coefficients.
					synthK5 = tmsK5[getBits(4)];
					synthK6 = tmsK6[getBits(4)];
					synthK7 = tmsK7[getBits(4)];
					synthK8 = tmsK8[getBits(3)];
					synthK9 = tmsK9[getBits(3)];
					synthK10 = tmsK10[getBits(3)];
				}
			}
		}
		delay(25);
	} while (energy != 0xf);
}

void Talkie::interrupt() {
	int16_t u0,u1,u2,u3,u4,u5,u6,u7,u8,u9,u10;

	LIMITING_REG = nextPwm;
	sei();
	if (synthPeriod) {
		// Voiced source
		if (periodCounter < synthPeriod) {
			periodCounter++;
		} else {
			periodCounter = 0;
		}
		if (periodCounter < CHIRP_SIZE) {
			u10 = ((chirp[periodCounter]) * (uint32_t) synthEnergy) >> 8;
		} else {
			u10 = 0;
		}
	} else {
	// Unvoiced source
		static uint16_t synthRand = 1;
		synthRand = (synthRand >> 1) ^ ((synthRand & 1) ? 0xB800 : 0);
		u10 = (synthRand & 1) ? synthEnergy : -synthEnergy;
	}
	// Lattice filter forward path
	u9 = u10 - (((int16_t)synthK10*x9) >> 7);
	u8 = u9 - (((int16_t)synthK9*x8) >> 7);
	u7 = u8 - (((int16_t)synthK8*x7) >> 7);
	u6 = u7 - (((int16_t)synthK7*x6) >> 7);
	u5 = u6 - (((int16_t)synthK6*x5) >> 7);
	u4 = u5 - (((int16_t)synthK5*x4) >> 7);
	u3 = u4 - (((int16_t)synthK4*x3) >> 7);
	u2 = u3 - (((int16_t)synthK3*x2) >> 7);
	u1 = u2 - (((int32_t)synthK2*x1) >> 15);
	u0 = u1 - (((int32_t)synthK1*x0) >> 15);

	// Output clamp
	if (u0 > 511) u0 = 511;
	if (u0 < -512) u0 = -512;

	// Lattice filter reverse path
	x9 = x8 + (((int16_t)synthK9*u8) >> 7);
	x8 = x7 + (((int16_t)synthK8*u7) >> 7);
	x7 = x6 + (((int16_t)synthK7*u6) >> 7);
	x6 = x5 + (((int16_t)synthK6*u5) >> 7);
	x5 = x4 + (((int16_t)synthK5*u4) >> 7);
	x4 = x3 + (((int16_t)synthK4*u3) >> 7);
	x3 = x2 + (((int16_t)synthK3*u2) >> 7);
	x2 = x1 + (((int32_t)synthK2*u1) >> 15);
	x1 = x0 + (((int32_t)synthK1*u0) >> 15);
	x0 = u0;

	nextPwm = (u0>>2)+0x80;
}


ISR(TIMER1_COMPA_vect) {
	if (lastInstance!=NULL) {
		lastInstance->interrupt();
	}
}
