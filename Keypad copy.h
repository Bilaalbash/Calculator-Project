#ifndef _KEYPAD_H
#define _KEYPAD_H

void Keypad_Init(void);
unsigned char readKeypad (void);
char decodeKeyPress(unsigned char k);
void Set_Col(void);
void ReadValue(float in);
void ResetAnswer(void);

extern float Answer;
extern char AString[50];



#endif

