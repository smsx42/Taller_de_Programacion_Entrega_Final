#ifndef ANIMACION_LORI_CAYENDO_H_
#define ANIMACION_LORI_CAYENDO_H_

#include "../src/client_src/Animaciones/animacion.h"
#include "../src/client_src/direcciones.h"

class Animacion_Lori_Cayendo : public Animacion {

   public:

   explicit Animacion_Lori_Cayendo();

   ~Animacion_Lori_Cayendo();

   void crear_texturas(SDL2pp::Renderer *render) override;
};

#endif