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
    disp_drv.hor_res = 320;
    disp_drv.ver_res = 240;

    lvgl_interface_init(&disp_drv);
    lvgl_display_gpios_init();

    size_t display_buffer_size = lvgl_get_display_buffer_size(&disp_drv);
    lv_color_t *buf1 = heap_caps_malloc(display_buffer_size * sizeof(lv_color_t), MALLOC_CAP_DMA);
    lv_color_t *buf2 = heap_caps_malloc(display_buffer_size * sizeof(lv_color_t), MALLOC_CAP_DMA);

    static lv_disp_draw_buf_t disp_buf;
    lv_disp_draw_buf_init(&disp_buf, buf1, buf2, display_buffer_size);

    disp_drv.draw_buf = &disp_buf;
    disp_drv.flush_cb = disp_driver_flush;
    disp_drv.drv_update_cb = st7789_update_cb;
    lv_disp_drv_register(&disp_drv);
    disp_driver_init(&disp_drv);

    lv_disp_t *disp = lv_disp_get_default();
    lv_disp_set_rotation(disp, LV_DISP_ROT_90);

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