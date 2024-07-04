#include "enviadorCliente.h"

EnviadorCliente::EnviadorCliente(Socket& skt, Queue<CodigoAccion>& queue):
        protocolo_cliente(skt), queue_acciones(queue){}

void EnviadorCliente::run() {
    
    while (_keep_running) {
        try {
            CodigoAccion codigo_accion = queue_acciones.pop();
            if (!protocolo_cliente.enviar_accion_juego(codigo_accion)) {
                // Perdi la conexion con el servidor, salgo.
                break;
            }
        } catch (const ClosedQueue &err) {
            // Me cerraron la queue, fue por el recibidor o el cliente.
            // Debo salir.
            break;
        }
    }
    _keep_running = false;
}

EnviadorCliente::~EnviadorCliente() { 
    this->join(); }