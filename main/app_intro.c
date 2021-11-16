#include "app_intro.h"
#include "sdkconfig.h"
#include "esp_err.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include <stdio.h>

static const char menu_separator[] =
    "==================================================================";

static void app_print_menu(const char *menu_title)
{
    printf("\n%s\n%s\n%s\n", menu_separator, menu_title, menu_separator);
}

static void app_print_end_intro(void)
{
    puts(menu_separator);
    fflush(stdout);
}

static void app_print_chip_info(void)
{
    esp_chip_info_t chip_info;

    esp_chip_info(&chip_info);

    /* Print chip information */
    printf("CPU           : %s (rev=%d,cores=%d)\n", CONFIG_IDF_TARGET, chip_info.revision, chip_info.cores);
    printf("RF MODULES    : WiFi%s%s\n", (chip_info.features & CHIP_FEATURE_BT) ? ",BT" : "",
           (chip_info.features & CHIP_FEATURE_BLE) ? ",BLE" : "");
    printf("FLASH MEMORY  : %dMB (%s)\n", spi_flash_get_chip_size() / (1024 * 1024),
           (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");
    printf("MIN FREE HEAP : %d (bytes)\n", esp_get_minimum_free_heap_size());
}

esp_err_t app_intro(const char *prj_name)
{
    app_print_menu(prj_name);
    app_print_chip_info();
    app_print_end_intro();
    return ESP_OK;
}
