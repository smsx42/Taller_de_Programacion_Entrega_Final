#ifndef ESTADO_ESPECIAL_H_
#define ESTADO_ESPECIAL_H_


#include "estado.h"


class EstadoEspecial : public Estado {
private:
  

public:

    EstadoEspecial();

    void manejarEstado(uint8_t codigo_estado, double tiempo) override;

    void actualizar(double tiempo) override;

};


#endif