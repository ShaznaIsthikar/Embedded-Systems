#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 100



int main(){
  
  	DDRD = DDRD &~((1<<3)|(1<<2));	//PD3 (INT1) is input
   
    DDRB = DDRB | ((1)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5)) ; 
    //6 LSB of port B is output
    
    EICRA |= (1<< ISC00)|(1<< ISC01)|(1<< ISC10)|(1<< ISC11);	
  	//set for rising edge detection
  
	sei() ;	//enable external interrupts for int0
  
    EIMSK |= (1<<INT0)|(1<<INT1);
  	//enable external input for int0 and int1
   
 	while(1);
   	return 0;
}
signed int z=0;
//led off
ISR (INT0_vect){
  		z=(z<<1) ; //z is shifted by 1
 		PORTB &= ~0xFF;	//port B is st to 0
      	PORTB |= z ;  //port B is or ed with value of z
}
//led on
ISR (INT1_vect){
 		z=(z<<1)+1 ; //z is shifted by 1 and then 1 is added
 		PORTB &= ~0xFF; //port B is st to 0	
      	PORTB |= z ;  //port B is or ed with value of z
  
}


