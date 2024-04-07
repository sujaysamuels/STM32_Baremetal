#include "stm32c031xx.h"
#include <stdio.h>
#include<string.h>

#define RS 0x01   //Assigning RS to the Pin PA0
#define RW 0x02   //Assigning RS to the Pin PA1
#define EN 0x04   //Assigning RS to the Pin PA2



void LCD_Init(void) {
    GPIO_Init();//Initialising the GPIO Ports

    //Initialising the LCD
    delayMs(30);
    LCD_command(0x30);
    delayMs(10);
    LCD_command(0x30);
    delayMs(1);
    LCD_command(0x30);

    LCD_command(0x38);      //set 8-bit data, 2-line, 5x7 font
    LCD_command(0x06);      //move cursor right after each char
    LCD_command(0x01);      //clear screen, move cursor to home
    LCD_command(0x0F);      //turn on display, cursor blinking
}


//GPIO Initializtion Function
void GPIO_Init(void) {

  //Setting RCC IOPENER REG for both Ports A and B
	RCC->IOPENR|=(0x03UL);

	//Setting Output mode for B pins
	GPIOB->MODER|=(0x5555UL);
	GPIOB->MODER&=~(0xAAAAUL);

	//Setting Output mode for A pins
	GPIOA->MODER|=(0x15UL);
	GPIOA->MODER&=~(0x2AUL);

}


//LCD Command Function
void LCD_command(unsigned char command) {
    GPIOA->BSRR = (RS | RW) << 16;  // RS = 0, RW = 0 , setting command mode

    GPIOB->ODR = command;           //sending command from port B pins
    GPIOA->BSRR = EN;               //Turning on EN
    delayMs(0);
    GPIOA->BSRR = EN << 16;        // clear EN

}


void LCD_data(char data) {

    GPIOA->BSRR = RS;               // RS = 1
    GPIOA->BSRR = RW << 16;         // RW = 0
    GPIOB->ODR = data;             //sending data from port B pins
    GPIOA->BSRR = EN;                //Turning on EN
    delayMs(0);
    GPIOA->BSRR = EN << 16;         // clear EN
}

//take string as input(Better than doing it char by char :)
void LCD_string(char* data)
{

  for(int i=0;i<strlen(data);i++)
  {
    LCD_data(*(data+i));

  }

}





//shift the display by requested length to right
void shiftright(int length)
{
   for(int i=0;i<length;i++)
   {


    delayMs(5000);
    LCD_command(0x1C);

   }
}


//shift the display by requested length to left
void shiftleft(int length)
{
   for(int i=0;i<length;i++)
   {


    delayMs(5000);
    LCD_command(0x18);

   }
}

//function to set custom characters
void Custom_Char(char location, char* data)
{
    LCD_command(0x40 + 8*location); // Set CGRAM address for the custom character
    for(int i=0; i<8; i++)
    {

      LCD_data(data[i]); // Write custom character pattern to CGRAM
    }

}


void delayMs(int delay)
{
  for(int i=0;i<delay;i++)
  {

  }
}
