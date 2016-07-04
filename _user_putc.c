/* this default version should not do anything. it is entirely a
   placeholder symbol. To keep code size at a minimum, it is declared
   without a return value or parameters. The caller will still clean up 
   the stack frame correctly. 

   When using the _H_USER stream, the function will be implemented in
   application code with the prototype:   
    int _user_putc (char c);
  */

//this sets up fprintf to be able to use USART 2 for the printer
int _user_putc (char c)
{
    while(!PIR3bits.TX2IF);
    TXREG2 = c;
    return c;
}
