#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , model(new QStandardItemModel(this))
    , main_widget(new QSplitter(Qt::Horizontal, this))  
    , scrollArea(new QScrollArea(this)) 
{
    ui->setupUi(this);
    ui->tilesListView->setModel(model);
    baseTileDirectory = "../src/mapas/tiles";

    scrollArea->setWidgetResizable(true); 

    levelRenderer = new LevelRenderer(model, this);
    scrollArea->setWidget(levelRenderer);

    main_widget->addWidget(ui->tilesListView);
    main_widget->addWidget(scrollArea);

    main_widget->setCollapsible(0, false);  
    main_widget->setSizes({200, 800});  

    setCentralWidget(main_widget);

    connect(ui->tilesListView->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &MainWindow::onItemSelectionChanged);

    cargarTiles(baseTileDirectory);

    setWindowTitle("EDITOR DE MAPAS JACK JAZZRABBIT 2");

    QToolBar *toolbar = new QToolBar(this);
    addToolBar(Qt::TopToolBarArea, toolbar);

    limpiarMapaAction = new QAction(tr("Limpiar Mapa"), this);
    connect(limpiarMapaAction, &QAction::triggered, this, &MainWindow::limpiarMapa);
    toolbar->addAction(limpiarMapaAction);

    guardarMapaAction = new QAction(tr("Guardar Mapa"), this);
    connect(guardarMapaAction, &QAction::triggered, this, &MainWindow::guardarMapa);
    toolbar->addAction(guardarMapaAction);

    leerMapaAction = new QAction(tr("Cargar Mapa"), this);
    connect(leerMapaAction, &QAction::triggered, this, &MainWindow::leerMapa);
    toolbar->addAction(leerMapaAction);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::cargarTilesSubdir(const QString &directoryPath)
{
    QDir dir(directoryPath);
    if (!dir.exists()) {
        qDebug() << "El directorio no existe:" << directoryPath;
        return;
    }

    dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    QFileInfoList subDirs = dir.entryInfoList();

    model->clear();

    if (directoryPath != baseTileDirectory) {
        QStandardItem *backItem = new QStandardItem("Volver Atrás");
        backItem->setEditable(false);
        backItem->setData(baseTileDirectory, Qt::UserRole);
        model->appendRow(backItem);
    }

    for (const QFileInfo &subDir : subDirs)
    {
        QStandardItem *sectionItem = new QStandardItem(subDir.fileName());
        sectionItem->setEditable(false);
        sectionItem->setData(subDir.filePath(), Qt::UserRole);
        sectionItem->setText(subDir.fileName()); 
        model->appendRow(sectionItem);
    }
}

void MainWindow::cargarTiles(const QString &directoryPath)
{
    QDir dir(directoryPath);
    if (!dir.exists()) {
        qDebug() << "El directorio no existe:" << directoryPath;
        return;
    }

    dir.setFilter(QDir::Files | QDir::NoDotAndDotDot);
    QFileInfoList tiles = dir.entryInfoList();

    model->clear();

    QStandardItem *backItem = new QStandardItem("Volver Atrás");
    backItem->setEditable(false);
    backItem->setData(baseTileDirectory, Qt::UserRole);
    backItem->setText("Volver Atrás");  
    model->appendRow(backItem);

    for (const QFileInfo &tile : tiles)
    {
        if (tile.suffix().toLower() == "png")
        {
            QStandardItem *tileItem = new QStandardItem();  
            tileItem->setEditable(false);
            
            //tileItem->setIcon(QIcon(tile.filePath()));
            
            QIcon icon(tile.filePath());
            QPixmap pixmap = icon.pixmap(QSize(64, 64)); 
            pixmap = pixmap.scaled(QSize(64, 64), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            tileItem->setIcon(QIcon(pixmap));
            
            QVariantMap itemData;
            itemData.insert("path", tile.filePath());
            itemData.insert("filename", tile.fileName());
            tileItem->setData(itemData, Qt::UserRole);
            model->appendRow(tileItem);
        }
    }
}

void MainWindow::onItemSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(deselected);

    QModelIndexList indexes = selected.indexes();
    if (!indexes.isEmpty())
    {
        QModelIndex index = indexes.first();

        if (index.isValid())
        {
            QString itemPath;
            QString itemText;
            QVariant itemData = index.data(Qt::UserRole);
            if (itemData.canConvert<QVariantMap>())
            {
                QVariantMap dataMap = itemData.toMap();
                itemPath = dataMap.value("path").toString();
                itemText = dataMap.value("filename").toString();

                qDebug() << "Path del archivo: " << itemPath;
                qDebug() << "Nombre del archivo: " << itemText;
                
            }else{
                itemText = index.data(Qt::DisplayRole).toString();  
                itemPath = index.data(Qt::UserRole).toString();
            }
        
            QString blockType = "solid";

            if (itemText == "Volver Atrás")
            {
                cargarTilesSubdir(itemPath);
            }
            else if (!itemPath.isEmpty() && QDir(itemPath).exists())
            {
                cargarTiles(itemPath);
            }
            else
            {
                selectedTilePixmap = QPixmap(itemPath);
                int blockSize = 50; // Ajusta esto según la lógica de tu aplicación
                qDebug() << "Item text: " << itemText;  // Verificar el texto
                qDebug() << "Item path: " << itemPath;  // Verificar el texto
                if (itemText.contains("zanahoria")) { // Suponiendo que el nombre del archivo contiene el tamaño
                    blockSize = 25;
                    blockType = "zanahoria";
                } else if (itemText.contains("gema")){
                    blockSize = 25;
                    blockType = "gema";
                } else if (itemText.contains("moneda")){
                    blockSize = 25;
                    blockType = "moneda";
                } else if (itemText.contains("municion_1")){
                    blockSize = 25;
                    blockType = "bala_veloz";
                } else if (itemText.contains("municion_2")){
                    blockSize = 25;
                    blockType = "cohete_rapido";
                } else if (itemText.contains("municion_3")){
                    blockSize = 25;
                    blockType = "cohete_toxico";
                } else if(itemText.contains("bloque")){
                    blockSize = 50;
                    blockType = "solid";
                } else if(itemText.contains("triangulo_izquierdo")){
                    blockSize = 50;
                    blockType = "triangulo_izquierdo";
                } else if (itemText.contains("triangulo_derecho")){
                    blockSize = 50;
                    blockType = "triangulo_derecho";
                } else if (itemText.contains("enemigo_bruja")){
                    blockSize = 50;
                    blockType = "bruja";
                } else if (itemText.contains("enemigo_lizzard")){
                    blockSize = 50;
                    blockType = "lizzard";
                } else if (itemText.contains("enemigo_fencer")){
                    blockSize = 50;
                    blockType = "fencer";
                } else if (itemText.contains("enemigo_rat")){
                    blockSize = 50;
                    blockType = "rat";
                } else if (itemText.contains("fondo")){
                    blockSize = 50;
                    blockType = "fondo";
                } else if(itemText.contains("spawn")){
                    blockSize = 50;
                    blockType = "spawn";
                } else if(itemText.contains("miscelaneo")){
                    blockSize = 50;
                    blockType = "miscelaneo";
                }



                levelRenderer->setTilePixmap(selectedTilePixmap, blockSize, blockType, itemPath);
            }
        }
    }
}



void MainWindow::limpiarMapa()
{
    levelRenderer->limpiarMapa(); 
}

void MainWindow::guardarMapa()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Guardar Mapa"), "", tr("Archivos de mapa (*.yaml)"));
    if (!fileName.isEmpty()) {
        if (!fileName.endsWith(".yaml", Qt::CaseInsensitive)) {
            fileName += ".yaml"; 
        }
        levelRenderer->saveToFile(fileName);
    }
}


void MainWindow::leerMapa()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Abrir Mapa"), "",
        tr("Archivos YAML (*.yaml);;Todos los archivos (*)"));

    if (fileName.isEmpty())
        return;

    // Asegurar que el archivo tenga la extensión .yaml
    if (!fileName.endsWith(".yaml", Qt::CaseInsensitive)) {
        QMessageBox::warning(this, tr("Error"), tr("El archivo seleccionado no es un archivo YAML (.yaml)."));
        return;
    }

    levelRenderer->loadFromFile(fileName);
}