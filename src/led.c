//
// LED: Handles blinking of status light
//

#include "stm32f0xx_hal.h"
#include "led.h"


// Private variables
#ifdef CANABLE_HW
static uint32_t led_blue_laston = 0;
static uint32_t led_green_laston = 0;
static uint32_t led_blue_lastoff = 0;
static uint32_t led_green_lastoff = 0;
#else
static uint32_t led_rx_laston = 0;
static uint32_t led_tx_laston = 0;
static uint32_t led_rx_lastoff = 0;
static uint32_t led_tx_lastoff = 0;
#endif

// Initialize LED GPIOs
void led_init()
{
    __HAL_RCC_GPIOB_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitStruct;
#ifdef CANABLE_HW
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1;
#else
    GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_10 | GPIO_PIN_11;
#endif
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
    GPIO_InitStruct.Alternate = 0;

    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

#ifdef CANABLE_HW
    HAL_GPIO_WritePin(LED_GREEN, 1);
#endif
}


#ifdef CANABLE_HW

// Turn green LED on
void led_green_on(void)
{
	// Make sure the LED has been off for at least LED_DURATION before turning on again
	// This prevents a solid status LED on a busy canbus
	if(led_green_laston == 0 && HAL_GetTick() - led_green_lastoff > LED_DURATION)
	{
        // Invert LED
		HAL_GPIO_WritePin(LED_GREEN, 0);
		led_green_laston = HAL_GetTick();
	}
}


// Turn green LED on
void led_green_off(void)
{
	HAL_GPIO_WritePin(LED_GREEN, 0);
}


// Blink blue LED (blocking)
void led_blue_blink(uint8_t numblinks)
{
	uint8_t i;
	for(i=0; i<numblinks; i++)
	{
		HAL_GPIO_WritePin(LED_BLUE, 1);
		HAL_Delay(100);
		HAL_GPIO_WritePin(LED_BLUE, 0);
		HAL_Delay(100);
	}
}


// Attempt to turn on status LED
void led_blue_on(void)
{
	// Make sure the LED has been off for at least LED_DURATION before turning on again
	// This prevents a solid status LED on a busy canbus
	if(led_blue_laston == 0 && HAL_GetTick() - led_blue_lastoff > LED_DURATION)
	{
		HAL_GPIO_WritePin(LED_BLUE, 1);
		led_blue_laston = HAL_GetTick();
	}
}

// Process time-based LED events
void led_process(void)
{
	// If LED has been on for long enough, turn it off
	if(led_blue_laston > 0 && HAL_GetTick() - led_blue_laston > LED_DURATION)
	{
		HAL_GPIO_WritePin(LED_TX, 0);
		led_blue_laston = 0;
		led_blue_lastoff = HAL_GetTick();
	}

	// If LED has been on for long enough, turn it off
	if(led_green_laston > 0 && HAL_GetTick() - led_green_laston > LED_DURATION)
	{
        // Invert LED
		HAL_GPIO_WritePin(LED_RX, 1);
		led_green_laston = 0;
		led_green_lastoff = HAL_GetTick();
	}
}
#else

// Turn rx LED on
void led_rx_on(void)
{
	// Make sure the LED has been off for at least LED_DURATION before turning on again
	// This prevents a solid status LED on a busy canbus
	if(led_rx_laston == 0 && HAL_GetTick() - led_rx_lastoff > LED_DURATION)
	{
        // Invert LED
		HAL_GPIO_WritePin(LED_RX, 1);
		led_rx_laston = HAL_GetTick();
	}
}


// Turn rx LED on
void led_rx_off(void)
{
	HAL_GPIO_WritePin(LED_RX, 0);
}

// Turn rx LED on
void led_tx_on(void)
{
	// Make sure the LED has been off for at least LED_DURATION before turning on again
	// This prevents a solid status LED on a busy canbus
	if(led_tx_laston == 0 && HAL_GetTick() - led_tx_lastoff > LED_DURATION)
	{
        // Invert LED
		HAL_GPIO_WritePin(LED_TX, 1);
		led_tx_laston = HAL_GetTick();
	}
}


// Turn green LED on
void led_tx_off(void)
{
	HAL_GPIO_WritePin(LED_TX, 0);
}


// Blink link LED (blocking)
void led_link_blink(uint8_t numblinks)
{
	uint8_t i;
	for(i=0; i<numblinks; i++)
	{
		HAL_GPIO_WritePin(LED_LINK, 1);
		HAL_Delay(100);
		HAL_GPIO_WritePin(LED_LINK, 0);
		HAL_Delay(100);
	}
}

// Turn link LED on
void led_link_off(void)
{
	HAL_GPIO_WritePin(LED_LINK, 0);
}

// Turn link LED on
void led_link_on(void)
{
	HAL_GPIO_WritePin(LED_LINK, 1);
}


// Process time-based LED events
void led_process(void)
{
	// If LED has been on for long enough, turn it off
	if(led_tx_laston > 0 && HAL_GetTick() - led_tx_laston > LED_DURATION)
	{
		HAL_GPIO_WritePin(LED_TX, 0);
		led_tx_laston = 0;
		led_tx_lastoff = HAL_GetTick();
	}

	// If LED has been on for long enough, turn it off
	if(led_rx_laston > 0 && HAL_GetTick() - led_rx_laston > LED_DURATION)
	{
        // Invert LED
		HAL_GPIO_WritePin(LED_RX, 0);
		led_rx_laston = 0;
		led_rx_lastoff = HAL_GetTick();
	}
}
#endif



