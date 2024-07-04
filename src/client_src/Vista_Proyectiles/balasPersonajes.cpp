#include "balasPersonajes.h"

BalasPersonajes::BalasPersonajes(): 
mapa_balas_pjs()
{};

// Método para agregar un nuevo mapa para un nuevo id_cliente
void BalasPersonajes::agregarNuevoMapaBalas(uint32_t id_jugador) {
    auto it = mapa_balas_pjs.find(id_jugador);
    if (it == mapa_balas_pjs.end()) {
        mapa_balas_pjs.insert({id_jugador, std::map<uint32_t, std::unique_ptr<BalaView>>()});
    }
}

void BalasPersonajes::agregarBala(uint32_t id_jugador, uint32_t id_bala, std::unique_ptr<BalaView> bala) {
    // Verificar si la bala ya existe
    auto& balas = mapa_balas_pjs[id_jugador];
    if (balas.find(id_bala) != balas.end()) {
        return;
    }

    // Insertar la nueva bala en el mapa del jugador
    balas.insert({id_bala, std::move(bala)});
}

// Método para eliminar una bala de un jugador
void BalasPersonajes::eliminarBala(uint32_t id_jugador, uint32_t id_bala) {
    auto it_jugador = mapa_balas_pjs.find(id_jugador);
    if (it_jugador != mapa_balas_pjs.end()) {
        auto& balas = it_jugador->second;
        auto it_bala = balas.find(id_bala);
        if (it_bala != balas.end()) {
            balas.erase(it_bala);
        }
    }
}

// Método para eliminar todas las balas de un jugador
void BalasPersonajes::eliminarTodasLasBalasDeJugador(uint32_t id_jugador) {
    auto it_jugador = mapa_balas_pjs.find(id_jugador);
    if (it_jugador != mapa_balas_pjs.end()) {
        mapa_balas_pjs.erase(it_jugador);
    }
}

void BalasPersonajes::eliminarTodasLasBalas() {
    mapa_balas_pjs.clear();
}

BalaView* BalasPersonajes::obtenerBala(uint32_t id_jugador, uint32_t id_bala) {
    auto it_jugador = mapa_balas_pjs.find(id_jugador);
    if (it_jugador != mapa_balas_pjs.end()) { // Si el jugador existe en el mapa
        auto& balas = it_jugador->second;
        auto it_bala = balas.find(id_bala);
        if (it_bala != balas.end()) { // Si la bala existe para ese jugador
            return it_bala->second.get(); // Devolvemos un puntero al objeto BalaView dentro del mapa
        } 
    }
    return nullptr; // Devolvemos nullptr si la bala no se encuentra o el jugador no existe (no tendria que pasar...)
}