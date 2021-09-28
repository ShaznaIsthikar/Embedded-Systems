
/*
F_input = 16 MHz / 128
		= 125 kHz
Max = 5V
Precision = 5V/8
		  = 0.625 V
*/

#include <avr/io.h>
int main (void){
  
  int x;
  unsigned char y;
  
  DDRC 	 &= ~(1<<1) ;	//Set the ADC1 PC1 as an input pin
  
  DDRD	|= 0xFF ;	//set the PORTD s as output
  
  ADCSRA |= (1<<ADEN) ;	//Enabling ADC bit
  ADCSRA |= ((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)) ; //select the conversion speed
  						//set the division factor as 128
  ADMUX |= (1<<REFS0) ;	//Voltage reference is set to Vcc
  ADMUX &=~(1<<REFS1) ;
    
  ADMUX |= (1<<MUX0) ;	//Set the ADC1 input channel
  ADMUX &= ~((1<<MUX1)|(1<<MUX2)|(1<<MUX3)) ;
  
  ADCSRA|= (1<<ADSC) ; //Activate the start conversion
  
  ADMUX |= (1<<ADLAR);  //left justification of the ADC
  
  while (1) {
  	
    if(ADCSRA & (1<<ADIF)){   // Checking  for ADIF bit for compleate the conversion
  		x=ADCH;	
      	y= (x*8)/256;
      	
      for (int i=0;i<=y;i++){
      	PORTD = (1<<i);
      }
  	     
    } 
    
    
  }
}