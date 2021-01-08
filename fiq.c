/*-----------------------------------------------------------------------
*													  				   
*   Startup.s modified: line 263 ;FIQ_Handler     B     FIQ_Handler   
*	    				line 264 EXTERN FIQ_Handler					   
*																	   
*----------------------------------------------------------------------*/

#include <lpc21xx.h>
#include "config.h"

/************************ Timer0 delay function ************************/
/************************ Configured for 15 MHz ************************/
void delay_ms(unsigned int millisec)
{
	T0PR=15000-1;
	T0PC=T0TC=0x00;
	T0TCR=0x01;
	while(T0TC<millisec);
	T0TCR=0x00;
}

/*************************** FIQ handler(ISR) **************************/
extern __irq void FIQ_Handler(void)
{
	/* Store current state of Timer0 */ 
	unsigned int tc_state=T0TC; 																					
	
	/* Clear EINT3 */
	EXTINT |= EINT3_CONFIG;																							
	IOCLR0 = LED_PIN2;
	/* Delay for 5 sec */
	delay_ms(2500);             																					
	IOSET0 = LED_PIN2;
	
	/*Restore previous state of Timer0 */
	T0TC=tc_state;		
	/*Enable Timer0 */	
	T0TCR=0x01;
	
	VICVectAddr = 0x00;
}
/*************************** IRQ handler(ISR) **************************/
__irq void VIC_Int0_Handler(void)
{
	/* Store current state of Timer0 */
	unsigned int tc_state=T0TC; 																					
	
	/* Clear EINT2 */
	EXTINT |= EINT2_CONFIG;																							
	IOCLR0 = LED_PIN1;
	/* Delay for 10 sec */
	delay_ms(5000);																									
	IOSET0 = LED_PIN1;
	
	/*Restore previous state of Timer0 */
	T0TC=tc_state;																									
	/*Enable Timer0 */
	T0TCR=0x01;																										
	
	VICVectAddr = 0x00;	
}

void Extint_Init()
{
	/*Configure P0.7 and P0.9 as external interrupt 2 and 3*/
	PINSEL0 |= PINSEL_EINT2|PINSEL_EINT3; 																			
	/*Clear external interrupt 2 and 3 in EXTINT register */
	EXTINT &= ~(EINT2_CONFIG|EINT3_CONFIG); 																		
	/*Configure EINT2 and EINT3 as edge sensitive*/
	EXTMODE &= EINT2_CONFIG|EINT3_CONFIG; 																			
	/*Configure EINT2 and EINT3 as falling edge sensitive*/
	EXTPOLAR &= EINT2_CONFIG|EINT3_CONFIG;																			

	/* Enable EINT2(IRQ) PIN P0.3 and EINT3(FIQ)  P0.7 */
	VICIntEnable |= EINT2|EINT3; 																					
	/*Configure EINT3 as FIQ*/
	VICIntSelect |= EINT3;																							
	/* Enable VICVectCntl0 and map EINT2 */
	VICVectCntl0 = VICVECTCNT_ENABLE|VICSOFTINT_MAP;																
	/*Copy address or ISR EINT2*/
	VICVectAddr0 = (unsigned) VIC_Int0_Handler; 																	
}



int main(void)
{	
	Extint_Init();
	/* Set LED pins as output*/
	IODIR0 = LED_PIN0|LED_PIN1|LED_PIN2;																			
	/* Off LED's */ 
	IOSET0 = LED_PIN0|LED_PIN1|LED_PIN2;																			
	
	/********************* Blink LED0 each second ************************/
	while(1)
	{
		IOCLR0 = LED_PIN0;
		delay_ms(1000);
		IOSET0 = LED_PIN0;
		delay_ms(1000);
	}
}
