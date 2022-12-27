#ifndef _LED_H
#define _LED_H

#ifdef CANABLE_HW
#define LED_BLUE_Pin GPIO_PIN_1
#define LED_BLUE_Port GPIOB
#define LED_BLUE LED_BLUE_Port , LED_BLUE_Pin

#define LED_GREEN_Pin GPIO_PIN_0
#define LED_GREEN_Port GPIOB
#define LED_GREEN LED_GREEN_Port , LED_GREEN_Pin
#else

#define LED_LINK_Pin GPIO_PIN_11
#define LED_LINK_Port GPIOB
#define LED_LINK LED_LINK_Port , LED_LINK_Pin

#define LED_RX_Pin GPIO_PIN_10
#define LED_RX_Port GPIOB
#define LED_RX LED_RX_Port , LED_RX_Pin

#define LED_TX_Pin GPIO_PIN_2
#define LED_TX_Port GPIOB
#define LED_TX LED_TX_Port , LED_TX_Pin

#endif

#define LED_DURATION 25 

void led_init();
#ifdef CANABLE_HW
void led_blue_blink(uint8_t numblinks);
void led_green_on(void);
void led_green_off(void);
void led_blue_on(void);
#else
void led_link_blink(uint8_t numblinks);
void led_link_on(void);
void led_link_off(void);
void led_rx_on(void);
void led_tx_on(void);
#endif
void led_process(void);

#endif
