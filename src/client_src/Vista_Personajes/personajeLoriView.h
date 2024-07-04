#ifndef PERSONAJE_LORI_VIEW_H_
#define PERSONAJE_LORI_VIEW_H_

#include "personajeView.h"
#include "personajeLoriViewFactory.h"

class PersonajeLoriView : public PersonajeView {

   private:

    PersonajeLoriViewFactory factory;

   public:
    
    PersonajeLoriView(EventoPersonaje &evento, SDL2pp::Renderer *render);

    ~PersonajeLoriView();

};

#endif