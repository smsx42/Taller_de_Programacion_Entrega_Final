#ifndef ANIMACION_JAZZ_HABILIDAD_H_
#define ANIMACION_JAZZ_HABILIDAD_H_

#include "../src/client_src/Animaciones/animacion.h"
#include "../src/client_src/direcciones.h"

class Animacion_Jazz_Habilidad : public Animacion {

   public:

   explicit Animacion_Jazz_Habilidad();

   ~Animacion_Jazz_Habilidad();

   void crear_texturas(SDL2pp::Renderer *render) override;
};

#endif