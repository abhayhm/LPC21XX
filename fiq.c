/***********************************************************************/
/*																																		 */
/*   Startup.s modified: line 263 ;FIQ_Handler     B     FIQ_Handler   */
/*											 line 264 EXTERN FIQ_Handler									 */
/*																																		 */
/***********************************************************************/

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
	unsigned int tc_state=T0TC; 																									/* Store current state of Timer0 */ 
	
	EXTINT |= EINT3_CONFIG;																												/* Clear EINT3 */
	IOCLR0 = LED_PIN2;
	delay_ms(2500);             																									/* Delay for 5 sec */
	IOSET0 = LED_PIN2;
	
	T0TC=tc_state;																																/*Restore previous state of Timer0 */
	T0TCR=0x01;																																		/*Enable Timer0 */
	
	VICVectAddr = 0x00;
}
/*************************** IRQ handler(ISR) **************************/
__irq void VIC_Int0_Handler(void)
{
	unsigned int tc_state=T0TC; 																									/* Store current state of Timer0 */
	
	EXTINT |= EINT2_CONFIG;																												/* Clear EINT2 */
	IOCLR0 = LED_PIN1;
	delay_ms(5000);																																/* Delay for 10 sec */
	IOSET0 = LED_PIN1;
	
	T0TC=tc_state;																																/*Restore previous state of Timer0 */
	T0TCR=0x01;																																		/*Enable Timer0 */
	
	VICVectAddr = 0x00;	
}

void Extint_Init()
{
	PINSEL0 |= PINSEL_EINT2|PINSEL_EINT3; 																				/*Configure P0.7 and P0.9 as external interrupt 2 and 3*/
	EXTINT &= ~(EINT2_CONFIG|EINT3_CONFIG); 																			/*Clear external interrupt 2 and 3 in EXTINT register */
	EXTMODE &= EINT2_CONFIG|EINT3_CONFIG; 																				/*Configure EINT2 and EINT3 as edge sensitive*/
	EXTPOLAR &= EINT2_CONFIG|EINT3_CONFIG;																				/*Configure EINT2 and EINT3 as falling edge sensitive*/

	VICIntEnable |= EINT2|EINT3; 																									/* Enable EINT2(IRQ) PIN P0.3 and EINT3(FIQ)  P0.7 */
	VICIntSelect |= EINT3;																												/*Configure EINT3 as FIQ*/
	VICVectCntl0 = VICVECTCNT_ENABLE|VICSOFTINT_MAP;															/* Enable VICVectCntl0 and map EINT2 */
	VICVectAddr0 = (unsigned) VIC_Int0_Handler; 																	/*Copy address or ISR EINT2*/
}



int main(void)
{	
	Extint_Init();
	IODIR0 = LED_PIN0|LED_PIN1|LED_PIN2;																					/* Set LED pins as output*/
	IOSET0 = LED_PIN0|LED_PIN1|LED_PIN2;																					/* Off LED's */ 
	
	/********************* Blink LED0 each second ************************/
	while(1)
	{
		IOCLR0 = LED_PIN0;
		delay_ms(1000);
		IOSET0 = LED_PIN0;
		delay_ms(1000);
	}
}
