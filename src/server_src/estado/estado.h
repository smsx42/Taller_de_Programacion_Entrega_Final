#ifndef ESTADO_H_
#define ESTADO_H_


#include "../personaje/personaje.h"
#include "../../common_src/codigo_estado.h"

class Personaje;


class Estado{
protected:
    Personaje *personaje;
    
    uint8_t codigo_estado;
public:

    explicit Estado(uint8_t codigo_estado);

    virtual ~Estado(){}

    virtual void asignarPersonaje(Personaje *personaje);

    virtual uint8_t obtener_estado();

    virtual void manejarEstado(uint8_t codigo_estado, double tiempo) = 0;

    virtual void actualizar(double tiempo) = 0;

};

#endif