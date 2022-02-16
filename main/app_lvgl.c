#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "lvgl.h"
#include "demos/lv_demos.h"
#include "lvgl_helpers.h"

#define LV_TICK_PERIOD_MS 1

static lv_disp_drv_t disp_drv;

static void lv_tick_task(void *arg);

void app_lvgl_benchmark(void *vParam)
{
    lv_init();

    lv_disp_drv_init(&disp_drv);
    disp_drv.flush_cb = disp_driver_flush;
    // disp_drv.drv_update_cb = st7789_update_cb;
    // disp_drv.rotated = LV_DISP_ROT_NONE;

    /* Initialize SPI or I2C bus used by the drivers */
    lvgl_interface_init();
    lvgl_display_gpios_init();

    /* Removed from lvgl_driver_init, that function is meant to initialize all
     * the needed peripherals */
    st7789_init(&disp_drv);

    size_t display_buffer_size = lvgl_get_display_buffer_size();
    lv_color_t *buf1 = heap_caps_malloc(display_buffer_size * sizeof(lv_color_t), MALLOC_CAP_DMA);
    assert(buf1 != NULL);

    /* Use double buffered when not working with monochrome displays */
    lv_color_t *buf2 = heap_caps_malloc(display_buffer_size * sizeof(lv_color_t), MALLOC_CAP_DMA);
    assert(buf2 != NULL);

    static lv_disp_draw_buf_t disp_buf;

    uint32_t size_in_px = display_buffer_size;

    /* Initialize the working buffer depending on the selected display.
     * NOTE: buf2 == NULL when using monochrome displays. */
    lv_disp_draw_buf_init(&disp_buf, buf1, buf2, size_in_px);

    disp_drv.draw_buf = &disp_buf;

    lv_disp_drv_register(&disp_drv);

    /* Create and start a periodic timer interrupt to call lv_tick_inc */
    const esp_timer_create_args_t periodic_timer_args = {
        .callback = &lv_tick_task,
        .name = "lv_tick-task"};
    esp_timer_handle_t periodic_timer;
    ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, LV_TICK_PERIOD_MS * 1000));

    /* Create the demo application */
    lv_demo_benchmark();

    while (true)
    {
        lv_task_handler();

        vTaskDelay(pdMS_TO_TICKS(10));
    }
    free(buf1);
    free(buf2);

    vTaskDelete(NULL);
}

static void lv_tick_task(void *arg)
{
    lv_tick_inc(LV_TICK_PERIOD_MS);
}