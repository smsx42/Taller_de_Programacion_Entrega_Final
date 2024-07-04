#include "bala.h"


Bala::Bala(uint8_t codigo_bala,uint32_t pos_x, uint32_t pos_y, uint32_t id_jugador, uint32_t id_bala, int velocidad) : 
    codigo_bala(codigo_bala), id_jugador(id_jugador),posicion_x(pos_x), posicion_y(pos_y),
    largo(15), ancho(15),impacto(false), id_bala(id_bala), velocidad(velocidad), danio(10)

{
    
}

void Bala::actualizar_posicion(){
    posicion_x += velocidad;
}

void Bala::impactar(){
    this->impacto = true;
}


uint32_t Bala::obtener_id_bala() const{
    return id_bala;
}

uint32_t Bala::obtener_id_jugador() const{
    return id_jugador;
}

uint8_t Bala::obtener_codigo() const{
    return codigo_bala;
}

uint8_t Bala::obtener_ancho() const{
    return ancho;
}

uint8_t Bala::obtener_largo() const{
    return largo;
}

uint32_t Bala::obtener_posicionX() const{
    return posicion_x;
}

uint32_t Bala::obtener_posicionY() const{
    return posicion_y;
}

uint8_t Bala::obtener_danio() const{
    return danio;
}

bool Bala::obtener_impacto() const{
    return impacto;
}