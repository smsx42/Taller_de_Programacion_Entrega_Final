#include "proyectilViewFactory.h"

ProyectilViewFactory::ProyectilViewFactory(std::unique_ptr<Animacion> &animacion, std::unique_ptr<SDL2pp::Chunk> &sonido) 
: animacion(animacion), sonido(sonido) {}

void ProyectilViewFactory::crear_animaciones_sonidos(uint8_t tipo_bala) {
    
    
    switch (tipo_bala)
    {
    case CodigoObjeto::BALA_VELOZ:
        this->animacion = std::unique_ptr<Animacion_Proyectil_Tipo_1>(new Animacion_Proyectil_Tipo_1());
        this->sonido = std::make_unique<SDL2pp::Chunk>(PATH_SONIDO_PROYECTIL_2);
        this->sonido->SetVolume(30);
        break;
    case CodigoObjeto::COHETE_RAPIDO:
        this->animacion = std::unique_ptr<Animacion_Proyectil_Tipo_2>(new Animacion_Proyectil_Tipo_2());
        this->sonido = std::make_unique<SDL2pp::Chunk>(PATH_SONIDO_PROYECTIL_3);
        this->sonido->SetVolume(70);
        break;
    case CodigoObjeto::COHETE_TOXICO:
        this->animacion = std::unique_ptr<Animacion_Proyectil_Tipo_3>(new Animacion_Proyectil_Tipo_3());
        this->sonido = std::make_unique<SDL2pp::Chunk>(PATH_SONIDO_PROYECTIL_6);
        this->sonido->SetVolume(50);
        break;
    default:
        this->animacion = std::unique_ptr<Animacion_Bala_Pistola>(new Animacion_Bala_Pistola());
        this->sonido = std::make_unique<SDL2pp::Chunk>(PATH_SONIDO_PROYECTIL_1);
        break;
    }
}

void ProyectilViewFactory::crear_texturas(SDL2pp::Renderer *render) {
    this->animacion->crear_texturas(render); 
}

ProyectilViewFactory::~ProyectilViewFactory() {}