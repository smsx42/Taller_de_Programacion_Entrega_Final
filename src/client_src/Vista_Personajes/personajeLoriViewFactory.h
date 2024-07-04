#ifndef PERSONAJE_LORI_VIEW_FACTORY_H_
#define PERSONAJE_LORI_VIEW_FACTORY_H_

#include "personajeViewFactory.h"
#include "../src/client_src/Animaciones/Animaciones_Lori/animacion_Lori_caminando.h"
#include "../src/client_src/Animaciones/Animaciones_Lori/animacion_Lori_corriendo.h"
#include "../src/client_src/Animaciones/Animaciones_Lori/animacion_Lori_quieto.h"
#include "../src/client_src/Animaciones/Animaciones_Lori/animacion_Lori_saltando.h"
#include "../src/client_src/Animaciones/Animaciones_Lori/animacion_Lori_saltando_horizontal.h"
#include "../src/client_src/Animaciones/Animaciones_Lori/animacion_Lori_disparo_quieto.h"
#include "../src/client_src/Animaciones/Animaciones_Lori/animacion_Lori_deja_disparo_quieto.h"
#include "../src/client_src/Animaciones/Animaciones_Lori/animacion_Lori_intoxicado_quieto.h"
#include "../src/client_src/Animaciones/Animaciones_Lori/animacion_Lori_intoxicado_caminando.h"
#include "../src/client_src/Animaciones/Animaciones_Lori/animacion_Lori_herido.h"
#include "../src/client_src/Animaciones/Animaciones_Lori/animacion_Lori_muerte.h"
#include "../src/client_src/Animaciones/Animaciones_Lori/animacion_Lori_habilidad.h"
#include "../src/client_src/Animaciones/Animaciones_Lori/animacion_Lori_cayendo.h"
#include "../src/client_src/Animaciones/Animaciones_Lori/animacion_Lori_cayendo_horizontal.h"
#include "../src/client_src/Animaciones/Animaciones_Lori/animacion_Lori_disparo_saltando.h"
#include "../src/client_src/Animaciones/Animaciones_Lori/animacion_Lori_tambalear.h"


class PersonajeLoriViewFactory : public PersonajeViewFactory {

   public: 
    
    PersonajeLoriViewFactory(std::map<std::string, std::unique_ptr<Animacion>> &animaciones);

    std::unique_ptr<Animacion> crear_animacion(std::string const nombre_animacion) override;

    ~PersonajeLoriViewFactory();
};

#endif