#include "animacion_agarrar_objeto.h"

Animacion_Agarrar_Objeto::Animacion_Agarrar_Objeto() : Animacion() {}

void Animacion_Agarrar_Objeto::crear_texturas(SDL2pp::Renderer *render) {

    this->texturas = std::unique_ptr<SDL2pp::Texture>(new SDL2pp::Texture(this->crear_surface_y_texturas(PATH_EFECTO_OBJETO_AGARRAR, render)));
    this->size_frame = texturas->GetHeight();
    this->cantidad_frames = texturas->GetWidth() / this->size_frame;
}

Animacion_Agarrar_Objeto::~Animacion_Agarrar_Objeto() {}