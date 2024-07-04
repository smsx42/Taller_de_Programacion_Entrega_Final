#ifndef ANIMACION_RAT_LIZZARD_H_
#define ANIMACION_RAT_LIZZARD_H_

#include "../src/client_src/Animaciones/animacion.h"
#include "../src/client_src/direcciones.h"

class Animacion_Lizzard_Caminando : public Animacion {

   public:

    explicit Animacion_Lizzard_Caminando();

    ~Animacion_Lizzard_Caminando();

    void crear_texturas(SDL2pp::Renderer *render) override;


};

#endif