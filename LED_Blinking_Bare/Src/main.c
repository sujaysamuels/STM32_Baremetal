

//AHB1 configuration base addresses
#define PERIPH_BASE  				(0x40000000UL)
#define AHB1_PERIPH_OFFSET 			(0x00020000UL)
#define AHB1_PERIPH_BASE 			(PERIPH_BASE + AHB1_PERIPH_OFFSET)

//RCC base addresses
#define RCC_OFFSET					(0x3800UL)
#define RCC_AHB1_BASE				(AHB1_PERIPH_BASE + RCC_OFFSET)

//GPIOA Base Addresses
#define GPIOA_PERIPH_OFFSET			(0x00UL)
#define GPIOA_PERIPH_BASE			(GPIOA_PERIPH_OFFSET + AHB1_PERIPH_BASE)


//RCC peripheral clock enable
#define AHB_RCC_REG_OFFSET			 (0x30UL)
#define AHB_RCC_REG			(*(volatile unsigned int*)(RCC_AHB1_BASE + AHB_RCC_REG_OFFSET))

//GPIO mode register
#define GPIO_MODE_REG_OFFSET		 (0x00UL)
#define GPIO_MODE_REG		(*(volatile unsigned int*)(GPIOA_PERIPH_BASE + GPIO_MODE_REG_OFFSET))

//GPIO output configuration
#define GPIO_OP_REG_OFFSET			(0x14UL)
#define GPIO_OP_REG			(*(volatile unsigned int*)(GPIO_OP_REG_OFFSET+GPIOA_PERIPH_BASE))


#define GPIOAEN						(1UL<<0)

#define GPIO_OP						(1UL<<5)
#define LED_PIN						GPIO_OP


int main(void)
{
	AHB_RCC_REG |= GPIOAEN;

	GPIO_MODE_REG |=(1UL<<10);
	GPIO_MODE_REG &=~(1UL<<11);

	while(1)
	{
		GPIO_OP_REG |=LED_PIN;

	}



}
