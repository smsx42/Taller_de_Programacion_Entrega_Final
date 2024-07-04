#ifndef ANIMACION_JAZZMUERTE_H_
#define ANIMACION_JAZZ_MUERTE_H_

#include "../src/client_src/Animaciones/animacion.h"
#include "../src/client_src/direcciones.h"

class Animacion_Jazz_Muerte : public Animacion {

   public:

   explicit Animacion_Jazz_Muerte();

   ~Animacion_Jazz_Muerte();

   void crear_texturas(SDL2pp::Renderer *render) override;
};

#endif