#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

#define VENDOR_NAME "Rabid Prototypes"
#define PRODUCT_NAME "Tau"
#define VOLUME_LABEL "TAU_BOOT"
#define INDEX_URL "https://rabidprototypes.com/product/tau"
#define BOARD_ID "SAMD21E17A-Tau-v0"

#define USB_VID 0x230a
#define USB_PID 0x00E9

#define LED_PIN PIN_PA27

// This is needed because SAMD21E17A only has 128kB of flash
#define FLASH_NUM_ROWS 512

#endif
