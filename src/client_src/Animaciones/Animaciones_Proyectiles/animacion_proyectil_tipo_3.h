#ifndef ANIMACION_PROYECTIL_TIPO_3_H_
#define ANIMACION_PROYECTIL_TIPO_3_H_

#include "../src/client_src/Animaciones/animacion.h"
#include "../src/client_src/direcciones.h"

class Animacion_Proyectil_Tipo_3 : public Animacion {

   public:

    explicit Animacion_Proyectil_Tipo_3();

    void crear_texturas(SDL2pp::Renderer *render) override;

    ~Animacion_Proyectil_Tipo_3();
};

#endif 