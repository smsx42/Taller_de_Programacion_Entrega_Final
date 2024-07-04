#ifndef ANIMACION_LORI_CORRIENDO_H_
#define ANIMACION_LORI_CORRIENDO_H_

#include "../src/client_src/Animaciones/animacion.h"
#include "../src/client_src/direcciones.h"

class Animacion_Lori_Corriendo : public Animacion {

   public:

   explicit Animacion_Lori_Corriendo();

   ~Animacion_Lori_Corriendo();

   void crear_texturas(SDL2pp::Renderer *render) override;
};

#endif