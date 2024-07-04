#ifndef ANIMACION_FENCER_CAMINANDO_H_
#define ANIMACION_FENCER_CAMINANDO_H_

#include "../src/client_src/Animaciones/animacion.h"
#include "../src/client_src/direcciones.h"

class Animacion_Fencer_Caminando : public Animacion {

   public:

    explicit Animacion_Fencer_Caminando();

    ~Animacion_Fencer_Caminando();

    void crear_texturas(SDL2pp::Renderer *render) override;


};

#endif