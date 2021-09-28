#include <avr/io.h>
#include <ctype.h>
#include <string.h>

//initialize function
void usart_init()
{
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);   //enable transmitter & receiver
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); //8-bit data, no parity, 1 stop bit
    UBRR0L = 0x67;                          //baud rate=9600
}
//To transmit a character
void usart_send(char data){
  
  // Wait for empty transmit buffer
  while(!((UCSR0A >> UDRE0)&1)){}
  
  // Put data into buffer, sends the data 
  UDR0 = data;
}


//To return a recieved character
char usart_receive(){
  
  // Wait for data to be received 
  while(!((UCSR0A >> RXC0)&1)){}
  
  //Get and return received data from buffer 
  return UDR0;
}

  
void EEPROMwrite(unsigned int address, char data){

	// wait for completion of previous write
	while (EECR & (1<<EEPE));

	// set up address and data regs
	EEAR = address;
	EEDR = data;

	// write logical 1 to EEMPE(EEPROM master write enable)

	EECR |= (1<<EEMPE); 
	
	// start eeprom write (EEPROM write enable)
	EECR |= (1<<EEPE);
}

char EEPROMread(unsigned int address){

	// wait for completion of previous write
	while (EECR & (1<<EEPE));

	// set up address
	EEAR = address;

	// start eeprom read
	EECR |= (1<<EERE);

	return EEDR;
}
/*
int main(){
    
    
  	usart_init();  //initializing the USART
    
    char data[1024];   //character variable to store the receiving character
    char D;
    unsigned int A=0;
    
    int i=0;

    while(1){
        
        while(D!='\r'){        //doing until data is not equal to a carriage return
            D=usart_receive();   //receive the character
            data[i]=D;
            i++;
        }
        D=' ';

        for(int j=0;j<i;j++){
            EEPROMwrite(A,data[j]);
            A++;
        }
        i=0; 
        

        for(int k=0;k<1024;k++){ // clearring
            data[k]='\0';
        }
		//for(int a=0;a<1024;a++){
        //    EEPROMwrite(a,data[a]);
        //}
               
    }
    

    return 0;
}
*/

int main()
{

    usart_init();

    unsigned int i;

    for (i = 0; i < 1023; i++)
    {
        // read from eeprom
        char ret = EEPROMread(i);
        usart_send(ret);
    }

    return 0;
}
