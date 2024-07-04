#include <iostream>
#include <string>
#include "lobby.h"
#include "cliente.h"
#include <SDL2pp/SDL.hh>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/Mixer.hh>
#include <SDL2pp/Music.hh>
#include <SDL2/SDL.h>
#include <QApplication>
#include <QWidget>
#include "../ventana_lobby/mainwindow.h"


int main(int argc, char* argv[]) {
    try {
        if (argc == 3) {
            
            SDL2pp::SDL(SDL_INIT_AUDIO);
            SDL2pp::Mixer reproductor(44100, MIX_DEFAULT_FORMAT, 2, 4096);
            SDL2pp::Music musica_menu(PATH_MUSICA_MENU);
            reproductor.PlayMusic(musica_menu, -1);

            // Inicio app
            QApplication app(argc,argv);
            
            

            // Creo el lobby
            const std::string hostname = std::string(argv[1]);
            const std::string servname = std::string(argv[2]);
            Lobby lobby(hostname,servname);

            // Creo el mainwindow

            MainWindow mainWindow(&lobby);
            mainWindow.show();
            


            if(app.exec()){
                lobby.close();
                throw std::runtime_error("ERROR");
            }
            Mix_CloseAudio();
            SDL_Quit();            
            std::string mapa = lobby.devolver_mapa();
            Cliente cliente(lobby.obtener_socket(), mapa);
            cliente.comunicarse_con_el_servidor();
            //lobby.close();
            //cliente.comunicarse_con_el_servidor();
            //lobby.main();

            return 0;
        } else {
            std::cerr << "Bad program call. Expected " << argv[0] << " <hostname> <servername>"
                      << std::endl;
            return 1;
        }
    } catch (const std::exception& err) {
        std::cerr << "Something went wrong and an exception was caught: " << err.what()
                  << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught." << std::endl;
        return 1;
    }
}
