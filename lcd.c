//lcd
void lcd_init()
{
    delaylcd();
	
    send_command(0x38);          //function set, 8 bit, 2 line
    send_command(0x0C);          //turn display on, cursor off
    send_command(0x06);          //entry mode, cursor increment and no display shift
    send_command(0x01);          //clear display

}

void send_command(char command)
{
    char value;
    
    DC = 0;          //D/C set to command    
    RW = 1;          //R/W starts high
    delaylcd();
    RW = 0;          //set R/W for write
    delaylcd();  
    EN = 1;          //enable the chip select
    delaylcd();
    
    value = reverse_bits(command);	//reverse the bits before sending to port
            
    PORTA = value;
    
    delaylcd();
    EN = 0;          //enable the chip select
    delaylcd();
    RW = 1;          //R/W starts high
    delaylcd();    
}

void send_data(char data)
{
    char value;
    
    DC = 1;          //D/C set to data    
    RW = 1;          //R/W starts high
    delaylcd();
    RW = 0;          //set R/W for write
    delaylcd();
    EN = 1;          //enable the chip select
    delaylcd();
    
    value = reverse_bits(data);		//reverse the bits before sending to port
            
    PORTA = value;
    delaylcd();
    EN = 0;          //enable the chip select
    delaylcd();
    RW = 1;          //R/W starts high
    delaylcd();    
    
}

void send_string(char string[],int length)
{
    int i;
    
    for (i = 0; i < length; i++)
    {
        send_data(string[i]);
    }
    
}

//I designed my board wrong and reversed the data pins, all I'm doing here is reversing the bits before sending it out to the port
char reverse_bits(char value)
{
    
    char reversed = 0;
    int i;
    
    for(i=0; i<=7; i++)
    {
        reversed<<=1;
        reversed|=(value&1);
        value>>=1;
    }
    return reversed;
}
