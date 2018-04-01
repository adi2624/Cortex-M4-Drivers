#include <stdint.h>
#include "led.h"

int main(void)
{
	uint32_t i;
	led_init();
	while(1)
	{
	
		led_turn_on(GPIOD,LED_BLUE);
		for(i=0;i<500000;i++);
	led_toggle(GPIOD, LED_BLUE);
		for(i=0;i<500000;i++);
		led_turn_on(GPIOD,LED_ORANGE);
		for(i=0;i<500000;i++);
	led_toggle(GPIOD, LED_ORANGE);
		for(i=0;i<500000;i++);
		led_turn_on(GPIOD,LED_GREEN);
		for(i=0;i<500000;i++);
	led_toggle(GPIOD, LED_RED);
		for(i=0;i<500000;i++);
		led_turn_on(GPIOD,LED_RED);
		for(i=0;i<500000;i++);
	led_toggle(GPIOD, LED_RED);
		for(i=0;i<500000;i++);
		led_turn_on(GPIOD,LED_BLUE);
		led_turn_on(GPIOD,LED_ORANGE);
		led_turn_on(GPIOD,LED_RED);
		led_turn_on(GPIOD,LED_GREEN);
			for(i=0;i<500000;i++);
		
		led_toggle(GPIOD, LED_RED);
		led_toggle(GPIOD, LED_BLUE);
		led_toggle(GPIOD, LED_GREEN);
		led_toggle(GPIOD, LED_ORANGE);
		for(i=0;i<500000;i++);
	
		//for(i=0;i<50000;i++);
	//	led_toggle(GPIOD, LED_ORANGE);
	//	led_toggle(GPIOD, LED_BLUE);
		//for(i=0;i<500000;i++);
		
		//for(i=0;i<50000;i++);
	//	led_turn_off(GPIOD, LED_ORANGE);
	//	led_turn_off(GPIOD, LED_BLUE);
		//	led_turn_on(GPIOD, LED_ORANGE);
		//for(i=0;i<500000;i++);
		//for(i=0;i<500000;i++);
		//	for(i=0;i<500000;i++);
	//	for(i=0;i<500000;i++);
	}
	return 0;
}


void led_init(void)
{
	gpio_pin_conf_t led_pin_conf;
	
	_HAL_RCC_GPIOD_CLK_ENABLE();
	
	led_pin_conf.pin = LED_ORANGE;
	led_pin_conf.mode = GPIO_PIN_OUTPUT_MODE;
	led_pin_conf.op_type = GPIO_PIN_OP_TYPE_PUSH_PULL;
	led_pin_conf.pull = GPIO_PIN_NO_PULL;
	led_pin_conf.speed = GPIO_PIN_SPEED_MEDIUM;
	hal_gpio_init(GPIOD, &led_pin_conf);
	
	led_pin_conf.pin = LED_BLUE;
	hal_gpio_init(GPIOD, &led_pin_conf);
	
	led_pin_conf.pin = LED_GREEN;
	hal_gpio_init(GPIOD, &led_pin_conf);
	
	led_pin_conf.pin = LED_RED;
	hal_gpio_init(GPIOD, &led_pin_conf);
	
}

void led_turn_on(GPIO_TypeDef *GPIOx, uint16_t pin_no)
{
	hal_gpio_write_to_pin(GPIOx,pin_no,1);
}

void led_turn_off(GPIO_TypeDef *GPIOx, uint16_t pin_no)
{
	hal_gpio_write_to_pin(GPIOx,pin_no,0);
}

void led_toggle(GPIO_TypeDef *GPIOx,uint16_t pin_no)
{
	if(hal_gpio_read_from_pin(GPIOx,pin_no))

	{

		 hal_gpio_write_to_pin(GPIOx,pin_no, 0);

	}else

	{

		 hal_gpio_write_to_pin(GPIOx,pin_no, 1);

		

	}
	//hal_gpio_write_to_pin(GPIOx,pin_no, ~(hal_gpio_read_from_pin(GPIOx, pin_no)));
}
