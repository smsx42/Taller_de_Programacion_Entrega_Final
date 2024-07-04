#include "animacion_Spaz_corriendo.h"

Animacion_Spaz_Corriendo::Animacion_Spaz_Corriendo() : Animacion() {}

void Animacion_Spaz_Corriendo::crear_texturas(SDL2pp::Renderer *render) {
    
    this->texturas = std::unique_ptr<SDL2pp::Texture>(new SDL2pp::Texture(this->crear_surface_y_texturas(PATH_SPAZ_CORRIENDO, render)));
    this->size_frame = texturas->GetHeight();
    this->cantidad_frames = texturas->GetWidth() / this->size_frame;
}

Animacion_Spaz_Corriendo::~Animacion_Spaz_Corriendo() {}

