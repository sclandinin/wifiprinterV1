/* Scott Clandinin
 * Tech Thesis Project V2
 * Weather data from Open Weather Map:
 * http://api.openweathermap.org/data/2.5/find?q=Saskatoon&units=metric&appid=1324024f8cb94b1444352b7f894fb724
 * Word of the day from Wordnik
 * http://api.wordnik.com/v4/words.json/wordOfTheDay?api_key=a2a73e7b926c924fad7001ca3111acd55af2ffabf50eb4ae5
 * 
 * CSN-A2 thermal receipt printer
 * ESP8266-12 Wi-Fi module
 * 
 */
#include <p18lf25k22.h>
#include "defines.h"
#include "prototypes.h"
#include "delays.h"
#include <stdio.h>
#include <stdlib.h>

//global variables
unsigned char definition[255];

char buff;
char weather1[14] = "Scott's Wi-Fi";
char weather2[16] = "Weather Station";

char printing[13] = "Now Printing";

char press[15] = "Press to Print";

char fail1[11] = "Connection";
char fail2[7] = "Failed";

char try[10] = "Try Again";

char connected[18] = "Wi-Fi Connected  ";

char paperOut[13] = "Out of Paper";
char paperIn[15] = "Paper Replaced";
char connect[14] = "Connecting...";

void main ()
{
    int status;
    //initializations
    port_init();
    lcd_init();
    serial_init();
    
	//this temporary code was used to initialize the ESP. It retains this info without power
    //fprintf(_H_USART, "AT+UART=19200,8,1,0,0\r\n");
 //   fprintf(_H_USART, "AT+CWMODE=1\r\n");           //AP + station mode 
//    delay ();
    
    fprintf(_H_USER, "%c%c%c%c%c", 0x1B, 0x37, 0x07, 0x64, 0x02);   //1ms heat time, 20us heat interval
    delay ();
    
    sleep_all();
    paperCheck();           //check paper status
    
    send_command(0x01);          //clear display
    send_string(press, 14);

    while (1)
    {
        paperCheck();           //check paper status
        delay ();

        if (!button)     //push button
        {
            status = wifi_connect();
            
            if (status == 1)
            {
                send_command(0x01);          //clear display
                send_string(connected, 17);

                get_weather();           //get and print weather

                get_wordoftheday();      //get and print word of the day
                
                delaywifi2();
            }
            
            else
            {
                send_command(0x01);          //clear display
                send_string(fail1, 10);
                send_command(0xC0);          //second line
                send_string(fail2, 6);
                delaywifi2();
                send_command(0x01);          //clear display
                send_string(try, 9);
                delaywifi2();
            }
            
            sleep_all();

            send_command(0x01);          //clear display
            send_string(press, 14);
        } 
    }
}

void get_weather()
{   
    char temp[6] = " ";
    char wind[6] = " ";
    
    weather_start();            //connect to server
    RCSTA1bits.CREN = 1;        //enable receive
    wifi_skip_data();           //skip headers
    temp_read(&temp);           //find temperature
    wind_read(&wind);           //get the wind speed
    RCSTA1bits.CREN = 0;        //disable receive
    
    fprintf(_H_USER, "%c", 0xFF);                       //wake
    delay();
    fprintf(_H_USER, "%c%c", 0x1B, 0x40);               //clear print buffer
   
    fprintf(_H_USER, "%c%c%c", 0x1B, 0x61, 0x01);       //justify center
    fprintf(_H_USER, "-------------------------------\r\n");
    fprintf(_H_USER, "%c%c%c", 0x1B, 0x21, 0x30);       //double size and width
    fprintf(_H_USER, "Current Weather\r\n");  
    fprintf(_H_USER, "in Saskatoon\r\n\r\n"); 

    fprintf(_H_USER, "%c%c%c", 0x1B, 0x21, 0x00);       //normal size
    fprintf(_H_USER, "%c%c%c", 0x1B, 0x61, 0x01);       //justify center
    fprintf(_H_USER, "Temperature:\r\n");  
            
    //get the temperature
    fprintf(_H_USER, "%s", temp); 
            
    fprintf(_H_USER, " %cC\r\n\r\n", 0xF8);  

    fprintf(_H_USER, "Wind Speed:\r\n");  
            
    //get the wind speed
    fprintf(_H_USER, "%s", wind); 
            
    fprintf(_H_USER, " m/s\r\n\r\n");   
    fprintf(_H_USER, "via openweathermap.org\r\n");
    fprintf(_H_USER, "--------------------------------\r\n");  
    fprintf(_H_USER, "%c%c", 0x1B, 0x40);       //clear print buffer
    
}

void get_wordoftheday()
{   
    unsigned char word[15] = " ";
    unsigned char partOfSpeech[10] = " ";

    word_start();                     //connect to server
    RCSTA1bits.CREN = 1;              //enable receive
    wifi_skip_data();                 //skip headers
    word_read(&word);                //find word of the day
    definition_read(&definition);   //get the definition
    partOfSpeech_read(&partOfSpeech); //get the part of speech of the word
    RCSTA1bits.CREN = 0;        //disable receive

    fprintf(_H_USER, "%c", 0xFF);                       //wake
    fprintf(_H_USER, "%c%c", 0x1B, 0x40);       //clear print buffer
    fprintf(_H_USER, "%c%c%c", 0x1B, 0x21, 0x30);       //double size and width
    fprintf(_H_USER, "Word of the Day\r\n\r\n");  
    fprintf(_H_USER, "%c%c%c", 0x1B, 0x21, 0x00);       //normal size
    fprintf(_H_USER, "%c%c%c", 0x1B, 0x61, 0x00);       //justify left
    fprintf(_H_USER, "%c%c%c", 0x1B, 0x21, 0x08);       //bold
    fprintf(_H_USER, "%s - %s\r\n\r\n", word, partOfSpeech); 
    fprintf(_H_USER, "%c%c%c", 0x1B, 0x21, 0x00);       //not bold
    fprintf(_H_USER, "%s", definition); 
    fprintf(_H_USER, "%c%c%c", 0x1B, 0x61, 0x01);       //justify center
    fprintf(_H_USER, "\r\n\r\nvia wordnik.com\r\n");
    fprintf(_H_USER, "%c%c%c", 0x1B, 0x61, 0x00);       //justify left
    fprintf(_H_USER, "-------------------------------\r\n");  
    fprintf(_H_USER, "By Scott Clandinin\r\n\r\n\r\n\r\n\r\n");  

}

void sleep_all()
{
    
    fprintf(_H_USER, "%c%c%c%c", 0x1B, 0x38, 0x00, 0x01);     //send printer to sleep x seconds after printing
    
    send_command(0x01);          //clear display
    send_string(weather1, 13);
    send_command(0xC0);          //second line
    send_string(weather2, 15);
    
    delay();
    INTCONbits.INT0IF = 0;
    fprintf(_H_USART, "AT+GSLP=5000\r\n");                    //send ESP to sleep
    delay();
    reset = 0;      //bring line low to sleep ESP
    
    Sleep();
    Nop();			//nop needs to follow upon waking

    //wake
    
    delay();
    reset = 1;		//wake up ESP

}

//misc
#include "port_init.c"
#include "delays.c"

//LCD
#include "lcd.c"

//USART
#include "wifi_serial.c"
#include "_user_putc.c"

//Printer
#include "printer_serial.c"


