//port init
void port_init()
{
    OSCCON = 0x70;  //16MHz

    ANSELA = 0;
	ANSELB = 0;
    ANSELC = 0;

    PORTA = 0;   
    PORTB = 0; 
    PORTC = 0b00100000;    

    TRISA = 0;      
    TRISB = 0b10000001;   
    TRISC = 0b10000000;    

    
    INTCONbits.INT0IE = 1;
    
}
