#include<avr/io.h>

void delay_timer0(){
  

  TCNT0 =131;		//Load timer counter register with initial value 131
  
  TCCR0A = 0x00;	//Set Timer0under nnormal mode 
  TCCR0B =0x04;		//set precaler 1:256
  
  while ((TIFR0 &  0x01)==0);	//wait till timer overflowbit(T0V0) is set
  
  TCCR0A =0x00; 	//clear timer settings which stops the timer
  TCCR0B = 0x00;
  
  TIFR0 = 0x01; 	//clear timer overflowbit(T0V0) for next round

}

int main (void){
	
  DDRB == DDRB| (1<<5);	//configure pin 5 of PORTB for output
  
  while(1){					//infinite loop
  
  	PORTB = PORTB ^ (1<<5);//toggling PIN 5
    delay_timer0();			//delay
  }

}