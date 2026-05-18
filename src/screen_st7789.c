#include "uf2.h"
#include "sam.h"

#ifdef BOARD_SCREEN

#include <string.h>
#include "board_config.h"

static const uint8_t font5x7[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, // (space)
    0x00, 0x00, 0x5F, 0x00, 0x00, // !
    0x00, 0x07, 0x00, 0x07, 0x00, // "
    0x14, 0x7F, 0x14, 0x7F, 0x14, // #
    0x24, 0x2A, 0x7F, 0x2A, 0x12, // $
    0x23, 0x13, 0x08, 0x64, 0x62, // %
    0x36, 0x49, 0x55, 0x22, 0x50, // &
    0x00, 0x05, 0x03, 0x00, 0x00, // '
    0x00, 0x1C, 0x22, 0x41, 0x00, // (
    0x00, 0x41, 0x22, 0x1C, 0x00, // )
    0x08, 0x2A, 0x1C, 0x2A, 0x08, // *
    0x08, 0x08, 0x3E, 0x08, 0x08, // +
    0x00, 0x50, 0x30, 0x00, 0x00, // ,
    0x08, 0x08, 0x08, 0x08, 0x08, // -
    0x00, 0x60, 0x60, 0x00, 0x00, // .
    0x20, 0x10, 0x08, 0x04, 0x02, // /
    0x3E, 0x51, 0x49, 0x45, 0x3E, // 0
    0x00, 0x42, 0x7F, 0x40, 0x00, // 1
    0x42, 0x61, 0x51, 0x49, 0x46, // 2
    0x21, 0x41, 0x45, 0x4B, 0x31, // 3
    0x18, 0x14, 0x12, 0x7F, 0x10, // 4
    0x27, 0x45, 0x45, 0x45, 0x39, // 5
    0x3C, 0x4A, 0x49, 0x49, 0x30, // 6
    0x01, 0x71, 0x09, 0x05, 0x03, // 7
    0x36, 0x49, 0x49, 0x49, 0x36, // 8
    0x06, 0x49, 0x49, 0x29, 0x1E, // 9
    0x00, 0x36, 0x36, 0x00, 0x00, // :
    0x00, 0x56, 0x36, 0x00, 0x00, // ;
    0x00, 0x08, 0x14, 0x22, 0x41, // <
    0x14, 0x14, 0x14, 0x14, 0x14, // =
    0x41, 0x22, 0x14, 0x08, 0x00, // >
    0x02, 0x01, 0x51, 0x09, 0x06, // ?
    0x32, 0x49, 0x79, 0x41, 0x3E, // @
    0x7E, 0x11, 0x11, 0x11, 0x7E, // A
    0x7F, 0x49, 0x49, 0x49, 0x36, // B
    0x3E, 0x41, 0x41, 0x41, 0x22, // C
    0x7F, 0x41, 0x41, 0x22, 0x1C, // D
    0x7F, 0x49, 0x49, 0x49, 0x41, // E
    0x7F, 0x09, 0x09, 0x01, 0x01, // F
    0x3E, 0x41, 0x41, 0x51, 0x32, // G
    0x7F, 0x08, 0x08, 0x08, 0x7F, // H
    0x00, 0x41, 0x7F, 0x41, 0x00, // I
    0x20, 0x40, 0x41, 0x3F, 0x01, // J
    0x7F, 0x08, 0x14, 0x22, 0x41, // K
    0x7F, 0x40, 0x40, 0x40, 0x40, // L
    0x7F, 0x02, 0x04, 0x02, 0x7F, // M
    0x7F, 0x04, 0x08, 0x10, 0x7F, // N
    0x3E, 0x41, 0x41, 0x41, 0x3E, // O
    0x7F, 0x09, 0x09, 0x09, 0x06, // P
    0x3E, 0x41, 0x51, 0x21, 0x5E, // Q
    0x7F, 0x09, 0x19, 0x29, 0x46, // R
    0x46, 0x49, 0x49, 0x49, 0x31, // S
    0x01, 0x01, 0x7F, 0x01, 0x01, // T
    0x3F, 0x40, 0x40, 0x40, 0x3F, // U
    0x1F, 0x20, 0x40, 0x20, 0x1F, // V
    0x7F, 0x20, 0x18, 0x20, 0x7F, // W
    0x63, 0x14, 0x08, 0x14, 0x63, // X
    0x03, 0x04, 0x78, 0x04, 0x03, // Y
    0x61, 0x51, 0x49, 0x45, 0x43, // Z
};

// ST7789V Command definitions
#define ST7789_NOP        0x00
#define ST7789_SWRESET    0x01
#define ST7789_SLPIN      0x10
#define ST7789_SLPOUT     0x11
#define ST7789_PTLON      0x12
#define ST7789_NORON      0x13
#define ST7789_INVOFF     0x20
#define ST7789_INVON      0x21
#define ST7789_DISPOFF    0x28
#define ST7789_DISPON     0x29
#define ST7789_CASET      0x2A
#define ST7789_RASET      0x2B
#define ST7789_RAMWR      0x2C
#define ST7789_RAMRD      0x2E
#define ST7789_MADCTL     0x36
#define ST7789_COLMOD     0x3A
#define ST7789_PORCTRL    0xB2
#define ST7789_GCTRL      0xB7
#define ST7789_VCOMS      0xBB
#define ST7789_LCMCTRL    0xC0
#define ST7789_VDVVRHEN   0xC2
#define ST7789_VRHS       0xC3
#define ST7789_VDVSET     0xC4
#define ST7789_FRCTR2     0xC6
#define ST7789_PWCTRL1    0xD0
#define ST7789_PVGAMCTRL  0xE0
#define ST7789_NVGAMCTRL  0xE1


#define ST7789_MADCTL_MY  0x80
#define ST7789_MADCTL_MX  0x40
#define ST7789_MADCTL_MV  0x20
#define ST7789_MADCTL_ML  0x10
#define ST7789_MADCTL_RGB 0x00
#define ST7789_MADCTL_BGR 0x08

// Color definitions
#define COLOR_BLACK   0x0000
#define COLOR_WHITE   0xFFFF
#define COLOR_RED     0xF800
#define COLOR_GREEN   0x07E0
#define COLOR_BLUE    0x001F
#define COLOR_YELLOW  0xFFE0
#define COLOR_CYAN    0x07FF
#define COLOR_MAGENTA 0xF81F
#define COLOR_ORANGE  0xFC00

// Pin definitions
static uint8_t pin_sck;
static uint8_t pin_mosi;
static uint8_t pin_cs;
static uint8_t pin_dc;
static uint8_t pin_rst;
static uint8_t pin_bl;

// Display dimensions
static const uint16_t screen_width = 240;
static const uint16_t screen_height = 320;

// Software SPI write
static void spi_write(uint8_t data) {
    for (int i = 7; i >= 0; i--) {
        PINOP(pin_sck, OUTCLR);
        
        if (data & (1 << i)) {
            PINOP(pin_mosi, OUTSET);
        } else {
            PINOP(pin_mosi, OUTCLR);
        }
        
        PINOP(pin_sck, OUTSET);
    }
}

static void write_cmd(uint8_t cmd) {
    PINOP(pin_dc, OUTCLR);  
    PINOP(pin_cs, OUTCLR);  
    spi_write(cmd);
    PINOP(pin_cs, OUTSET);  
}

static void write_data(uint8_t data) {
    PINOP(pin_dc, OUTSET);  
    PINOP(pin_cs, OUTCLR);  
    spi_write(data);
    PINOP(pin_cs, OUTSET);  
}

static void write_data_16(uint16_t data) {
    write_data(data >> 8);
    write_data(data & 0xFF);
}

// ST7789V Initialization sequence
static void st7789_init(void) {
    // Hardware reset
    if (pin_rst != 0xFF) {
        PINOP(pin_rst, OUTCLR);
        delay(10);
        PINOP(pin_rst, OUTSET);
        delay(50);
    }
    
    // Software reset
    write_cmd(ST7789_SWRESET);
    delay(50);
    
    // Sleep out
    write_cmd(ST7789_SLPOUT);
    delay(10);
    
    // Interface pixel format
    write_cmd(ST7789_COLMOD);
    write_data(0x55);  // 16-bit color
    
    // Memory access control
    write_cmd(ST7789_MADCTL);
    write_data(0x00); 
    
    // Column address set
    write_cmd(ST7789_CASET);
    write_data_16(0);
    write_data_16(screen_width - 1);
    
    // Row address set
    write_cmd(ST7789_RASET);
    write_data_16(0);
    write_data_16(screen_height - 1);
    
    // Normal display on
    write_cmd(ST7789_NORON);
    write_cmd(ST7789_INVON);
    // Display on
    write_cmd(ST7789_DISPON);
    
    // Turn on backlight if available
    if (pin_bl != 0xFF) {
        PINOP(pin_bl, OUTSET);
    }
}

// Set drawing window
static void set_window(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
    write_cmd(ST7789_CASET);
    write_data_16(x0);
    write_data_16(x1);
    
    write_cmd(ST7789_RASET);
    write_data_16(y0);
    write_data_16(y1);
    
    write_cmd(ST7789_RAMWR);
}

// Fill rectangle with color
void screen_fill_rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color) {
    set_window(x, y, x + w - 1, y + h - 1);
    
    PINOP(pin_dc, OUTSET);
    PINOP(pin_cs, OUTCLR);
    
    uint8_t hi = color >> 8;
    uint8_t lo = color & 0xFF;
    
    for (uint32_t i = 0; i < w * h; i++) {
        spi_write(hi);  
        spi_write(lo);  
    }
    
    PINOP(pin_cs, OUTSET);
}

static void draw_char(uint16_t x, uint16_t y, char c, uint16_t color, uint16_t bg_color) {
    if (c < 32 || c > 90) {
        c = 32;
    }
    
    const uint8_t *char_data = &font5x7[(c - 32) * 5];
    
    // If background is black, only draw the set pixels
    if (bg_color == COLOR_BLACK) {
        for (int col = 0; col < 5; col++) {
            uint8_t column = char_data[col];
            for (int row = 0; row < 7; row++) {
                if (column & (1 << row)) {
                    
                    screen_fill_rect(x + col*2, y + row*2, 2, 2, color);
                }
            }
        }
    } else {
        // Draw full character with background
        for (int col = 0; col < 5; col++) {
            uint8_t column = char_data[col];
            for (int row = 0; row < 7; row++) {
                uint16_t pixel_color = (column & (1 << row)) ? color : bg_color;
                
                screen_fill_rect(x + col*2, y + row*2, 2, 2, pixel_color);
            }
        }
        
        screen_fill_rect(x + 10, y, 2, 14, bg_color);
    }
}

// Draw a string at specified position
static void draw_string(uint16_t x, uint16_t y, const char* str, uint16_t color, uint16_t bg_color) {
    while (*str) {
        draw_char(x, y, *str, color, bg_color);
        x += 12;  
        str++;
    }
}

// Draw centered string
static void draw_string_centered(uint16_t y, const char* str, uint16_t color, uint16_t bg_color) {
    
    uint16_t len = 0;
    const char* p = str;
    while (*p++) len++;
    
    
    uint16_t total_width = len * 12;
    uint16_t x = (screen_width - total_width) / 2;
    
    draw_string(x, y, str, color, bg_color);
}

// Progress bar
static void draw_progress_bar(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t percent) {
    // Draw border
    screen_fill_rect(x, y, w, h, COLOR_WHITE);
    screen_fill_rect(x+2, y+2, w-4, h-4, COLOR_BLACK);
    
    // Draw progress
    if (percent > 100) percent = 100;
    uint16_t fill_w = ((w - 6) * percent) / 100;
    if (fill_w > 0) {
        screen_fill_rect(x+3, y+3, fill_w, h-6, COLOR_GREEN);
    }
}

// Draw simple USB icon
static void draw_usb_icon(uint16_t x, uint16_t y, uint16_t color) {
    screen_fill_rect(x, y, 30, 15, color);
    screen_fill_rect(x+10, y-5, 10, 5, color);
}

// Draw simple folder icon
static void draw_folder_icon(uint16_t x, uint16_t y, uint16_t color) {
    // Folder body
    screen_fill_rect(x, y+10, 50, 30, color);
    // Folder tab
    screen_fill_rect(x, y, 20, 12, color);
}

// Show boot screen
void screen_show_boot(void) {
    // Clear screen
    screen_fill_rect(0, 0, screen_width, screen_height, COLOR_BLACK);
    
    // Draw header with text
    screen_fill_rect(0, 30, screen_width, 40, COLOR_BLUE);
    draw_string_centered(45, "UF2 BOOTLOADER", COLOR_WHITE, COLOR_BLUE);
    
    // Draw device name
    draw_string_centered(90, "FEATHER M4", COLOR_CYAN, COLOR_BLACK);
    
    // Draw status
    draw_string_centered(130, "INITIALIZING", COLOR_BLUE, COLOR_BLACK);
    
    // Progress bar
    screen_fill_rect(60, 160, 120, 10, COLOR_WHITE);
    screen_fill_rect(62, 162, 116, 6, COLOR_BLACK);
    screen_fill_rect(62, 162, 40, 6, COLOR_GREEN);
}

// Show USB enumeration status
void st7789_show_usb_status(bool connected) {
    // Clear status area
    screen_fill_rect(0, 120, screen_width, 80, COLOR_BLACK);
    
    if (connected) {
        draw_string_centered(130, "USB CONNECTED", COLOR_GREEN, COLOR_BLACK);
        draw_usb_icon(105, 155, COLOR_GREEN);
    } else {
        draw_string_centered(130, "WAITING FOR USB", COLOR_YELLOW, COLOR_BLACK);
    }
}

// Show main UF2 drag-drop screen
void screen_show_uf2_mode(void) {
    // Clear screen
    screen_fill_rect(0, 0, screen_width, screen_height, COLOR_BLACK);

    // Header 
    screen_fill_rect(0, 0, screen_width, 70, COLOR_BLUE);
    draw_string_centered(15, "UF2 BOOTLOADER", COLOR_WHITE, COLOR_BLUE);
    draw_string_centered(40, "VERSION 3.16.0", COLOR_WHITE, COLOR_BLUE);
    
    // Status 
    screen_fill_rect(60, 90, 120, 35, COLOR_GREEN);
    draw_string_centered(100, "READY", COLOR_BLACK, COLOR_GREEN);
    
    // Instructions 
    draw_string_centered(145, "DRAG UF2 FILE TO", COLOR_WHITE, COLOR_BLACK);
    draw_string_centered(170, "FEATHERBOOT DRIVE", COLOR_CYAN, COLOR_BLACK);
    
    // Draw folder icon
    draw_folder_icon(95, 210, COLOR_YELLOW);
    
    // Bottom text
    draw_string_centered(260, "DOUBLE TAP RESET", COLOR_WHITE, COLOR_BLACK);
    draw_string_centered(285, "TO ENTER BOOTLOADER", COLOR_WHITE, COLOR_BLACK);
    
    // Bottom status 
    screen_fill_rect(0, screen_height - 40, screen_width, 40, COLOR_GREEN);
    draw_string_centered(screen_height - 30, "DRIVE MOUNTED", COLOR_BLACK, COLOR_GREEN);
}

static bool upload_screen_initialized = false;
// Update screen_show_upload_progress function
void screen_show_upload_progress(uint32_t bytes_written, uint32_t total_bytes) {
    if (!upload_screen_initialized) {
        // First time - set up upload screen
        screen_fill_rect(0, 0, screen_width, screen_height, COLOR_BLACK);
        
        // Header
        screen_fill_rect(0, 0, screen_width, 50, COLOR_ORANGE);
        draw_string_centered(20, "UPLOADING FIRMWARE", COLOR_WHITE, COLOR_ORANGE);
        
        draw_string_centered(80, "PLEASE WAIT", COLOR_WHITE, COLOR_BLACK);
        upload_screen_initialized = true;
    }
    
    // Calculate percentage
    uint8_t percent = 0;
    if (total_bytes > 0) {
        percent = (bytes_written * 100) / total_bytes;
    }
    
    // Draw progress bar
    draw_progress_bar(20, 130, screen_width - 40, 30, percent);
    
    // Draw percentage text
    char percent_text[10];
    percent_text[0] = (percent / 100) + '0';
    percent_text[1] = ((percent / 10) % 10) + '0';
    percent_text[2] = (percent % 10) + '0';
    percent_text[3] = '%';
    percent_text[4] = '\0';
    
    screen_fill_rect(90, 170, 60, 20, COLOR_BLACK);
    draw_string_centered(175, percent_text, COLOR_WHITE, COLOR_BLACK);
    
    if (percent >= 100) {
        // Upload complete
        draw_string_centered(210, "COMPLETE!", COLOR_GREEN, COLOR_BLACK);
        draw_string_centered(230, "RESTARTING", COLOR_WHITE, COLOR_BLACK);
        delay(1000); // Show complete message
        upload_screen_initialized = false; // Reset for next upload
    }
}

// Add a function to reset screen state
void screen_reset_upload_state(void) {
    upload_screen_initialized = false;
}

// Early initialization (called from led_init)
void st7789_early_init(void) {
    // Empty for now - pins will be initialized in screen_init
}

// Initialize screen
void st7789_init_display(void) {
    pin_sck = PIN_PA17;
    pin_mosi = PIN_PB23;
    pin_cs = PIN_PA16;
    pin_dc = PIN_PA20;
    pin_rst = PIN_PA19;
    pin_bl = PIN_PA18;
    
    // Configure all pins as outputs
    PINOP(pin_sck, DIRSET);
    PINOP(pin_mosi, DIRSET);
    PINOP(pin_cs, DIRSET);
    PINOP(pin_dc, DIRSET);
    PINOP(pin_rst, DIRSET);
    PINOP(pin_bl, DIRSET);
    
    // Set initial states
    PINOP(pin_cs, OUTSET);   
    PINOP(pin_sck, OUTCLR);  
    PINOP(pin_dc, OUTSET);   
    
    delay(100);
    
    // Initialize display
    st7789_init();
    
    // Clear screen first
    screen_fill_rect(0, 0, screen_width, screen_height, COLOR_BLACK);
    delay(50);
    
    // Show boot screen
    screen_show_boot();
}

// Update function called periodically
void st7789_update(void) {

}

// Show drag-and-drop interface
void st7789_draw_drag(void) {
    screen_show_uf2_mode();
}

// Called when USB connects
void screen_on_usb_connect(void) {
    screen_show_usb_status(true);
    delay(500); 
    screen_show_uf2_mode();
}

// Driver interface functions for screen.c
void screen_driver_init(void) {
    st7789_init_display();
}

void screen_driver_clear(uint16_t color) {
    screen_fill_rect(0, 0, screen_width, screen_height, color);
}

// Main UF2 screen drawing function
void st7789_draw_uf2_screen(void) {
    screen_show_uf2_mode(); 
}

#endif // BOARD_SCREEN