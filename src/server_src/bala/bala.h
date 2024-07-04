#ifndef COMMON_BALA_H_
#define COMMON_BALA_H_

#include <iostream>
#include "../common_src/codigo_objeto.h"
#include "../personaje/personaje.h"
#include "../enemigo/enemigo.h"


class Personaje;
class Enemigo;

class Bala{
private:

    uint8_t codigo_bala;
    uint32_t id_jugador;
    uint32_t id_bala;
    uint32_t posicion_x;
    uint32_t posicion_y;
    uint8_t ancho;
    uint8_t largo;
    bool impacto;

    uint8_t danio;
    int velocidad;
    double tiempo_entre_disparo;
    uint32_t rango_explosion;
    uint16_t municion;


public:
    Bala(uint8_t codigo_bala,uint32_t pos_x, uint32_t pos_y, uint32_t id_jugador, uint32_t id_bala, int velocidad, uint8_t danio, double tiempo_entre_disparo, uint32_t rango_explosion, int municion, uint32_t ancho, uint32_t largo);

    void actualizar_posicion();

    void impactar();

    // Getters para snapshot


    uint32_t obtener_id_bala() const;

    uint32_t obtener_id_jugador() const;

    uint8_t obtener_codigo() const;

    uint8_t obtener_ancho() const;

    uint8_t obtener_largo() const;

    uint32_t obtener_posicionX() const;

    uint32_t obtener_posicionY() const;

    uint8_t obtener_danio() const;

    bool obtener_impacto() const;

    void inflingir_danio(Personaje *personaje, std::chrono::duration<double> tiempo_transcurrido);

    void inflingir_danio(Enemigo *enemigo, std::chrono::duration<double> tiempo_transcurrido);



};  



#endif

