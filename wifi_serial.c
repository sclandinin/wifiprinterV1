//wifi serial
void serial_init()
{
    //USART 1 - wifi module
	TXSTA1bits.SYNC = 0;
	TXSTA1bits.BRGH = 1;
	TXSTA1bits.TX9 = 0;
	TXSTA1bits.TXEN = 1;

	RCSTA1bits.SPEN = 1;
	RCSTA1bits.RX9 = 0;

//	SPBRG1 = 0x08;	//115200 baud rate
//	SPBRGH1 = 0x00;	//115200 baud rate
    SPBRG1 = 0x33;	//19200 baud rate
	SPBRGH1 = 0x00;	//19200 baud rate
//	SPBRG1 = 0x0C;	//74880 baud rate
//	SPBRGH1 = 0x00;	//74880 baud rate    
    
    
    //USART 2 - Printer
	TXSTA2bits.SYNC = 0;
	TXSTA2bits.BRGH = 1;
	TXSTA2bits.TX9 = 0;
	TXSTA2bits.TXEN = 1;

	RCSTA2bits.SPEN = 1;
	RCSTA2bits.RX9 = 0;

	SPBRG2 = 0x33;	//19200 baud rate
	SPBRGH2 = 0x00;	//19200 baud rate

}

void wifi_acknowledge()
{
    char buffer = 'a';

    RCSTA1bits.CREN = 1;
    
    while (buffer != 'K')      //wait for connection acknowledgment 
    {
        while (!PIR1bits.RC1IF);
        buffer = RCREG1;
    }
    RCSTA1bits.CREN = 0;

}

//connect to AP
int wifi_connect()
{
    char buffer = 'a';
    char buffer2 = 'a';
    
    send_command(0x01);          //clear display
    send_string(connect, 13);
    delay();

    fprintf(_H_USART, "AT+CWJAP=\"<NETWORK ID>\",\"<PASSWORD>\"\r\n");
    
    RCSTA1bits.CREN = 1;		//enable receive
    
	//ESP replies with "OK" upon success, so I only look for the first 'K' (my home network doesn't have a 'K', will improve in the future)
    while (buffer != 'K')      //wait for connection acknowledgment 
    {
        while (!PIR1bits.RC1IF);
        buffer = RCREG1;
    } 

    RCSTA1bits.CREN = 0;

        return 1;
}

//start communication with OpenWeatherMap
void weather_start()
{
    fprintf(_H_USART, "AT+CIPSTART=\"TCP\",\"api.openweathermap.org\",80\r\n");
    wifi_acknowledge();              //wait for connection acknowledgment 
    fprintf(_H_USART, "AT+CIPSEND=127\r\n");
    wifi_acknowledge();              //wait for connection acknowledgment 
    fprintf(_H_USART, "GET /data/2.5/find?q=Saskatoon&units=metric&appid=<APP ID> HTTP/1.0\r\nHost: api.openweathermap.org\r\n\r\n\r\n");

}

//start communication with wordnik
void word_start()
{
    fprintf(_H_USART, "AT+CIPSTART=\"TCP\",\"api.wordnik.com\",80\r\n");
    wifi_acknowledge();              //wait for connection acknowledgment 
    fprintf(_H_USART, "AT+CIPSEND=127\r\n");
    wifi_acknowledge();              //wait for connection acknowledgment 
    fprintf(_H_USART, "GET /v4/words.json/wordOfTheDay?api_key=<API KEY> HTTP/1.0\r\nHost: api.wordnik.com\r\n\r\n\r\n");	
	//the above GET request was 127 bytes long including my API KEY
}

void wifi_close()		//ended up not using this
{
    fprintf(_H_USART, "AT+CIPSEND=127\r\n");
    wifi_acknowledge();              //wait for connection acknowledgment 
}

//skips all header and meta data
void wifi_skip_data()
{
    char buffer1;
    buffer1 = 'a';

    while (buffer1 != '{')      //skip to the start of the JSON data
    {
        while (!PIR1bits.RC1IF);
        buffer1 = RCREG1;
        
    }
}

//**********************************************************************************************
void temp_read(char temp[])
{
	int i,j;
    char buffer1, buffer2, buffer3;

    //wait for '{' to appear 3 times
    while (buffer1 != '{')
    {
        while (!PIR1bits.RC1IF)
        {
            Nop();
        }    
        buffer1 = RCREG1;
    }
    
    while (buffer2 != '{')
    {
        while (!PIR1bits.RC1IF)
        {
            Nop();
        }    
        buffer2 = RCREG1;
    }
    
    while (buffer3 != '{')
    {
        while (!PIR1bits.RC1IF)
        {
            Nop();
        }    
        buffer3 = RCREG1;
    }
    
    //skip next 7 characters
    for (i = 0; i < 7; i++)
    {   
        while (!PIR1bits.RC1IF)
        {
            Nop();
        }    
        buffer1 = RCREG1;
    }
    
    //record word until , appears
    for (j = 0; j < 10; j++)
    {   
        while (!PIR1bits.RC1IF)
        {
            Nop();
        }    
        buffer2 = RCREG1;
        
        if (buffer2 == ',')
        {
            return;
        }
        temp[j] = buffer2;
    }
}

void wind_read(char wind[])
{
	int i,j;
    char buffer1, buffer2;

    //wait for 'w' to appear
    while (buffer1 != 'w')
    {
        while (!PIR1bits.RC1IF)
        {
            Nop();
        }    
        buffer1 = RCREG1;
    }
    
    //skip next 14 characters
    for (i = 0; i < 14; i++)
    {   
        while (!PIR1bits.RC1IF)
        {
            Nop();
        }    
        buffer1 = RCREG1;
    }
    
    //record word until , appears
    for (j = 0; j < 10; j++)
    {   
        while (!PIR1bits.RC1IF)
        {
            Nop();
        }    
        buffer2 = RCREG1;
        
        if (buffer2 == ',')
        {
            return;
        }
        wind[j] = buffer2;
    }
}

//**********************************************************************************************
void word_read(char word[])
{
	int i,j;
    char buffer1, buffer2;

    //wait for 'w' to appear
    while (buffer1 != 'w')
    {
        while (!PIR1bits.RC1IF)
        {
            Nop();
        }    
        buffer1 = RCREG1;
    }
    
    //skip next 6 characters
    for (i = 0; i < 6; i++)
    {   
        while (!PIR1bits.RC1IF)
        {
            Nop();
        }    
        buffer1 = RCREG1;
    }
    
    //record word until " appears
    for (j = 0; j < 10; j++)
    {   
        while (!PIR1bits.RC1IF)
        {
            Nop();
        }    
        buffer2 = RCREG1;
        
        if (buffer2 == '"')
        {
            return;
        }
        word[j] = buffer2;
    }

}

void definition_read(char definition[])
{
	int i,j;
    char buffer1, buffer2;

    //wait for '[' to appear twice
    while (buffer1 != '[')
    {
        while (!PIR1bits.RC1IF)
        {
            Nop();
        }    
        buffer1 = RCREG1;
    }
    
    while (buffer2 != '[')
    {
        while (!PIR1bits.RC1IF)
        {
            Nop();
        }    
        buffer2 = RCREG1;
    }
    
    //skip next 9 characters
    for (i = 0; i < 9; i++)
    {   
        while (!PIR1bits.RC1IF)
        {
            Nop();
        }    
        buffer1 = RCREG1;
    }
    
    //record word until " appears
    for (j = 0; j < 255; j++)
    {   
        while (!PIR1bits.RC1IF)
        {
            Nop();
        }    
        buffer2 = RCREG1;
        
        if (buffer2 == '"')
        {
            return;
        }
        definition[j] = buffer2;
    }
}


void partOfSpeech_read(char partOfSpeech[])
{
	int i,j;
    char buffer1, buffer2, buffer3;

    //skip next 17 characters
    for (i = 0; i < 17; i++)
    {   
        while (!PIR1bits.RC1IF)
        {
            Nop();
        }    
        buffer1 = RCREG1;
    }
    
    //record word until " appears
    for (j = 0; j < 30; j++)
    {   
        while (!PIR1bits.RC1IF)
        {
            Nop();
        }    
        buffer3 = RCREG1;
        
        if (buffer3 == '"')
        {
            return;
        }
        partOfSpeech[j] = buffer3;
    }
}

