#include "driver/gpio.h"
#include "driver/ledc.h"
#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "hal/gpio_types.h"
#include <stdio.h>

#define LEDC_TIMER LEDC_TIMER_0
#define LEDC_MODE LEDC_LOW_SPEED_MODE
#define LEDC_CHANNEL LEDC_CHANNEL_0
#define LEDC_DUTY_RES LEDC_TIMER_13_BIT
#define LEDC_DUTY (4096)
#define LEDC_FREQUENCY (4000)

#define PWM1 GPIO_NUM_27
#define FWD1 GPIO_NUM_16
#define BAK1 GPIO_NUM_17
#define PWM2 GPIO_NUM_26
#define FWD2 GPIO_NUM_18
#define BAK2 GPIO_NUM_19

#define LED GPIO_NUM_2

#define ACTIVE_TIME 250
#define INACTIVE_TIME 100

void init_motor(gpio_num_t pin) {
  ledc_timer_config_t ledc_timer = {.speed_mode = LEDC_MODE,
                                    .duty_resolution = LEDC_DUTY_RES,
                                    .timer_num = LEDC_TIMER,
                                    .freq_hz = LEDC_FREQUENCY,
                                    .clk_cfg = LEDC_AUTO_CLK};
  ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

  ledc_channel_config_t ledc_channel = {.speed_mode = LEDC_MODE,
                                        .channel = LEDC_CHANNEL,
                                        .timer_sel = LEDC_TIMER,
                                        .intr_type = LEDC_INTR_DISABLE,
                                        .gpio_num = pin,
                                        .duty = 0,
                                        .hpoint = 0};
  ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));
}

void app_main(void) {
  gpio_set_direction(PWM1, GPIO_MODE_OUTPUT);
  gpio_set_direction(FWD1, GPIO_MODE_OUTPUT);
  gpio_set_direction(BAK1, GPIO_MODE_OUTPUT);

  gpio_set_direction(PWM2, GPIO_MODE_OUTPUT);
  gpio_set_direction(FWD2, GPIO_MODE_OUTPUT);
  gpio_set_direction(BAK2, GPIO_MODE_OUTPUT);

  gpio_set_direction(LED, GPIO_MODE_OUTPUT);

  gpio_set_level(FWD1, 1);
  gpio_set_level(FWD2, 1);
  gpio_set_level(LED, 1);

  init_motor(PWM1);
  init_motor(PWM2);

  ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, LEDC_DUTY));
  ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL));

  vTaskDelay(ACTIVE_TIME);

  gpio_set_level(FWD1, 0);
  gpio_set_level(FWD2, 0);
  gpio_set_level(LED, 0);

  vTaskDelay(INACTIVE_TIME);

  gpio_set_level(BAK1, 1);
  gpio_set_level(BAK2, 1);
  gpio_set_level(LED, 1);

  vTaskDelay(ACTIVE_TIME);

  gpio_set_level(BAK1, 0);
  gpio_set_level(BAK2, 0);
  gpio_set_level(LED, 0);

  vTaskDelay(INACTIVE_TIME);

  gpio_set_level(FWD1, 1);
  gpio_set_level(BAK2, 1);
  gpio_set_level(LED, 1);

  vTaskDelay(ACTIVE_TIME);

  gpio_set_level(FWD1, 0);
  gpio_set_level(BAK2, 0);
  gpio_set_level(LED, 0);

  vTaskDelay(INACTIVE_TIME);

  gpio_set_level(BAK1, 1);
  gpio_set_level(FWD2, 1);
  gpio_set_level(LED, 1);

  vTaskDelay(ACTIVE_TIME);

  gpio_set_level(FWD1, 0);
  gpio_set_level(FWD2, 0);
  gpio_set_level(BAK1, 0);
  gpio_set_level(BAK2, 0);
  gpio_set_level(LED, 0);

  ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, 0));
  ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL));
}
