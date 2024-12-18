#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

#define VENDOR_NAME "Szymon Klause"
#define PRODUCT_NAME "UARTLogger II"
#define VOLUME_LABEL "UARTLOGBOOT"
#define INDEX_URL "https://github.com/NightSkySK"
#define BOARD_ID "SAMD51J19A-UARTLogger-II-v1"

#define USB_VID 0x239A
#define USB_PID 0x0095

#define LED_PIN PIN_PA16
#define LED_TX_PIN PIN_PB07
#define LED_RX_PIN PIN_PB06

#define BOARD_NEOPIXEL_PIN PIN_PB22
#define BOARD_NEOPIXEL_COUNT 1

#define BOOT_USART_MODULE                 SERCOM3
#define BOOT_USART_MASK                   APBBMASK
#define BOOT_USART_BUS_CLOCK_INDEX        MCLK_APBBMASK_SERCOM3
#define BOOT_USART_PAD_SETTINGS           UART_RX_PAD1_TX_PAD0
#define BOOT_USART_PAD3                   PINMUX_UNUSED
#define BOOT_USART_PAD2                   PINMUX_UNUSED
#define BOOT_USART_PAD1                   PINMUX_PA22C_SERCOM3_PAD0
#define BOOT_USART_PAD0                   PINMUX_PA23C_SERCOM3_PAD1
#define BOOT_GCLK_ID_CORE                 SERCOM3_GCLK_ID_CORE
#define BOOT_GCLK_ID_SLOW                 SERCOM3_GCLK_ID_SLOW

#endif
