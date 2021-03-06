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

lv_ui guider_ui;
lv_key_t key_event = 0;

static lv_disp_drv_t disp_drv;
static SemaphoreHandle_t xGuiSemaphore;
static lv_indev_t *indev_key;
static lv_group_t *group_indev;

static void lv_tick_task(void *arg);
static void lv_custom_event_init(lv_ui *ui);
static void scrWelcome_event_cb(lv_event_t *e);
static void scrModeSelect_listMode_event_cb(lv_event_t *e);
static void scrPowerMeter_event_cb(lv_event_t *e);
static void scr_load_welcome(lv_ui *ui, lv_group_t *group, lv_scr_load_anim_t anim);
static void scr_load_mode_select(lv_ui *ui, lv_group_t *group, lv_scr_load_anim_t anim);
static void scr_load_power_meter(lv_ui *ui, lv_group_t *group, lv_scr_load_anim_t anim);
static void key_read_cb(lv_indev_drv_t *indev_drv, lv_indev_data_t *data);

esp_err_t dev_lvgl_init(void)
{
    // Create GUI mutex
    xGuiSemaphore = xSemaphoreCreateMutex();
    // Init LVGL
    lv_init();
    // Init LVGL display driver
    lv_disp_drv_init(&disp_drv);
    // Resolution is needed by calculation of display buffer
    disp_drv.hor_res = 320;
    disp_drv.ver_res = 240;
    // Init ESP DMA buffer & SPI & GPIO
    lvgl_interface_init(&disp_drv);
    lvgl_display_gpios_init();
    // Malloc two display buffers with DMA capability
    size_t display_buffer_size = lvgl_get_display_buffer_size(&disp_drv);
    lv_color_t *buf1 = heap_caps_malloc(display_buffer_size * sizeof(lv_color_t), MALLOC_CAP_DMA);
    lv_color_t *buf2 = heap_caps_malloc(display_buffer_size * sizeof(lv_color_t), MALLOC_CAP_DMA);
    assert(buf1 != NULL);
    assert(buf2 != NULL);
    // Init double diplay buffer mode
    static lv_disp_draw_buf_t disp_buf;
    lv_disp_draw_buf_init(&disp_buf, buf1, buf2, display_buffer_size);
    // Assign display buffer & flush callback & update callback (rotation)
    disp_drv.draw_buf = &disp_buf;
    disp_drv.flush_cb = disp_driver_flush;
    disp_drv.drv_update_cb = st7789_update_cb;
    // Regist LVGL display driver
    lv_disp_t *disp = lv_disp_drv_register(&disp_drv);
    // Rotate diplay to right direction
    lv_disp_set_rotation(disp, LV_DISP_ROT_90);
    // Init LCD controller
    disp_driver_init(&disp_drv);
    // Regist input device (keypad)
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_KEYPAD;
    indev_drv.read_cb = key_read_cb;
    indev_key = lv_indev_drv_register(&indev_drv);
    // Create input group
    group_indev = lv_group_create();
    lv_indev_set_group(indev_key, group_indev);
    // Create and start a periodic timer interrupt to call lv_tick_inc
    const esp_timer_create_args_t periodic_timer_args = {
        .callback = &lv_tick_task,
        .name = "lv_tick-task"};
    esp_timer_handle_t periodic_timer;
    ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, LV_TICK_PERIOD_MS * 1000));
    ESP_LOGI(TAG, "lvgl init is done.");
    // Init theme & screens
    lv_theme_default_init(NULL, lv_palette_main(LV_PALETTE_GREY), lv_palette_main(LV_PALETTE_BLUE_GREY), 1, LV_FONT_DEFAULT);
    setup_scr_scrWelcome(&guider_ui);
    setup_scr_scrModeSelect(&guider_ui);
    setup_scr_scrWifi(&guider_ui);
    setup_scr_scrProg(&guider_ui);
    setup_scr_scrPowerMeter(&guider_ui);
    // Add custom events
    lv_custom_event_init(&guider_ui);
    // Load welcome screen
    lv_scr_load(guider_ui.scrWelcome);
    // Add screen to input group
    lv_group_add_obj(group_indev, guider_ui.scrWelcome);

    return ESP_OK;
}

void app_lvgl(void *vParam)
{
    while (true)
    {
        // Try to take GUI mutex
        if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY))
        {
            lv_task_handler();
            // Give GUI mutex
            xSemaphoreGive(xGuiSemaphore);
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
    // Should never reach here
    free(disp_drv.draw_buf->buf1);
    free(disp_drv.draw_buf->buf2);
    vTaskDelete(NULL);
}

static void lv_tick_task(void *arg)
{
    lv_tick_inc(LV_TICK_PERIOD_MS);
}

static void lv_custom_event_init(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->scrWelcome, scrWelcome_event_cb, LV_EVENT_KEY, NULL);
    lv_obj_add_event_cb(ui->scrPowerMeter, scrPowerMeter_event_cb, LV_EVENT_KEY, NULL);
    lv_obj_add_event_cb(ui->scrModeSelect_listMode_item0, scrModeSelect_listMode_event_cb, LV_EVENT_KEY, NULL);
    lv_obj_add_event_cb(ui->scrModeSelect_listMode_item1, scrModeSelect_listMode_event_cb, LV_EVENT_KEY, NULL);
    lv_obj_add_event_cb(ui->scrModeSelect_listMode_item2, scrModeSelect_listMode_event_cb, LV_EVENT_KEY, NULL);
}

static void scrWelcome_event_cb(lv_event_t *e)
{
    if (LV_EVENT_KEY == lv_event_get_code(e))
    {
        uint32_t key_code = lv_indev_get_key(lv_indev_get_act());
        if (LV_KEY_ENTER == key_code)
        {
            ESP_LOGI(TAG, "scrWelcome -> scrModeSelect");
            scr_load_mode_select(&guider_ui, group_indev, LV_SCR_LOAD_ANIM_MOVE_LEFT);
        }
    }
}

static void scrModeSelect_listMode_event_cb(lv_event_t *e)
{
    if (LV_EVENT_KEY == lv_event_get_code(e))
    {
        uint32_t key_code = lv_indev_get_key(lv_indev_get_act());
        if (LV_KEY_ENTER == key_code)
        {
            lv_obj_t *obj = lv_event_get_target(e);
            if (guider_ui.scrModeSelect_listMode_item2 == obj)
            {
                ESP_LOGI(TAG, "scrModeSelect -> scrPowerMeter");
                scr_load_power_meter(&guider_ui, group_indev, LV_SCR_LOAD_ANIM_MOVE_LEFT);
            }
        }
        else if (LV_KEY_ESC == key_code)
        {
            ESP_LOGI(TAG, "scrModeSelect -> scrWelcome");
            scr_load_welcome(&guider_ui, group_indev, LV_SCR_LOAD_ANIM_MOVE_RIGHT);
        }
    }
}

static void scrPowerMeter_event_cb(lv_event_t *e)
{
    if (LV_EVENT_KEY == lv_event_get_code(e))
    {
        uint32_t key_code = lv_indev_get_key(lv_indev_get_act());
        if (LV_KEY_ESC == key_code)
        {
            ESP_ERROR_CHECK(terminate_ina226_service());
            ESP_LOGI(TAG, "scrPowerMeter -> scrModeSelect");
            scr_load_mode_select(&guider_ui, group_indev, LV_SCR_LOAD_ANIM_MOVE_RIGHT);
        }
    }
}

static void scr_load_welcome(lv_ui *ui, lv_group_t *group, lv_scr_load_anim_t anim)
{
    lv_group_remove_all_objs(group);
    lv_scr_load_anim(ui->scrWelcome, anim, 250, 0, false);
    lv_group_add_obj(group, ui->scrWelcome);
}

static void scr_load_mode_select(lv_ui *ui, lv_group_t *group, lv_scr_load_anim_t anim)
{
    lv_group_remove_all_objs(group);
    lv_scr_load_anim(ui->scrModeSelect, anim, 250, 0, false);
    lv_group_add_obj(group, ui->scrModeSelect_listMode_item0);
    lv_group_add_obj(group, ui->scrModeSelect_listMode_item1);
    lv_group_add_obj(group, ui->scrModeSelect_listMode_item2);
    lv_obj_clear_state(ui->scrModeSelect_listMode_item0, LV_STATE_ANY);
    lv_obj_clear_state(ui->scrModeSelect_listMode_item1, LV_STATE_ANY);
    lv_obj_clear_state(ui->scrModeSelect_listMode_item2, LV_STATE_ANY);
    lv_obj_add_state(ui->scrModeSelect_listMode_item0, LV_STATE_FOCUS_KEY);
}

static void scr_load_power_meter(lv_ui *ui, lv_group_t *group, lv_scr_load_anim_t anim)
{
    lv_group_remove_all_objs(group);
    lv_scr_load_anim(ui->scrPowerMeter, anim, 250, 0, false);
    lv_group_add_obj(group, ui->scrPowerMeter);
    ESP_ERROR_CHECK(start_ina226_service());
}

void ui_power_meter_update(float vol, float cur, float pwr)
{
    static char str_vol[16], str_cur[16], str_pwr[16];

    sprintf(str_vol, "%.4f", vol);
    str_vol[6] = '\0';
    if (cur < 0)
    {
        cur = 0 - cur;
    }
    sprintf(str_cur, "%.4f", cur);
    str_cur[6] = '\0';
    sprintf(str_pwr, "%.4f", pwr);
    str_pwr[6] = '\0';
    if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY))
    {
        lv_label_set_text(guider_ui.scrPowerMeter_labelVolVal, str_vol);
        lv_label_set_text(guider_ui.scrPowerMeter_labelCurVal, str_cur);
        lv_label_set_text(guider_ui.scrPowerMeter_labelPwrVal, str_pwr);
        xSemaphoreGive(xGuiSemaphore);
    }
}

static void key_read_cb(lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
{
    if (key_event != 0)
    {
        ESP_LOGI(TAG, "Key 0x%02X is pressed", key_event);
        data->state = LV_INDEV_STATE_PRESSED;
        data->key = key_event;
        key_event = 0;
    }
    else
    {
        data->state = LV_INDEV_STATE_RELEASED;
    }
}
