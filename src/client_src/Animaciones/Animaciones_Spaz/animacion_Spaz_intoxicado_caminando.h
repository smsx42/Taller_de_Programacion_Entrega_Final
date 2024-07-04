#ifndef ANIMACION_SPAZ_INTOXICADO_CAMINANDO_H_
#define ANIMACION_SPAZ_INTOXICADO_CAMINANDO_H_

#include "../src/client_src/Animaciones/animacion.h"
#include "../src/client_src/direcciones.h"

class Animacion_Spaz_Intoxicado_Caminando : public Animacion {

   public:
    
    explicit Animacion_Spaz_Intoxicado_Caminando();

    void crear_texturas(SDL2pp::Renderer *render) override;

    ~Animacion_Spaz_Intoxicado_Caminando();
};
#endif