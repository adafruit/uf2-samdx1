#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

#define VENDOR_NAME "Flirc"
#define PRODUCT_NAME "Jeff Probe"
#define VOLUME_LABEL "JEFF_BOOT"
#define INDEX_URL "https://flirc.tv/products/flirc-jeffprobe"
#define BOARD_ID "SAMD21E17A-Jeff_Probe"

#define USB_VID 0x1d50
#define USB_PID 0x6017

#define LED_PIN PIN_PA10

#define BOOT_LOAD_PIN PIN_PA27

// This is needed because SAMD21E17A only has 128kB of flash
#define FLASH_NUM_ROWS 512

#endif
