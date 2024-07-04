#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QFileInfo>
#include <QDebug>
#include <QListWidgetItem>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QSplitter>
#include <QScrollArea>
#include <QPushButton>
#include <QToolBar>
#include <QAction>
#include <QFileDialog>
#include "level_render.h"
#include <fstream>
#include <QMessageBox>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onItemSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;
    QString baseTileDirectory;
    QGraphicsScene *scene;
    LevelRenderer *levelRenderer;
    QSplitter *main_widget;
    QPixmap selectedTilePixmap;
    QScrollArea *scrollArea;

    QAction *limpiarMapaAction;
    QAction *guardarMapaAction;
    QAction *leerMapaAction;

    void cargarTiles(const QString &directoryPath);
    void cargarTilesSubdir(const QString &subfolderPath);

    void limpiarMapa();
    void guardarMapa();
    void leerMapa();
};

#endif // MAINWINDOW_H
