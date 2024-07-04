#ifndef ENVIADOR_CLIENTE_H
#define ENVIADOR_CLIENTE_H

#include "../common_src/thread.h"
#include "../common_src/queue.h"
#include "../common_src/evento.h"

#include "protocolo_cliente.h"

class EnviadorCliente: public Thread {
    private:
    ProtocoloCliente protocolo_cliente;
    Queue<CodigoAccion>& queue_acciones;
    
    public:
    explicit EnviadorCliente(Socket& skt, Queue<CodigoAccion>& queue);

    /**
     * Ejecuta el hilo encargado de recibir todo
     * lo que le envia el servidor.
     */
    virtual void run() override;

    /**
     * Destructor de la clase.
     */
    virtual ~EnviadorCliente();
};

#endif