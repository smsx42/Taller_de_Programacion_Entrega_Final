#ifndef OBJETO_MONEDA_VIEW_H_
#define OBJETO_MONEDA_VIEW_H_

#include "objetoView.h"

class ObjetoMonedaView : public ObjetoView {
    
   public:

    explicit ObjetoMonedaView(SDL2pp::Renderer *render);

    ~ObjetoMonedaView();
};

#endif