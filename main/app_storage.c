#include "app_storage.h"
#include "esp_err.h"
#include "nvs_flash.h"
#include "nvs.h"

esp_err_t app_init_storage(void)
{
    esp_err_t ret;

    ret = nvs_flash_init();
    if ((ESP_ERR_NVS_NO_FREE_PAGES == ret) ||
        (ESP_ERR_NVS_NEW_VERSION_FOUND == ret))
    {
        // NVS partition was truncated and needs to be erased,
        // retry nvs_flash_init
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
 
    return ret;
}
