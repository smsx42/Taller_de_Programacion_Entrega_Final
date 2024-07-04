#ifndef ANIMACION_RAT_CAMINANDO_H_
#define ANIMACION_RAT_CAMINANDO_H_

#include "../src/client_src/Animaciones/animacion.h"
#include "../src/client_src/direcciones.h"

class Animacion_Rat_Caminando : public Animacion {

   public:

    explicit Animacion_Rat_Caminando();

    ~Animacion_Rat_Caminando();

    void crear_texturas(SDL2pp::Renderer *render) override;


};

#endif