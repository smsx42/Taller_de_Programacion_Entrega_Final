#ifndef ESTADO_CORRIENDO_H_
#define ESTADO_CORRIENDO_H_


#include "estado.h"


class EstadoCorriendo : public Estado {
private:
   

public:

    EstadoCorriendo();

    void manejarEstado(uint8_t codigo_estado, double tiempo) override;

    void actualizar(double tiempo) override;

};


#endif