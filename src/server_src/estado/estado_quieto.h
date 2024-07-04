#ifndef ESTADO_QUIETO_H_
#define ESTADO_QUIETO_H_


#include "estado.h"


class EstadoQuieto : public Estado {
public:
    EstadoQuieto();  // Constructor si es necesario

    void manejarEstado(uint8_t codigo_estado, double tiempo) override;
    void actualizar(double tiempo) override;
};



#endif