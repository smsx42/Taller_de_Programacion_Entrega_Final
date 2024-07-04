#ifndef SERVER_PARTIDA_H_
#define SERVER_PARTIDA_H_

#include <iostream>
#include <list>
#include <map>

#include "../common_src/accion.h"
#include "../common_src/evento.h"
#include "../common_src/queue.h"
#include "../common_src/thread.h"

#include "logicaPartida.h"

#define FPS 15

class Partida: public Thread {
private:
    uint32_t id;

    uint32_t id_creador;

    uint8_t max_jugadores;

    Queue<Accion> queue_acciones;

    std::map<uint32_t, Queue<Evento>*> map_jugadores;

    std::mutex m;

    LogicaPartida logica_partida;

    std::string nombre_mapa;


public:
    Partida(uint32_t id_creador, uint8_t max_jugadores, uint32_t id, Queue<Evento>* queue_jugador, std::string mapa);

    Queue<Accion>* obtener_queue();

    std::string obtener_mapa();

    void listar_jugadores();

    Queue<Accion>* unir_jugador(uint32_t id_jugador, Queue<Evento>* queue_jugador);

    bool borrar_jugador(uint32_t id_jugador);

    uint8_t jugadores();

    uint8_t max();

    uint32_t creador();

    void run() override;

    ~Partida() override;
};


#endif
