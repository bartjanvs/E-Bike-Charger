/*
 * digital.c
 *
 * Created: 4-8-2022 16:43:12
 *  Author: Bart-Jan
 */ 

#include <avr/io.h>

void InitIO(void)
{
	/* set ICRG_SEL & BOOST_EN as output */
	PORTB.DIRSET = PIN0_bm | PIN1_bm;
	/* set LED's as output */
	PORTE.DIRSET = PIN0_bm | PIN1_bm;
	PORTD.DIRSET = PIN7_bm;
}

void MaxChargeCurrent(void)
{
	PORTB.OUTSET = PIN0_bm;
}

void MinChargeCurrent(void)
{
	PORTB.OUTCLR = PIN0_bm;
}

void EnabelCharging(void)
{
	PORTB.OUTSET = PIN1_bm;
}

void DisableCharging(void)
{
	PORTB.OUTCLR = PIN1_bm;
}

void Set15VLED(void)
{
	PORTD.OUTSET = PIN7_bm;
}

void Clear15VLED(void)
{
	PORTD.OUTCLR = PIN7_bm;
}

void SetCurrentLED(void)
{
	PORTE.OUTSET = PIN0_bm;
}

void ClearCurrentLED(void)
{
	PORTE.OUTCLR = PIN0_bm;
}

void SetChargingLED(void)
{
	PORTE.OUTSET = PIN1_bm;
}

void ClearChargingLED(void)
{
	PORTE.OUTCLR = PIN1_bm;
}