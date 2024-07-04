#ifndef ANIMACION_SPAZ_HERIDO_H_
#define ANIMACION_SPAZ_HERIDO_H_

#include "../src/client_src/Animaciones/animacion.h"
#include "../src/client_src/direcciones.h"

class Animacion_Spaz_Herido : public Animacion {

   public:

   explicit Animacion_Spaz_Herido();

   ~Animacion_Spaz_Herido();

   void crear_texturas(SDL2pp::Renderer *render) override;
};

#endif