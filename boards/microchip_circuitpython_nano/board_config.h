#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

#define VENDOR_NAME "Microchip"
#define PRODUCT_NAME "CircuitPython Nano"
#define VOLUME_LABEL "CPYNANOBOOT"
#define INDEX_URL "https://microchip.com"
#define BOARD_ID "SAMD51J20A-CPyNano-v0"

#define USB_VID 0x04D8
#define USB_PID 0xE52B

#define LED_PIN PIN_PB23
#define BOARD_NEOPIXEL_PIN PIN_PB22
#define BOARD_NEOPIXEL_COUNT 1

#define BOOT_USART_MODULE                 SERCOM5
#define BOOT_USART_MASK                   APBDMASK
#define BOOT_USART_BUS_CLOCK_INDEX        MCLK_APBDMASK_SERCOM5
#define BOOT_USART_PAD_SETTINGS           UART_RX_PAD1_TX_PAD0
#define BOOT_USART_PAD3                   PINMUX_UNUSED
#define BOOT_USART_PAD2                   PINMUX_UNUSED
#define BOOT_USART_PAD1                   PINMUX_PB02D_SERCOM5_PAD0
#define BOOT_USART_PAD0                   PINMUX_PB03D_SERCOM5_PAD1
#define BOOT_GCLK_ID_CORE                 SERCOM5_GCLK_ID_CORE
#define BOOT_GCLK_ID_SLOW                 SERCOM5_GCLK_ID_SLOW

#endif
