#ifndef ANIMACION_JAZZ_TAMBALEAR_H_
#define ANIMACION_JAZZ_TAMBALEAR_H_

#include "../src/client_src/Animaciones/animacion.h"
#include "../src/client_src/direcciones.h"

class Animacion_Jazz_Tambalear : public Animacion {

   public:

   explicit Animacion_Jazz_Tambalear();

   ~Animacion_Jazz_Tambalear();

   void crear_texturas(SDL2pp::Renderer *render) override;
};

#endif