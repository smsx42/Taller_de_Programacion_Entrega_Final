#ifndef ANIMACION_LORI_CAMINANDO_H_
#define ANIMACION_LORI_CAMINANDO_H_

#include "../src/client_src/Animaciones/animacion.h"
#include "../src/client_src/direcciones.h"

class Animacion_Lori_Caminando : public Animacion {

   public:

   explicit Animacion_Lori_Caminando();

   ~Animacion_Lori_Caminando();

   void crear_texturas(SDL2pp::Renderer *render) override;
};

#endif