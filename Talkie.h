// Talkie library
// Copyright 2011 Peter Knight
// This code is released under GPLv2 license.

#ifndef _Talkie_h_
#define _Talkie_h_

#include <inttypes.h>

#if defined(__AVR__) && !defined(TCCR2A)
#error "Sorry, when using an AVR chip, Talkie requires Timer2.  This board doesn't have it."
#elif defined(__MK20DX128__)
#error "Sorry, Talkie does not work with Teensy 3.0 (no DAC pin for audio output)."
#endif

#define SAY_BUFFER_SIZE     24	// 24 sets of 4 bytes plus added queue indexes is about 100 added bytes.

class Talkie
{
public:
	void begin(uint8_t pinPWM = 255);
	void say(const uint8_t * address);
	int8_t sayQ(const uint8_t * address);
	const uint8_t * ptrAddr;
	uint8_t ptrBit;
	uint8_t active( void );
	uint8_t getBits(uint8_t bits);
	bool setPtr(const uint8_t * addr);
	bool say_add( const uint8_t *addr );	// sayisr() calls this
	const uint8_t * say_remove();	// sayisr() calls this

	// inline function beginPWM(pinNo) is being kept only for backwards
	//compatibility with existing programs. It is simpler to use begin()
	//which will default to pin A0
	inline void beginPWM(uint8_t pinPWM){
		begin(pinPWM);
	}
private:
	// Say queue
	const uint8_t *  say_buffer[SAY_BUFFER_SIZE];
	uint8_t head; // init on setup = 0
	uint8_t tail; // init on setup = 0
	uint8_t free; // init on setup = SAY_BUFFER_SIZE
	
	// Setup
	uint8_t setup;
	
	// Bitstream parser
	uint8_t rev(uint8_t a);

};


#endif
