#include "servidor.h"

Servidor::Servidor(const char* puerto): skt_servidor(puerto), aceptador(&skt_servidor) {}


void Servidor::run() {
    aceptador.start();

    while (std::cin.get() != 'q') {
        /*Esperando mensaje de salida*/
    }
    skt_servidor.shutdown(SHUT_RDWR);
    skt_servidor.close();
    aceptador.join();
}
