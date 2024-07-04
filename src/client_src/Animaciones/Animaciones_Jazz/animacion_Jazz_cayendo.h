#ifndef ANIMACION_JAZZ_CAYENDO_H_
#define ANIMACION_JAZZ_CAYENDO_H_

#include "../src/client_src/Animaciones/animacion.h"
#include "../src/client_src/direcciones.h"

class Animacion_Jazz_Cayendo : public Animacion {

   public:

   explicit Animacion_Jazz_Cayendo();

   ~Animacion_Jazz_Cayendo();

   void crear_texturas(SDL2pp::Renderer *render) override;
};

#endif