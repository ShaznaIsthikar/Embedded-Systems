#include<avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define BLINK_DELAY_MS 1000


unsigned char z;		//declaring z variable

int main (void){
	
  
  DDRB = DDRB | (1<<5);	//configure pin 5 of PORTB for output
  DDRB = DDRB | (1<<0)|(1<<1)|(1<<2)|(1<<3);
  							//configure first 4 pins of PORTB for output
  PORTB =0;				//set Port B value to low which is led off
  
  TCNT1 =3036;		//Load timer counter register with initial value 3036
  
  TCCR1A = 0x00;	//Set Timer1 under nnormal mode 
  TCCR1B =0x04;		//set precaler 1:256
  
  sei();			//enable global interrupts
  
  TIMSK1 |= (1<<TOIE1);	//enable Timer1 overflow  interrupt-timer 1
  
  while(1){
        
    for ( z=0 ; z < 4 ; z++){	//loop z from 0 to 3
  
    	PORTB = PORTB | (1<<z);	//set pin z high to turn led on
     	_delay_ms(BLINK_DELAY_MS);	//delay
    	PORTB = PORTB &~(1<<z);	//set pin z low to turn led off
    
  	}
  
   	for ( z=0 ; z < 2 ; z++){	//loop z from 0 to 1
    
  		PORTB = PORTB | (4>>z);	//set pin z high to turn led on
     	_delay_ms(BLINK_DELAY_MS);	//delay
    	PORTB = PORTB &~(4>>z);	//set pin z low to turn led off
    
  	}
  
  }
  
  return 0;
  
}


ISR (TIMER1_OVF_vect){
  
  TCNT1 =3036;		//Load timer counter again
  PORTB = PORTB ^ (1<<5);
   
}