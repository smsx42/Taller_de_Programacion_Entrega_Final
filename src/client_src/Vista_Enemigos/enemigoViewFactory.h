#ifndef Enemigo_FACTORY_H_
#define Enemigo_FACTORY_H_

#include "../src/client_src/Animaciones/Animaciones_Enemigos/animacion_Fencer_caminando.h"
#include "../src/client_src/Animaciones/Animaciones_Enemigos/animacion_Lizzard_caminando.h"
#include "../src/client_src/Animaciones/Animaciones_Enemigos/animacion_Rat_caminando.h"
#include "../src/client_src/Animaciones/Animaciones_Enemigos/animacion_Bruja_caminando.h"
#include "../src/client_src/Animaciones/Animaciones_Enemigos/animacion_Enemigo_desaparecer.h"
#include "../src/client_src/direcciones.h"
#include <map>

class EnemigoViewFactory {

   protected:

    std::map<std::string, std::unique_ptr<Animacion>> &animaciones;

   public:

   explicit EnemigoViewFactory(std::map<std::string, std::unique_ptr<Animacion>> &animaciones);

   virtual void crear_texturas(SDL2pp::Renderer *render);

   virtual std::unique_ptr<Animacion> crear_animacion_enemigo(std::string const nombre_enemigo);

   virtual ~EnemigoViewFactory(); 
};

#endif