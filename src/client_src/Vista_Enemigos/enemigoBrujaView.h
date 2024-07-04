#ifndef ENEMIGO_BRUJA_VIEW_H_
#define ENEMIGO_BRUJA_VIEW_H_

#include "enemigoView.h"

class EnemigoBrujaView : public EnemigoView {

   public:

    explicit EnemigoBrujaView(SDL2pp::Renderer *render);

    ~EnemigoBrujaView();


};

#endif