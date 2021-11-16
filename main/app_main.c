#include "app_main.h"
#include "app_intro.h"
#include "app_storage.h"
#include "app_button.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_system.h"
#include "sdkconfig.h"
#include <stdio.h>

#define __THIS_PRJ_NAME    "MIDIFOOT"
#define __THIS_PRJ_VERSION "1.0.0"

static const char* TAG = "[" __FILE__ "]";

void app_main(void)
{
    ESP_LOGI(TAG, "Starting %s", __func__);
    ESP_ERROR_CHECK(app_intro(__THIS_PRJ_NAME " VERSION " __THIS_PRJ_VERSION));
    ESP_ERROR_CHECK(app_init_storage());
    ESP_ERROR_CHECK(app_init_button());

    ESP_LOGI(TAG, "Finished %s, entering infinite loop", __func__);
    while (1)
    {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

