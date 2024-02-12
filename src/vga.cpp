#include "vga.h"

#include "pin.h"

VGA::VGA()
{
    // clock init
    RCC->APB2ENR |= RCC_APB2ENR_LTDCEN; // enable LTDC clock

    // PLLSAI (pixel clock) configuration
    RCC->PLLSAICFGR |= (200 << 6);    // PLLSAIN *200
    RCC->PLLSAICFGR |= (0b010 << 28); // PLLSAIR /2
    RCC->DCKCFGR &= ~(0b11 << 16);    // reset
    RCC->DCKCFGR |= (0b01 << 16);     // /4

    RCC->CR |= RCC_CR_PLLSAION; // enable PLLSAI
    while ((RCC->CR & RCC_CR_PLLSAIRDY) == 0)
        ;

    // port setup
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOIEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOJEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOKEN;

    setPinAF(GPIOE, 14, 0b1110);

    setPinAF(GPIOI, 0, 0b1110);  // LCD_G5
    setPinAF(GPIOI, 1, 0b1110);  // LCD_G6
    setPinAF(GPIOI, 2, 0b1110);  // LCD_G7
    setPinAF(GPIOI, 4, 0b1110);  // LCD_B4
    setPinAF(GPIOI, 5, 0b1110);  // LCD_B5
    setPinAF(GPIOI, 6, 0b1110);  // LCD_B6
    setPinAF(GPIOI, 7, 0b1110);  // LCD_B7
    setPinAF(GPIOI, 12, 0b1110); // LCD_HSYNC
    setPinAF(GPIOI, 13, 0b1110); // LCD_VSYNC
    // setPinAF(GPIOI, 14, 0b1110); // LCD_CLK
    setPinAF(GPIOI, 15, 0b1110); // LCD_R0

    setPinAF(GPIOJ, 0, 0b1110);  // LCD_R1
    setPinAF(GPIOJ, 1, 0b1110);  // LCD_R2
    setPinAF(GPIOJ, 2, 0b1110);  // LCD_R3
    setPinAF(GPIOJ, 3, 0b1110);  // LCD_R4
    setPinAF(GPIOJ, 4, 0b1110);  // LCD_R5
    setPinAF(GPIOJ, 5, 0b1110);  // LCD_R6
    setPinAF(GPIOJ, 6, 0b1110);  // LCD_R7
    setPinAF(GPIOJ, 7, 0b1110);  // LCD_G0
    setPinAF(GPIOJ, 8, 0b1110);  // LCD_G1
    setPinAF(GPIOJ, 9, 0b1110);  // LCD_G2
    setPinAF(GPIOJ, 10, 0b1110); // LCD_G3
    setPinAF(GPIOJ, 11, 0b1110); // LCD_G4
    setPinAF(GPIOJ, 12, 0b1110); // LCD_B0
    setPinAF(GPIOJ, 13, 0b1110); // LCD_B1
    setPinAF(GPIOJ, 14, 0b1110); // LCD_B2
    setPinAF(GPIOJ, 15, 0b1110); // LCD_B3

    setPinAF(GPIOK, 7, 0b1110); // LCD_DE

    // timing setup
    LTDC->SSCR |= (((HSYNC - 1) << 16) | (VSYNC - 1));
    LTDC->BPCR |= (((HSYNC + HBP - 1) << 16) | (VSYNC + VBP - 1));
    LTDC->AWCR |= (((HSYNC + HBP + WIDTH - 1) << 16) | (VSYNC + VBP + HEIGHT - 1));
    LTDC->TWCR |= (((HSYNC + HBP + WIDTH + HFP - 1) << 16) | (VSYNC + VBP + HEIGHT + VFP - 1));
    // polarity
    LTDC->GCR &= ~(0b1 << 31); // HSYNC negative
    LTDC->GCR &= ~(0b1 << 30); // VSYNC negative

    // bg color
    LTDC->BCCR = 0;

    // layer setup
    LTDC_Layer2->WHPCR |= (((HSYNC + HBP + WIDTH - 1) << 16) | (HSYNC + HBP));
    LTDC_Layer2->WVPCR |= (((VSYNC + VBP + HEIGHT - 1) << 16) | (VSYNC + VBP));

    LTDC_Layer2->CFBAR = (uint32_t)fb;

    LTDC_Layer2->CACR = 255;

    LTDC_Layer2->CFBLR |= (((WIDTH * PIXEL_SIZE) << 16) | (WIDTH * PIXEL_SIZE + 3));
    LTDC_Layer2->CFBLNR |= HEIGHT;

    // enable layer and LTDC activation
    LTDC_Layer2->CR |= LTDC_LxCR_LEN;
    LTDC->GCR |= LTDC_GCR_LTDCEN;
}

void VGA::setPixel(uint16_t x, uint16_t y, uint32_t color)
{
    // fb[(y - 1) * WIDTH + x] = color;
}