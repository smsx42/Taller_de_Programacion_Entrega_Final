#ifndef CLIENTE_H
#define CLIENTE_H

#include "../common_src/socket.h"
#include "protocolo_cliente.h"
#include "renderizado.h"
#include "recibidor_cliente.h"
#include "enviadorCliente.h"
#include "../common_src/queue.h"
#include "../common_src/accion.h"
#include "../common_src/evento.h"
#include <arpa/inet.h>

class Cliente {
private:
    Socket &skt;        
    std::atomic<bool> estado;
    Renderizado renderizado;
    std::map<uint32_t, std::unique_ptr<PersonajeView>> personajes;
    uint32_t id_jugador;
    std::string nombre_mapa;
    
public:
    explicit Cliente(Socket &skt, std::string mapa);

    static bool verificar_argumentos(int argc, char* args[]);

    void comunicarse_con_el_servidor();

    void terminar_comunicacion();

    Cliente(const Cliente&) = delete;
    Cliente& operator=(const Cliente&) = delete;

    Cliente(Cliente&&) = default;
    Cliente& operator=(Cliente&&) = default;
};

#endif
