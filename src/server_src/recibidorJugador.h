#ifndef SERVER_RECIBIDOR_JUGADOR_H_
#define SERVER_RECIBIDOR_JUGADOR_H_


#include <memory>

#include "../common_src/accion.h"
#include "../common_src/evento.h"
#include "../common_src/queue.h"
#include "../common_src/socket.h"
#include "../common_src/thread.h"

#include "enviadorJugador.h"
#include "monitorPartidas.h"
#include "protocoloServidor.h"

class MonitorPartidas;

class RecibidorJugador: public Thread {
private:
    ProtocoloServidor* protocolo_servidor;

    MonitorPartidas* monitor_partidas;

    Queue<Accion>* queue_acciones;

    Queue<Evento>* queue_jugador;

    EnviadorJugador enviador_jugador;

    uint32_t id;

    std::atomic<bool>& en_partida;

    std::atomic<bool>& conectado;


public:
    RecibidorJugador(ProtocoloServidor* protocolo_servidor, MonitorPartidas* monitor_partidas,
                     Queue<Evento>* queue_jugador, int id, std::atomic<bool>& en_partida,
                     std::atomic<bool>& conectado);

    void run() override;

    void leer_lobby(std::atomic<bool>& partida_encontrada, bool& was_closed);

    void join_enviador();

    ~RecibidorJugador() override;
};


#endif
