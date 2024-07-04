#ifndef ANIMACION_LORI_HABILIDAD_H_
#define ANIMACION_LORI_HABILIDAD_H_

#include "../src/client_src/Animaciones/animacion.h"
#include "../src/client_src/direcciones.h"

class Animacion_Lori_Habilidad : public Animacion {

   public:

   explicit Animacion_Lori_Habilidad();

   ~Animacion_Lori_Habilidad();

   void crear_texturas(SDL2pp::Renderer *render) override;
};

#endif