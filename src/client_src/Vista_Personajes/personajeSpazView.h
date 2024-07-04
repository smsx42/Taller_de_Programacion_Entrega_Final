#ifndef PERSONAJE_SPAZ_VIEW_H_
#define PERSONAJE_SPAZ_VIEW_H_

#include "personajeView.h"
#include "personajeSpazViewFactory.h"

class PersonajeSpazView : public PersonajeView {

   private:

    PersonajeSpazViewFactory factory;

   public:
    
    PersonajeSpazView(EventoPersonaje &evento, SDL2pp::Renderer *render);

    ~PersonajeSpazView();

};

#endif