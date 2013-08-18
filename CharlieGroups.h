/*
  CharlieGroups.h
  
  This library is (C) Copyright 2013 George Eggleston (george@gem1954.com)
  Creative Commons Attribution-ShareAlike 
  CC BY-SA
  http://creativecommons.org/licenses/by-sa/3.0/
*/
#ifndef CharlieGroups_h
#define CharlieGroups_h

#include "Arduino.h"
#include <avr/pgmspace.h>

class CharlieGroups
{
	public:
	  CharlieGroups(unsigned long cycleTime, byte pinOne, byte pinTwo, 
	  	byte pinThree); 
	  CharlieGroups(unsigned long cycleTime, byte pinOne, byte pinTwo, 
	  	byte pinThree, byte pinFour);
	  int lightOne(byte activeLed, byte percentOn);
	  int oneOn(byte activeLed);
	  int oneOff();
	  int lightGroup(unsigned int rep, prog_uchar* act_a);
	  int lightGroup(unsigned int rep, int* act_a);
	  int startGroup(unsigned int rep, prog_uchar* act_a);
	  int continueGroup();
	private:
	  void findActives(byte activeLed);
	  unsigned long _cycleTime, _offTime, _returnTime;
	  unsigned int _togo;
	  prog_uchar* _working_arr_ptr;
	  byte _pinOne, _pinTwo, _pinThree, _pinFour, _pinFive, _pinSix, 
	  	_last_pos, _high_pin, _low_pin;
};

#endif
