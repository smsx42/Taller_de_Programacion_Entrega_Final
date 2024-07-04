#include "objetoViewFactory.h"

ObjetoViewFactory::ObjetoViewFactory(std::map<std::string, std::unique_ptr<Animacion>> &animaciones) : animaciones(animaciones) {}

void ObjetoViewFactory::crear_animacion_objeto(std::string const nombre_objeto) {

    if(nombre_objeto == GEMA_OBJETO) {
        this->animaciones.insert(std::make_pair(Mostrar, std::make_unique<Animacion_Gema>()));
    } else if(nombre_objeto == MONEDA_OBJETO) {
        this->animaciones.insert(std::make_pair(Mostrar, std::make_unique<Animacion_Moneda>()));
    } else if(nombre_objeto == ZANAHORIA_OBJETO) {
        this->animaciones.insert(std::make_pair(Mostrar, std::make_unique<Animacion_Zanahoria>()));
    } else if(nombre_objeto == MUNICION_TIPO_1) {
        this->animaciones.insert(std::make_pair(Mostrar, std::make_unique<Animacion_municion_tipo_1>()));
    } else if(nombre_objeto == MUNICION_TIPO_2) {
        this->animaciones.insert(std::make_pair(Mostrar, std::make_unique<Animacion_municion_tipo_2>()));
    } else if(nombre_objeto == MUNICION_TIPO_3) {
        this->animaciones.insert(std::make_pair(Mostrar, std::make_unique<Animacion_municion_tipo_3>()));
    } 
    
    this->animaciones.insert(std::make_pair(AGARRAR, std::make_unique<Animacion_Agarrar_Objeto>()));

}

void ObjetoViewFactory::crear_texturas(SDL2pp::Renderer *render) {

    this->animaciones.at(Mostrar)->crear_texturas(render);
    this->animaciones.at(AGARRAR)->crear_texturas(render);
}

ObjetoViewFactory::~ObjetoViewFactory() {}