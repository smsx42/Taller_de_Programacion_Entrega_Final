#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QIcon>
#include <QDebug>
#include <QPushButton>
#include <QMessageBox>
#include <QDir>
#include <QComboBox>
#include "../client_src/lobby.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Lobby *lobby, QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_botonSalir_clicked();

    void on_botonCrear_clicked();

    void on_botonUnirse_clicked();

    void on_botonSpaz_clicked();

    void on_botonJazz_clicked();

    void on_botonLori_clicked();

    void on_botonInicio_clicked();

    void on_botonEmpezar_clicked();

    void on_listaPartidas_itemSelectionChanged();

    void on_botonUnirseEmpezar_clicked();

private:
    Ui::MainWindow *ui;

    void paintEvent(QPaintEvent *event) override{
        QPainter painter(this);
        QPixmap pixmap(":/res/images/imagen_fondo.png");
        painter.drawPixmap(0,0,width(),height(),pixmap);
    }

    void actualizarEstiloBotones();

    void on_ComboBoxMapas_activated(const QString& text);

    Lobby *lobby;

    CodigoAccion personaje_elegido;

    QString mapa_seleccionado;

    uint32_t id_partida;

};
#endif // MAINWINDOW_H
