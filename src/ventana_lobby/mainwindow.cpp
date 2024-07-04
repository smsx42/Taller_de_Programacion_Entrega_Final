#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(Lobby *lobby, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , lobby(lobby)
{
    ui->setupUi(this);

    ui->listaPartidas->clear();
    //ui->listaPartidas->setRowCount(1);
    ui->listaPartidas->setColumnCount(3);
    QStringList encabezado;
    encabezado << "ID PARTIDA" << "ID CREADOR" << "SLOTS";

    

    ui->listaPartidas->setHorizontalHeaderLabels(encabezado);
    ui->listaPartidas->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->listaPartidas->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    
    ui->botonUnirseEmpezar->setVisible(false);

    ui->listaPartidas->setVisible(false);
    ui->botonInicio->setVisible(false);
    ui->cantidadJugadores->setVisible(false);
    ui->labelJugadores->setVisible(false);
    ui->botonEmpezar->setVisible(false);
    ui->labelMapa->setVisible(false);
    ui->seleccionMapas->setVisible(false);

    personaje_elegido = NINGUNO;

    QDir directory("../src/mapas");
    QStringList yamlFiles = directory.entryList(QStringList() << "*.yaml", QDir::Files);
    ui->seleccionMapas->clear(); // Limpiar el ComboBox si hay elementos previos
    for (const QString &archivo : yamlFiles) {
        QString nombreSinExtension = archivo;
        nombreSinExtension.chop(5); // Quitar los últimos 5 caracteres (.yaml)
        ui->seleccionMapas->addItem(nombreSinExtension);
    }
    connect(ui->seleccionMapas, QOverload<const QString&>::of(&QComboBox::textActivated),
        this, &MainWindow::on_ComboBoxMapas_activated);

    mapa_seleccionado = ui->seleccionMapas->currentText();

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_botonSalir_clicked()
{
    close();
}


void MainWindow::on_botonCrear_clicked()
{

    if(personaje_elegido == NINGUNO){
        QMessageBox::warning(this, "Crear partida", "Seleccione su personaje antes de crear la partida");
    }else{
        ui->listaPartidas->setVisible(false);
        ui->botonInicio->setVisible(true);
        ui->botonSpaz->setVisible(false);
        ui->botonJazz->setVisible(false);
        ui->botonLori->setVisible(false);
        ui->botonCrear->setVisible(false);
        ui->botonUnirse->setVisible(false);
        ui->botonSalir->setVisible(false);
        ui->botonUnirseEmpezar->setVisible(false);
        ui->cantidadJugadores->setVisible(true);
        ui->labelJugadores->setVisible(true);
        ui->botonEmpezar->setVisible(true);
        ui->labelMapa->setVisible(true);
    ui->seleccionMapas->setVisible(true);

    }



}


void MainWindow::on_botonUnirse_clicked()
{
    if(personaje_elegido == NINGUNO){
        QMessageBox::warning(this, "Unirse a partida", "Seleccione su personaje antes de unirse a una partida");
    }else{
        ui->listaPartidas->setVisible(true);
        ui->botonInicio->setVisible(true);
        ui->botonUnirseEmpezar->setVisible(true);
        ui->botonSpaz->setVisible(false);
        ui->botonJazz->setVisible(false);
        ui->botonLori->setVisible(false);
        ui->botonCrear->setVisible(false);
        ui->botonUnirse->setVisible(false);
        ui->botonSalir->setVisible(false);
        ui->cantidadJugadores->setVisible(false);
        ui->labelJugadores->setVisible(false);
        ui->botonEmpezar->setVisible(false);
        ui->labelMapa->setVisible(false);
        ui->seleccionMapas->setVisible(false);

        std::vector<InfoPartida> info_partidas = lobby->obtener_partidas();
        ui->listaPartidas->setRowCount(info_partidas.size());
        int fila = 0;
        for(InfoPartida p : info_partidas){
            QTableWidgetItem *itemPartida = new QTableWidgetItem(QString::number(p.id_partida));
            QTableWidgetItem *itemCreador = new QTableWidgetItem(QString::number(p.id_creador));
            QTableWidgetItem *itemCantJugadores = new QTableWidgetItem(QString("%1/%2").arg(p.jugadores).arg(p.max_jugadores));

            
            itemPartida->setTextAlignment(Qt::AlignCenter);
            itemCreador->setTextAlignment(Qt::AlignCenter);
            itemCantJugadores->setTextAlignment(Qt::AlignCenter);


            ui->listaPartidas->setItem(fila,0,itemPartida);
            ui->listaPartidas->setItem(fila,1,itemCreador);
            ui->listaPartidas->setItem(fila,2,itemCantJugadores);


            fila++;
        }
    }

}


void MainWindow::on_botonSpaz_clicked()
{
    personaje_elegido = SPAZ;
    actualizarEstiloBotones();
    ui->botonSpaz->setStyleSheet(
        "QPushButton {"
        " border-image: url(:/res/images/Spaz.png);"
        " background-color: qradialgradient(spread:repeat, cx:0.5, cy:0.5, radius:0.077, fx:0.5, fy:0.5, stop:0 rgba(0, 169, 255, 147), stop:0.497326 rgba(0, 0, 0, 147), stop:1 rgba(0, 169, 255, 147));"
        "}"

        );
}


void MainWindow::on_botonJazz_clicked()
{
    personaje_elegido = JAZZ;
    actualizarEstiloBotones();
    ui->botonJazz->setStyleSheet(
        "QPushButton {"
        " border-image: url(:/res/images/Jazz.png);"
        " background-color: qradialgradient(spread:repeat, cx:0.5, cy:0.5, radius:0.077, fx:0.5, fy:0.5, stop:0 rgba(0, 169, 255, 147), stop:0.497326 rgba(0, 0, 0, 147), stop:1 rgba(0, 169, 255, 147));"
        "}"

        );
}


void MainWindow::on_botonLori_clicked()
{
    personaje_elegido = LORI;
    actualizarEstiloBotones();
    ui->botonLori->setStyleSheet(
        "QPushButton {"
        " border-image: url(:/res/images/Lori.png);"
        " background-color: qradialgradient(spread:repeat, cx:0.5, cy:0.5, radius:0.077, fx:0.5, fy:0.5, stop:0 rgba(0, 169, 255, 147), stop:0.497326 rgba(0, 0, 0, 147), stop:1 rgba(0, 169, 255, 147));"
        "}"

        );
}

void MainWindow::actualizarEstiloBotones()
{
    ui->botonSpaz->setStyleSheet(
        "QPushButton {"
        " border-image: url(:/res/images/Spaz_no_seleccionado.png);"
        "}"

        );

    ui->botonJazz->setStyleSheet(
        "QPushButton {"
        " border-image: url(:/res/images/Jazz_no_seleccionado.png);"
        "}"

        );

    ui->botonLori->setStyleSheet(
        "QPushButton {"
        " border-image: url(:/res/images/Lori_no_seleccionado.png);"
        "}"

        );
}

void MainWindow::on_botonInicio_clicked()
{
    ui->listaPartidas->setVisible(false);
    ui->botonInicio->setVisible(false);
    ui->cantidadJugadores->setVisible(false);
    ui->labelJugadores->setVisible(false);
    ui->botonEmpezar->setVisible(false);
    ui->botonUnirseEmpezar->setVisible(false);
    ui->labelMapa->setVisible(false);
    ui->seleccionMapas->setVisible(false);
    ui->botonSpaz->setVisible(true);
    ui->botonJazz->setVisible(true);
    ui->botonLori->setVisible(true);
    ui->botonCrear->setVisible(true);
    ui->botonUnirse->setVisible(true);
    ui->botonSalir->setVisible(true);

}


void MainWindow::on_botonEmpezar_clicked()
{
    
    uint8_t max_jugadores = (uint8_t)ui->cantidadJugadores->text().toInt();
    if(lobby->crear_partida(max_jugadores, mapa_seleccionado.toStdString())){
        lobby->definir_mapa(mapa_seleccionado.toStdString());
        lobby->elegir_personaje(personaje_elegido);
        close();
    }else{
        QMessageBox::warning(this, "Crear partida", "Error al crear la partida, intentelo nuevamente");
    }
}

void MainWindow::on_listaPartidas_itemSelectionChanged(){
    QList<QTableWidgetItem*> itemsSeleccionados = ui->listaPartidas->selectedItems();
    if (!itemsSeleccionados.isEmpty()) {
        QTableWidgetItem *itemSeleccionado = itemsSeleccionados.first();
        int fila = itemSeleccionado->row();
        QTableWidgetItem *itemIDPartida = ui->listaPartidas->item(fila, 0); // Suponiendo que la columna 0 es la del ID de la partida
        if (itemIDPartida) {
            id_partida = (uint32_t)itemIDPartida->text().toInt();
        }
    }
}


void MainWindow::on_botonUnirseEmpezar_clicked(){
    QList<QTableWidgetItem*> itemsSeleccionados = ui->listaPartidas->selectedItems();
    if (!itemsSeleccionados.isEmpty()) {
    std::string nombre_mapa; 
    if(lobby->unirse_partida(id_partida, nombre_mapa)){
        lobby->definir_mapa(nombre_mapa);
        lobby->elegir_personaje(personaje_elegido);
        close();
    }else{
        QMessageBox::warning(this, "Unirse a partida", "Error al unirse a la partida, intentelo nuevamente");
    }
    }else{
        QMessageBox::warning(this, "Unirse a partida", "Error, seleccione una partida");
    }
}

void MainWindow::on_ComboBoxMapas_activated(const QString& text)
{
    
    mapa_seleccionado = text;
}