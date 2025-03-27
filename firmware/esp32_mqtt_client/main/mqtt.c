#include "esp_log.h"
#include "mqtt_client.h"

#include "./robot.h"
#include "sdkconfig.h"

static void mqtt_initialize(void) {
  const esp_mqtt_client_config_t mqtt_cfg = {
      .broker = {
          .address.hostname = CONFIG_MQTT_BROKER,
          .address.port = CONFIG_MQTT_PORT,
          .address.transport = MQTT_TRANSPORT_OVER_TCP,
      }};

  esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
  ESP_ERROR_CHECK(esp_mqtt_client_start(client));

  ESP_LOGI(TAG, "mqtt client started.");

  esp_mqtt_client_publish(client, "test/topic", "hello world", 0, 0, 0);
}
