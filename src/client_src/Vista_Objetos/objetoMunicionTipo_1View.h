#ifndef OBJETO_MUNICION_TIPO_1_VIEW_H_
#define OBJETO_MUNICION_TIPO_1_VIEW_H_

#include "objetoView.h"

class ObjetoMunicionTipo_1View : public ObjetoView {

   public:
    
    explicit ObjetoMunicionTipo_1View(SDL2pp::Renderer *render);

    ~ObjetoMunicionTipo_1View();
};
#endif
