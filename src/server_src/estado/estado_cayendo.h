#ifndef ESTADO_CAYENDO_H_
#define ESTADO_CAYENDO_H_

#include "estado.h"


class EstadoCayendo : public Estado {
public:
    EstadoCayendo();  // Constructor si es necesario

    void manejarEstado(uint8_t codigo_estado, double tiempo) override;
    void actualizar(double tiempo) override;
};



#endif