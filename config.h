/***********************************************************************/
/*																	   */
/*             Header file for LPC2129 FIQ example                     */
/*																	   */
/***********************************************************************/

/* P0.0 as LED0 used in main()*/
#define LED_PIN0 (1<<0)
/* P0.1 as LED1 used in __irq VIC_Int0_Handler()*/
#define LED_PIN1 (1<<1)									
/* P0.2 as LED2 used in FIQ FIQ_Handler()*/
#define LED_PIN2 (1<<2)															

/* Select bit 16 (external interrupt 2) in interrupt table*/
#define EINT2 (1<<16)															
/* Select bit 17 (external interrupt 3) in interrupt table*/
#define EINT3 (1<<17)															

/* Selecting pin P0.7 */
#define PINSEL_EINT2 (3<<14)													
/* Selecting pin p0.9 */
#define PINSEL_EINT3 (3<<18)													

/* Select external interrupt 2 in EXTINT */
#define EINT2_CONFIG (1<<2)														
/* Select external interrupt 3 in EXTINT */
#define EINT3_CONFIG (1<<3)														

/* Set enable pin for VICVectCntl */
#define VICVECTCNT_ENABLE (1<<5)												
/* Used for Mapping EINT2 0x10 */
#define VICSOFTINT_MAP (1<<4)													
