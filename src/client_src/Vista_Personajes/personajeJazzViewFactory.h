#ifndef PERSONAJE_JAZZ_VIEW_FACTORY_H_
#define PERSONAJE_JAZZ_VIEW_FACTORY_H_

#include "personajeViewFactory.h"
#include "../src/client_src/Animaciones/Animaciones_Jazz/animacion_Jazz_caminando.h"
#include "../src/client_src/Animaciones/Animaciones_Jazz/animacion_Jazz_corriendo.h"
#include "../src/client_src/Animaciones/Animaciones_Jazz/animacion_Jazz_quieto.h"
#include "../src/client_src/Animaciones/Animaciones_Jazz/animacion_Jazz_saltando.h"
#include "../src/client_src/Animaciones/Animaciones_Jazz/animacion_Jazz_saltando_horizontal.h"
#include "../src/client_src/Animaciones/Animaciones_Jazz/animacion_Jazz_disparo_quieto.h"
#include "../src/client_src/Animaciones/Animaciones_Jazz/animacion_Jazz_deja_disparo_quieto.h"
#include "../src/client_src/Animaciones/Animaciones_Jazz/animacion_Jazz_intoxicado_quieto.h"
#include "../src/client_src/Animaciones/Animaciones_Jazz/animacion_Jazz_intoxicado_caminando.h"
#include "../src/client_src/Animaciones/Animaciones_Jazz/animacion_Jazz_herido.h"
#include "../src/client_src/Animaciones/Animaciones_Jazz/animacion_Jazz_muerte.h"
#include "../src/client_src/Animaciones/Animaciones_Jazz/animacion_Jazz_habilidad.h"
#include "../src/client_src/Animaciones/Animaciones_Jazz/animacion_Jazz_cayendo.h"
#include "../src/client_src/Animaciones/Animaciones_Jazz/animacion_Jazz_cayendo_horizontal.h"
#include "../src/client_src/Animaciones/Animaciones_Jazz/animacion_Jazz_disparo_saltando.h"
#include "../src/client_src/Animaciones/Animaciones_Jazz/animacion_Jazz_tambalear.h"


class PersonajeJazzViewFactory : public PersonajeViewFactory {

   public: 
    
    PersonajeJazzViewFactory(std::map<std::string, std::unique_ptr<Animacion>> &animaciones);

    std::unique_ptr<Animacion> crear_animacion(std::string const nombre_animacion) override;

    ~PersonajeJazzViewFactory();

    


    
};

#endif