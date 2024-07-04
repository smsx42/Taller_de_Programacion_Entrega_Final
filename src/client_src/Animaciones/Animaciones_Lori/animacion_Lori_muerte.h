#ifndef ANIMACION_LORI_MUERTE_H_
#define ANIMACION_LORI_MUERTE_H_

#include "../src/client_src/Animaciones/animacion.h"
#include "../src/client_src/direcciones.h"

class Animacion_Lori_Muerte : public Animacion {

   public:

   explicit Animacion_Lori_Muerte();

   ~Animacion_Lori_Muerte();

   void crear_texturas(SDL2pp::Renderer *render) override;
};

#endif