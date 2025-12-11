#include <Arduino.h>
#include "lvgl.h"
#include "lvgl_drv.h"

static lv_display_t *display;

void setup() {
    Serial.begin(115200);
    delay(2000);
    Serial.println("Pico2 LVGL Scaffold Starting");

    lv_init();

    // Initialize our RGB565 display driver
    display = lvgl_driver_init();
    if (!display) {
        Serial.println("DISPLAY INIT FAILED!");
        while (1) delay(100);
    }

    Serial.println("DISPLAY INIT OK");

    // Create a simple LVGL widget
    lv_obj_t *label = lv_label_create(lv_screen_active());
    lv_label_set_text(label, "Hello Pico2 + LVGL!");
    lv_obj_center(label);
}

void loop() {
    lv_timer_handler();   // LVGL tick
    delay(5);
}
