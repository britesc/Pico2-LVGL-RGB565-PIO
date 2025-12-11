#include "lvgl_drv.h"
#include <Arduino.h>

// ------------------------
// Waveshare 3.5" parameters
// ------------------------
#define LCD_WIDTH   480
#define LCD_HEIGHT  320

// Framebuffer (1 frame = ~300 KB)
static lv_color16_t *fb = nullptr;

static void disp_flush(lv_display_t *disp,
                       const lv_area_t *area,
                       uint8_t *px_map)
{
    // DMA transfer to RGB bus will go here
    // For now just pretend we did it
    lv_display_flush_ready(disp);
}

lv_display_t* lvgl_driver_init() {

    Serial.println("Allocating framebuffer...");
    fb = (lv_color16_t*) malloc(LCD_WIDTH * LCD_HEIGHT * sizeof(lv_color16_t));

    if (!fb) {
        Serial.println("Framebuffer alloc FAILED");
        return nullptr;
    }

    // Create LVGL display object
    lv_display_t *disp = lv_display_create(LCD_WIDTH, LCD_HEIGHT);

    // Register the flush callback
    lv_display_set_flush_cb(disp, disp_flush);

    // Set the framebuffer
    lv_display_set_buffers(
        disp,
        fb,
        nullptr,
        LCD_WIDTH * LCD_HEIGHT * sizeof(lv_color16_t),
        LV_DISPLAY_RENDER_MODE_DIRECT
    );

    Serial.println("Display driver scaffold ready.");
    return disp;
}
