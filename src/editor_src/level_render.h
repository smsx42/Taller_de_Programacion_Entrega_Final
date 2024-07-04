#ifndef LEVELRENDER_H
#define LEVELRENDER_H

#include <QWidget>
#include <QStandardItemModel>
#include <QPixmap>
#include <QPainter>
#include <QMouseEvent>
#include <QHash>
#include <functional> 
#include <map>
#include <yaml-cpp/yaml.h>
#include <QBuffer>
#include <QFile>
#include <fstream>
#include <QTextStream>
#include <QDebug>

struct Tile {
    QPixmap pixmap;
    int blockSize;
    QString type;
    QString text;
};

struct BlockCoordinates {
    int x;
    int y;
    QString type;

    bool operator<(const BlockCoordinates &other) const {
        return (x < other.x) || (x == other.x && y < other.y);
    }
};

class LevelRenderer : public QWidget
{
    Q_OBJECT

public:
    explicit LevelRenderer(QStandardItemModel *tiles, QWidget *parent = nullptr);
    void setTilePixmap(const QPixmap &pixmap, int blockSize, QString blockType, QString blockText);
    void limpiarMapa();
    void saveToFile(const QString &filename) const;
    void loadFromFile(const QString &filename);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QMap<BlockCoordinates, QList<Tile>> tileMap;
    QPixmap m_tilePixmap;
    int currentBlockSize;
    QString currentBlockType;
    QString currentBlockText;
    QPoint scrollOffset;
    bool placingTiles;
    QPixmap m_backgroundPixmap;
    QString backgroundText;

    void placeTile(const QPoint &position);
    void removeTile(const QPoint &position);
};
#endif // LEVELRENDERER_H
