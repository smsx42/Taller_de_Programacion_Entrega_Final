#ifndef SERVER_PROTOCOLO_SERVIDOR_H_
#define SERVER_PROTOCOLO_SERVIDOR_H_

#include <memory>
#include <string>
#include <vector>

#include <arpa/inet.h>

#include "../common_src/accion.h"
#include "../common_src/socket.h"

#include "monitorPartidas.h"

class ProtocoloServidor {
private:
    Socket skt_jugador;

public:
    explicit ProtocoloServidor(Socket skt);

    uint8_t obtener_accion(bool& was_closed);

    void enviar_evento(bool& was_closed, Evento evento);

    uint8_t leer_jugadores(bool& was_closed);
    
    std::string leer_mapa(bool& was_closed);

    uint32_t leer_id_partida(bool& was_closed);

    void enviar_mapa(std::string nombre_mapa, bool& was_closed);

    void enviar_confirmacion(uint8_t codigo, bool& was_closed);

    void enviar_id_jugador(uint32_t id, bool& was_closed);

    void enviar_lista_partidas(MonitorPartidas& monitor_partidas, bool& was_closed);

    void close();

    ~ProtocoloServidor();

private:
    void enviar_tipo_entidad(const std::string& entity_type, bool& was_closed);
    void enviar_posiciones_entidad(const std::vector<Position>& positions, bool& was_closed);
};


#endif
