#ifndef CLIENT_LOBBY_H_
#define CLIENT_LOBBY_H_

#include "../common_src/queue.h"
#include "lobbyProtocolo.h"
#include "../common_src/accion.h"
#include "recibidorLobby.h"

#include "SDL2/SDL.h"
#include <sstream>

class Lobby{
private:
    Socket skt;

    LobbyProtocolo lobby_protocolo;

    RecibidorLobby recibidor_lobby;

    std::string nombre_mapa;

public:
    Lobby(const std::string &hostname, const std::string &servname);

    bool crear_partida(uint8_t max_jugadores, std::string mapa);

    bool unirse_partida(uint32_t codigo_partida, std::string &mapa);

    void elegir_personaje(uint8_t personaje);

    std::string devolver_mapa();
    
    void definir_mapa(std::string mapa);

    void close();

    Socket& obtener_socket();

    std::vector<InfoPartida> obtener_partidas();

};







#endif