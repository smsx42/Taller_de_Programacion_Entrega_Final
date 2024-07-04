#ifndef ESTADO_TAMBALEAR_H_
#define ESTADO_TAMBALEAR_H_


#include "estado.h"


class EstadoTambalear : public Estado {
public:
    EstadoTambalear(); 

    void manejarEstado(uint8_t codigo_estado, double tiempo) override;
    void actualizar(double tiempo) override;
};



#endif