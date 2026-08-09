volatile char *portc = (volatile char *)0x27;
volatile char *portl = (volatile char *)0x10A;
volatile char *outc = (volatile char *)0x28;
volatile char  *outl = (volatile char *)0x10B;


void delaygen()
{
  delay(1);
}

void send()
{
 *outl |=(1<<1);
   delaygen();
   *outl &=~(1<<1);
}

void initlcd()
{

  *outl &=~(1<<0);
    *outc = 0x01;
    send();
    *outc = 0x38;
    send();
    *outc = 0x0C;
    send();
    *outc = 0x06;
    send();
    *outl |=(1<<0);
}
void display()
{
*outl |= (1<<0); 
*outc = 'W';
send();
*outc = 'E';
send();
*outc = 'L';
send();
*outc = 'C';
send();
*outc = 'O';
send();
*outc = 'M';
send();
*outc = 'E';
send();

*outl &= ~(1<<0); 
}

void access_granted()
{
    *outl &= ~(1 << 0);     // RS = 0
    *outc = 0x01;           // Clear LCD
    send();

    *outl |= (1 << 0);      // RS = 1

    *outc = 'A';
    send();
    *outc = 'C';
    send();
    *outc = 'C';
    send();
    *outc = 'E';
    send();
    *outc = 'S';
    send();
    *outc = 'S';
    send();

    *outc = ' ';
    send();

    *outc = 'G';
    send();
    *outc = 'R';
    send();
    *outc = 'A';
    send();
    *outc = 'N';
    send();
    *outc = 'T';
    send();
    *outc = 'E';
    send();
    *outc = 'D';
    send();

    *outl &= ~(1 << 0);
}

void access_denied()
{
    *outl &= ~(1 << 0);
    *outc = 0x01;
    send();

    *outl |= (1 << 0);

    *outc = 'A';
    send();
    *outc = 'C';
    send();
    *outc = 'C';
    send();
    *outc = 'E';
    send();
    *outc = 'S';
    send();
    *outc = 'S';
    send();

    *outc = ' ';
    send();

    *outc = 'D';
    send();
    *outc = 'E';
    send();
    *outc = 'N';
    send();
    *outc = 'I';
    send();
    *outc = 'E';
    send();
    *outc = 'D';
    send();

    *outl &= ~(1 << 0);
}

