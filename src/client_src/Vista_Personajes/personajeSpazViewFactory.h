#ifndef PERSONAJE_SPAZ_VIEW_FACTORY_H_
#define PERSONAJE_SPAZ_VIEW_FACTORY_H_

#include "personajeViewFactory.h"
#include "../src/client_src/Animaciones/Animaciones_Spaz/animacion_Spaz_caminando.h"
#include "../src/client_src/Animaciones/Animaciones_Spaz/animacion_Spaz_corriendo.h"
#include "../src/client_src/Animaciones/Animaciones_Spaz/animacion_Spaz_quieto.h"
#include "../src/client_src/Animaciones/Animaciones_Spaz/animacion_Spaz_saltando.h"
#include "../src/client_src/Animaciones/Animaciones_Spaz/animacion_Spaz_saltando_horizontal.h"
#include "../src/client_src/Animaciones/Animaciones_Spaz/animacion_Spaz_disparo_quieto.h"
#include "../src/client_src/Animaciones/Animaciones_Spaz/animacion_Spaz_deja_disparo_quieto.h"
#include "../src/client_src/Animaciones/Animaciones_Spaz/animacion_Spaz_intoxicado_quieto.h"
#include "../src/client_src/Animaciones/Animaciones_Spaz/animacion_Spaz_intoxicado_caminando.h"
#include "../src/client_src/Animaciones/Animaciones_Spaz/animacion_Spaz_herido.h"
#include "../src/client_src/Animaciones/Animaciones_Spaz/animacion_Spaz_muerte.h"
#include "../src/client_src/Animaciones/Animaciones_Spaz/animacion_Spaz_habilidad.h"
#include "../src/client_src/Animaciones/Animaciones_Spaz/animacion_Spaz_cayendo.h"
#include "../src/client_src/Animaciones/Animaciones_Spaz/animacion_Spaz_cayendo_horizontal.h"
#include "../src/client_src/Animaciones/Animaciones_Spaz/animacion_Spaz_disparo_saltando.h"
#include "../src/client_src/Animaciones/Animaciones_Spaz/animacion_Spaz_tambalear.h"


class PersonajeSpazViewFactory : public PersonajeViewFactory {

   public: 
    
    PersonajeSpazViewFactory(std::map<std::string, std::unique_ptr<Animacion>> &animaciones);

    std::unique_ptr<Animacion> crear_animacion(std::string const nombre_animacion) override;

    ~PersonajeSpazViewFactory();
};

#endif