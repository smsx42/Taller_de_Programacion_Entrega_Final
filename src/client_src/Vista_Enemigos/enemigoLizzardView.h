#ifndef ENEMIGO_LIZZARD_VIEW_H_
#define ENEMIGO_LIZZARD_VIEW_H_

#include "../src/client_src/Animaciones/Animaciones_Enemigos/animacion_Lizzard_caminando.h"
#include "enemigoView.h"

class EnemigoLizzardView : public EnemigoView {

   public:

    explicit EnemigoLizzardView(SDL2pp::Renderer *render);

    ~EnemigoLizzardView();


};

#endif