#ifndef SERVER_JUGADOR_H_
#define SERVER_JUGADOR_H_

#include "../common_src/socket.h"
#include "../common_src/thread.h"

#include "enviadorJugador.h"
#include "recibidorJugador.h"

class MonitorPartidas;

class Jugador {
private:
    uint32_t id;

    ProtocoloServidor protocolo_servidor;

    Queue<Evento> queue_jugador;

    RecibidorJugador recibidor_jugador;

    std::atomic<bool> en_partida;

    std::atomic<bool> conectado;


public:
    Jugador(uint32_t id, Socket skt, MonitorPartidas& monitor_partidas);

    bool esta_vivo();

    void join();

    void stop();

    ~Jugador();
};

#endif
