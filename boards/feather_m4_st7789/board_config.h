#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

#define VENDOR_NAME "Adafruit Industries"
#define PRODUCT_NAME "Feather M4 ST7789"
#define VOLUME_LABEL "FEATHERBOOT"
#define INDEX_URL "http://adafru.it/3857"
#define BOARD_ID "SAMD51J19A-FeatherM4-ST7789"
#define VENDOR_NAME "Dalcorp Solutions Inc."
#define PRODUCT_NAME "Breadboard Power Supply ST7789"
#define VOLUME_LABEL "DSIPST7789"
#define INDEX_URL "http://dalcorpsolutions.com/products/breadboard-power-supply-st7789"
#define BOARD_ID "SAMD51J19A-ST7789"

#define USB_VID 0x239A
#define USB_PID 0x0022

#define LED_PIN PIN_PA23

#define BOARD_NEOPIXEL_PIN PIN_PB03
#define BOARD_NEOPIXEL_COUNT 1

#define BOOT_USART_MODULE                 SERCOM0
#define BOOT_USART_MASK                   APBAMASK
#define BOOT_USART_BUS_CLOCK_INDEX        MCLK_APBAMASK_SERCOM0
#define BOOT_USART_PAD_SETTINGS           UART_RX_PAD3_TX_PAD0
#define BOOT_USART_PAD3                   PINMUX_PA07D_SERCOM0_PAD3
#define BOOT_USART_PAD2                   PINMUX_UNUSED
#define BOOT_USART_PAD1                   PINMUX_UNUSED
#define BOOT_USART_PAD0                   PINMUX_PA04D_SERCOM0_PAD0
#define BOOT_GCLK_ID_CORE                 SERCOM0_GCLK_ID_CORE
#define BOOT_GCLK_ID_SLOW                 SERCOM0_GCLK_ID_SLOW

// Enable display support
#define HAS_CONFIG_DATA 1
#define BOARD_SCREEN 1

// Configuration data for the display
#ifdef DEFINE_CONFIG_DATA
const uint32_t config_data[] = {
    /* CF2 START */
    513675505, 539130489, // magic
    50, 100,  // used entries, total entries
    
    // Basic pin definitions
    4, 0x6, // PIN_BTN_A = PA06 (A5)
    5, 0x5, // PIN_BTN_B = PA05 (A1)
    13, 0x17, // PIN_LED = PA23 (D13)
    18, 0x15, // PIN_MISO = PA21 (MISO)
    19, 0x18, // PIN_MOSI = PA24 (MOSI) 
    20, 0x23, // PIN_NEOPIXEL = PB03
    21, 0x1, // PIN_RX = PA01 (A0)
    23, 0x19, // PIN_SCK = PA25 (SCK)
    24, 0xd, // PIN_SCL = PA13 (SCL)
    25, 0xc, // PIN_SDA = PA12 (SDA)
    28, 0x0, // PIN_TX = PA00 (not exposed on Feather M4)
    
    // Display pins for ST7789V
    32, 0x11, // PIN_DISPLAY_SCK = PA17 - CLK pin
    34, 0x37, // PIN_DISPLAY_MOSI = PB23 - DIN pin
    35, 0x10, // PIN_DISPLAY_CS = PA16 - CS pin
    36, 0x14, // PIN_DISPLAY_DC = PA20 - DC pin (Data/Command)
    43, 0x13, // PIN_DISPLAY_RST = PA19 - RST pin
    59, 0x12, // PIN_DISPLAY_BL = PA18 - BL pin (backlight)
    
    // Display parameters
    37, 240, // DISPLAY_WIDTH = 240
    38, 320, // DISPLAY_HEIGHT = 320
    39, 0x80, // DISPLAY_CFG0 = 0x80 (ST7789V specific config)
    40, 0x00, // DISPLAY_CFG1 = 0x00
    41, 0x00, // DISPLAY_CFG2 = 0x00
    
    // Display type - ST7789
    87, 0x7789, // DISPLAY_TYPE = ST7789
    
    204, 0x80000, // FLASH_BYTES = 512K
    205, 0x30000, // RAM_BYTES = 192K
    208, 0x55114460, // BOOTLOADER_BOARD_ID
    209, 0x55114460, // UF2_BOARD_ID
    210, 0x20, // UF2_NUM_BLOCKS = 32
    211, 0x08000000, // FLASH_RESERVED_START_ADDRESS
    212, 0x2000, // FLASH_RESERVED_END_ADDRESS
    
    0, 0, 0, 0 // Terminator
    /* CF2 END */
};
#endif

#endif // BOARD_CONFIG_H