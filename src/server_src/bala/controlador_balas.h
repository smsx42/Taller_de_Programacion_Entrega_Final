#ifndef SERVER_CONTROLADOR_BALAS_H_
#define SERVER_CONTROLADOR_BALAS_H_

#include <algorithm>
#include <unordered_set>
#include <vector>
#include <random>
#include "../personaje/personaje.h"
#include "bala.h"
#include "../configuracion.h"

#define CONFIG Configuracion::config()

class ControladorBalas {
private:
    std::vector<Bala> balas;
    std::unordered_set<uint32_t> ids_disponibles;
    uint32_t proximo_id;
    std::vector<uint8_t> codigo_balas;

public:
    ControladorBalas(): proximo_id(-1) {
        std::map<std::string, uint8_t> codigos = CONFIG.obtenerBalas();
        for (const auto& par : codigos) {
            if(par.second == BALA_NORMAL) continue;
            codigo_balas.push_back(par.second);
        }
    }


    void agregar_bala(uint8_t codigo_bala, uint32_t id_jugador, uint32_t pos_x, uint32_t offset,uint32_t pos_y,
                      int velocidad) {
        uint32_t id_bala = obtener_id();
        const ConfigBala& config_bala = CONFIG.obtenerBala(codigo_bala);
        balas.push_back(Bala(codigo_bala,
                         pos_x + offset,
                         pos_y,
                         id_jugador,
                         id_bala,
                         velocidad *  config_bala.velocidad_del_proyectil,
                         config_bala.danio,
                         config_bala.tiempo_entre_disparo,
                         config_bala.rango_explosion,
                         config_bala.municion,
                         config_bala.ancho,
                         config_bala.largo));
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


    uint8_t obtener_bala_aleatoria(){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distribucion(0, codigo_balas.size() - 1);
        return codigo_balas[distribucion(gen)];
    }

private:
    uint32_t obtener_id() {
       proximo_id += 1;
    return proximo_id ;
    }

};

#endif
