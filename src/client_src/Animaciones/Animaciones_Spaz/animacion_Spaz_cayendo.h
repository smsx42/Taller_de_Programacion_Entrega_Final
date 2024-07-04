#ifndef ANIMACION_SPAZ_CAYENDO_H_
#define ANIMACION_SPAZ_CAYENDO_H_

#include "../src/client_src/Animaciones/animacion.h"
#include "../src/client_src/direcciones.h"

class Animacion_Spaz_Cayendo : public Animacion {

   public:

   explicit Animacion_Spaz_Cayendo();

   ~Animacion_Spaz_Cayendo();

   void crear_texturas(SDL2pp::Renderer *render) override;
};

#endif