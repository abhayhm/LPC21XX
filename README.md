# LPC2129 FIQ EXAMPLE

This project is an example for enabling FIQ with IRQ(vectored).<br>
Built and tested on target LPC2129 development board.<br>

This example demonstrates the context switching from main to ISR of Fast Interrupt Request and Vectored Interrupt.<br>
This project is built using  keil microvision 4.<br>

## prerequisite

1-Keil microvision 4

download here: [Keil v4.74](https://www.keil.com/demo/eval/armv4.htm)<br>

## Execution 

1-Download the zip.<br>
2-Extract to a folder.<br>
3-Open __fiq.uvproj__ (opens the project by default).<br>
4-Add config.h and fiq.c to the project.<br>
5-__Startup.s__ has been modified please refer to the comments in __fiq.c__<br>
6-__config.h__ has register declaration.<br>



