// Lab 1
// F.S.Isthikar


#include <avr/io.h>
#include <util/delay.h>


#define BLINK_DELAY_MS 500


int main (void){

  //---lab 1.1---

  DDRD = 0x0F ;		//Port D is output			
  PORTD =0;			//set Port B value to low which is led off
  
  while(1){			//loop forever
  
  PORTD = ~ PORTD ;	//toggle portD
  _delay_ms(BLINK_DELAY_MS);	//dealy
  }


  
  //---lab 1.2---
  
 

  unsigned char z;		
  DDRB = 0xF0 ;			//Port B is output
  PORTB =0;				//set Port B value to low which is led off
  
  while(1){				//loop forever
  
  for ( z=0 ; z < 4 ; z++){	//loop z from 0 to 3
  
    PORTB = PORTB | (1<<z);	//set pin z high to turn led on
     _delay_ms(BLINK_DELAY_MS);	//delay
    PORTB = PORTB &~(1<<z);		//set pin z low to turn led off
    _delay_ms(BLINK_DELAY_MS);	//delay
  }
  
   for ( z=0 ; z < 2 ; z++){	//loop z from 0 to 1
    
  	PORTB = PORTB | (4>>z);		//set pin z high to turn led on
     _delay_ms(BLINK_DELAY_MS);	//delay
    PORTB = PORTB &~(4>>z);		//set pin z low to turn led off
    _delay_ms(BLINK_DELAY_MS);	//delay
    
  }


  }
  
  
  return 0;
}
