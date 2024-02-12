#include <stm32f4xx.h>
#include "vga.h"

void systemClockInit()
{
    RCC->CR |= (1 << 16); // enable HSE
    while ((RCC->CR & (1 << 17)) == 0)
        ;
    FLASH->ACR |= FLASH_ACR_LATENCY_4WS; // flash memory delay
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC;  // HSE as PLL clock entry

    // PLL clock configuration
    RCC->PLLCFGR &= ~0x3F; // reset PLLM
    RCC->PLLCFGR |= 8;     // PLLM : HSE (8) / 8 = 1 mhz

    RCC->PLLCFGR &= ~0x7FC0;    // reset PLLN
    RCC->PLLCFGR |= (360 << 6); // PLLN : 360 mhz VCO = 360 mhz

    // system clock divider
    RCC->PLLCFGR &= ~(0b11 << 16); // reset PLLP
    RCC->PLLCFGR |= (0b00 << 16);  // div factor 2, useless, just a reminder

    // USB frequency
    RCC->PLLCFGR &= ~(0b1111 << 24); // reset 27:24
    RCC->PLLCFGR |= (8 << 24);       // PLLQ: 360/8 = 45 mhz

    RCC->CR |= RCC_CR_PLLON; // enable PLL
    while ((RCC->CR & RCC_CR_PLLRDY) == 0)
        ;

    // clock for bus
    RCC->CFGR |= (0b1010 << 4) | (0b101 << 10) | (0b100 << 13); // AHB div: 180/8 = 22.5 mhz APB1 div: 180/4 = 45 mhz APB2 div: 180/2 = 90 mhz

    RCC->CFGR |= 0b10; // set PLL as source of the system frequency
    while ((RCC->CFGR & (RCC_CFGR_SWS)) != RCC_CFGR_SWS_1)
        ;
}

int main()
{
    // setup
    systemClockInit();
    VGA vga;

    while (1)
    {
    }
}