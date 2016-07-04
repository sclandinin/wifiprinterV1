//printer
void printerTest()
{
    //fprintf(_H_USER, "First print test from prototype. February 23, 2016.\r\n Sending text to printer with default settings.\r\n");
    fprintf(_H_USER, "%c%c%c%c%c", 0x1B, 0x37, 0x07, 0x64, 0x02);   //1ms heat time, 20us heat interval
    fprintf(_H_USER, "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. \r\n\r\n");
    
    //justification
    fprintf(_H_USER, "%c%c%c", 0x1B, 0x61, 0x02);
    fprintf(_H_USER, "Right justified\r\n");     
    fprintf(_H_USER, "%c%c%c", 0x1B, 0x61, 0x01);
    fprintf(_H_USER, "Center justified\r\n");  
    fprintf(_H_USER, "%c%c%c", 0x1B, 0x61, 0x00);
    fprintf(_H_USER, "Left justified\r\n");  
    
    
    //font test
    fprintf(_H_USER, "%c%c%c", 0x1B, 0x21, 0x00);
    fprintf(_H_USER, "Font A test\r\n");
    
    fprintf(_H_USER, "%c%c%c", 0x1B, 0x21, 0x01);
    fprintf(_H_USER, "Font B test\r\n");
    
    //bold test
    fprintf(_H_USER, "%c%c%c", 0x1B, 0x21, 0x08);       //bold
    fprintf(_H_USER, "Bolded text\r\n");
    fprintf(_H_USER, "%c%c%c", 0x1B, 0x21, 0x00);       //not bold
    fprintf(_H_USER, "Not bolded\r\n");
    
    //double height and width
    fprintf(_H_USER, "%c%c%c", 0x1B, 0x21, 0x30);       //double size and width
    fprintf(_H_USER, "double height and width\r\n");
    fprintf(_H_USER, "%c%c%c", 0x1B, 0x21, 0x00);       //normal size
    fprintf(_H_USER, "Normal size\r\n");
    

}

void paperCheck()
{
    char status;
    //fprintf(_H_USER, "%c%c%c", 0x1B, 0x76, 0x04);       //request paper status
    status = printerRead();
    
    if (status != 0x24)
    {
        return;
    }
    else
    {
        send_command(0x01);          //clear display
        send_string(paperOut, 12);
    }
    
    while (status == 0x24)
    {
        LED = 0;
        delay ();
        delay ();
        delay ();
        LED = 1;
        delay ();
        delay ();
        delay ();
        status = printerRead();
    }
    LED = 0;        //turn off LED
    
    send_command(0x01);          //clear display
    send_string(paperIn, 14);
    delaywifi2();
    delaywifi2();
    send_command(0x01);          //clear display
    send_string(press, 14);
}

char printerRead()
{
    char status;
    RCSTA2bits.CREN = 1;                                //receive enable
    fprintf(_H_USER, "%c%c%c", 0x1B, 0x76, 0x04);       //request paper status
    
    while (!PIR3bits.RC2IF)
    {
        Nop();
    }    
    status = RCREG2;
    RCSTA2bits.CREN = 0;                                //receive disable
    return status;
}
