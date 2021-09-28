/*
E17122 E17153
F_CPU 16000000		
USART_BAUDRATE 9600
BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16))) - 1)
*/
#include<avr/io.h>

void usart_init(){
	
	/*Set baud rate */
	UBRR0H = 0; 
	UBRR0L = 0x67;
		
	/*Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	
	/*asynchronous mode*/
	UCSR0C &= ~((1<<UMSEL01)|(1<<UMSEL00)); 
	
	/* Set frame format: 8data,no parity, 1 stop bit */
	
	UCSR0C &= ~(1<<UCSZ02); 				//8 bit data frame 
	UCSR0C |= ((1<<UCSZ01)|(1<<UCSZ00));
	
	UCSR0C &= ~((1<<UPM01)|(1<<UPM00));	//no parity
	
	UCSR0C &= (~(1<<USBS0));				//1 stop bit
}	

void usart_send( unsigned char data ){
	
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) );
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

unsigned char usart_receive( void ){
	
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) );
	/* Get and return received data from buffer */
	return UDR0;
}

int main(){
	
	/* initialize the USART*/
	usart_init();
  
	while(1){
	
		/* transmit a character given as the argument*/
		char e_no = usart_receive();
	
		/*returns a received character from the USART*/
		usart_send(e_no);
  
  }
}

