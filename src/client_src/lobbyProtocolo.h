#ifndef CLIENT_LOBBY_PROTOCOLO_H_
#define CLIENT_LOBBY_PROTOCOLO_H_

#include "../common_src/socket.h"   
#include "../common_src/evento.h"
#include "../common_src/accion.h"
#include <arpa/inet.h>

class LobbyProtocolo{
private:
    Socket *skt;
public:
    LobbyProtocolo(Socket *skt);

    uint8_t serializar_creacion_partida(uint8_t max_jugadores, std::string mapa);

    uint8_t serializar_unirse_partida(uint32_t codigo_partida, std::string &mapa);

    void serializar_personaje(uint8_t personaje);

    void serializar_mapa(std::string nombre_mapa);

    std::string deserializar_mapa();

    std::vector<InfoPartida> obtener_partidas();

    ~LobbyProtocolo();
};





#endif