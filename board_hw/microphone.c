//
// downloaded from http://www.renesasrulz.com/message/10221#10221 posted by http://www.renesasrulz.com/people/dudmuck
//

#include "microphone.h"
#include "board.h" // leds on...

uint16_t samples[N_SAMPLES];
int sample_idx;
volatile int mic_samples = 0;

void Interrupt_ADC1(void)
{
	uint16_t sample;
	mic_samples++;
	sample = AD1.ADDRB;
	samples[sample_idx] = sample;
	if (++sample_idx == N_SAMPLES){
		sample_idx = 0;
	}
	ALL_LEDS_ON 
}

void adc_trigger_enable(char en)
{
	TMR0.TCSR.BIT.ADTE = en;
	AMP_SHDN = en;
}

void adc_init()
{
	/* 34.3.8 A/D converter activation with TMTRG0AN_0 of TMR */
	/* TCORA of TMR unit 0 in channel 0 */

	/************ ADC ***********************/
	SYSTEM.MSTPCRA.BIT.MSTPA22 = 0;	// start AD1

	AD1.ADCR.BIT.TRGS = 2;	// trigger from: compare-match A from TMR0

	AD1.ADCSR.BIT.CH = 1;	// single mode AN5
	AD1.ADCSR.BIT.ADIE = 1;	// interrupt enable, at conversion end

	IPR(AD1, ADI1) = 1;	// set interrupt priority
	IEN(AD1, ADI1) = 1;	// enable interrupt in the ICU

	/************ timer ***********************/
	SYSTEM.MSTPCRA.BIT.MSTPA5 = 0;	// start TMR0

	TMR0.TCR.BIT.CCLR = 1;	// clear count by compare-match-A

	// timer output -- TMO0
	TMR0.TCSR.BIT.OSA = 3;	// toggle out	(see R46, if not using USB)
	TMR0.TCSR.BIT.OSB = 3;	// toggle out

	TMR0.TCORA = 4;	// constant divider	5=7813hz, 4=9375hz

	TMR0.TCCR.BIT.CKS = 5;	// clock select, 5=PCLK/1024=46875Hz (if PCLK=48MHz)
	TMR0.TCCR.BIT.CSS = 1;	// clock source select, 1=internal clock

	// if you need timer interrupt for purpose other than adc trigger
	IPR(TMR0, CMIA0) = 1;	// set interrupt priority
	IEN(TMR0, CMIA0) = 1;	// enable interrupt in the ICU

	sample_idx = 0;

	/********************* amp enable pin ***************************/
	AMP_SHDN_DDR = 0xFF;//OUTPUT_PIN;
	AMP_SHDN = 0;	// default to shut down
}

