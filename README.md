Talkie
======

Speech library for Arduino

Quick start
-----------
Download the .zip file from the link at the top of the page. Install the "talkie" directory in your Arduino / libraries directory. Restart the Arduino software, and pick one of the examples from the Talkie section. Program it onto a 168 or 328 based Arduino (Uno, Duemilanove or Diecimila - not a Mega or Leonardo). Connect headphones or an audio amplifier to digital pin 3.

Note that currently, Talkie only on 168 or 328 based Arduinos at 16MHz only. Other devices may be supported in future releases, as I acquire them.


Introduction
------------
It is a software implementation of the Texas Instruments speech synthesis architecture (Linear Predictive Coding) from the late 1970s / early 1980s, as used on several popular applications:
* Texas Instruments Speak & Spell family of educational products
* Texas Instruments TI-99/4A Speech System expansion
* Acorn BBC Micro Speech Synthesiser expansion
* Atari arcade games (eg. Star Wars series, Indiana Jones, Gauntlet)
* Apple ][ Echo 2
* IBM PS/2 Speech Adapter

Talkie comes with over 1000 words of speech data that can be included in your projects. Most words only take a fraction of a KB, so you can add plenty.


How to use the library
----------------------
See the examples. Any commented data lines in the examples can be un-commented and used. Note that some speech libraries come with word endings such as '-S', '-Z', '-TEEN' that can be used to increase vocabulary.

Word dictionaries
-----------------
* Vocab_UK_Acorn
  16K bytes speech data
  165 words related to home computing
  Male UK English (voiced by BBC newsreader Kenneth Kendall)
  Data originally part of Acorn Computers Speech Synthesiser

* Vocab_US_Clock
  4K bytes speech data
  35 words related to the time of day
  Female US English
  Data of unknown origin. ROM serial number VM71003A.

* Vocab_US_TI99
  32K bytes speech data
  360 words related to home computing
  Male US English
  Data originally part of Texas Instruments TI-99/4A Speech System

* Vocab_US_Male
  16K bytes speech data
  206 words related to flight and engineering
  Data of unknown origin. ROM serial number VM61002.

* Vocab_US_Male_Large:
  48K bytes speech data
  402 words and phrases related to flight and engineering
  Data of unknown origin. ROM serial number VM61003/4/5.

* Demo_Toms_Diner:
  24K bytes music data
  Results from the work-in-progress Talkie compressor
  Tom's Diner by Suzanne Vega [Amazon UK](http://www.amazon.co.uk/Solitude-Standing-Suzanne-Vega/dp/B000026GZQ) [Amazon US](http://www.amazon.com/Solitude-Standing-Suzanne-Vega/dp/B000002GHB) or look for 'Solitude Standing' on your preferred music store. (Only this album contains the original a capella version)


The Audio output
----------------
Talkie sets up a special very high speed PWM, so audio can be taken directly from pin 3 with no other filtering.

Note that Talkie uses Timers 1 and 2 for this purpose, which may conflict with PWM outputs or other libraries.


Future plans
------------
1. I'm working on an encoder for generating your own recordings (See demo). Its not producing results of the quality I would like, but things are improving. For now Qboxpro, an unsupported old Windows application, can produce Talkie compatible data streams.
2. Improve compatibility with other Arduinos and AVR devices
3. Implement rule based infinite vocabulary synthesis from Computer Concepts Speech ROM and Texas Instruments Terminal Emulator 2.

Important facts
---------------
* LPC currently outputs speech sounds on digital pin 3 only. This is currently hard-wired within the library.
* Tivoice uses Timer 1 and Timer 2, which can break analogWrite(), and some other libraries.


Thanks
------
* For motivation and encouragement: Linx Electronics Club, esp. Rob, Shaw, Steve
* Thanks to the original Texas Instruments speech group: Larry Brantingham, Paul Breedlove, Richard Wiggins and Gene Frantz
* Thanks to the emulator-heads for their inspiration and coefficient tables: Lord Midnight, Kevtris and all MAME/MESS contributors
* Thanks to the authors of low bandwidth open source speech codecs: Asterisk, Codec2, Hawkvoice, Speex
* Scene greets: LFT, Mahoney


This library was developed using Arduino and Freemat.
