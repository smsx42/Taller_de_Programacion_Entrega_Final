#ifndef SERVER_SERVIDOR_H_
#define SERVER_SERVIDOR_H_

#include <iostream>
#include <string>

#include <sys/socket.h>

#include "../common_src/thread.h"

#include "aceptador.h"

class Servidor {
private:
    Socket skt_servidor;

    Aceptador aceptador;

public:
    explicit Servidor(const char* puerto);

    void run();

    Servidor(const Servidor&) = delete;
    Servidor& operator=(const Servidor&) = delete;
};


#endif
