#ifndef CLIENT_RECIBIDOR_LOBBY_H_
#define CLIENT_RECIBIDOR_LOBBY_H_

#include "lobbyProtocolo.h"
#include "../common_src/thread.h"
#include "../common_src/accion.h"
#include "../common_src/evento.h"

class RecibidorLobby : public Thread{
private:
    LobbyProtocolo *lobby_protocolo;
public:
    RecibidorLobby(LobbyProtocolo *lobby_protocolo);

    void run() override;

    ~RecibidorLobby() override;
};


#endif