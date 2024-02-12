#ifndef PIN_H
#define PIN_H

#include <stm32f4xx.h>

void setPinAF(GPIO_TypeDef *port, uint8_t pin, uint8_t af_mode);

#endif