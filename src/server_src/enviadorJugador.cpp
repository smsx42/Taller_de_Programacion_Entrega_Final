#include "enviadorJugador.h"


EnviadorJugador::EnviadorJugador(ProtocoloServidor* protocolo_servidor,
                                 Queue<Evento>* queue_jugador, uint32_t id,
                                 std::atomic<bool>& en_partida, std::atomic<bool>& conectado):
        protocolo_servidor(protocolo_servidor),
        queue_jugador(queue_jugador),
        id(id),
        en_partida(en_partida),
        conectado(conectado) {}


void EnviadorJugador::run() {
    bool was_closed = false;
    // Deberia correr mientas el jugador este conectado al servidor
    while (conectado) {
        try {
            try {
                Evento evento = queue_jugador->pop();
                protocolo_servidor->enviar_evento(was_closed, evento);
            } catch (const ClosedQueue& err) {
                // Se cerro la queue del jugador, salio de la partida
                // Se cerro el socket, se perdio la conexion
                break;
            }
        } catch (std::runtime_error& err) {
            break;
        }
    }

    // Cierro todo por las dudas
    en_partida = false;
    conectado = false;
}


EnviadorJugador::~EnviadorJugador() {}
