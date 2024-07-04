#ifndef BALAS_PERSONAJES_H
#define BALAS_PERSONAJES_H

#include "balaView.h"

class BalasPersonajes {
    private:
        std::map<uint32_t, std::map<uint32_t, std::unique_ptr<BalaView>>> mapa_balas_pjs;

    public:
        explicit BalasPersonajes();

    // Método para agregar un nuevo mapa para un nuevo id_jugador
    void agregarNuevoMapaBalas(uint32_t id_jugador);

    void agregarBala(uint32_t id_jugador, uint32_t id_bala, std::unique_ptr<BalaView> bala);

    void eliminarBala(uint32_t id_jugador, uint32_t id_bala);

    void eliminarTodasLasBalasDeJugador(uint32_t id_jugador);

    void eliminarTodasLasBalas();

    BalaView* obtenerBala(uint32_t id_jugador, uint32_t id_bala);

};

#endif