#ifndef OBJETO_VIEW_H_
#define OBJETO_VIEW_H_

#include "../src/client_src/Animaciones/animacion.h"
#include "../src/common_src/evento.h"
#include "objetoViewFactory.h"
#include <SDL2pp/Chunk.hh>
#include <SDL2pp/Mixer.hh>


class ObjetoView {

   protected:
    
    int posicion_x;
    int posicion_y;
    int widht;
    int height;
    std::map<std::string, std::unique_ptr<Animacion>> animaciones;
    std::unique_ptr<SDL2pp::Chunk> sonido;
    ObjetoViewFactory factory;
    bool mostrarse;
    int contador_agarres;

   public:

    explicit ObjetoView();

    virtual bool mostrandose();

    virtual void actualizar_vista_objeto(EventoObjeto &evento, float df);

    virtual void renderizar_objeto(std::unique_ptr<SDL2pp::Renderer> &render, int cam_x, int cam_y);
    
    virtual void reproducir_audio_objeto(std::unique_ptr<SDL2pp::Mixer> &reproductor_audio);

    virtual ~ObjetoView();
};

#endif