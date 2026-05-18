#include "uf2.h"

#ifdef BOARD_SCREEN

extern void screen_show_upload_progress(uint32_t bytes_written, uint32_t total_bytes);

// State tracking
static bool upload_in_progress = false;
static bool uf2_detected = false;
static uint32_t total_blocks = 0;
static uint32_t current_block = 0;
static uint32_t uf2_blocks_written = 0;

// Buffer to check for UF2 magic
static uint8_t* last_block_data = NULL;

// Hook called when MSC reset occurs
void screen_msc_reset(void) {
    upload_in_progress = false;
    uf2_detected = false;
    current_block = 0;
    total_blocks = 0;
    uf2_blocks_written = 0;
    last_block_data = NULL;
    draw_drag(); 
}

// Hook called before a write operation
void screen_msc_write_start(uint32_t num_blocks) {
    total_blocks = num_blocks;
    current_block = 0;
    uf2_blocks_written = 0;
    
}

// New function to check if a block contains UF2 data
bool screen_msc_check_uf2_block(uint8_t* block_data) {
    if (!block_data) return false;
    
    // Store pointer to check the data
    last_block_data = block_data;
    
    // Check for UF2 magic numbers at the start of the block
    uint32_t magic0, magic1;
    memcpy(&magic0, block_data, 4);
    memcpy(&magic1, block_data + 4, 4);
    
    if (magic0 == UF2_MAGIC_START0 && magic1 == UF2_MAGIC_START1) {
        if (!uf2_detected) {
            uf2_detected = true;
            upload_in_progress = true;
            
            // Extract total number of UF2 blocks from the UF2 header
            // UF2 block structure has total blocks at offset 20
            uint32_t uf2_total_blocks;
            memcpy(&uf2_total_blocks, block_data + 20, 4);
            
            if (uf2_total_blocks > 0) {
                total_blocks = uf2_total_blocks;
            }
        }
        return true;
    }
    return false;
}

// Hook called after each block write
void screen_msc_write_block(uint32_t block_num) {
    current_block++;
    
    // Check if this was a UF2 block
    if (last_block_data && screen_msc_check_uf2_block(last_block_data)) {
        uf2_blocks_written++;
    }
    
    if (!upload_in_progress) {
        return;
    }
    
    // Update screen based on UF2 blocks written, not total blocks
    if ((uf2_blocks_written % 32) == 0 || current_block >= total_blocks) {
        uint32_t percent = (uf2_blocks_written * 100) / total_blocks;
        screen_show_upload_progress(percent, 100);
    }
}

// Hook called when write operation completes
void screen_msc_write_complete(void) {
    if (upload_in_progress) {
        upload_in_progress = false;
        uf2_detected = false;
        if (uf2_blocks_written > 0) {
            delay(1000); // Show complete message briefly only for actual UF2 uploads
        }
        draw_drag(); // Return to main screen
    }
    last_block_data = NULL;
}

// New function to set the block data pointer (called from msc.c)
void screen_msc_set_block_data(uint8_t* data) {
    last_block_data = data;
}

#else

// Empty implementations when screen is not enabled
void screen_msc_reset(void) {}
void screen_msc_write_start(uint32_t num_blocks) { (void)num_blocks; }
void screen_msc_write_block(uint32_t block_num) { (void)block_num; }
void screen_msc_write_complete(void) {}
void screen_msc_set_block_data(uint8_t* data) { (void)data; }

#endif // BOARD_SCREEN