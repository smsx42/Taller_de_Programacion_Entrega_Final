#ifndef ANIMACION_BRUJA_CAMINANDO_H_
#define ANIMACION_BRUJA_CAMINANDO_H_

#include "../src/client_src/Animaciones/animacion.h"
#include "../src/client_src/direcciones.h"

class Animacion_Bruja_Caminando : public Animacion {

   public:

    explicit Animacion_Bruja_Caminando();

    ~Animacion_Bruja_Caminando();

    void crear_texturas(SDL2pp::Renderer *render) override;


};

#endif