#include "arma.h"


Arma::Arma(): balas(100), tiempo_disparo(-TIEMPO_ENTRE_DISPARO), codigo_bala(BALA_NORMAL) {}

bool Arma::disparar(std::chrono::duration<double> tiempo_transcurrido) {
    double tiempo = tiempo_transcurrido.count();
    if (balas > 0 && (tiempo - tiempo_disparo) >= TIEMPO_ENTRE_DISPARO) {
        balas--;
        tiempo_disparo = tiempo;
        return true;
    }
    return false;
}

void Arma::recargar() {}

uint8_t Arma::obtener_bala() { return codigo_bala; }
