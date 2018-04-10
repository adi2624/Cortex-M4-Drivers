#include "gpio_driver.h"
#ifndef LED_H
#define LED_H

#define GPIOD_PIN_12 					12
#define GPIOD_PIN_13					13
#define GPIOD_PIN_14					14
#define GPIOD_PIN_15					15

#define LED_GREEN 						GPIOD_PIN_12
#define LED_ORANGE						GPIOD_PIN_13
#define LED_RED								GPIOD_PIN_14
#define LED_BLUE							GPIOD_PIN_15

#define GPIO_BUTTON_PIN				0

void led_init(void);

void led_turn_on(GPIO_TypeDef *GPIOx, uint16_t pin);
void led_turn_off(GPIO_TypeDef *GPIOx, uint16_t pin);
void led_toggle(GPIO_TypeDef *GPIOx, uint16_t pin);

#endif

