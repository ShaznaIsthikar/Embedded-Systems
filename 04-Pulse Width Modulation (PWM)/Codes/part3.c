//Group 33
/* 
Duty_cycle = [ (OCR0 + 1)/256 ] x 100
Duty_cycle = 50 % =>  OCR0 = 127

F_generated_wave = F_oscillator/(256 x Prescaler )

Prescaler = 8
F_generated_wave = 7812.5 Hz

Prescaler = 64
F_generated_wave = 976.56 Hz

Prescaler = 256
F_generated_wave = 244.14 Hz

Prescaler = 1024
F_generated_wave = 61 Hz

*/

#include<avr/io.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 2500
  
unsigned char i;

int main (void){
  
  DDRD = DDRD |(1<<6);	//configure pin 6 of PORTD for output-PWM
  
  OCR0A = 127 ;	//Duty cycle of 50%
  
  //PWM settings
  TCCR0A |= (1<<COM0A1) | (1<<WGM01) | (1<<WGM00);	//Non-Inverting Fast PWM mode
  
  while(1){

    for (i=2;i<6;i++){  //change the prescaler value
   		 TCCR0B=i;
  		_delay_ms(BLINK_DELAY_MS);  //delay
    }
    
  }
  
  return 0;
} 


