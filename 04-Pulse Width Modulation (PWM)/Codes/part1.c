//Group 33
/* 
F_generated_wave = F_oscillator/(256 x Prescaler )
F_generated_wave = 976.56 Hz => Prescaler = 64

Duty_cycle = [ (OCR0 + 1)/256 ] x 100
Duty_cycle = 50 % =>  OCR0 = 127
 */

#include<avr/io.h>

int main (void){
	
  DDRB = DDRB |(1<<0);	//configure pin 0 of PORTB for output
  DDRD = DDRD |(1<<6);	//configure pin 6 of PORTD for output-PWM
  
  PORTB = (1<<0);	//Set PB0 high 
  
  OCR0A = 127 ;		//Duty cycle of 50%
  
  TCCR0B |= (1<<CS00)|(1<<CS01);	//set prescaler 1:64
  
  //PWM settings
  TCCR0A |= (1<<COM0A1) | (1<<WGM01) | (1<<WGM00);	//Non-Inverting Fast PWM mode
 
  while(1); //Prevent the program from ending
  
  return 0;
} 


