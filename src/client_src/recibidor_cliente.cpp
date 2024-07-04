#include "recibidor_cliente.h"

RecibidorCliente::RecibidorCliente(Socket& skt, Queue<Evento>& queue, std::atomic<bool>& estado):
        protocolo_cliente(skt), queue_eventos(queue), estado_cliente(estado){}

void RecibidorCliente::run() {
    
    Evento evento;
    while (_keep_running) {
        if (protocolo_cliente.recibir_evento(evento)) {
            try {
                queue_eventos.push(evento);
            } catch (const ClosedQueue&) {
                // Se cerro la queue, debo salir.
                break;
            }
        } else {
            // No se pudo recibir el evento, debo salir.
            break;
        }
    }
    _keep_running = false;
    estado_cliente = false; 
    // El recibidor va a ser el primero en darse cuenta
    // que el servidor cerro, por ende, le avisa al cliente.
}

RecibidorCliente::~RecibidorCliente() { 
    this->join(); }