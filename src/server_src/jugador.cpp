#include "jugador.h"

#include <utility>

#include "recibidorJugador.h"

Jugador::Jugador(uint32_t id, Socket skt, MonitorPartidas& monitor_partidas):
        id(id),
        protocolo_servidor(std::move(skt)),
        queue_jugador(1000),
        recibidor_jugador(&protocolo_servidor, &monitor_partidas, &queue_jugador, id,
                          std::ref(en_partida), std::ref(conectado)),
        en_partida(false),
        conectado(true) {


    /*
        Antes de iniciar los hilos, espero el mensaje de crear o unirse
        En base a eso, obtengo una queue donde van a ir cargandose las acciones en el recibidor
        también, debo enviarle a la partida la cola donde mandar sus respuestas al jugador
        para luego hacer broadcast

    */
    recibidor_jugador.start();
}

bool Jugador::esta_vivo() { return conectado; }


void Jugador::join() {
    recibidor_jugador.join();
    recibidor_jugador.join_enviador();
}

void Jugador::stop() {
    en_partida = false;  // Controla si el jugador esta en una partida
    conectado = false;   // Controla si el jugador esta en el lobby + partida

    // protocolo_servidor.close();

    // queue_jugador.close();
}


Jugador::~Jugador() {}
