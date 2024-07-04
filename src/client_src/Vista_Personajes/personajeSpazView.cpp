#include "personajeSpazView.h"

PersonajeSpazView::PersonajeSpazView(EventoPersonaje &evento, SDL2pp::Renderer *render) : PersonajeView(evento), factory(this->animaciones) {
    this->sonidos.insert(std::make_pair(GOLPE, std::make_unique<SDL2pp::Chunk>(PATH_SONIDO_GOLPE_3)));
    factory.crear_animaciones_personaje();
    factory.crear_texturas(render);
}

PersonajeSpazView::~PersonajeSpazView() {}