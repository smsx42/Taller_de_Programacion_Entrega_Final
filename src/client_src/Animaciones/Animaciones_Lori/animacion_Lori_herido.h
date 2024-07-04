#ifndef ANIMACION_LORI_HERIDO_H_
#define ANIMACION_LORI_HERIDO_H_

#include "../src/client_src/Animaciones/animacion.h"
#include "../src/client_src/direcciones.h"

class Animacion_Lori_Herido : public Animacion {

   public:

   explicit Animacion_Lori_Herido();

   ~Animacion_Lori_Herido();

   void crear_texturas(SDL2pp::Renderer *render) override;
};

#endif