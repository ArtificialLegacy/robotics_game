#include "esp_log.h"
#include "nvs_flash.h"

#include "./robot.h"

#include "./mqtt.c"
#include "./wifi.c"
#include "portmacro.h"

void app_main(void) {
  esp_err_t ret = nvs_flash_init();
  if (ret == ESP_ERR_NVS_NO_FREE_PAGES ||
      ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ret = nvs_flash_init();
  }
  ESP_ERROR_CHECK(ret);

  ESP_LOGI(TAG, "ESP_WIFI_MODE_STA");
  wifi_init_sta();

  vTaskDelay(1000 / portTICK_PERIOD_MS);

  mqtt_initialize();
}
