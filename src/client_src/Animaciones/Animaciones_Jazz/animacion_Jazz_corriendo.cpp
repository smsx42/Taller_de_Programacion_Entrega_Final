#include "animacion_Jazz_corriendo.h"

Animacion_Jazz_Corriendo::Animacion_Jazz_Corriendo() : Animacion() {}

void Animacion_Jazz_Corriendo::crear_texturas(SDL2pp::Renderer *render) {

    this->texturas = std::unique_ptr<SDL2pp::Texture>(new SDL2pp::Texture(this->crear_surface_y_texturas(PATH_JAZZ_CORRIENDO, render)));
    this->size_frame = 67.0F;
    this->cantidad_frames = texturas->GetWidth() / this->size_frame;
}

Animacion_Jazz_Corriendo::~Animacion_Jazz_Corriendo() {}