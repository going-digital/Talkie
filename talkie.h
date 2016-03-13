// Talkie library
// Copyright 2011 Peter Knight
// This code is released under GPLv2 license.

#ifndef _Talkie_h_
#define _Talkie_h_

#include <inttypes.h>
#include <avr/io.h>


class Talkie
{
	public:
		void say(uint8_t* address);
		uint8_t* ptrAddr;
		uint8_t ptrBit;
	private:
		// Setup
		uint8_t setup;
		
		// Bitstream parser
		void setPtr(uint8_t* addr);
		uint8_t rev(uint8_t a);
		uint8_t getBits(uint8_t bits);
};


#endif
