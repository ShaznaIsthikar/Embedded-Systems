#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 5000

unsigned char z=0;	//declaring z variable

int main(){
  	
    DDRD &=~(1<<2);	//PD2 (INT0) is input

  	DDRB = DDRB | ((1)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5)) ; 
  	//6 LSB of port B is output
  
  	EICRA &= ~(1<< ISC00); 
    EICRA |=(1<< ISC01);
  	//set for release of the button
  
 	sei() ;	//enable external interrupts for int0
    EIMSK |= (1<<INT0);	//enable external input for int0
   
 	
  	
    while(1);	//loop forever
  
}

ISR (INT0_vect){
  
     	 z++;			//incrementing z by 1
     	 PORTB = z;		//displaying z

}
  