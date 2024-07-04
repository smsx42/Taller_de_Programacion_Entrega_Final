#include "partida.h"

#include <chrono>

#include <arpa/inet.h>

Partida::Partida(uint32_t id_creador, uint8_t max_jugadores, uint32_t id,
                 Queue<Evento>* queue_creador, std::string mapa):
        id(id),
        id_creador(id_creador),
        max_jugadores(max_jugadores),
        queue_acciones(1000),
        logica_partida(mapa),
        nombre_mapa(mapa) {

    map_jugadores[id_creador] = queue_creador;
}

std::string Partida::obtener_mapa() {
    return nombre_mapa;
}

Queue<Accion>* Partida::obtener_queue() { return &queue_acciones; }

void Partida::listar_jugadores() {
    std::cout << "LISTA DE JUGADORES" << std::endl;

    for (const auto& par: map_jugadores) {
        std::cout << "JUGADOR " << par.first << std::endl;
    }
}

Queue<Accion>* Partida::unir_jugador(uint32_t id_jugador, Queue<Evento>* queue_jugador) {
    std::lock_guard<std::mutex> lock(m);

    if ((uint8_t)map_jugadores.size() < max_jugadores) {
        map_jugadores[id_jugador] = queue_jugador;
        return obtener_queue();
    }
    std::cout << "PARTIDA LLENA" << std::endl;
    return nullptr;
}

bool Partida::borrar_jugador(uint32_t id_jugador) {
    if (map_jugadores.find(id_jugador) != map_jugadores.end()) {
        map_jugadores.erase(id_jugador);
        logica_partida.abandonar_partida(id_jugador);
    }

    if (map_jugadores.empty()) {
        return true;
    }
    return false;
}

uint8_t Partida::jugadores() { return map_jugadores.size(); }

uint8_t Partida::max() { return max_jugadores; }

uint32_t Partida::creador() { return id_creador; }

void Partida::run() {

    auto start = std::chrono::high_resolution_clock::now();  // Guarda el tiempo de inicio
    std::atomic<bool> _tiempo_corriendo = true;

    while (_keep_running &&
           _tiempo_corriendo) {  // Mientras no hayan terminado la partida y el timer siga


        Accion accion;
        int cantidad_eventos = 0;
        auto inicio = std::chrono::high_resolution_clock::now();
        while (queue_acciones.try_pop(accion) && cantidad_eventos < 100) {
            logica_partida.ejecutar(accion, start);
            cantidad_eventos++;
        }

        logica_partida.actualizar_partida(start);

        Evento snapshot = logica_partida.obtener_snapshot(start);

        for (auto it = map_jugadores.begin(); it != map_jugadores.end(); ++it) {
            Queue<Evento>* queue = it->second;
            try {
                queue->push(snapshot);
            } catch (const ClosedQueue& err) {
                map_jugadores.erase(it);
            }
        }
        auto fin = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> tiempo = fin - inicio;
        double tiempo_transcurrido = tiempo.count();
        double tiempo_por_frame = 1000.0 / 15;
        double tiempo_descanso = tiempo_por_frame - tiempo_transcurrido;

        if (tiempo_descanso > 0) {
            std::this_thread::sleep_for(
                    std::chrono::milliseconds(static_cast<int>(tiempo_descanso)));
        } else {
            std::this_thread::sleep_for(
                    std::chrono::milliseconds(static_cast<int>(tiempo_por_frame)));
        }


        if (snapshot.tiempo_restante <= 0) {
            _tiempo_corriendo = false;
        }
    }

    // Partida terminada, cierro la queue
    queue_acciones.close();
}


Partida::~Partida() { }
