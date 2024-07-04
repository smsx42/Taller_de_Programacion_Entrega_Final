#ifndef ANIMACION_SPAZ_MUERTE_H_
#define ANIMACION_SPAZ_MUERTE_H_

#include "../src/client_src/Animaciones/animacion.h"
#include "../src/client_src/direcciones.h"

class Animacion_Spaz_Muerte : public Animacion {

   public:

   explicit Animacion_Spaz_Muerte();

   ~Animacion_Spaz_Muerte();

   void crear_texturas(SDL2pp::Renderer *render) override;
};

#endif