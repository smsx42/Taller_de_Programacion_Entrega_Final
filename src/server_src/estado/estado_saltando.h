#ifndef ESTADO_SALTANDO_H_
#define ESTADO_SALTANDO_H_


#include "estado.h"


class EstadoSaltando : public Estado {
public:
    EstadoSaltando();  // Constructor si es necesario

    void manejarEstado(uint8_t codigo_estado, double tiempo) override;
    void actualizar(double tiempo) override;
};



#endif