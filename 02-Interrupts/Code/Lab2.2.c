#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 5000

int main(){
  	
  	DDRD &= ~(1<<2);	//PD2 (INT0) is input

    DDRB |= (1<<0);		//PB0 is output
 
	EICRA &= ~(1<< ISC00);
    EICRA |=(1<< ISC01);
  	//set for release of the button
  
    EIMSK |= (1<<INT0);	//enable external input for int0
   
 	sei() ;	//enable external interrupts for int0
  	
    while(1);
  	  	
  return 0;
}

ISR (INT0_vect){
  
      PORTB = PORTB ^ (1) ;	//toggling the port B
	
}


