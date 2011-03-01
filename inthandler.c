/***********************************************************************/
/*                                                                     */
/*  FILE        :inthandler.c                                          */
/*  DATE        :Wed, Aug 25, 2010                                     */
/*  DESCRIPTION :Interrupt Handler                                     */
/*  CPU TYPE    :Other                                                 */
/*                                                                     */
/*  This file is generated by KPIT GNU Project Generator.              */
/*                                                                     */
/***********************************************************************/
                



#include "inthandler.h"
#include "iodefine.h"
#pragma section IntPRG

// Exception(Supervisor Instruction)
void INT_Excep_SuperVisorInst(void){/* brk(); */}

// Exception(Undefined Instruction)
void INT_Excep_UndefinedInst(void){ __asm volatile ("brk"); }

// Exception(Floating Point)
void INT_Excep_FloatingPoint(void){/* brk(); */}

// NMI
void INT_NonMaskableInterrupt(void){/* brk(); */}

// Dummy
void Dummy(void){/* brk(); */}

// BRK
void INT_Excep_BRK(void){ /*wait(); */}

// BUSERR
void INT_Excep_BUSERR(void){ }

// FCU_FCUERR
void INT_Excep_FCU_FCUERR(void){ }

// FCU_FRDYI
void INT_Excep_FCU_FRDYI(void){ }

// CMTU0_CMT0 - (RB) NOTE This has been replaced in the vector table with vTickISR().
void INT_Excep_CMTU0_CMT0(void){ }

// CMTU0_CMT1
void INT_Excep_CMTU0_CMT1(void){ }

// CMTU1_CMT2
void INT_Excep_CMTU1_CMT2(void){ }

// CMTU1_CMT3
void INT_Excep_CMTU1_CMT3(void){ }

// IRQ0
void INT_Excep_IRQ0(void){ }

// IRQ1
void INT_Excep_IRQ1(void){ }

// IRQ2
void INT_Excep_IRQ2(void){ }

// IRQ3
void INT_Excep_IRQ3(void){ }

// IRQ4
void INT_Excep_IRQ4(void){ }

// IRQ5
void INT_Excep_IRQ5(void){ }

// IRQ6
void INT_Excep_IRQ6(void){ }

// IRQ7
void INT_Excep_IRQ7(void){ }

// IRQ8
void INT_Excep_IRQ8(void){ }

// IRQ9
void INT_Excep_IRQ9(void){ }

// IRQ10
void INT_Excep_IRQ10(void){ }

// IRQ11
void INT_Excep_IRQ11(void){ }

// IRQ12
void INT_Excep_IRQ12(void){ }

// IRQ13

void INT_Excep_IRQ13(void){
	//debug("im INT");
	rsi_external_inerrupt_handler();
	ICU.IER[9].BIT.IEN5 = 0;
}

// IRQ14
void INT_Excep_IRQ14(void){ }

// IRQ15
void INT_Excep_IRQ15(void){ }

// WDT_WOVI
void INT_Excep_WDT_WOVI(void){ }

// AD0_ADI0
void INT_Excep_AD0_ADI0(void){ }

// AD1_ADI1
extern void Interrupt_ADC1();
void INT_Excep_AD1_ADI1(void){ 
	Interrupt_ADC1();
}

// AD2_ADI2
void INT_Excep_AD2_ADI2(void){ }

// AD3_ADI3
void INT_Excep_AD3_ADI3(void){ }

// TPU0_TGI0A
void INT_Excep_TPU0_TGI0A(void){ }

// TPU0_TGI0B
void INT_Excep_TPU0_TGI0B(void){ }

// TPU0_TGI0C
void INT_Excep_TPU0_TGI0C(void){ }

// TPU0_TGI0D
void INT_Excep_TPU0_TGI0D(void){ }

// TPU0_TCI0V
void INT_Excep_TPU0_TCI0V(void){ }

// TPU1_TGI1A
void INT_Excep_TPU1_TGI1A(void){ }

// TPU1_TGI1B
void INT_Excep_TPU1_TGI1B(void){ }

// TPU1_TCI1V
void INT_Excep_TPU1_TCI1V(void){ }

// TPU1_TCI1U
void INT_Excep_TPU1_TCI1U(void){ }

// TPU2_TGI2A
void INT_Excep_TPU2_TGI2A(void){ }

// TPU2_TGI2B
void INT_Excep_TPU2_TGI2B(void){ }

// TPU2_TCI2V
void INT_Excep_TPU2_TCI2V(void){ }

// TPU2_TCI2U
void INT_Excep_TPU2_TCI2U(void){ }

// TPU3_TGI3A
void INT_Excep_TPU3_TGI3A(void){ }

// TPU3_TGI3B
void INT_Excep_TPU3_TGI3B(void){ }

// TPU3_TGI3C
void INT_Excep_TPU3_TGI3C(void){ }

// TPU3_TGI3D
void INT_Excep_TPU3_TGI3D(void){ }

// TPU3_TCI3V
void INT_Excep_TPU3_TCI3V(void){ }

// TPU4_TGI4A
void INT_Excep_TPU4_TGI4A(void){ }

// TPU4_TGI4B
void INT_Excep_TPU4_TGI4B(void){ }

// TPU4_TCI4V
void INT_Excep_TPU4_TCI4V(void){ }

// TPU4_TCI4U
void INT_Excep_TPU4_TCI4U(void){ }

// TPU5_TGI5A
void INT_Excep_TPU5_TGI5A(void){ }

// TPU5_TGI5B
void INT_Excep_TPU5_TGI5B(void){ }

// TPU5_TCI5V
void INT_Excep_TPU5_TCI5V(void){ }

// TPU5_TCI5U
void INT_Excep_TPU5_TCI5U(void){ }

// TPU6_TGI6A
void INT_Excep_TPU6_TGI6A(void){ }

// TPU6_TGI6B
void INT_Excep_TPU6_TGI6B(void){ }

// TPU6_TGI6C
void INT_Excep_TPU6_TGI6C(void){ }

// TPU6_TGI6D
void INT_Excep_TPU6_TGI6D(void){ }

// TPU6_TCI6V
void INT_Excep_TPU6_TCI6V(void){ }

// TPU7_TGI7A
void INT_Excep_TPU7_TGI7A(void){ }

// TPU7_TGI7B
void INT_Excep_TPU7_TGI7B(void){ }

// TPU7_TCI7V
void INT_Excep_TPU7_TCI7V(void){ }

// TPU7_TCI7U
void INT_Excep_TPU7_TCI7U(void){ }

// TPU8_TGI8A
void INT_Excep_TPU8_TGI8A(void){ }

// TPU8_TGI8B
void INT_Excep_TPU8_TGI8B(void){ }

// TPU8_TCI8V
void INT_Excep_TPU8_TCI8V(void){ }

// TPU8_TCI8U
void INT_Excep_TPU8_TCI8U(void){ }

// TPU9_TGI9A
void INT_Excep_TPU9_TGI9A(void){ }

// TPU9_TGI9B
void INT_Excep_TPU9_TGI9B(void){ }

// TPU9_TGI9C
void INT_Excep_TPU9_TGI9C(void){ }

// TPU9_TGI9D
void INT_Excep_TPU9_TGI9D(void){ }

// TPU9_TCI9V
void INT_Excep_TPU9_TCI9V(void){ }

// TPU10_TGI10A
void INT_Excep_TPU10_TGI10A(void){ }

// TPU10_TGI10B
void INT_Excep_TPU10_TGI10B(void){ }

// TPU10_TCI10V
void INT_Excep_TPU10_TCI10V(void){ }

// TPU10_TCI10U
void INT_Excep_TPU10_TCI10U(void){ }

// TPU11_TGI11A
void INT_Excep_TPU11_TGI11A(void){ }

// TPU11_TGI11B
void INT_Excep_TPU11_TGI11B(void){ }

// TPU11_TCI11V
void INT_Excep_TPU11_TCI11V(void){ }

// TPU11_TCI11U
void INT_Excep_TPU11_TCI11U(void){ }

// TMR0_CMI0A
void INT_Excep_TMR0_CMI0A(void){ }

// TMR0_CMI0B
void INT_Excep_TMR0_CMI0B(void){ }

// TMR0_OV0I
void INT_Excep_TMR0_OV0I(void){ }

// TMR1_CMI1A
void INT_Excep_TMR1_CMI1A(void){ }

// TMR1_CMI1B
void INT_Excep_TMR1_CMI1B(void){ }

// TMR1_OV1I
void INT_Excep_TMR1_OV1I(void){ }

// TMR2_CMI2A
void INT_Excep_TMR2_CMI2A(void){ }

// TMR2_CMI2B
void INT_Excep_TMR2_CMI2B(void){ }

// TMR2_OV2I
void INT_Excep_TMR2_OV2I(void){ }

// TMR3_CMI3A
void INT_Excep_TMR3_CMI3A(void){ }

// TMR3_CMI3B
void INT_Excep_TMR3_CMI3B(void){ }

// TMR3_OV3I
void INT_Excep_TMR3_OV3I(void){ }

// DMAC_DMTEND0
void INT_Excep_DMAC_DMTEND0(void){ }

// DMAC_DMTEND1
void INT_Excep_DMAC_DMTEND1(void){ }

// DMAC_DMTEND2
void INT_Excep_DMAC_DMTEND2(void){ }

// DMAC_DMTEND3
void INT_Excep_DMAC_DMTEND3(void){ }

// SCI0_ERI0
void INT_Excep_SCI0_ERI0(void){ }

// SCI0_RXI0
void INT_Excep_SCI0_RXI0(void){ }

// SCI0_TXI0
void INT_Excep_SCI0_TXI0(void){ }

// SCI0_TEI0
void INT_Excep_SCI0_TEI0(void){ }

// SCI1_ERI1
void INT_Excep_SCI1_ERI1(void){ }

// SCI1_RXI1
void INT_Excep_SCI1_RXI1(void){ }

// SCI1_TXI1
void INT_Excep_SCI1_TXI1(void){ }

// SCI1_TEI1
void INT_Excep_SCI1_TEI1(void){ }

// SCI2_ERI2
void INT_Excep_SCI2_ERI2(void){ }

// SCI2_RXI2
void INT_Excep_SCI2_RXI2(void){ }

// SCI2_TXI2
void INT_Excep_SCI2_TXI2(void){ }

// SCI2_TEI2
void INT_Excep_SCI2_TEI2(void){ }

// SCI3_ERI3
void INT_Excep_SCI3_ERI3(void){ }

// SCI3_RXI3
void INT_Excep_SCI3_RXI3(void){ }

// SCI3_TXI3
void INT_Excep_SCI3_TXI3(void){ }

// SCI3_TEI3
void INT_Excep_SCI3_TEI3(void){ }

// SCI4_ERI4
void INT_Excep_SCI4_ERI4(void){ }

// SCI4_RXI4
void INT_Excep_SCI4_RXI4(void){ }

// SCI4_TXI4
void INT_Excep_SCI4_TXI4(void){ }

// SCI4_TEI4
void INT_Excep_SCI4_TEI4(void){ }

// SCI5_ERI5
void INT_Excep_SCI5_ERI5(void){ }

// SCI5_RXI5
void INT_Excep_SCI5_RXI5(void){ }

// SCI5_TXI5
void INT_Excep_SCI5_TXI5(void){ }

// SCI5_TEI5
void INT_Excep_SCI5_TEI5(void){ }

// SCI6_ERI6
void INT_Excep_SCI6_ERI6(void){ }

// SCI6_RXI6
void INT_Excep_SCI6_RXI6(void){ }

// SCI6_TXI6
void INT_Excep_SCI6_TXI6(void){ }

// SCI6_TEI6
void INT_Excep_SCI6_TEI6(void){ }

// RIIC0_EEI0
void INT_Excep_RIIC0_EEI0(void){ }

// RIIC0_RXI0
void INT_Excep_RIIC0_RXI0(void){ }

// RIIC0_TXI0
void INT_Excep_RIIC0_TXI0(void){ }

// RIIC0_TEI0
void INT_Excep_RIIC0_TEI0(void){ }

// RIIC1_EEI1
void INT_Excep_RIIC1_EEI1(void){ }

// RIIC1_RXI1
void INT_Excep_RIIC1_RXI1(void){ }

// RIIC1_TXI1
void INT_Excep_RIIC1_TXI1(void){ }

// RIIC1_TEI1
void INT_Excep_RIIC1_TEI1(void){ }


