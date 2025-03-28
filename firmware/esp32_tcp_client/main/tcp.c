#include "esp_log.h"
#include "sdkconfig.h"
#include <arpa/inet.h>
#include <netdb.h> // struct addrinfo
#include <sys/socket.h>
#include <unistd.h>

#include "./robot.h"

#define HOST_IP_ADDR CONFIG_IPV4_ADDR
#define PORT CONFIG_PORT

static const char *payload = "ping";

void tcp_client(void) {
  char rx_buffer[128];
  char host_ip[] = HOST_IP_ADDR;
  int addr_family = 0;
  int ip_protocol = 0;

  while (1) {
    struct sockaddr_in dest_addr;
    inet_pton(AF_INET, host_ip, &dest_addr.sin_addr);
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(PORT);
    addr_family = AF_INET;
    ip_protocol = IPPROTO_IP;

    int sock = socket(addr_family, SOCK_STREAM, ip_protocol);
    if (sock < 0) {
      ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
      break;
    }
    ESP_LOGI(TAG, "Socket created, connecting to %s:%d", host_ip, PORT);

    int err = connect(sock, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
    if (err != 0) {
      ESP_LOGE(TAG, "Socket unable to connect: errno %d", errno);
      break;
    }
    ESP_LOGI(TAG, "Successfully connected");

    while (1) {
      int err = send(sock, payload, strlen(payload), 0);
      if (err < 0) {
        ESP_LOGE(TAG, "Error occurred during sending: errno %d", errno);
        break;
      }

      int len = recv(sock, rx_buffer, sizeof(rx_buffer) - 1, 0);
      // Error occurred during receiving
      if (len < 0) {
        ESP_LOGE(TAG, "recv failed: errno %d", errno);
        break;
      }
      // Data received
      else {
        rx_buffer[len] =
            0; // Null-terminate whatever we received and treat like a string
        ESP_LOGI(TAG, "Received %d bytes from %s:", len, host_ip);
        ESP_LOGI(TAG, "%s", rx_buffer);
      }
    }

    if (sock != -1) {
      ESP_LOGE(TAG, "Shutting down socket and restarting...");
      shutdown(sock, 0);
      close(sock);
    }
  }
}
