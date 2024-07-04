#ifndef COMMON_BALA_H_
#define COMMON_BALA_H_

#include <iostream>


// Aca van a ir los tipos de bala
enum CodigoBala : uint8_t{
    NORMAL,
    NINGUNA

};

class Bala{
private:

    uint8_t codigo_bala;
    uint32_t id_jugador;
    uint32_t id_bala;

    uint32_t posicion_x;
    uint32_t posicion_y;
    uint8_t ancho;
    uint8_t largo;
    uint8_t danio;
    bool impacto;
    int velocidad;



public:
    Bala(uint8_t codigo_bala,uint32_t pos_x, uint32_t pos_y, uint32_t id_jugador, uint32_t id_bala, int velocidad);

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

};



#endif

