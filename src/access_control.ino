#include<Arduino.h>
#include "lcd.h"
volatile unsigned char *ddrb   = (volatile unsigned char *)0x24;
volatile unsigned char *tccr1a = (volatile unsigned char *)0x80;
volatile unsigned char *tccr1b = (volatile unsigned char *)0x81;

volatile unsigned char *ocr1al = (volatile unsigned char *)0x88;
volatile unsigned char *ocr1ah = (volatile unsigned char *)0x89;

volatile unsigned char *icr1l = (volatile unsigned char *)0x86;
volatile unsigned char *icr1h = (volatile unsigned char *)0x87;

volatile char *dirf, *dirk, *dira, *dirb;
volatile char *outf, *outa, *ink, *outb;

volatile char col, digit,ok,clear;



unsigned char seg[11] =
{
    0x3F,   
    0x06, 
    0x5B,   
    0x4F,   
    0x66,  
    0x6D,  
    0x7D,  
    0x07,   
    0x7F, 
    0x6F,
    0x00   
};

volatile char d[4] = {10, 10, 10, 10};

void setup()
{
  
    dirf = (volatile char *)0x30;
    dirk = (volatile char *)0x107;

    
    dira = (volatile char *)0x21;
    dirb = (volatile char *)0x24;

    *dirf = 0x0F;      
    *dirk = 0x00;      

    *dira = 0xFF;     
    *dirb = 0xFF;     

    outf = (volatile char *)0x31;
    outa = (volatile char *)0x22;
    outb = (volatile char *)0x25;

    ink = (volatile char *)0x106;

  
    *ddrb |= (1 << 5);

    

    *tccr1a = (1 << 7) | (1 << 1);

    *tccr1b = (1 << 4) |
              (1 << 3) |
              (1 << 1);

    /* TOP = 39999 */
    *icr1h = 39999 >> 8;
    *icr1l = 39999 & 0xFF;

    /* 1.5 ms pulse */
    *ocr1ah = 3000 >> 8;
    *ocr1al = 3000 & 0xFF;


     *portc= 0xFF;
  *portl = 0x03;
  initlcd();
  display();


}


void loop()
{
    static unsigned char count = 0;

    for(volatile int row = 0; row < 4; row++)
    {
        
        *outf = 1 << row;

        col = *ink & 0x0F;

        if(col)
        {
          

            if(row == 0 && col == 0x01)
                digit = 1;

            else if(row == 0 && col == 0x02)
                digit = 2;

            else if(row == 0 && col == 0x04)
                digit = 3;

            else if(row == 1 && col == 0x01)
                digit = 4;

            else if(row == 1 && col == 0x02)
                digit = 5;

            else if(row == 1 && col == 0x04)
                digit = 6;

            else if(row == 2 && col == 0x01)
                digit = 7;

            else if(row == 2 && col == 0x02)
                digit = 8;

            else if(row == 2 && col == 0x04)
                digit = 9;

            else if(row == 3 && col == 0x02)
                digit = 0;
            
            else if(row == 3 && col == 0x04)
                ok = 1;

            else if(row == 3 && col == 0x01)
                clear = 1;
          

            if(count < 4)
            {
                d[count] = digit;
                count++;
            }

           

            delay(100);

            while((*ink & 0x0F) != 0)
            {
              
            }
        }

if(clear == 1)
{
    d[0] = 10;
    d[1] = 10;
    d[2] = 10;
    d[3] = 10;

    count = 0;

    clear = 0;
}
       

        *outb = 0x01;
        *outa = ~(seg[d[0]]);
        delay(2);
        *outa = 0xFF;


        *outb = 0x02;
        *outa = ~(seg[d[1]]);
        delay(2);
        *outa = 0xFF;


        *outb = 0x04;
        *outa = ~(seg[d[2]]);
        delay(2);
        *outa = 0xFF;


        *outb = 0x08;
        *outa = ~(seg[d[3]]);
        delay(2);
        *outa = 0xFF;

        if((count == 4) && (ok ==1))
{
    if(d[0] == 1 &&
       d[1] == 2 &&
       d[2] == 3 &&
       d[3] == 4)
    {
        access_granted();

        *ocr1ah = 4000 >> 8;
        *ocr1al = 4000 & 0xFF;

        delay(3000);

   
        *ocr1ah = 3000 >> 8;
        *ocr1al = 3000 & 0xFF;

        d[0] = 10;
    d[1] = 10;
    d[2] = 10;
    d[3] = 10;
    }
    else
    {
        access_denied();
    }

    count = 0;
    ok=0;
}
    }
}
