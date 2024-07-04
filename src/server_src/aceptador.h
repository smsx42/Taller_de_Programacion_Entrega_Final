#ifndef SERVER_ACEPTADOR_H_
#define SERVER_ACEPTADOR_H_

#include <iostream>
#include <list>

#include "../common_src/socket.h"
#include "../common_src/thread.h"

#include "jugador.h"
#include "monitorPartidas.h"

class Aceptador: public Thread {
private:
    Socket* skt_servidor;

    std::list<Jugador*> jugadores;

    uint32_t cantidad_jugadores;

public:
    explicit Aceptador(Socket* skt);

    void run() override;

    void agregar_jugador(Socket skt_jugador, MonitorPartidas& monitor_partidas);

    void verificar_jugadores();

    void borrar_jugadores();

    ~Aceptador() override;
};


#endif
