#ifndef SERVER_ENVIADOR_JUGADOR_H_
#define SERVER_ENVIADOR_JUGADOR_H_


#include "../common_src/queue.h"
#include "../common_src/thread.h"

#include "protocoloServidor.h"

class EnviadorJugador: public Thread {
private:
    ProtocoloServidor* protocolo_servidor;

    Queue<Evento>* queue_jugador;

    uint32_t id;

    std::atomic<bool>& en_partida;

    std::atomic<bool>& conectado;

public:
    EnviadorJugador(ProtocoloServidor* protocolo_servidor, Queue<Evento>* queue_jugador,
                    uint32_t id, std::atomic<bool>& en_partida, std::atomic<bool>& conectado);

    void run() override;

    ~EnviadorJugador() override;
};


#endif
