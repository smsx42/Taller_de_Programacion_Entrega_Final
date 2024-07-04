#ifndef ANIMACION_SPAZ_QUIETO_H_
#define ANIMACION_SPAZ_QUIETO_H_

#include "../src/client_src/Animaciones/animacion.h"
#include "../src/client_src/direcciones.h"

class Animacion_Spaz_Quieto : public Animacion {

   public:

   explicit Animacion_Spaz_Quieto();

   ~Animacion_Spaz_Quieto();

   void crear_texturas(SDL2pp::Renderer *render) override;
};

#endif