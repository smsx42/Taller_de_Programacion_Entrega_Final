#ifndef PERSONAJE_VIEW_FACTORY_H_
#define PERSONAJE_VIEW_FACTORY_H_

#include "../src/client_src/Animaciones/animacion.h"
#include "../src/client_src/direcciones.h"
#include <map>

class PersonajeViewFactory {

   protected:

    std::map<std::string, std::unique_ptr<Animacion>> &animaciones;

   public:

    explicit PersonajeViewFactory(std::map<std::string, std::unique_ptr<Animacion>> &animaciones);

    virtual void crear_texturas(SDL2pp::Renderer *render);

    virtual std::unique_ptr<Animacion> crear_animacion(std::string const nombre_animacion) = 0;

    virtual void crear_animaciones_personaje();

    virtual ~PersonajeViewFactory();

     

};


#endif