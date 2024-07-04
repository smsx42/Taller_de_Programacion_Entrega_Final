#include "camara.h"

Camara::Camara(int x_inicial, int y_inicial, int ancho, int alto): camara(x_inicial, y_inicial, ancho, alto){}

void Camara::actualizar_posicion(int x, int y) {
    camara.SetX(x +20/2- camara.GetW()/2.0);
    camara.SetY(y +20/2- camara.GetH()/2.0);
}

int Camara::obtener_posicion_x() {
    return camara.GetX();
}

int Camara::obtener_posicion_y() {
    return camara.GetY();
}


void Camara::definir_posicion_x(int x) {
    camara.SetX(x);
}

void Camara::definir_posicion_y(int y) {
    camara.SetY(y);
}