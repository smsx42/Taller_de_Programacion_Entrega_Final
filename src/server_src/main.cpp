#include <iostream>

#include "../common_src/socket.h"

#include "servidor.h"
#include "configuracion.h"

int main(int argc, char* argv[]) {
    try {
        if (argc >= 2) {
            if (argc == 2){
                Configuracion::loadConfig(false);
            }
            else{
                Configuracion::loadConfig(true);
                std::cout << "Cheats enabled" << std::endl;
            }
            Servidor servidor(argv[1]);
            servidor.run();
            Configuracion::destroyConfig();
            return 0;
        } else {
            std::cerr << "Bad program call. Expected " << argv[0] << " <servername>" << std::endl;
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
