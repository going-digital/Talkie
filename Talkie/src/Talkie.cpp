// Talkie library
// Copyright 2011 Peter Knight
// This code is released under GPLv2 license.

// GaryA 4/2018 Modified const variables & pointers to compile in Arduino 1.6 onwards
//				Also changed signed int arrays to decimal to show negative numbers
//				properly and prevent warnings

#include "Arduino.h"
#include "Talkie.h"

#define FS 8000 // Speech engine sample rate

uint8_t synthPeriod;
uint16_t synthEnergy;
int16_t synthK1,synthK2;
int8_t synthK3,synthK4,synthK5,synthK6,synthK7,synthK8,synthK9,synthK10;

uint8_t tmsEnergy[0x10] = {0x00,0x02,0x03,0x04,0x05,0x07,0x0a,0x0f,0x14,0x20,0x29,0x39,0x51,0x72,0xa1,0xff};
uint8_t tmsPeriod[0x40] = {0x00,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,
							0x1F,0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2D,0x2F,0x31,
							0x33,0x35,0x36,0x39,0x3B,0x3D,0x3F,0x42,0x45,0x47,0x49,0x4D,0x4F,0x51,0x55,0x57,
							0x5C,0x5F,0x63,0x66,0x6A,0x6E,0x73,0x77,0x7B,0x80,0x85,0x8A,0x8F,0x95,0x9A,0xA0};
int16_t tmsK1[0x20]     = {-32064,-31872,-31808,-31680,-31552,-31424,-31232,-30848,
							-30592,-30336,-30016,-29696,-29376,-28928,-28480,-27968,
							-26368,-24256,-21632,-18368,-14528,-10048,-5184,0,
							5184,10048,14528,18368,21632,24256,26368,27968};
int16_t tmsK2[0x20]     = {-20992,-19328,-17536,-15552,-13440,-11200,-8768,-6272,
							-3712,-1088,1536,4160,6720,9216,11584,13824,
							15936,17856,19648,21248,22656,24000,25152,26176,
							27072,27840,28544,29120,29632,30080,30464,32384};
int8_t tmsK3[0x10]      = {-110,-97,-83,-70,-56,-43,-29,-16,-2,11,25,38,52,65,79,92};
int8_t tmsK4[0x10]      = {-82,-68,-54,-40,-26,-12,1,15,29,43,57,71,85,99,113,126};
int8_t tmsK5[0x10]      = {-82,-70,-59,-47,-35,-24,-12,-1,11,23,34,46,57,69,81,92};
int8_t tmsK6[0x10]      = {-64,-53,-42,-31,-20,-9,3,14,25,36,47,58,69,80,91,102};
int8_t tmsK7[0x10]      = {-77,-65,-53,-41,-29,-17,-5,7,19,31,43,55,67,79,90,102};
int8_t tmsK8[0x08]      = {-64,-40,-16,7,31,55,79,102};
int8_t tmsK9[0x08]      = {-64,-44,-24,-4,16,37,57,77};
int8_t tmsK10[0x08]     = {-51,-33,-15,4,22,32,59,77};

#define CHIRP_SIZE 41
int8_t chirp[CHIRP_SIZE] = {0,42,-44,50,-78,18,37,20,
							2,-31,-59,2,95,90,5,15,
							38,-4,-91,-91,-42,-35,-36,-4,
							37,43,34,33,15,-1,-8,-18,
							-19,-17,-9,-10,-6,0,3,2,1};
							
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

	if (!setup) {
		// Auto-setup.
		// 
		// Enable the speech system whenever say() is called.
		
		pinMode(3,OUTPUT);
		// Timer 2 set up as a 62500Hz PWM.
		//
		// The PWM 'buzz' is well above human hearing range and is
		// very easy to filter out.
		//
		TCCR2A = _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
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

		setup = 1;
	}

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

ISR(TIMER1_COMPA_vect) {
  static uint8_t nextPwm;
  static uint8_t periodCounter;
  static int16_t x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10;
  int16_t u0,u1,u2,u3,u4,u5,u6,u7,u8,u9,u10;

  OCR2B = nextPwm;
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
