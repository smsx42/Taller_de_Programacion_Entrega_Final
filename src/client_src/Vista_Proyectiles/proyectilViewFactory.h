#ifndef PROYECTIL_VIEW_FACTORY_H_
#define PROYECTIL_VIEW_FACTORY_H_

#include "../src/client_src/Animaciones/animacion.h"

#include "../src/common_src/evento.h"
#include "../src/common_src/codigo_objeto.h"

#include "../src/client_src/Animaciones/animacion.h"
#include "../src/client_src/Animaciones/Animaciones_Proyectiles/animacion_bala_pistola.h"
#include "../src/client_src/Animaciones/Animaciones_Proyectiles/animacion_proyectil_tipo_1.h"
#include "../src/client_src/Animaciones/Animaciones_Proyectiles/animacion_proyectil_tipo_2.h"
#include "../src/client_src/Animaciones/Animaciones_Proyectiles/animacion_proyectil_tipo_3.h"
#include "../src/client_src/direcciones.h"
#include <SDL2pp/Chunk.hh>
#include <SDL2pp/Mixer.hh>


class ProyectilViewFactory {

   private:

    std::unique_ptr<Animacion> &animacion;
    std::unique_ptr<SDL2pp::Chunk> &sonido;

   public:

    ProyectilViewFactory(std::unique_ptr<Animacion> &animacion, std::unique_ptr<SDL2pp::Chunk> &sonido);

    void crear_animaciones_sonidos(uint8_t tipo);

    void crear_texturas(SDL2pp::Renderer *render);

    ~ProyectilViewFactory();
};

#endif