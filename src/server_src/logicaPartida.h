#ifndef SERVER_LOGICA_PARTIDA_H_
#define SERVER_LOGICA_PARTIDA_H_


#include <chrono>
#include <iostream>
#include <map>
#include <memory>

#include "../common_src/accion.h"
#include "../common_src/evento.h"

#include "./bala/controlador_balas.h"
#include "./enemigo/fabrica_enemigos.h"
#include "./objeto/fabrica_objetos.h"
#include "./objeto/objeto_solido.h"
#include "./personaje/personaje_jazz.h"
#include "./personaje/personaje_lori.h"
#include "./personaje/personaje_spaz.h"
#include "rectangulo.h"



class LogicaPartida {
private:
    std::map<uint32_t, Personaje*> map_personajes;
    std::map<uint32_t, std::unique_ptr<Enemigo>> map_enemigos;
    std::map<uint32_t, Objeto*> map_objetos_solidos;
    std::map<uint32_t, std::unique_ptr<Objeto>> map_objetos_comunes;
    std::vector<SpawnPoint> spawns;
    uint32_t id_objetos;
    ControladorBalas controlador_balas;
    FabricaObjetos fabrica_objetos;
    FabricaEnemigos fabrica_enemigos;


    void crear_drop(uint8_t codigo_objeto, uint32_t x, uint32_t y);

public:
    LogicaPartida(std::string mapa);

    void ejecutar(Accion accion,
                  std::chrono::time_point<std::chrono::high_resolution_clock> tiempo);

    void mover_derecha(uint32_t id_jugador, std::chrono::time_point<std::chrono::high_resolution_clock> tiempo);

    void mover_izquierda(uint32_t id_jugador, std::chrono::time_point<std::chrono::high_resolution_clock> tiempo);

    void mover_arriba(uint32_t id_jugador,
                      std::chrono::time_point<std::chrono::high_resolution_clock> tiempo);

    void mover_abajo(uint32_t id_jugador);

    void mover_quieto(uint32_t id_jugador);

    void mover_correr_rapido(uint32_t id_jugador, std::chrono::time_point<std::chrono::high_resolution_clock> tiempo);

    void mover_correr(uint32_t id_jugador);

    void disparar(uint32_t id_jugador,
                  std::chrono::time_point<std::chrono::high_resolution_clock> tiempo);

    void dejar_disparar(uint32_t id_jugador);


    void usar_habilidad(uint32_t id_jugador,
                        std::chrono::time_point<std::chrono::high_resolution_clock> tiempo);

    void cambiar_bala(uint32_t id_jugador);

    void abandonar_partida(uint32_t id_jugador);

    void agregar_personaje(Accion accion);

    void actualizar_partida(std::chrono::time_point<std::chrono::high_resolution_clock> tiempo);

    Evento obtener_snapshot(std::chrono::time_point<std::chrono::high_resolution_clock> start);


    // Getters para tests

    int getPersonajesSize();

    int getEnemigosSize();

    int getObjetosSolidosSize();

    int getObjetosComunesSize();

    ~LogicaPartida();
};


#endif
