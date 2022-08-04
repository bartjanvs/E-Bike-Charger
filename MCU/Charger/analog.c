/*
 * analog.c
 *
 * Created: 4-8-2022 16:24:16
 *  Author: Bart-Jan
 */ 

#define VREF 2.048
#define ADC_MAX_VALUE 2047

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stddef.h>
#include <stdlib.h>

uint16_t readCalibrationWord(uint8_t index)
{
	uint16_t result;
	/* request calibration words */
	NVM_CMD = NVM_CMD_READ_CALIB_ROW_gc;
	/* read correct word */
	result = pgm_read_word(index);
	/* reset NVM controller */
	NVM_CMD = NVM_CMD_NO_OPERATION_gc;
	return result;
}

void InitAdc(void)
{
	// set the correct pins as input
	PORTA.DIR = 0x00;
	/* set adc channel 0 to differential mode */
	ADCA.CH0.CTRL = ADC_CH_INPUTMODE_DIFF_gc | ADC_CH_GAIN_1X_gc;
	/* internal reference */
	ADCA.REFCTRL = ADC_REFSEL_INTVCC_gc;
	/* 12 bit resolution, signed conversion */
	ADCA.CTRLB = ADC_RESOLUTION_12BIT_gc | ADC_CONMODE_bm;
	/* adc clock F_CPU/16 */
	ADCA.PRESCALER = ADC_PRESCALER_DIV16_gc;
	/* read calibration words */
	ADCA.CAL = readCalibrationWord(offsetof(NVM_PROD_SIGNATURES_t,ADCACAL0));
	/* enable adc */
	ADCA.CTRLA = ADC_ENABLE_bm;
}

int16_t ReadAdc(void)
{
	int16_t result;
	/* start adc and wait the result */
	ADCA.CH0.CTRL |= ADC_CH_START_bm;
	while ( !(ADCA.CH0.INTFLAGS & ADC_CH_CHIF_bm) );
	/* clear interrupt flag */
	ADCA.CH0.INTFLAGS |= ADC_CH_CHIF_bm;
	/* read result and return */
	result = ADCA.CH0.RES;
	return result;
}

double ReadIcharge(void)
{
	double current;
	double voltage;
	int16_t res = 0;
	/* adc channel 0 to PA2 and GND (signed single-ended) */
	ADCA.CH0.MUXCTRL = ADC_CH_MUXPOS_PIN2_gc | ADC_CH_MUXNEG_GND_MODE3_gc;
	res = ReadAdc();
	/* convert adc result to real voltage */
	voltage = ((double)res) * VREF / (ADC_MAX_VALUE + 1);
	/* get actual current by dividing the voltage by the shunt resistance (0R002) */
	current = voltage / 0.002;
	/* divide by 200 to get rid of the amplification of the INA181 */
	current = current / 200;
	return current;
}

double ReadVsupply(void)
{
	int16_t res;
	double voltage;
	/* adc channel 0 to PA3 and GND (signed single-ended) */
	ADCA.CH0.MUXCTRL = ADC_CH_MUXPOS_PIN3_gc | ADC_CH_MUXNEG_GND_MODE3_gc;
	res = ReadAdc();
	/* convert adc result to real voltage */
	voltage = ((double)res) * VREF / (ADC_MAX_VALUE + 1);
	/* Input is connected via 150k/10k (16x) resistor divider */
	voltage = voltage * 16;
	return voltage;
}