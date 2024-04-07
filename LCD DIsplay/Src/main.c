#include <stdio.h>
#include <string.h>
#include "stm32c031xx.h"
#include "LCD.h"
#include "custom.h"





int main(void) {

    LCD_Init();
    Custom_Char(0, middle);
    Custom_Char(1, left);
    Custom_Char(2, right);

    LCD_command(0x80);
    LCD_string("THE BATMAN ");
    //LCD_command(0xC0);


    LCD_data(1);

    LCD_data(0);
    LCD_data(2);


}


