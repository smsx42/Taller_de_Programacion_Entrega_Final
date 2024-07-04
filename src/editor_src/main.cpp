#include "mainwindow.h"
#include <iostream>
#include <filesystem>
#include <QApplication>
#include <QWidget>

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    try {
        if (argc == 1) {
            // Inicio app
            QApplication app(argc,argv);

            MainWindow mainWindow;
            mainWindow.show();
            


            if(app.exec()){
                //throw std::runtime_error("ERROR");
            }


            return 0;
        } else {
            std::cerr << "Bad program call. Expected " << argv[0] << std::endl;
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
