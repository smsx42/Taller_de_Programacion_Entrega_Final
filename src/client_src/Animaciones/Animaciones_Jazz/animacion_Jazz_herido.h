#ifndef ANIMACION_JAZZ_HERIDO_H_
#define ANIMACION_JAZZ_HERIDO_H_

#include "../src/client_src/Animaciones/animacion.h"
#include "../src/client_src/direcciones.h"

class Animacion_Jazz_Herido : public Animacion {

   public:

   explicit Animacion_Jazz_Herido();

   ~Animacion_Jazz_Herido();

   void crear_texturas(SDL2pp::Renderer *render) override;
};

#endif