//************************************************************************************************
//defines

#define button PORTBbits.RB0
#define reset PORTCbits.RC5
#define LED PORTBbits.RB1

#define DC PORTCbits.RC2
#define RW PORTCbits.RC1
#define EN PORTCbits.RC0

//************************************************************************************************
//Configuration Bits Set in code
//You find the definitions in MPlab only
//Help -> PIC18 Config Settings -> PIC18F25K22
#pragma config FOSC = INTIO67 		//Internal oscillator block, CLKOUT function on RA6, port function on RA7  
#pragma config PLLCFG = OFF		//Oscillator multiplied by 4
#pragma config PRICLKEN = ON 		//Primary clock is always enabled  
#pragma config IESO = OFF		//Oscillator Switchover mode disabled  
#pragma config FCMEN = OFF 		//Fail-Safe Clock Monitor disabled  
#pragma config PWRTEN = OFF		//Power up timer disabled  
#pragma config BOREN = OFF	 	//Brown-out Reset disabled in hardware only   
#pragma config BORV = 190 		//VBOR set to 1.90 V nominal  
#pragma config WDTEN = OFF 		//Watch dog timer is always disabled. SWDTEN has no effect. 
#pragma config CCP2MX = PORTB3 		//CCP2 input/output is multiplexed with RB3  
#pragma config PBADEN = OFF		//PORTB<5:0> pins are configured as digital I/O on Reset 
#pragma config HFOFST = OFF 		//HFINTOSC output and ready status are delayed by the oscillator stable status  
#pragma config MCLRE = EXTMCLR 		//MCLR pin enabled, RE3 input pin disabled  
#pragma config STVREN = OFF		//Stack full/underflow will cause Reset  
#pragma config LVP = OFF		//NO Low Voltage Program, Single-Supply ICSP disabled 
#pragma config XINST = OFF 		//Instruction set extension and Indexed Addressing mode disabled (Legacy mode)  
#pragma config DEBUG = ON		//Background debugging on RB7 & RB6
//
#pragma config CP0 = OFF		//BLOCK 0 NOT CODE PROTECTED
#pragma config CP1 = OFF		//BLOCK 1 NOT CODE PROTECTED
#pragma config CP2 = OFF		//BLOCK 2 NOT CODE PROTECTED
#pragma config CP3 = OFF		//BLOCK 3 NOT CODE PROTECTED
#pragma config CPB = OFF		//BOOT BLOCK NOT CODE PROTECTED
#pragma config CPD = OFF		//DATA EEPROM NOT CODE PROTECTED
#pragma config WRT0 = OFF		//BLOCK 0 NOT WRITE PROTECTED
#pragma config WRT1 = OFF		//BLOCK 1 NOT WRITE PROTECTED
#pragma config WRT2 = OFF		//BLOCK 2 NOT WRITE PROTECTED
#pragma config WRT3 = OFF		//BLOCK 3 NOT WRITE PROTECTED
#pragma config WRTB = OFF		//BOOT BLOCK NOT WRITE PROTECTED
#pragma config WRTC = OFF		//CONFIGURATION REGISTER NOT WRITE PROTECTED
#pragma config WRTD = OFF		//DATA EEPROM NOT WRITE PROTECTED
#pragma config EBTR0 = OFF		//BLOCK 0 NOT PROTECTED FROM TABLE READS FROM OTHER BLOCKS
#pragma config EBTR1 = OFF		//BLOCK 1 NOT PROTECTED FROM TABLE READS FROM OTHER BLOCKS
#pragma config EBTR2 = OFF		//BLOCK 2 NOT PROTECTED FROM TABLE READS FROM OTHER BLOCKS
#pragma config EBTR3 = OFF		//BLOCK 3 NOT PROTECTED FROM TABLE READS FROM OTHER BLOCKS
#pragma config EBTRB = OFF		//BOOT BLOCK NOT PROTECTED FROM TABLE READS FROM OTHER BLOCKS
