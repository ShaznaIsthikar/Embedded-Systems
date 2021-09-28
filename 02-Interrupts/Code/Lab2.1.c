

#include <util/delay.h>

#define BLINK_DELAY_MS 100

int main (void){
  
  DDRD &= ~(1<<7) ; //PD7 is input
  DDRB = DDRB | ((1)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5)) ;
   //6 LSB of port B is output
  
  unsigned char z=0;	//z variable
  
  while (1){			//loop forever
    
    if (PIND & (1<<7)){	//checking whether the 7th pin is high
      
      z++;				//incrementing z by 1
      PORTB = z;		//displaying z
      _delay_ms(BLINK_DELAY_MS);	//delay
      
     }
  }
  return 0;
}
 