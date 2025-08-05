/*
Author: Munna
Date: 05/08/2025

Program description:
This program demonstrates the implementation of using GPIO(General Purpose Input/Output) in STM32F091RC
microcontroller by the means of implementing the "SOS Morse code". The SOS Morse code is "...---...".
*/

#include <stm32f091xc.h>

// DEFINING CORRESPONDING DELAYS TO MATCH THE MORSE CODE SEQUENCE
#define DOT 250 //250 MS, DOT TIME
#define DASH 1000 //250 MS, DASH TIME
#define GAP 250 //250 MS, GAP TIME
#define ON GPIO_BSRR_BR_0 /* LED ON (because active low) */
#define OFF GPIO_BSRR_BS_0 //LED OFF 
#define LED (GPIOC->BSRR) //LED 
#define BUTTON (GPIOC->IDR & MASK(B1_POS)) //BUTTON 

// macro to modify fields in registers with values. Parameters: (register, field, value)
#define MODIFY_FIELD(reg, field, value) \
((reg) = ((reg)& ~ (field ## _Msk)) | \
(((uint32_t)(value) << field ## _Pos)& field ## _Msk))
 
// CRUDE DELAY FUNCTION
void Delay(volatile unsigned int time_del) 
{
	volatile int n;
	while (time_del--) 
	{
		n = 1000;
		while (n--);
	}
}
 
int main()
{
	// Enable peripheral clock of GPIOC (for Switch B1 AND AN EXTERNAL LED)
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN; 
	 
	// Configure PA0 as OUTPUT mode
	MODIFY_FIELD(GPIOC->MODER, GPIO_MODER_MODER0, 1); // 1 = OUTPUT
	 
	int i;
	while(1){
		
		for (i = 0; i < 3; i++){
			LED |= ON;
			Delay(DOT);
			LED |= OFF;
			Delay(GAP);
		}
		
		Delay(500);
		
		for (i = 0; i < 3; i++){
			LED |= ON;
			Delay(DASH);
			LED |= OFF;
			Delay(GAP);
		}
		
		Delay(1000);
	}
}