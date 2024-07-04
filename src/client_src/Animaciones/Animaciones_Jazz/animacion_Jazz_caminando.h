#ifndef ANIMACION_JAZZ_CAMINANDO_H_
#define ANIMACION_JAZZ_CAMINANDO_H_

#include "../src/client_src/Animaciones/animacion.h"
#include "../src/client_src/direcciones.h"

class Animacion_Jazz_Caminando : public Animacion {

   public:

   explicit Animacion_Jazz_Caminando();

   ~Animacion_Jazz_Caminando();

   void crear_texturas(SDL2pp::Renderer *render) override;
};

#endif