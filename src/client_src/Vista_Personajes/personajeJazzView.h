#ifndef PERSONAJE_JAZZ_VIEW_H_
#define PERSONAJE_JAZZ_VIEW_H_

#include "personajeView.h"
#include "personajeJazzViewFactory.h"



class PersonajeJazzView : public PersonajeView {

   private:

   PersonajeJazzViewFactory factory;

   public:
    
    PersonajeJazzView(EventoPersonaje &evento, SDL2pp::Renderer *render);


    ~PersonajeJazzView();

};

#endif