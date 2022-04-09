#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_system.h"
#include "esp_log.h"
#include "lvgl.h"
#include "demos/lv_demos.h"
#include "lvgl_helpers.h"
#include "gui_guider.h"
#include "app_list.h"

static const char *TAG = "APP_LVGL";

#define LV_TICK_PERIOD_MS 1
typedef enum
{
    SCR_WELCOME,
    SCR_MODE_SELECT,
    SCR_WIFI,
    SCR_PROG,
    SCR_POWER_METER
} scr_t;

lv_ui guider_ui;
scr_t current_screen;

static lv_disp_drv_t disp_drv;
static SemaphoreHandle_t xGuiSemaphore;

static void lv_tick_task(void *arg);
static void scr_welcome_key_event_handler(key_event_t event);
static void scr_mode_select_key_event_handler(key_event_t event);
static void scr_power_meter_key_event_handler(key_event_t event);

esp_err_t dev_lvgl_init(void)
{
    xGuiSemaphore = xSemaphoreCreateMutex();

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

    ESP_LOGI(TAG, "lvgl init is done.");

    setup_scr_scrWelcome(&guider_ui);
    setup_scr_scrModeSelect(&guider_ui);
    setup_scr_scrWifi(&guider_ui);
    setup_scr_scrProg(&guider_ui);
    setup_scr_scrPowerMeter(&guider_ui);
    lv_scr_load(guider_ui.scrWelcome);
    current_screen = SCR_WELCOME;

    return ESP_OK;
}

void app_lvgl(void *vParam)
{
    while (true)
    {
        if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY))
        {
            lv_task_handler();
            xSemaphoreGive(xGuiSemaphore);
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }

    vTaskDelete(NULL);
}

static void lv_tick_task(void *arg)
{
    lv_tick_inc(LV_TICK_PERIOD_MS);
}

void ui_power_meter_update(float vol, float cur, float pwr)
{
    static char str_vol[16], str_cur[16], str_pwr[16];

    if (vol >= 9.99995)
    {
        sprintf(str_vol, "%2.3f", vol);
    }
    else
    {
        sprintf(str_vol, "%1.4f", vol);
    }
    if (cur < 0)
    {
        cur = 0 - cur;
    }
    sprintf(str_cur, "%1.4f", cur);
    if (pwr >= 99.9995)
    {
        sprintf(str_pwr, "%3.2f", pwr);
    }
    else if (pwr >= 9.99995)
    {
        sprintf(str_pwr, "%2.3f", pwr);
    }
    else
    {
        sprintf(str_pwr, "%1.4f", pwr);
    }
    if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY))
    {
        lv_label_set_text(guider_ui.scrPowerMeter_labelVolVal, str_vol);
        lv_label_set_text(guider_ui.scrPowerMeter_labelCurVal, str_cur);
        lv_label_set_text(guider_ui.scrPowerMeter_labelPwrVal, str_pwr);
        xSemaphoreGive(xGuiSemaphore);
    }
}

void app_key_event_handler(void *vParam)
{
    key_event_t event;
    while (true)
    {
        if (KEY_NO_EVENT == key_event)
        {
            vTaskDelay(pdMS_TO_TICKS(50));
        }
        else
        {
            event = key_event;
            key_event = KEY_NO_EVENT;
            switch (current_screen)
            {
            case SCR_WELCOME:
                scr_welcome_key_event_handler(event);
                break;
            case SCR_MODE_SELECT:
                scr_mode_select_key_event_handler(event);
                break;
            case SCR_POWER_METER:
                scr_power_meter_key_event_handler(event);
                break;
            case SCR_PROG:
            default:
                break;
            }
        }
    }

    vTaskDelete(NULL);
}

static void scr_welcome_key_event_handler(key_event_t event)
{
    if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY))
    {
        lv_scr_load(guider_ui.scrModeSelect);
        xSemaphoreGive(xGuiSemaphore);
    }
    current_screen = SCR_MODE_SELECT;
}

static void scr_mode_select_key_event_handler(key_event_t event)
{
    if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY))
    {
        lv_scr_load(guider_ui.scrPowerMeter);
        xSemaphoreGive(xGuiSemaphore);
    }
    current_screen = SCR_POWER_METER;
    ESP_ERROR_CHECK(start_ina226_service());
}

static void scr_power_meter_key_event_handler(key_event_t event)
{
    if (KEY_BACK_EVENT == event)
    {
        ESP_ERROR_CHECK(terminate_ina226_service());
        if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY))
        {
            lv_scr_load(guider_ui.scrModeSelect);
            xSemaphoreGive(xGuiSemaphore);
        }
        current_screen = SCR_MODE_SELECT;
    }
}
