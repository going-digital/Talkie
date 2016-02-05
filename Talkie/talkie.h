// Talkie library
// Copyright 2011 Peter Knight
// This code is released under GPLv2 license.

#ifndef _Talkie_h_
#define _Talkie_h_

#include <inttypes.h>
#include <avr/io.h>

#define CHIRP_SIZE 41

class Talkie
{
public:
	Talkie();
	~Talkie();
	void begin();
	void end();
	void say(const uint8_t* address);
	void interrupt();
	const uint8_t* ptrAddr;
	uint8_t ptrBit;
private:
		// Setup
	uint8_t tmsEnergy[0x10];
	uint8_t tmsPeriod[0x40];
	int16_t tmsK1[0x20];
	int16_t tmsK2[0x20];
	int8_t tmsK3[0x10];
	int8_t tmsK4[0x10];
	int8_t tmsK5[0x10];
	int8_t tmsK6[0x10];
	int8_t tmsK7[0x10];
	int8_t tmsK8[0x08];
	int8_t tmsK9[0x08];
	int8_t tmsK10[0x08];
	int8_t chirp[CHIRP_SIZE];

	uint8_t nextPwm;
	uint8_t periodCounter;
	int16_t x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10;

	uint8_t synthPeriod;
	uint16_t synthEnergy;
	int16_t synthK1,synthK2;
	int8_t synthK3,synthK4,synthK5,synthK6,synthK7,synthK8,synthK9,synthK10;

	uint8_t R_TCCR2A, R_TCCR2B, R_TIMSK2, R_TCCR1A, R_TCCR1B, R_TCNT1, R_OCR1A, R_TIMSK1, R_LIMITING_REG;

		// Bitstream parser
	void setPtr(const uint8_t* addr);
	void readPgmArrayU(uint8_t* array, const uint8_t* ptr, int size);
	void readPgmArrayW(int16_t* array, const int16_t* ptr, int size);
	void readPgmArray(int8_t* array, const int8_t* ptr, int size);
	uint8_t rev(uint8_t a);
	uint8_t getBits(uint8_t bits);
};

#endif
