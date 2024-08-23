#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>
#define LEDPORT (GPIOC)
#define LEDPIN (GPIO_Pin_9)
#define ENABLE_GPIO_CLOCK (RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE))

/* timing is not guaranteed :) */
void simple_delay(uint32_t us)
{
    /* simple delay loop */
    while (us--) {
        asm volatile ("nop");
    }
}

/* system entry point */
int main(void)
{
    /* gpio init struct */
    GPIO_InitTypeDef gpio;
    /* reset rcc */
    RCC_DeInit();
    /* enable clock GPIO */
    ENABLE_GPIO_CLOCK;
    /* use LED pin */
    gpio.GPIO_Pin = LEDPIN;
    /* mode: output push pull */
    gpio.GPIO_Mode = GPIO_Mode_Out_PP;
    gpio.GPIO_Speed = GPIO_Speed_2MHz;
    /* apply configuration */
    GPIO_Init(LEDPORT, &gpio);
    /* main program loop */
    for (;;) {
        /* set led on */
        GPIO_SetBits(LEDPORT, LEDPIN);
        /* delay */
        simple_delay(100000);
        /* clear led */
        GPIO_ResetBits(LEDPORT, LEDPIN);
        /* delay */
        simple_delay(100000);
    }

    /* never reached */
    return 0;
}