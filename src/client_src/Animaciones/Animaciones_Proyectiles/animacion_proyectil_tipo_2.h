#ifndef ANIMACION_PROYECTIL_TIPO_2_H_
#define ANIMACION_PROYECTIL_TIPO_2_H_

#include "../src/client_src/Animaciones/animacion.h"
#include "../src/client_src/direcciones.h"

class Animacion_Proyectil_Tipo_2 : public Animacion {

   public:

    explicit Animacion_Proyectil_Tipo_2();

    void crear_texturas(SDL2pp::Renderer *render) override;

    ~Animacion_Proyectil_Tipo_2();
};

#endif 