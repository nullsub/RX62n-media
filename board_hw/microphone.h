#ifndef MICROPHONE_H_
#define MICROPHONE_H_

#include "iodefine.h"
#include <stdint.h>

#define	AMP_SHDN_DDR		PORT5.DDR.BIT.B5
#define	AMP_SHDN		PORT5.DR.BIT.B5

#define N_SAMPLES	16

extern uint16_t samples[N_SAMPLES];
extern int sample_idx;
extern volatile int mic_samples;

void adc_init();
void adc_trigger_enable(char en);


#endif //MICROPHONE_H_


