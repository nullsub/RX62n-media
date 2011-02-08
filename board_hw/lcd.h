#ifndef __LCD_H
#define __LCD_H

#include <stdint.h>

#define LCD_COMMAND_PAGE_ZERO    0x28
#define LCD_COMMAND_PAGE_ONE     0x29
#define LCD_COMMAND_PAGE_TWO     0x2A
#define LCD_COMMAND_PAGE_THREE   0x2B
 

#define LCD_LINE0 0
#define LCD_LINE1 1
#define LCD_LINE2 2
#define LCD_LINE3 3
#define LCD_LINE4 4
#define LCD_LINE5 5
#define LCD_LINE6 6
#define LCD_LINE7 7

const uint8_t * const Fontx5x7_table[256];

void lcd_open();
void lcd_set_x(uint8_t xx);
void lcd_set_y_page(uint8_t yy);
void lcd_command(int8_t command);
void lcd_write(int8_t data);
void lcd_set_address(uint8_t yy, uint8_t xx);
void lcd_string(uint8_t yy, uint8_t xx, const char *str);
void lcd_display_char(char c);
void lcd_display_number(int number);
void lcd_display_number_w_decimal(int number, int decimal_place);


#endif /* __LCD_H */
 
 
