#ifndef SERVER_ARMA_H_
#define SERVER_ARMA_H_

#include <chrono>
#include <iostream>

#include "./bala/bala.h"

#define TIEMPO_ENTRE_DISPARO 0.5

class Arma {
private:
    uint8_t balas;

    double tiempo_disparo;

    uint8_t codigo_bala;

public:
    Arma();

    void recargar();

    bool disparar(std::chrono::duration<double> tiempo_transcurrido);

    uint8_t obtener_bala();
};


#endif
