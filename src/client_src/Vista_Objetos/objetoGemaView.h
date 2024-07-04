#ifndef OBJETO_GEMA_VIEW_H_
#define OBJETO_GEMA_VIEW_H_

#include "objetoView.h"

class ObjetoGemaView : public ObjetoView {

   public:

    explicit ObjetoGemaView(SDL2pp::Renderer *render);

    ~ObjetoGemaView();
};

#endif