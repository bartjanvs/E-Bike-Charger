/*
 * Charger.c
 *
 * Created: 4-8-2022 16:20:47
 * Author : Bart-Jan
 */ 

#define F_CPU 2000000UL

#include <avr/io.h>

#include "analog.h"
#include "digital.h"

int main(void)
{
    
	InitAdc();
	InitIO();
	
    while (1) 
    {
    }
}

