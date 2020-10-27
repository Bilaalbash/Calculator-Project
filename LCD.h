#ifndef LCD_H
#define LCD_H

void lcd_Init(void);
void lcdENpulse(void);
void lcdClearScreen(void);
void lcdWriteCommand(unsigned char c);
void lcdWriteHalfCommand(unsigned char c2);
void lcdWriteString(char *string);
void lcdWriteChar(char c3);

#endif

