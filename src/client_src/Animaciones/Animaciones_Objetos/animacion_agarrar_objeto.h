#ifndef ANIMACION_AGARRAR_OBJETO_H_
#define ANIMACION_AGARRAR_OBJETO_H_

#include "../src/client_src/Animaciones/animacion.h"
#include "../src/client_src/direcciones.h"

class Animacion_Agarrar_Objeto : public Animacion {

   public:

    explicit Animacion_Agarrar_Objeto();

    void crear_texturas(SDL2pp::Renderer *render) override;

    ~Animacion_Agarrar_Objeto();
};

#endif