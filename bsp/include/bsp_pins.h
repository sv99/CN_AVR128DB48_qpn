/*
 * bsp_pins.h
 *
 * Created: 11.08.2021 13:47:34
 *  Author: user
 */

#ifndef BSP_PINS_H_
#define BSP_PINS_H_

#define Q_TIMER         TCA0
#define Q_TIMER_vect    TCA0_OVF_vect
#define TIMER_PRESCALER 1U
#define TIMER_PERIOD    ((float)F_CPU / TIMER_PRESCALER / BSP_TICKS_PER_SEC) - 1U

#define TCB0_TOP_VALUE 0xFFFF

#define LOGGER            USART3
#define LOGGER_RXC_vect   USART3_RXC_vect
#define LOGGER_DRE_vect   USART3_DRE_vect
#define LOGGER_TXD_PORT   PORTB
#define LOGGER_TXD_VPORT  VPORTB
#define LOGGER_TXD_CTRL   PORTB.PIN0CTRL
#define LOGGER_TXD_PIN_bm PIN0_bm
#define LOGGER_RXD_PORT   PORTB
#define LOGGER_RXD_VPORT  VPORTB
#define LOGGER_RXD_CTRL   PORTB.PIN1CTRL
#define LOGGER_RXD_PIN_bm PIN1_bm

#define LED_PORT   PORTB
#define LED_VPORT  VPORTB
#define LED_CTRL   PORTB.PIN3CTRL
#define LED_PIN_bm PIN3_bm

#define BUTTON_PORT   PORTB
#define BUTTON_VPORT  VPORTB
#define BUTTON_CTRL   PORTB.PIN2CTRL
#define BUTTON_PIN_bm PIN2_bm

#endif /* BSP_PINS_H_ */
