// Talkie library
// Copyright 2011 Peter Knight
// This code is released under GPLv2 license.

#if (ARDUINO >= 100)
#include "Arduino.h"
#else
#include <avr/io.h>
#include "WProgram.h"
#endif
#include "Talkie.h"

#define FS 8000 // Speech engine sample rate

static void timerInterrupt();
static uint8_t synthPeriod;
static uint16_t synthEnergy;
static int16_t synthK1,synthK2;
static int8_t synthK3,synthK4,synthK5,synthK6,synthK7,synthK8,synthK9,synthK10;

static void sayisr();
static Talkie *isrTalkptr;
static uint8_t nextData=0;
const uint8_t spStopSay[]    PROGMEM = { 0x0F};	// This is a special sound to cleanly: Silence the synthesiser



static const uint8_t tmsEnergy[0x10] = {0x00,0x02,0x03,0x04,0x05,0x07,0x0a,0x0f,0x14,0x20,0x29,0x39,0x51,0x72,0xa1,0xff};
static const uint8_t tmsPeriod[0x40] = {0x00,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2D,0x2F,0x31,0x33,0x35,0x36,0x39,0x3B,0x3D,0x3F,0x42,0x45,0x47,0x49,0x4D,0x4F,0x51,0x55,0x57,0x5C,0x5F,0x63,0x66,0x6A,0x6E,0x73,0x77,0x7B,0x80,0x85,0x8A,0x8F,0x95,0x9A,0xA0};
static const uint16_t tmsK1[0x20]     = {0x82C0,0x8380,0x83C0,0x8440,0x84C0,0x8540,0x8600,0x8780,0x8880,0x8980,0x8AC0,0x8C00,0x8D40,0x8F00,0x90C0,0x92C0,0x9900,0xA140,0xAB80,0xB840,0xC740,0xD8C0,0xEBC0,0x0000,0x1440,0x2740,0x38C0,0x47C0,0x5480,0x5EC0,0x6700,0x6D40};
static const uint16_t tmsK2[0x20]     = {0xAE00,0xB480,0xBB80,0xC340,0xCB80,0xD440,0xDDC0,0xE780,0xF180,0xFBC0,0x0600,0x1040,0x1A40,0x2400,0x2D40,0x3600,0x3E40,0x45C0,0x4CC0,0x5300,0x5880,0x5DC0,0x6240,0x6640,0x69C0,0x6CC0,0x6F80,0x71C0,0x73C0,0x7580,0x7700,0x7E80};
static const uint8_t tmsK3[0x10]      = {0x92,0x9F,0xAD,0xBA,0xC8,0xD5,0xE3,0xF0,0xFE,0x0B,0x19,0x26,0x34,0x41,0x4F,0x5C};
static const uint8_t tmsK4[0x10]      = {0xAE,0xBC,0xCA,0xD8,0xE6,0xF4,0x01,0x0F,0x1D,0x2B,0x39,0x47,0x55,0x63,0x71,0x7E};
static const uint8_t tmsK5[0x10]      = {0xAE,0xBA,0xC5,0xD1,0xDD,0xE8,0xF4,0xFF,0x0B,0x17,0x22,0x2E,0x39,0x45,0x51,0x5C};
static const uint8_t tmsK6[0x10]      = {0xC0,0xCB,0xD6,0xE1,0xEC,0xF7,0x03,0x0E,0x19,0x24,0x2F,0x3A,0x45,0x50,0x5B,0x66};
static const uint8_t tmsK7[0x10]      = {0xB3,0xBF,0xCB,0xD7,0xE3,0xEF,0xFB,0x07,0x13,0x1F,0x2B,0x37,0x43,0x4F,0x5A,0x66};
static const uint8_t tmsK8[0x08]      = {0xC0,0xD8,0xF0,0x07,0x1F,0x37,0x4F,0x66};
static const uint8_t tmsK9[0x08]      = {0xC0,0xD4,0xE8,0xFC,0x10,0x25,0x39,0x4D};
static const uint8_t tmsK10[0x08]     = {0xCD,0xDF,0xF1,0x04,0x16,0x20,0x3B,0x4D};

bool Talkie::setPtr(const uint8_t * addr) {
	ptrAddr = addr;
	ptrBit = 0;
	if ( addr ) return(true);
	else return(false);
}
uint8_t Talkie::active() {
	yield();
	if ( 0 == ptrAddr ) return 0;	// Nothing playing!
	else return( 1 + (SAY_BUFFER_SIZE - free) );	// 1 active plus X in queue
}	// active()

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

void Talkie::say(const uint8_t * addr) {
	sayQ( addr );
	while ( active() );
}	// say()

bool Talkie::say_add( const uint8_t *addr ) {
	if ( addr && free ) {
		free--;
		say_buffer[head] = addr;
		if (++head >= SAY_BUFFER_SIZE) head = 0;
		return true;
	}
	return false;	// Do not add on ZERO addr or ZERO free queue
}	// say_add()


const uint8_t * Talkie::say_remove() {
	const uint8_t *addr = 0;	// Return 0 on empty
	if ( free < SAY_BUFFER_SIZE ) {
		free++;
		addr = say_buffer[tail];
		if (++tail >= SAY_BUFFER_SIZE) tail = 0;
	}
	else if ( ( ptrAddr ) && ( spStopSay != ptrAddr ) ) {
		addr = spStopSay;
	}
	return addr;
}	// say_remove()

int8_t Talkie::sayQ(const uint8_t * addr) {
	if (!setup) {
		// Auto-setup.
		// 
		// Enable the speech system whenever say() is called.
#if defined(__AVR__)
#if F_CPU != 16000000L
#error "F_CPU must be 16 MHz"
#endif
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
#define ISR_RATIO (25000/ (F_CPU / FS) )
#elif defined(__arm__) && defined(CORE_TEENSY)
#define ISR(f) void f(void)
		IntervalTimer *t = new IntervalTimer();
		t->begin(timerInterrupt, 1000000.0f / (float)FS);
#define ISR_RATIO (25000/ (1000000.0f / (float)FS) )
#endif
		isrTalkptr = this;
		head = 0;
		tail = 0;
		free = SAY_BUFFER_SIZE;

		setup = 1;
	}
	if ( 0 == addr  ) {	// Caller asked to have queue made empty and sound stopped
		head = 0;
		tail = 0;
		free = SAY_BUFFER_SIZE;
		setPtr(spStopSay);	// Force this NOP sound to play to turn off the output on next timerinterrupt()
		nextData=ISR_RATIO;
	}
	else if ( !active() ) {
		if ( setPtr(addr) ) {	// START the sound on this address : on zero addr just return free count
			nextData=0;	// This tracks the timing of the call to sayisr()
			sayisr();	// Get first data now
		}
	}
	else {	// Still active queue this addr when there is room
		while ( (0==free) && active() );
		say_add( addr );
	}
	return(free);	// return free count after adding
}	// sayQ()

#define CHIRP_SIZE 41
static uint8_t chirp[CHIRP_SIZE] = {0x00,0x2a,0xd4,0x32,0xb2,0x12,0x25,0x14,0x02,0xe1,0xc5,0x02,0x5f,0x5a,0x05,0x0f,0x26,0xfc,0xa5,0xa5,0xd6,0xdd,0xdc,0xfc,0x25,0x2b,0x22,0x21,0x0f,0xff,0xf8,0xee,0xed,0xef,0xf7,0xf6,0xfa,0x00,0x03,0x02,0x01};

ISR(TIMER1_COMPA_vect) {
	timerInterrupt();
}

static void timerInterrupt() {
	static uint8_t nextPwm;
	static uint8_t periodCounter;
	static int16_t x0,x1,x2,x3,x4,x5,x6,x7,x8,x9;
	Talkie *o = isrTalkptr;

	int16_t u0,u1,u2,u3,u4,u5,u6,u7,u8,u9,u10;

#if defined(__AVR__)
	OCR2B = nextPwm;
	sei();
#elif defined(__arm__) && defined(CORE_TEENSY)
#if defined(__MKL26Z64__)
	analogWrite(A12, nextPwm);
#else
	analogWrite(A14, nextPwm);
#endif
#endif
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

	if ( o->ptrAddr ) nextData++;	// if no sound don't run toward calling sayisr()
	if (ISR_RATIO <= nextData) { nextData=0; sayisr(); }
}


static void sayisr() {
	uint8_t energy;
	Talkie *o = isrTalkptr;

	if ( !(o->ptrAddr) ) {
		// Non Active :: try START the sound on say_remove() address
		if ( o->setPtr(o->say_remove()) ) nextData=ISR_RATIO;	// This tracks the timing of the call to sayisr() :: Force nextData next timerInterrupt()
		return;
	}
	energy = o->getBits(4);
	uint8_t repeat;
	// Read speech data, processing the variable size frames.
	if (energy == 0) {
		// Energy = 0: rest frame
		synthEnergy = 0;
	} else if (energy == 0xf) {	// Energy = 15: stop frame. Silence the synthesiser.
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
		
		// Going Non Active :: START the sound on say_remove() address
		if ( o->setPtr(o->say_remove()) ) nextData=ISR_RATIO;	// This tracks the timing of the call to sayisr() :: Force nextData next timerInterrupt()
		else	nextData=0;
		
	} else {
		synthEnergy = tmsEnergy[energy];
		repeat = o->getBits(1);
		synthPeriod = tmsPeriod[o->getBits(6)];
		// A repeat frame uses the last coefficients
		if (!repeat) {
			// All frames use the first 4 coefficients
			synthK1 = tmsK1[o->getBits(5)];
			synthK2 = tmsK2[o->getBits(5)];
			synthK3 = tmsK3[o->getBits(4)];
			synthK4 = tmsK4[o->getBits(4)];
			if (synthPeriod) {
				// Voiced frames use 6 extra coefficients.
				synthK5 = tmsK5[o->getBits(4)];
				synthK6 = tmsK6[o->getBits(4)];
				synthK7 = tmsK7[o->getBits(4)];
				synthK8 = tmsK8[o->getBits(3)];
				synthK9 = tmsK9[o->getBits(3)];
				synthK10 = tmsK10[o->getBits(3)];
			}
		}
	}
} // sayisr()

/*
>> When sayQ brings new addr - if not .active() then start it { 'current code' } return (free);
	if ( active() && free ) :: then ADD it :: return (free);
	else do a say() type while block until it can be added, then return
	
>> when timerInterrupt() completes :: if say_buffer_queued then start REMOVE
	setPtr( say_remove );

// RACE CONDITION :: sayQ : During Add - one active - none queued - on timerInterrupt() it completes  before item queued it won;t start next
>> solution when sayisr() is entered if ptrAddris zero do a check for set_remove() in case one comes in un announced

// Calling sayQ() will play or buffer and return free and if !free it will block like say() until room
// Calling say() with queued sayQ() items will block until queued and the queue is empty

*/
