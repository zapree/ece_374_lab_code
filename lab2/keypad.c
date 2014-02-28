// ******************************************************************************************* //

#include "p24fj64ga002.h"
#include "keypad.h"


#define KP_ROW0		PORTBbits.RB12
#define KP_ROW1		PORTBbits.RB13
#define KP_ROW2		PORTBbits.RB14
#define KP_ROW3		PORTBbits.RB15
#define KP_COL0 	PORTBbits.RB7
#define KP_COL1 	PORTBbits.RB10
#define KP_COL2 	PORTBbits.RB11

// ******************************************************************************************* //
volatile int pressed =0;

int main(void){
    KeypadInitialize();

    while(1);
    return 1;
}
void KeypadInitialize() {
        
	
	// TODO: Configure IOs and Change Notificaiton interrupt for keypad scanning. This 
	// configuration should ensure that if any key is pressed, a change notification interrupt 
	// will be generated.
	
	//rows set as output
        TRISBbits.TRISB15 = 0;
        TRISBbits.TRISB14 = 0;
        TRISBbits.TRISB13 = 0;
        TRISBbits.TRISB12= 0;
    //output 0
        LATBbits.LATB15 = 0;
		LATBbits.LATB14 = 0;
		LATBbits.LATB13 = 0;
		LATBbits.LATB12 = 0;

    // setting open drain configuration
        ODCBbits.ODB15 = 1;
        ODCBbits.ODB14 = 1;
        ODCBbits.ODB13 = 1;
        ODCBbits.ODB12 = 1;

    //disabling pull-up resistors for rb12-15
        CNPU1bits.CN11PUE = 0;
		CNPU1bits.CN12PUE = 0;
		CNPU1bits.CN13PUE = 0;
		CNPU1bits.CN14PUE = 0;

	//columns set as inputs
        TRISBbits.TRISB11 = 1;
        TRISBbits.TRISB10 = 1;
        TRISBbits.TRISB7 = 1;
    //for when we flip to be output we want it to be 0
        LATBbits.LATB11 = 0;
		LATBbits.LATB10 = 0;
		LATBbits.LATB7 = 0;

	// setting open drain configuration
		ODCBbits.ODB7 = 1;
		ODCBbits.ODB10 = 1;
		ODCBbits.ODB11 = 1;

	//enabling pull-up resistors
	
        CNPU1bits.CN15PUE = 1;
        CNPU2bits.CN16PUE = 1;
        CNPU2bits.CN23PUE = 1;

    // Change notification
        CNEN1bits.CN15IE = 1;
        CNEN2bits.CN16IE = 1;
        CNEN2bits.CN23IE = 1;

        IFS1bits.CNIF = 0; // Clear the change notification interrupt flag
        IEC1bits.CNIE = 1; // Enable the change notification interrupt.
	
}

// ******************************************************************************************* //

void FlipIO(){
    //rows set as input
        TRISBbits.TRISB15 ^= 1;
        TRISBbits.TRISB14 ^= 1;
        TRISBbits.TRISB13 ^= 1;
        TRISBbits.TRISB12 ^= 1;

    // setting open drain configuration
        ODCBbits.ODB15 ^= 1;
        ODCBbits.ODB14 ^= 1;
        ODCBbits.ODB13 ^= 1;
        ODCBbits.ODB12 ^= 1;
    //disabling pull-up resistors for rb12-15
		CNPU1bits.CN11PUE ^= 1;
		CNPU1bits.CN12PUE ^= 1;
		CNPU1bits.CN13PUE ^= 1;
		CNPU1bits.CN14PUE ^= 1;

	//columns set as outputs

        TRISBbits.TRISB11 ^= 1;
        TRISBbits.TRISB10 ^= 1;
        TRISBbits.TRISB7 ^= 1;

	// setting open drain configuration
		ODCBbits.ODB7 ^= 1;
		ODCBbits.ODB10 ^= 1;
		ODCBbits.ODB11 ^= 1;

    //flip pull up resistors for rb7, 10, 11

        CNPU1bits.CN15PUE ^= 1;
        CNPU2bits.CN16PUE ^= 1;
        CNPU2bits.CN23PUE ^= 1;
}

char KeypadScan(int key_value) {
	// TODO: Implement the keypad scanning procedure to detect if exactly one button of the 
	// keypad is pressed. The function should return:
	//
	//      -1         : Return -1 if no keys are pressed.
	//      '0' - '9'  : Return the ASCII character '0' to '9' if one of the 
	//                   numeric (0 - 9) keys are pressed.
	//      '#'        : Return the ASCII character '#' if the # key is pressed. 
	//      '*'        : Return the ASCII character '*' if the * key is pressed. 
	//       -1        : Return -1 if more than one key is pressed simultaneously.
        

	// Notes: 
	//        1. Only valid inputs should be allowed by the user such that all invalid inputs 
	//           are ignored until a valid input is detected.
	//        2. The user must release all keys of the keypad before the following key press
	//           is processed. This is to prevent invalid keypress from being processed if the 
	//           users presses multiple keys simultaneously.
	//
	char key=-1;
	int mult_check=0;
	FlipIO();
	mult_check = KP_ROW3 + KP_ROW2 + KP_ROW1 + KP_ROW0;
	if(mult_check<3)return key;
	key_value = key_value|KP_ROW3;
	key_value = key_value << 1;
	key_value = key_value|KP_ROW2;
	key_value = key_value << 1;
	key_value = key_value|KP_ROW1;
	key_value = key_value << 1;
	key_value = key_value|KP_ROW0;

	switch(key_value){
		case 0x37:
				key = '1';
				break;

		case 0x57:
				key = '2';
				break;

		case 0x67:
				key = '3';
				break;

		case 0x3B:
				key = '4';
				break;

		case 0x5b:
				key = '5';
				break;

		case 0x6b:
				key = '6';
				break;

		case 0x3D:
				key = '7';
				break;

		case 0x5D:
				key = '8';
				break;

		case 0x6D:
				key = '9';
				break;

		case 0x3E:
				key = '*';
				break;

		case 0x5E:
				key = '0';
				break;

		case 0x6E:
				key = '#';
				break;


	}


	return key;
}

void __attribute__((interrupt,auto_psv)) _CNInterrupt(void){

    char temp_pressed_char = -1;
    int check_mult=0;

    check_mult = check_mult|KP_COL0;
    check_mult = check_mult << 1;
    check_mult = check_mult|KP_COL1;
    check_mult = check_mult << 1;
    check_mult = check_mult|KP_COL2;
    if((check_mult == 0x6 || check_mult == 0x5 ||check_mult == 0x3) && (pressed != 1)){
        temp_pressed_char=KeypadScan(check_mult);
        pressed=1;
    }
    else if(check_mult== 0x7){
        pressed=0;
    }
    //TODO lcd print
    IFS1bits.CNIF = 0;

}

// ******************************************************************************************* //
