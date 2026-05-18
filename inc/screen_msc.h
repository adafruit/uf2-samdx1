#ifndef SCREEN_MSC_H
#define SCREEN_MSC_H

#include <stdint.h>

#ifdef BOARD_SCREEN

void screen_msc_reset(void);
void screen_msc_write_start(uint32_t num_blocks);
void screen_msc_write_block(uint32_t block_num);
void screen_msc_write_complete(void);
void screen_msc_set_block_data(uint8_t* data);
#else
// Empty inline functions for boards without screens
static inline void screen_msc_reset(void) {}
static inline void screen_msc_write_start(uint32_t num_blocks) { (void)num_blocks; }
static inline void screen_msc_write_block(uint32_t block_num) { (void)block_num; }
static inline void screen_msc_write_complete(void) {}
static inline void screen_msc_set_block_data(uint8_t* data) { (void)data; }
#endif

#endif // SCREEN_MSC_H