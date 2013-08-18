/*
  CharlieGroups.cpp
  
  This library is (C) Copyright 2013 George Eggleston (george@gem1954.com)
  Creative Commons Attribution-ShareAlike 
  CC BY-SA
  http://creativecommons.org/licenses/by-sa/3.0/
*/

#include "Arduino.h"
#include "CharlieGroups.h"

CharlieGroups::CharlieGroups(
unsigned long cycleTime,
byte pinOne,
byte pinTwo,
byte pinThree)
{
  _cycleTime = cycleTime;
  _pinOne = pinOne;
  _pinTwo = pinTwo;
  _pinThree = pinThree;
  _last_pos = 3 * 2 - 1;
}
CharlieGroups::CharlieGroups(
unsigned long cycleTime,
byte pinOne,
byte pinTwo,
byte pinThree,
byte pinFour)
{
  _cycleTime = cycleTime;
  _pinOne = pinOne;
  _pinTwo = pinTwo;
  _pinThree = pinThree;
  _pinFour = pinFour;
  _last_pos = 4 * 3 - 1;
  
}

int CharlieGroups::lightOne(byte activeLed, byte percentOn)
{
  if(activeLed > _last_pos)
  {
    return(0);
  }
  //byte highPin, lowPin;
  _offTime = micros() + ((_cycleTime * percentOn) / 255);
  _returnTime = micros() + _cycleTime;
  this->findActives(activeLed);
	if(percentOn)
	{

	  digitalWrite(_high_pin, HIGH);
	  digitalWrite(_low_pin, LOW);
	  pinMode(_high_pin, OUTPUT);
	  pinMode(_low_pin, OUTPUT);

	  while(_offTime > micros()){}
	}
	pinMode(_high_pin, INPUT);
	pinMode(_low_pin, INPUT);


  while(_returnTime > micros()){}
}
int CharlieGroups::oneOn(byte activeLed)
{
  this->oneOff();
  if(activeLed > _last_pos)
  {
    return(0);
  }
  //byte highPin, lowPin;
  this->findActives(activeLed);
	digitalWrite(_high_pin, HIGH);
	digitalWrite(_low_pin, LOW);
	pinMode(_high_pin, OUTPUT);
	pinMode(_low_pin, OUTPUT);
	return(1);
}
int CharlieGroups::oneOff()
{
	pinMode(_high_pin, INPUT);
	pinMode(_low_pin, INPUT);
}
void CharlieGroups::findActives(byte activeLed)
{
	switch (activeLed){
	case 0:
	  _high_pin = _pinOne;
	  _low_pin = _pinTwo;
	  break;
	case 1:
	  _high_pin = _pinTwo;
	  _low_pin = _pinOne;
	  break;
	case 2:
	  _high_pin = _pinOne;
	  _low_pin = _pinThree;
	  break;
	case 3:
	  _high_pin = _pinThree;
	  _low_pin = _pinOne;
	  break;
	case 4:
	  _high_pin = _pinTwo;
	  _low_pin = _pinThree;
	  break;
	case 5:
	  _high_pin = _pinThree;
	  _low_pin = _pinTwo;
	  break;
	case 6:
	  _high_pin = _pinOne;
	  _low_pin = _pinFour;
	  break;
	case 7:
	  _high_pin = _pinFour;
	  _low_pin = _pinOne;
	  break;
	case 8:
	  _high_pin = _pinTwo;
	  _low_pin = _pinFour;
	  break;
	case 9:
	  _high_pin = _pinFour;
	  _low_pin = _pinTwo;
	  break;
	case 10:
	  _high_pin = _pinThree;
	  _low_pin = _pinFour;
	  break;
	case 11:
	  _high_pin = _pinFour;
	  _low_pin = _pinThree;
	  break;
  }
}
int CharlieGroups::lightGroup(unsigned int rep, prog_uchar* act_a)
{
  int i, j;
  //Serial.println(_last_pos);
  for(j=0; j< rep; j++)
  {
    for(i=0; i<=_last_pos; i++)
    {
      this->lightOne(i, pgm_read_byte(act_a + i));
    }
  }
  return(1);
}
int CharlieGroups::lightGroup(unsigned int rep, int* act_a)
{
  int i, j;
  for(j=0; j< rep; j++)
  {
    for(i=0; i<=_last_pos; i++)
    {
      this->lightOne(i, act_a[i]);
    }
  }
  return(1);
}
int CharlieGroups::startGroup(unsigned int rep, prog_uchar* act_a)
{
	_togo = rep;
	_working_arr_ptr = act_a;
	this->lightGroup(1, _working_arr_ptr);
	_togo--;
	return(_togo);
}
int CharlieGroups::continueGroup()
{
	int i;
	if(_togo < 1)
	{
		for(i=0; i<=_last_pos; i++)
		{
			_returnTime = micros() + _cycleTime;
			while(_returnTime > micros()){}
		}
		return(0);
	}
	else
	{
		this->lightGroup(1, _working_arr_ptr);
		_togo--;
		return(_togo);
	}
}
