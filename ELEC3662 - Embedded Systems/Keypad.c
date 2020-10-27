#include <stdio.h>   // standard C library 
#include "UART.h"    // functions to implment input/output
#include "TExaS.h"   // Lab grader functions
#include "Keypad.h"

//void Keypad_Init(void);
//unsigned char readKeypad (unsigned char r);
//char decodeKeyPress(unsigned char k);

void Keypad_Init(void){ volatile unsigned long delay;
	
#define Row1	(*((volatile unsigned long *)0x40024004)) //-- Row 1
#define Row2	(*((volatile unsigned long *)0x40024008)) //-- Row 2
#define Row3	(*((volatile unsigned long *)0x40024010)) //-- Row 3
#define Row4	(*((volatile unsigned long *)0x40024020)) //-- Row 4

#define Col1	(*((volatile unsigned long *)0x40007004)) //-- Column 1
#define Col2	(*((volatile unsigned long *)0x40007008)) //-- Column 2
#define Col3	(*((volatile unsigned long *)0x40007010)) //-- Column 3
#define Col4	(*((volatile unsigned long *)0x40007020)) //-- Column 4

}



void readKeypad (void){
	
		//--- Column 1---//
	Col1 = 0x00;
	Col2 = 0x02;
	Col3 = 0x04;
	Col4 = 0x08;
	
	if(Row1 == 0){
		//KEY 1 PRESSED
		printf ("Key 1 has been pressed\n");
	}
	if(Row2 == 0){
		//KEY 4 PRESSED
		printf ("Key 4 has been pressed\n");		
	}
	if(Row3 == 0){
		//KEY 7 PRESSED
		printf ("Key 7 has been pressed\n");
	}
	if(Row4 == 0){
		//KEY * PRESSED
		printf ("Key * has been pressed\n");
	}
	
//	printf("Column 1 is %lu\n",Col1);
//	printf("Column 2 is %lu\n",Col2);
//	printf("Column 3 is %lu\n",Col3);
//	printf("Column 4 is %lu\n",Col4);

//	printf("Row 1 is %lu\n",Row1);
//	printf("Row 2 is %lu\n",Row2);
//	printf("Row 3 is %lu\n",Row3);
//	printf("Row 4 is %lu\n",Row4);
	

		//--- Column 2---//
	Col1 = 0x01;
	Col2 = 0x00;
	Col3 = 0x04;
	Col4 = 0x08;
	
	if(Row1 == 0){
		//KEY 2 PRESSED
		printf ("Key 2 has been pressed\n");
	}
	if(Row2 == 0){
		//KEY 5 PRESSED
		printf ("Key 5 has been pressed\n");
	}
	if(Row3 == 0){
		//KEY 8 PRESSED
		printf ("Key 8 has been pressed\n");
	}
	if(Row4 == 0){
		//KEY 0 PRESSED
		printf ("Key 0 has been pressed\n");
	}
	
//	printf("Column 1 is %lu\n",Col1);
//	printf("Column 2 is %lu\n",Col2);
//	printf("Column 3 is %lu\n",Col3);
//	printf("Column 4 is %lu\n",Col4);

//	printf("Row 1 is %lu\n",Row1);
//	printf("Row 2 is %lu\n",Row2);
//	printf("Row 3 is %lu\n",Row3);
//	printf("Row 4 is %lu\n",Row4);
	
	
		//--- Column 3---//
	Col1 = 0x01;
	Col2 = 0x02;
	Col3 = 0x00;
	Col4 = 0x08;
	
	if(Row1 == 0){
		//KEY 3 PRESSED
		printf ("Key 3 has been pressed\n");
	}
	if(Row2 == 0){
		//KEY 6 PRESSED
		printf ("Key 6 has been pressed\n");
	}
	if(Row3 == 0){
		//KEY 9 PRESSED
		printf ("Key 9 has been pressed\n");
	}
	if(Row4 == 0){
		//KEY # PRESSED
		printf ("Key # has been pressed\n");
	}

//	printf("Column 1 is %lu\n",Col1);
//	printf("Column 2 is %lu\n",Col2);
//	printf("Column 3 is %lu\n",Col3);
//	printf("Column 4 is %lu\n",Col4);

//	printf("Row 1 is %lu\n",Row1);
//	printf("Row 2 is %lu\n",Row2);
//	printf("Row 3 is %lu\n",Row3);
//	printf("Row 4 is %lu\n",Row4);
	
		//--- Column 4---//
	Col1 = 0x01;
	Col2 = 0x02;
	Col3 = 0x04;
	Col4 = 0x00;
	
	if(Row1 == 0){
		//KEY A PRESSED
		printf ("Key A has been pressed\n");
	}
	if(Row2 == 0){
		//KEY B PRESSED
		printf ("Key B has been pressed\n");
	}
	if(Row3 == 0){
		//KEY C PRESSED
		printf ("Key C has been pressed\n");
	}
	if(Row4 == 0){
		//KEY D PRESSED
		printf ("Key D has been pressed\n");
	}
	
//	printf("Column 1 is %lu\n",Col1);
//	printf("Column 2 is %lu\n",Col2);
//	printf("Column 3 is %lu\n",Col3);
//	printf("Column 4 is %lu\n",Col4);

//	printf("Row 1 is %lu\n",Row1);
//	printf("Row 2 is %lu\n",Row2);
//	printf("Row 3 is %lu\n",Row3);
//	printf("Row 4 is %lu\n",Row4);
} 

char decodeKeyPress(unsigned char k){
	
	return k;
}
