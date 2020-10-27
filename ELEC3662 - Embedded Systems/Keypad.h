#ifndef _KEYPAD_H
#define _KEYPAD_H

void Keypad_Init(void);
void readKeypad (void);
char decodeKeyPress(unsigned char k);
void Set_Col(void);
void ReadValue(float in);

float Answer;
char AString[50];

#endif