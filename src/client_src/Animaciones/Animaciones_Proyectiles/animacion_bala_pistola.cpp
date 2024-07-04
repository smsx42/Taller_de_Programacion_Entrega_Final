#include "animacion_bala_pistola.h"

Animacion_Bala_Pistola::Animacion_Bala_Pistola() : Animacion() {}

void Animacion_Bala_Pistola::crear_texturas(SDL2pp::Renderer *render) {

    this->texturas = std::unique_ptr<SDL2pp::Texture> (new SDL2pp::Texture(crear_surface_y_texturas(PATH_PROYECTIL_PISTOLA, render)));
    this->set_size_frames_y_cantida_frames();
}

Animacion_Bala_Pistola::~Animacion_Bala_Pistola() {}