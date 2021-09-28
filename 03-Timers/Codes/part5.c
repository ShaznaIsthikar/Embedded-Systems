#include<avr/io.h>
#include <avr/interrupt.h>

int counter=0;
int main (void){
	
  DDRB = DDRB| (1<<0);	//configure pin 5 of PORTB for output
  PORTB |=0x01 ;		//set PORTB pin0 high 

  TCNT0 =131;		//Load timer counter register with initial value 131
  
  TCCR0A = 0x00;	//Set Timer0under nnormal mode 
  TCCR0B =0x04;		//set precaler 1:256
  
  sei();	//enable global interrupts
    
  TIMSK0 |= (1<<TOIE0);	//enable Timer1 overflow  interrupt-timer 1
  
  while (1);	//infinite loop
  
 
  return 0;

}

ISR(TIMER0_OVF_vect){
  
  TCNT0 = 131;	//reload
  counter ++;
  
    if(counter==50){
        PORTB = PORTB ^ (1<<0);	//toggling 
        counter=0;
    }
    
 }