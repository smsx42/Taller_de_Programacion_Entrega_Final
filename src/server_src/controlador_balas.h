#ifndef SERVER_CONTROLADOR_BALAS_H_
#define SERVER_CONTROLADOR_BALAS_H_

#include <algorithm>
#include <unordered_set>
#include <vector>
#include "./personaje/personaje.h"

#include "../common_src/bala.h"

class ControladorBalas {
private:
    std::vector<Bala> balas;
    std::unordered_set<uint32_t> ids_disponibles;
    uint32_t proximo_id;

public:
    ControladorBalas(): proximo_id(0) {}

    void agregar_bala(uint8_t codigo_bala, uint32_t id_jugador, uint32_t pos_x, uint32_t pos_y,
                      int velocidad) {
        uint32_t id_bala = obtener_id();
        Bala nueva_bala(codigo_bala, pos_x + velocidad * PERSONAJE_HEIGHT, pos_y, id_jugador,
                        id_bala, velocidad * obtener_velocidad(codigo_bala));
        balas.push_back(nueva_bala);
    }

    void remover_bala(uint32_t id_bala) {
        auto it = std::remove_if(balas.begin(), balas.end(), [id_bala](const Bala& b) {
            return b.obtener_id_bala() == id_bala;
        });

        if (it != balas.end()) {
            balas.erase(it, balas.end());
            ids_disponibles.insert(id_bala);
        }
    }

    std::vector<Bala>& obtener_balas() { return balas; }

private:
    uint32_t obtener_id() {
        /*
        if (ids_disponibles.empty()) {
            return proximo_id++;
        } else {
            uint32_t id = *ids_disponibles.begin();
            ids_disponibles.erase(id);
            return id;
        }
        */
       proximo_id += 1;
        return proximo_id;
    }

    int obtener_velocidad(uint8_t codigo_bala) {
        switch (codigo_bala) {
            case NORMAL:
                return 10;
            default:
                return 0;
        }
    }
};

#endif
