#ifndef ESTADO_CAMINANDO_H_
#define ESTADO_CAMINANDO_H_


#include "estado.h"


class EstadoCaminando : public Estado {
private:


public:

    EstadoCaminando();

    void manejarEstado(uint8_t codigo_estado, double tiempo) override;

    void actualizar(double tiempo) override;

};


#endif