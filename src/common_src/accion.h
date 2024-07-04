#ifndef COMMON_ACCION_H_
#define COMMON_ACCION_H_

#include <iostream>


// Acciones posibles del jugador
enum CodigoAccion : uint8_t{
    CREAR,    // Crear una partida
    UNIRSE,   // Unirse a una partida
    SALIR,    // Salir del lobby, cerrar juego
    DISPARAR,   // Jugador dispara
    DEJAR_DISPARAR,
    SALTAR,     // Jugador salta
    DERECHA,    // Jugador se mueve a derecha
    IZQUIERDA,  // Jugador se mueve a izquierda
    QUIETO,     // Jugador se queda quieto
    RECARGAR,   // Jugador Recarga el arma
    CORRER,     // Jugador corre normal
    CORRER_RAPIDO,  // Jugador corre rapido
    ESPECIAL,    // Jugador usa habilidad especial
    LOBBY,    // Volver al lobby
    CAMBIAR_ARMA,

    ARRIBA,
    ABAJO,

    JAZZ, 
    SPAZ,
    LORI,
    NINGUNO,


    LIST_P   // Posible lista de partidas
};



// Struct tipo de acciones del jugador
struct __attribute__((packed)) Accion{
    uint8_t codigo;
    uint32_t id_jugador;
};


// Struct para obtener info de la partida
struct __attribute__((packed)) InfoPartida{
    uint32_t id_partida;
    uint32_t id_creador;
    uint8_t jugadores;
    uint8_t max_jugadores;
};


#define EXITO 0
#define FALLO 1


#endif