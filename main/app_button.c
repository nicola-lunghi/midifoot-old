#include "app_button.h"
#include "iot_button.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_assert.h"
#include "sdkconfig.h"
#include <stddef.h>

static const char *TAG = "[" __FILE__ "]";

#define BUTTON_IO_NUM 0
#define BUTTON_ACTIVE_LEVEL 0
#define BUTTON_NUM 16

#define MIDS_SIZE(x) (sizeof(x) / (sizeof(x[0])))
#define MIDS_STRINGIFY(x) #x
#define MIDS_TOSTRING(x) MIDS_STRINGIFY(x)

static button_handle_t g_btns[BUTTON_NUM] = {0};

static int get_btn_index(button_handle_t btn)
{
    for (size_t i = 0; i < MIDS_SIZE(g_btns); i++)
        if (btn == g_btns[i])
            return i;
    return -1;
}

static const char *get_button_event_string(button_event_t evt)
{
#define __BTN_CASE(_ename) \
    case (_ename):         \
        return MIDS_TOSTRING(_ename)
#define __BTN_DEFAULT(_ename) \
    default:                  \
        return MIDS_TOSTRING(_ename)

    switch (evt)
    {
        __BTN_CASE(BUTTON_PRESS_DOWN);
        __BTN_CASE(BUTTON_PRESS_UP);
        __BTN_CASE(BUTTON_PRESS_REPEAT);
        __BTN_CASE(BUTTON_SINGLE_CLICK);
        __BTN_CASE(BUTTON_DOUBLE_CLICK);
        __BTN_CASE(BUTTON_LONG_PRESS_START);
        __BTN_CASE(BUTTON_LONG_PRESS_HOLD);
        __BTN_CASE(BUTTON_EVENT_MAX);
        __BTN_CASE(BUTTON_NONE_PRESS);
        __BTN_DEFAULT("INVALID");
    }
}

#define GEN_BTN_CBACK(_event, _name)                      \
    static void _name(void *arg)                          \
    {                                                     \
        button_event_t evt = iot_button_get_event(arg);       \
        if (_event != evt)                                \
            ESP_LOGE(TAG, "BTN%d: %s != %s",              \
                     get_btn_index((button_handle_t)arg), \
                     MIDS_TOSTRING(_event),               \
                     get_button_event_string(evt));       \
        ESP_LOGI(TAG, "BTN%d: %s: ",                      \
                 get_btn_index((button_handle_t)arg),     \
                 MIDS_TOSTRING(_event));                  \
    }

// repeat is special, we cannot ge  the event but we can count
#define GEN_BTN_CBACK_REPEAT(_event, _name)                \
    static void _name(void *arg)                           \
    {                                                      \
        ESP_LOGI(TAG, "BTN%d: %s[%d]",                     \
                 get_btn_index((button_handle_t)arg),      \
                 MIDS_TOSTRING(_event),                    \
                 button_get_repeat((button_handle_t)arg)); \
    }

// repeat is special, we cannot ge  the event but we can count
#define GEN_BTN_CBACK_DISABLED(_event, _name) \
    static void _name(__attribute__((unused)) void *arg) { return; }

GEN_BTN_CBACK_DISABLED(BUTTON_PRESS_DOWN, button_press_down_cb)
GEN_BTN_CBACK_DISABLED(BUTTON_PRESS_UP, button_press_up_cb)
// repeat is special
// GEN_BTN_CBACK_REPEAT(BUTTON_PRESS_REPEAT, button_press_repeat_cb)
GEN_BTN_CBACK_DISABLED(BUTTON_PRESS_REPEAT, button_press_repeat_cb)

GEN_BTN_CBACK(BUTTON_SINGLE_CLICK, button_single_click_cb)
GEN_BTN_CBACK(BUTTON_DOUBLE_CLICK, button_double_click_cb)
GEN_BTN_CBACK(BUTTON_LONG_PRESS_START, button_long_press_start_cb)
GEN_BTN_CBACK(BUTTON_LONG_PRESS_HOLD, button_long_press_hold_cb)

esp_err_t app_init_button(void)
{
    button_config_t cfg = {
        .type = BUTTON_TYPE_GPIO,
        .gpio_button_config = {
            .gpio_num = BUTTON_IO_NUM,
            .active_level = BUTTON_ACTIVE_LEVEL,
        },
    };
    g_btns[0] = iot_button_create(&cfg);
    assert(NULL != g_btns[0]);
    iot_button_register_cb(g_btns[0], BUTTON_PRESS_DOWN, button_press_down_cb);
    iot_button_register_cb(g_btns[0], BUTTON_PRESS_UP, button_press_up_cb);
    iot_button_register_cb(g_btns[0], BUTTON_PRESS_REPEAT, button_press_repeat_cb);
    iot_button_register_cb(g_btns[0], BUTTON_SINGLE_CLICK, button_single_click_cb);
    iot_button_register_cb(g_btns[0], BUTTON_DOUBLE_CLICK, button_double_click_cb);
    iot_button_register_cb(g_btns[0], BUTTON_LONG_PRESS_START, button_long_press_start_cb);
    iot_button_register_cb(g_btns[0], BUTTON_LONG_PRESS_HOLD, button_long_press_hold_cb);
    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    iot_button_delete(g_btns[0]);
    return ESP_OK;
}

// void app_main(void)
// {
//     ESP_LOGI(TAG, "[APP] Startup..");
//     ESP_LOGI(TAG, "[APP] Free memory: %d bytes", esp_get_free_heap_size());
//     ESP_LOGI(TAG, "[APP] IDF version: %s", esp_get_idf_version());

//    esp_log_level_set("*", ESP_LOG_INFO);
//    esp_log_level_set("MQTT_CLIENT", ESP_LOG_VERBOSE);

//     esp_err_t ret = button_init();
//     ESP_ERROR_CHECK(ret);
// }