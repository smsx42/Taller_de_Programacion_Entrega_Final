#ifndef ANIMACION_JAZZ_CAYENDO_HORIZONTAL_H_
#define ANIMACION_JAZZ_CAYENDO_HORIZONTAL_H_

#include "../src/client_src/Animaciones/animacion.h"
#include "../src/client_src/direcciones.h"

class Animacion_Jazz_Cayendo_Horizontal : public Animacion {

   public:

   explicit Animacion_Jazz_Cayendo_Horizontal();

   ~Animacion_Jazz_Cayendo_Horizontal();

   void crear_texturas(SDL2pp::Renderer *render) override;
};

#endif