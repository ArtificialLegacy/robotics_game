idf_component_register(SRCS "esp32_spintest.c"
    INCLUDE_DIRS "."
    REQUIRES esp_driver_gpio esp_driver_ledc
)
