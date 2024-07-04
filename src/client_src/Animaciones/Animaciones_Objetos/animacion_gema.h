#ifndef ANIMACION_GEMA_H_
#define ANIMACION_GEMA_H_

#include "../src/client_src/Animaciones/animacion.h"
#include "../src/client_src/direcciones.h"

class Animacion_Gema : public Animacion {

   public:

    explicit Animacion_Gema();

    void crear_texturas(SDL2pp::Renderer *render) override;

    ~Animacion_Gema();
};

#endif