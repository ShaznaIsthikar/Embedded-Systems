#include <avr/io.h>

int main()
{
	DDRB  |= (1<<0);//Set the P7 as the output pin
	DDRC &= ~(1<<1);//Pin 1 of PORT C made as an input
	
    ADMUX |= 1<<MUX0;	//selecting the ADC input (ADC1 0001)
  	ADMUX &= ~(1<<MUX1 | 1<<MUX2 | 1<<MUX3);
    
	ADMUX  |= (1<<ADLAR); 	//left adugestment select 
	
   	ADCSRA |= (1<<ADEN);  	//Enable the ADC
  
	ADMUX &= ~(1<<REFS0);	//Selecting the Reference voltage- AREF 
  	ADMUX &= ~(1<<REFS1);
	
    ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);  //select 128 scaller
	ADCSRA |= (1<<ADSC); //start the conversion
    while(1){
  		
  		
      	//Bit ADIF is set when an ADC Conversion completes
   		if (((ADCSRA>>ADIF) & 1)==0){ // Wait until ADC conversion ends
      
      	if(ADCH<100){  //Turn of the LED
        	PORTB |= (1 << PD0); 
      	}
      	else {
      	 	PORTB &= ~(1 << PD0); //Turn off the LED
      	}
		
    	}
		ADCSRA |= 1<<ADSC;	//Turning back on the convertion process. 
	}		
		return 0;
}