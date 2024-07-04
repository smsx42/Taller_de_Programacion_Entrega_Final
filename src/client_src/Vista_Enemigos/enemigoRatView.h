#ifndef ENEMIGO_RAT_VIEW_H_
#define ENEMIGO_RAT_VIEW_H_

#include "../src/client_src/Animaciones/Animaciones_Enemigos/animacion_Rat_caminando.h"
#include "enemigoView.h"

class EnemigoRatView : public EnemigoView {

   public:

    explicit EnemigoRatView(SDL2pp::Renderer *render);

    ~EnemigoRatView();


};

#endif