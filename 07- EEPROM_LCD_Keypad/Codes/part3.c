#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>

#define ALPHABET_SIZE 15

// initialize the LCD Library
LiquidCrystal lcd(11, 10, 5, 4, 3, 2);
char alphabet[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','*'}; 

char Keypad[4][4] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// array for hold the port and pins
int inpArr[4] = {4, 5, 4, 5};

void initKeyPad() {
  DDRC |= 0x0F;// Set PC0, PC1, PC2, PC3 as outputs
  DDRC &= ~(0x30);// set PC4, PC5 as inputs
  DDRB &= ~(0x30);    // set PB4, PB5 as inputs
}

//scanning the key board and get inputs
char pressKeyBoard() {
  // loop until an input found
  while (1) {
    for (int i = 0; i < 4; i++){
      //Set input and output pins. 
      PORTC &= 0b11110000;
      // Setting High the corresponding scan line
      PORTC |= 1<<(i);
  
      // checking for Inputs
      for (int j = 0; j < 4; j++) {
        if (j < 2){
          //checking for input in PORTC
          if ((PINC>>inpArr[j])&1){
            
            _delay_ms(100);
            //return the coordinates of the pressed button
            return(Keypad[i][j]);
          }
        } else {
			//checking for input in PORTB
          if ((PINB>>inpArr[j])&1){
    
            _delay_ms(100);
             //return the coordinates of the pressed button
            return(Keypad[i][j]);
          }
        }
      }
    }
  }
}


// function to get the alphabatic index
int get_index(char c){
    int i = 0;
    // go through the alphabet and get the index
    for(i = 0; i < ALPHABET_SIZE; ++i){
        if(alphabet[i] == c) break;
    }
    return i;
}

int main(){
	
  // set up the LCD:
  lcd.begin(16, 2);
  initKeyPad();
  //set positions x and y
  int xpos = 0;
  int ypos = 0;
  
  char index, input, choice[2];
  int key = EEPROM.read(0);
  char plain_text[10];
  char encrypted[10];
    
  // infinite loop 
  while(1){
	//set the cursor
 	lcd.setCursor(0, 0);
	lcd.print("Encrypt-A");
    lcd.setCursor(0, 1);
    lcd.print("Change key-B");
    
    // read the input
    input = pressKeyBoard();
    
    //clear the screen
    lcd.clear();
    
    if(input == 'A'){
   	  lcd.setCursor(0, 0);
      lcd.print("Enter:");
      
      input = '0';
      xpos = 0;
      ypos = 1;
      
      lcd.setCursor(0, 1); //go to  the next line
      index = 0;
      // loop until 10 characters
      while(1){
      	input = pressKeyBoard();
        //if the number of characters in the input is less than 10
        if(input=='#'){
            break;
		}
        lcd.print(input);  //printing the inpust
        xpos++;  //increasing the crusor position
        
        // add to plain text array
        plain_text[index] = input;  //reading the plain text
        index++;
        // if the length of text is 9 break from loop
        if(index > 9){
        	break;
        }
        lcd.setCursor(xpos, ypos); //updating the crosor position
      }
	  
	 lcd.clear();
	 lcd.setCursor(0, 0);
     lcd.print("Encrypted: ");
     lcd.setCursor(0, 1); //go to next line
	 
    int n = 0, idx = 0;
	int i;
      
	//Encryption
    // go until the input string index ends
	for(i = 0;i<index ; i++ ){
        // get the alphabatic index of the current char
        idx = (get_index(plain_text[i]) + key) % ALPHABET_SIZE; 
        // display the encrypted char
      	lcd.setCursor(n, 1);
     	lcd.print(alphabet[idx]);
    	// increment the cursor position
        n++;

    }
	
     // wait util the next charachter 
     pressKeyBoard();  
	}
	else if(input == 'B'){
      key = 0;
      // set the cursor
      lcd.setCursor(0, 0);
      lcd.print("Enter key:");
      lcd.setCursor(0, 1); //go to the nextline
      lcd.print("__");
      
      // get the key
      input = pressKeyBoard();
      lcd.setCursor(0, 1);
      lcd.print(input);
      // get the first digit
      key += (input-'0')*10;///////
        
      _delay_ms(100);
      // get input for second digit
      input = pressKeyBoard();
      lcd.setCursor(1, 1);
      lcd.print(input);
      key += (input-'0');
      // write to EEPROM
      EEPROM.write(0,key);
        
    }
else{
        // display the error message
    	lcd.setCursor(4, 0);
      	lcd.write("Error!!");
      	_delay_ms(1000);
      	lcd.clear();
    }
	
    _delay_ms(100);
  
}
 return 0;

}