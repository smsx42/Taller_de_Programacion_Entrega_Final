#include "animacion_Enemigo_desaparecer.h"

Animacion_Enemigo_Desaparecer::Animacion_Enemigo_Desaparecer() : Animacion() {}


void Animacion_Enemigo_Desaparecer::crear_texturas(SDL2pp::Renderer *render) {

    this->texturas = std::unique_ptr<SDL2pp::Texture>(new SDL2pp::Texture(this->crear_surface_y_texturas(PATH_DESAPARECER_ENEMIGO, render)));
    this->size_frame = texturas->GetHeight();
    this->cantidad_frames = texturas->GetWidth() / this->size_frame;
    
}

Animacion_Enemigo_Desaparecer::~Animacion_Enemigo_Desaparecer() {}