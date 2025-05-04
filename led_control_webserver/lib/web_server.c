#include "web_server.h"
#include "pico/cyw43_arch.h"
#include "lwip/init.h"
#include "lwip/api.h"

void start_web_server(void) {
    // Inicializa a pilha de rede
    cyw43_arch_init();
    lwip_init();
    
    // Inicializa o servidor HTTP (aqui você pode usar uma biblioteca ou implementar a lógica de servidor)
    struct netconn *conn = netconn_new(NETCONN_TCP);
    netconn_bind(conn, NULL, 80);
    netconn_listen(conn);
    
    // Loop para servir páginas
    while (1) {
        struct netconn *new_conn;
        if (netconn_accept(conn, &new_conn) == ERR_OK) {
            // Aqui você pode adicionar a lógica para lidar com as requisições HTTP
            // Exemplo: processar a requisição para acionar LEDs ou mostrar temperatura
            netconn_close(new_conn);
            netconn_delete(new_conn);
        }
    }
}
