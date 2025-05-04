// src/main.c

#include "pico/stdlib.h"
#include "lwip/pbuf.h"
#include "lwip/tcp.h"
#include "lwip/netif.h"
#include "led_control.h"
#include "wifi.h"
#include "temperature.h"
#include "pico/cyw43_arch.h"

#define HTML_BUFFER_SIZE 4096

static err_t tcp_server_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err) {
    if (!p) {
        tcp_close(tpcb);
        tcp_recv(tpcb, NULL);
        return ERR_OK;
    }

    char *request = (char *)malloc(p->len + 1);
    memcpy(request, p->payload, p->len);
    request[p->len] = '\0';

    process_led_command(request);

    char html[HTML_BUFFER_SIZE];

    snprintf(html, sizeof(html),
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n\r\n"
        "<!DOCTYPE html><html><head><title>LED Control</title><style>"
        "body { font-family: Arial; text-align: center; margin-top: 40px; }"
        "button { font-size: 24px; padding: 10px 20px; margin: 10px; border-radius: 8px; }"
        ".temp { font-size: 28px; margin-top: 30px; }"
        "</style></head><body>"
        "<h1>Controle de LEDs</h1>"
        "<table style=\"margin: 0 auto;\">"
        "<tr>"
        "<td><form action=\"./blue_on\"><button style=\"background:#2196F3; color:white;\">AZUL ON</button></form></td>"
        "<td><form action=\"./green_on\"><button style=\"background:#4CAF50; color:white;\">GREEN ON</button></form></td>"
        "<td><form action=\"./red_on\"><button style=\"background:#F44336; color:white;\">RED ON</button></form></td>"
        "</tr>"
        "<tr>"
        "<td><form action=\"./blue_off\"><button>AZUL OFF</button></form></td>"
        "<td><form action=\"./green_off\"><button>GREEN OFF</button></form></td>"
        "<td><form action=\"./red_off\"><button>RED OFF</button></form></td>"
        "</tr>"
        "</table>"
        "<p class=\"temp\">Temperatura: %.2f &deg;C</p>"
        "</body></html>", current_temperature);

    tcp_write(tpcb, html, strlen(html), TCP_WRITE_FLAG_COPY);
    tcp_output(tpcb);

    free(request);
    pbuf_free(p);
    return ERR_OK;
}

static err_t tcp_server_accept(void *arg, struct tcp_pcb *newpcb, err_t err) {
    tcp_recv(newpcb, tcp_server_recv);
    return ERR_OK;
}

int main() {
    stdio_init_all();

    init_leds();

    if (init_wifi()) return -1;

    if (netif_default) {
        printf("IP do dispositivo: %s\n", ipaddr_ntoa(&netif_default->ip_addr));
    }

    struct tcp_pcb *server = tcp_new();
    if (!server || tcp_bind(server, IP_ADDR_ANY, 80) != ERR_OK) {
        printf("Erro ao configurar servidor\n");
        return -1;
    }

    server = tcp_listen(server);
    tcp_accept(server, tcp_server_accept);
    printf("Servidor iniciado na porta 80\n");

    init_temperature_sensor();

    while (true) {
        cyw43_arch_poll();

        static absolute_time_t next_update;
        if (absolute_time_diff_us(get_absolute_time(), next_update) <= 0) {
            update_temperature();
            next_update = make_timeout_time_ms(1000);
        }
    }

    cyw43_arch_deinit();
    return 0;
}
