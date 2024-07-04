#ifndef OBJETO_ZANAHORIA_VIEW_H_
#define OBJETO_ZANAHORIA_VIEW_H_

#include "objetoView.h"

class ObjetoZanahoriaView : public ObjetoView {

   public:

    explicit ObjetoZanahoriaView(SDL2pp::Renderer *render);

    ~ObjetoZanahoriaView();
};

#endif