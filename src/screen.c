#include "uf2.h"

#ifdef BOARD_SCREEN

// Dispatch to the appropriate screen driver based on compile-time flags

#ifdef USE_SCREEN_ST7789
// Forward declarations for ST7789 driver
void st7789_early_init(void);
void st7789_init_display(void);
void st7789_draw_drag(void);
void st7789_show_usb_status(bool connected);
void st7789_update(void);
void st7789_draw_screen(void);
void st7789_draw_hf2(void);

void screen_early_init(void) { st7789_early_init(); }
void screen_init(void) { st7789_init_display(); draw_drag(); }
void draw_drag(void) { st7789_draw_drag(); }
void screen_update(void) { st7789_update(); }
void screen_show_usb_status(bool connected) { st7789_show_usb_status(connected); }
void draw_screen(void) { st7789_draw_screen(); }
void draw_hf2(void) { st7789_draw_hf2(); }

#else
// Default to ST7735 driver (original screen.c code)
// Forward declarations for ST7735 driver
void st7735_early_init(void);
void st7735_init(void);
void st7735_draw_drag(void);
void st7735_draw_screen(void);
void st7735_draw_hf2(void);

void screen_early_init(void) { st7735_early_init(); }
void screen_init(void) { st7735_init(); }
void draw_drag(void) { st7735_draw_drag(); }
void screen_update(void) { /* ST7735 doesn't use this */ }
void screen_show_usb_status(bool connected) { (void)connected; /* ST7735 doesn't use this */ }
void draw_screen(void) { st7735_draw_screen(); }
void draw_hf2(void) { st7735_draw_hf2(); }

#endif

#endif // BOARD_SCREEN