#include "monitorPartidas.h"


MonitorPartidas::MonitorPartidas(): contador_partidas(0) {}


Queue<Accion>* MonitorPartidas::crear_partida(uint32_t id_creador, uint8_t cant_jugadores,
                                              Queue<Evento>* queue_jugador, std::string mapa) {
    Partida* nueva_partida =
            new Partida(id_creador, cant_jugadores, contador_partidas, queue_jugador, mapa);
    partidas.emplace(contador_partidas, nueva_partida);
    contador_partidas++;
    // Empiezo hilo partida
    nueva_partida->start();
    return nueva_partida->obtener_queue();
}

std::string MonitorPartidas::obtener_mapa_partida(uint32_t id_partida) {
    auto it = partidas.find(id_partida);
    // Buscar el mapa de la partida
    if (it != partidas.end()) {
        // Partida encontrada, uno al jugador y devuelvo la Queue si es posible
        return it->second->obtener_mapa();
    } else {
        // Partida no encontrada, devuelvo nullptr
        std::cout << "Error, partida no encontrada" << std::endl;
        return nullptr;
    }
}

void MonitorPartidas::listar_partidas() {
    for (auto it = partidas.begin(); it != partidas.end(); ++it) {
        uint32_t key = it->first;
        Partida* partida = it->second;
        std::cout << "\nPARTIDA " << key << std::endl;
        partida->listar_jugadores();
    }
}


Queue<Accion>* MonitorPartidas::unir_jugador(uint32_t id_jugador, uint32_t id_partida,
                                             Queue<Evento>* queue_jugador) {
    auto it = partidas.find(id_partida);

    // Buscar la partida en el map
    if (it != partidas.end()) {
        // Partida encontrada, uno al jugador y devuelvo la Queue si es posible
        return it->second->unir_jugador(id_jugador, queue_jugador);
    } else {
        // Partida no encontrada, devuelvo nullptr
        std::cout << "Error, partida no encontrada" << std::endl;
        return nullptr;
    }
}


void MonitorPartidas::borrar_jugador(uint32_t id_jugador) {
    auto it = partidas.begin();
    while (it != partidas.end()) {
        Partida* partida = it->second;

        // Si al eliminar el jugador la partida queda vacia, la borro
        if (partida->borrar_jugador(id_jugador)) {
            partida->stop();
            partida->join();
            delete partida;
            it = partidas.erase(it);
        } else {
            ++it;
        }
    }
}

void MonitorPartidas::borrar_partidas() {
    for (auto& par: partidas) {
        par.second->stop();
        par.second->join();
        delete par.second;
    }
    partidas.clear();
}

const std::map<uint32_t, Partida*>* MonitorPartidas::obtener_partidas() const { return &partidas; }


MonitorPartidas::~MonitorPartidas() {}
