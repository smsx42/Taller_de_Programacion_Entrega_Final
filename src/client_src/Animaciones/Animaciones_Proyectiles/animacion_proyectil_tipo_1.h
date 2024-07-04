#ifndef ANIMACION_PROYECTIL_TIPO_1_H_
#define ANIMACION_PROYECTIL_TIPO_1_H_

#include "../src/client_src/Animaciones/animacion.h"
#include "../src/client_src/direcciones.h"

class Animacion_Proyectil_Tipo_1 : public Animacion {

   public:

    explicit Animacion_Proyectil_Tipo_1();

    void crear_texturas(SDL2pp::Renderer *render) override;

    ~Animacion_Proyectil_Tipo_1();
};

#endif 