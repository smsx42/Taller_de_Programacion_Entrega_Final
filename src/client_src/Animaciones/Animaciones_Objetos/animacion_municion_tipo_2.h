#ifndef ANIMACION_MUNICION_TIPO_2_H_
#define ANIMACION_MUNICION_TIPO_2_H_

#include "../src/client_src/Animaciones/animacion.h"
#include "../src/client_src/direcciones.h"

class Animacion_municion_tipo_2 : public Animacion {
    
   public:
    
    explicit Animacion_municion_tipo_2();

    void crear_texturas(SDL2pp::Renderer *render) override;

    ~Animacion_municion_tipo_2();




};

#endif