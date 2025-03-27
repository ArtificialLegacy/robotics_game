idf_component_register(SRCS "esp32_client.c"
                    PRIV_REQUIRES "esp_wifi" "nvs_flash" "esp_netif" "unity"
                    REQUIRES "mqtt"
                    INCLUDE_DIRS ".")
