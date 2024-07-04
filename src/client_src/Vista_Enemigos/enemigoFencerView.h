#ifndef ENEMIGO_FENCER_VIEW_H_
#define ENEMIGO_FENCER_VIEW_H_

#include "enemigoView.h"

class EnemigoFencerView : public EnemigoView {

   public:

    explicit EnemigoFencerView(SDL2pp::Renderer *render);

    ~EnemigoFencerView();


};

#endif