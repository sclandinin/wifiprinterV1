//delays

void delay ()
{
  int i;

  for (i = 0; i < 10000; i++)
  {
     Delay1TCY();
     Delay1TCY();
     Delay1TCY();
     Delay1TCY();
  }      
}

void delaywifi ()
{
  int i;

  for (i = 0; i < 10; i++)
  {
      delay();
  } 
}


void delaywifi2 ()
{
  int i;

  for (i = 0; i < 20; i++)
  {
      delay();
  }    
}

void delaylcd ()
{
  int i;

  for (i = 0; i < 999; i++)
  {
     Delay1TCY();
  }
}
