#include<avr/io.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 20
int i;

int main (void){
	
  DDRD = DDRD |(1<<6);	//configure pin 6 of PORTD for output-PWM
    
  //OCR0A = 0;
  /*
  Duty cycle =(OCR0A+1)/256*100
  50=(OCR0A+1)*100%
  OCR0A=127
  */
 
 /*
 976.56Hz=16MHz/256*N
 N=64 (prescalar)
 */
 
  TCCR0B |= (1<<CS00)|(1<<CS01);	//set prescaler 1:64
  
  //PWM settings
  TCCR0A |= (1<<COM0A1) | (1<<WGM01) | (1<<WGM00);	//Non-Inverting Fast PWM mode
 
  while(1){
	for (i=0;i<256;i++){
	  OCR0A=i;
	
      //changing the duty cyce from 0 to 100
      _delay_ms(BLINK_DELAY_MS);
	}
    
  	
    for (i=255;i>=0;i--){
      //changing the duty cyce from 100 to 0
	  OCR0A=i;
      _delay_ms(BLINK_DELAY_MS);
	}
    
    
  }
  
  return 0;
}