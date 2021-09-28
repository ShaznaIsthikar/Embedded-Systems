#include<avr/io.h>
#include <avr/interrupt.h>

int counter=0;
int main (void){
	
  DDRB = DDRB| (1<<0) | (1<<1);	//configure pin 0,1 of PORTB for output
  PORTB |=0x03 ;			//set PORTB pin0,1 high 

  //timer0
  TCNT0 =131;		//Load timer counter register with initial value 131
  
  TCCR0A = 0x00;	//Set Timer0under nnormal mode 
  TCCR0B =0x04;		//set precaler 1:256
  
  //timer1
  TCNT1 =34286;		//Load timer counter register with initial value 34286
  
  TCCR1A = 0x00;	//Set Timer1under nnormal mode 
  TCCR1B =0x04;		//set precaler 1:256
  
  sei();	//enable global interrupts
    
  TIMSK0 |= (1<<TOIE0);	//enable Timer0 overflow  interrupt-timer 0
  TIMSK1 |= (1<<TOIE1);	//enable Timer1 overflow  interrupt-timer 1
  
  while (1);	//infinite loop
  
 
  return 0;

}

ISR(TIMER0_OVF_vect){
  
  TCNT0 = 131;	//reload
  counter ++;
  
    if(counter==25){
        PORTB = PORTB ^ (1<<0);
        counter=0;
    }
    
 }

ISR (TIMER1_OVF_vect){
  
  TCNT1 =34286;		//Load timer counter again
  PORTB = PORTB ^ (1<<1);

       
}