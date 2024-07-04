#include "level_render.h"

LevelRenderer::LevelRenderer(QStandardItemModel *tiles, QWidget *parent)
    : QWidget(parent), currentBlockSize(50), placingTiles(false)
{
    setFixedSize(2000, 2000);  
    scrollOffset = QPoint(0, 0);  
    backgroundText = "../src/mapas/tiles/background/beach_fondo.png";
}

void LevelRenderer::setTilePixmap(const QPixmap &pixmap, int blockSize, QString blockType, QString blockText)
{
    if (blockType == "fondo"){
        m_backgroundPixmap = pixmap;
        backgroundText = blockText;
    } else {
        m_tilePixmap = pixmap;
        currentBlockSize = blockSize; 
        currentBlockType = blockType;
    }
    currentBlockText = blockText;
    update();
}

void LevelRenderer::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    if (!m_backgroundPixmap.isNull())
    {
        painter.drawPixmap(0, 0, width(), height(), m_backgroundPixmap);
    }

    QRect visibleRect(scrollOffset, QSize(width(), height()));

    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine));
    for (int x = scrollOffset.x() % currentBlockSize; x < width(); x += currentBlockSize)
    {
        painter.drawLine(x, 0, x, height());
    }
    for (int y = scrollOffset.y() % currentBlockSize; y < height(); y += currentBlockSize)
    {
        painter.drawLine(0, y, width(), y);
    }

    for (auto it = tileMap.begin(); it != tileMap.end(); ++it)
    {
        BlockCoordinates coords = it.key();
        QList<Tile> tiles = it.value();

        for (const Tile &tile : tiles)
        {
            QRect rect(coords.x * tile.blockSize - scrollOffset.x(),
                       coords.y * tile.blockSize - scrollOffset.y(),
                       tile.blockSize, tile.blockSize);

            if (rect.intersects(visibleRect))
            {
                painter.drawRect(rect);
                painter.drawPixmap(rect, tile.pixmap);
            }
        }
    }
}

void LevelRenderer::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && !m_tilePixmap.isNull())
    {
        placeTile(event->pos());
        placingTiles = true;
    }
    else if (event->button() == Qt::RightButton)
    {
        removeTile(event->pos());
        placingTiles = true;
    }
}

void LevelRenderer::mouseMoveEvent(QMouseEvent *event)
{
    if (placingTiles && event->buttons() & Qt::LeftButton && !m_tilePixmap.isNull())
    {
        placeTile(event->pos());
    }
    else if (placingTiles && event->buttons() & Qt::RightButton)
    {
        removeTile(event->pos());
    }
}

void LevelRenderer::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton || event->button() == Qt::RightButton)
    {
        placingTiles = false;
    }
}


void LevelRenderer::placeTile(const QPoint &position)
{
    int x = (position.x() + scrollOffset.x()) / currentBlockSize;
    int y = (position.y() + scrollOffset.y()) / currentBlockSize;
    BlockCoordinates coords = { x, y };

    if (!tileMap.contains(coords))
    {
        QList<Tile> newList;
        tileMap.insert(coords, newList);
    }

    bool yaExiste = false;
    for (const Tile &tile : tileMap[coords])
    {
        if (tile.blockSize == currentBlockSize && tile.type != "miscelaneo")
        {
            yaExiste = true;
            break;
        }

        if(tile.type == "miscelaneo" && currentBlockType == "miscelaneo" && currentBlockText == tile.text){
            yaExiste = true;
        }
    }

    if (!yaExiste)
    {
        Tile nuevoTile = { m_tilePixmap, currentBlockSize,currentBlockType, currentBlockText};
        tileMap[coords].append(nuevoTile);
        update();
    }
}

void LevelRenderer::removeTile(const QPoint &position)
{
    int x = (position.x() + scrollOffset.x()) / currentBlockSize;
    int y = (position.y() + scrollOffset.y()) / currentBlockSize;
    BlockCoordinates coords = { x, y };

    if (tileMap.contains(coords))
    {
        for (int i = tileMap[coords].size() - 1; i >= 0; --i)
        {
            if (tileMap[coords][i].blockSize == currentBlockSize)
            {
                tileMap[coords].removeAt(i);
                break;
            }
        }

        if (tileMap[coords].isEmpty())
        {
            tileMap.remove(coords);
        }

        update();
    }
}

void LevelRenderer::limpiarMapa()
{
    tileMap.clear(); 
    update();  
}

void LevelRenderer::saveToFile(const QString &fileName) const
{
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;

    emitter << YAML::Key << "miscelaneo" << YAML::Value << YAML::BeginSeq;
    for (auto it = tileMap.begin(); it != tileMap.end(); ++it)
    {
        BlockCoordinates coords = it.key();
        QList<Tile> tiles = it.value(); 

        for (const Tile &tile : tiles)
        {
            if (tile.type == "miscelaneo")
            {
                emitter << YAML::BeginMap;
                emitter << YAML::Key << "x" << YAML::Value << coords.x*50;
                emitter << YAML::Key << "y" << YAML::Value << coords.y*50;
                emitter << YAML::Key << "width" << YAML::Value << 50;
                emitter << YAML::Key << "height" << YAML::Value << 50;
                emitter << YAML::Key << "imagen" << YAML::Value << tile.text.toStdString();
                emitter << YAML::EndMap;
            }
        }
    }
    emitter << YAML::EndSeq;

    // Sección para bloques 'solid'
    emitter << YAML::Key << "solid" << YAML::Value << YAML::BeginSeq;
    for (auto it = tileMap.begin(); it != tileMap.end(); ++it)
    {
        BlockCoordinates coords = it.key();
        QList<Tile> tiles = it.value(); 

        for (const Tile &tile : tiles)
        {
            if (tile.type == "solid")
            {
                emitter << YAML::BeginMap;
                emitter << YAML::Key << "x" << YAML::Value << coords.x*50;
                emitter << YAML::Key << "y" << YAML::Value << coords.y*50;
                emitter << YAML::Key << "width" << YAML::Value << 50;
                emitter << YAML::Key << "height" << YAML::Value << 50;
                emitter << YAML::Key << "imagen" << YAML::Value << tile.text.toStdString();
                emitter << YAML::EndMap;
            }
        }
    }
    emitter << YAML::EndSeq;


    emitter << YAML::Key << "triangulo_izquierdo" << YAML::Value << YAML::BeginSeq;
    for (auto it = tileMap.begin(); it != tileMap.end(); ++it)
    {
        BlockCoordinates coords = it.key();
        QList<Tile> tiles = it.value(); 

        for (const Tile &tile : tiles)
        {
            if (tile.type == "triangulo_izquierdo")
            {
                emitter << YAML::BeginMap;
                emitter << YAML::Key << "x" << YAML::Value << coords.x*50;
                emitter << YAML::Key << "y" << YAML::Value << coords.y*50;
                emitter << YAML::Key << "width" << YAML::Value << 50;
                emitter << YAML::Key << "height" << YAML::Value << 50;
                emitter << YAML::Key << "imagen" << YAML::Value << tile.text.toStdString();
                emitter << YAML::EndMap;
            }
        }
    }
    emitter << YAML::EndSeq;

    emitter << YAML::Key << "triangulo_derecho" << YAML::Value << YAML::BeginSeq;
    for (auto it = tileMap.begin(); it != tileMap.end(); ++it)
    {
        BlockCoordinates coords = it.key();
        QList<Tile> tiles = it.value(); 

        for (const Tile &tile : tiles)
        {
            if (tile.type == "triangulo_derecho")
            {
                emitter << YAML::BeginMap;
                emitter << YAML::Key << "x" << YAML::Value << coords.x*50;
                emitter << YAML::Key << "y" << YAML::Value << coords.y*50;
                emitter << YAML::Key << "width" << YAML::Value << 50;
                emitter << YAML::Key << "height" << YAML::Value << 50;
                emitter << YAML::Key << "imagen" << YAML::Value << tile.text.toStdString();
                emitter << YAML::EndMap;
            }
        }
    }
    emitter << YAML::EndSeq;

    emitter << YAML::Key << "zanahoria" << YAML::Value << YAML::BeginSeq;
    for (auto it = tileMap.begin(); it != tileMap.end(); ++it)
    {
        BlockCoordinates coords = it.key();
        QList<Tile> tiles = it.value();

        for (const Tile &tile : tiles)
        {
            if (tile.type == "zanahoria")
            {
                bool veneno = tile.text.contains("envenenada") ? true : false;
                emitter << YAML::BeginMap;
                emitter << YAML::Key << "x" << YAML::Value << coords.x*25;
                emitter << YAML::Key << "y" << YAML::Value << coords.y*25;
                emitter << YAML::Key << "veneno" << YAML::Value << veneno;
                emitter << YAML::EndMap;
            }
        }
    }
    emitter << YAML::EndSeq;

    emitter << YAML::Key << "gema" << YAML::Value << YAML::BeginSeq;
    for (auto it = tileMap.begin(); it != tileMap.end(); ++it)
    {
        BlockCoordinates coords = it.key();
        QList<Tile> tiles = it.value(); 

        for (const Tile &tile : tiles)
        {
            if (tile.type == "gema")
            {
               bool veneno = tile.text.contains("envenenada") ? true : false;
                emitter << YAML::BeginMap;
                emitter << YAML::Key << "x" << YAML::Value << coords.x*25;
                emitter << YAML::Key << "y" << YAML::Value << coords.y*25;
                emitter << YAML::Key << "veneno" << YAML::Value << veneno;
                emitter << YAML::EndMap;
            }
        }
    }
    emitter << YAML::EndSeq;

    emitter << YAML::Key << "moneda" << YAML::Value << YAML::BeginSeq;
    for (auto it = tileMap.begin(); it != tileMap.end(); ++it)
    {
        BlockCoordinates coords = it.key();
        QList<Tile> tiles = it.value(); 

        for (const Tile &tile : tiles)
        {
            if (tile.type == "moneda")
            {
                bool veneno = tile.text.contains("envenenada") ? true : false;
                emitter << YAML::BeginMap;
                emitter << YAML::Key << "x" << YAML::Value << coords.x*25;
                emitter << YAML::Key << "y" << YAML::Value << coords.y*25;
                emitter << YAML::Key << "veneno" << YAML::Value << veneno;
                emitter << YAML::EndMap;
            }
        }
    }
    emitter << YAML::EndSeq;

    emitter << YAML::Key << "bala_veloz" << YAML::Value << YAML::BeginSeq;
    for (auto it = tileMap.begin(); it != tileMap.end(); ++it)
    {
        BlockCoordinates coords = it.key();
        QList<Tile> tiles = it.value(); 

        for (const Tile &tile : tiles)
        {
            if (tile.type == "bala_veloz")
            {
                emitter << YAML::BeginMap;
                emitter << YAML::Key << "x" << YAML::Value << coords.x*25;
                emitter << YAML::Key << "y" << YAML::Value << coords.y*25;
                emitter << YAML::EndMap;
            }
        }
    }
    emitter << YAML::EndSeq;

    emitter << YAML::Key << "cohete_rapido" << YAML::Value << YAML::BeginSeq;
    for (auto it = tileMap.begin(); it != tileMap.end(); ++it)
    {
        BlockCoordinates coords = it.key();
        QList<Tile> tiles = it.value(); 

        for (const Tile &tile : tiles)
        {
            if (tile.type == "cohete_rapido")
            {
                emitter << YAML::BeginMap;
                emitter << YAML::Key << "x" << YAML::Value << coords.x*25;
                emitter << YAML::Key << "y" << YAML::Value << coords.y*25;
                emitter << YAML::EndMap;
            }
        }
    }
    emitter << YAML::EndSeq;

    emitter << YAML::Key << "cohete_toxico" << YAML::Value << YAML::BeginSeq;
    for (auto it = tileMap.begin(); it != tileMap.end(); ++it)
    {
        BlockCoordinates coords = it.key();
        QList<Tile> tiles = it.value(); 

        for (const Tile &tile : tiles)
        {
            if (tile.type == "cohete_toxico")
            {
                emitter << YAML::BeginMap;
                emitter << YAML::Key << "x" << YAML::Value << coords.x*25;
                emitter << YAML::Key << "y" << YAML::Value << coords.y*25;
                emitter << YAML::EndMap;
            }
        }
    }
    emitter << YAML::EndSeq;

    emitter << YAML::Key << "bruja" << YAML::Value << YAML::BeginSeq;
    for (auto it = tileMap.begin(); it != tileMap.end(); ++it)
    {
        BlockCoordinates coords = it.key();
        QList<Tile> tiles = it.value(); 

        for (const Tile &tile : tiles)
        {
            if (tile.type == "bruja")
            {
                emitter << YAML::BeginMap;
                emitter << YAML::Key << "x" << YAML::Value << coords.x*50;
                emitter << YAML::Key << "y" << YAML::Value << coords.y*50;
                emitter << YAML::EndMap;
            }
        }
    }
    emitter << YAML::EndSeq;

    emitter << YAML::Key << "lizzard" << YAML::Value << YAML::BeginSeq;
    for (auto it = tileMap.begin(); it != tileMap.end(); ++it)
    {
        BlockCoordinates coords = it.key();
        QList<Tile> tiles = it.value(); 

        for (const Tile &tile : tiles)
        {
            if (tile.type == "lizzard")
            {
                emitter << YAML::BeginMap;
                emitter << YAML::Key << "x" << YAML::Value << coords.x*50;
                emitter << YAML::Key << "y" << YAML::Value << coords.y*50;
                emitter << YAML::EndMap;
            }
        }
    }
    emitter << YAML::EndSeq;

    emitter << YAML::Key << "fencer" << YAML::Value << YAML::BeginSeq;
    for (auto it = tileMap.begin(); it != tileMap.end(); ++it)
    {
        BlockCoordinates coords = it.key();
        QList<Tile> tiles = it.value(); 

        for (const Tile &tile : tiles)
        {
            if (tile.type == "fencer")
            {
                emitter << YAML::BeginMap;
                emitter << YAML::Key << "x" << YAML::Value << coords.x*50;
                emitter << YAML::Key << "y" << YAML::Value << coords.y*50;
                emitter << YAML::EndMap;
            }
        }
    }
    emitter << YAML::EndSeq;

    emitter << YAML::Key << "rat" << YAML::Value << YAML::BeginSeq;
    for (auto it = tileMap.begin(); it != tileMap.end(); ++it)
    {
        BlockCoordinates coords = it.key();
        QList<Tile> tiles = it.value(); 

        for (const Tile &tile : tiles)
        {
            if (tile.type == "rat")
            {
                emitter << YAML::BeginMap;
                emitter << YAML::Key << "x" << YAML::Value << coords.x*50;
                emitter << YAML::Key << "y" << YAML::Value << coords.y*50+20;
                emitter << YAML::EndMap;
            }
        }
    }
    emitter << YAML::EndSeq;

    emitter << YAML::Key << "spawn" << YAML::Value << YAML::BeginSeq;
    for (auto it = tileMap.begin(); it != tileMap.end(); ++it)
    {
        BlockCoordinates coords = it.key();
        QList<Tile> tiles = it.value(); 

        for (const Tile &tile : tiles)
        {
            if (tile.type == "spawn")
            {
                emitter << YAML::BeginMap;
                emitter << YAML::Key << "x" << YAML::Value << coords.x*50;
                emitter << YAML::Key << "y" << YAML::Value << coords.y*50;
                emitter << YAML::EndMap;
            }
        }
    }
    emitter << YAML::EndSeq;

    emitter << YAML::Key << "fondo" << YAML::Value << backgroundText.toStdString();

    emitter << YAML::EndMap;

    std::ofstream fout(fileName.toStdString(), std::ios::out | std::ios::trunc);
    if (!fout.is_open()) {
        qDebug() << "No se puede abrir el archivo para escritura:" << fileName;
        return;
    }
    fout << emitter.c_str();
    fout.close();

}

void LevelRenderer::loadFromFile(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open file for reading:" << filename;
        return;
    }

    QTextStream stream(&file);
    QString yamlContent = stream.readAll();
    file.close();

    YAML::Node node = YAML::Load(yamlContent.toStdString());
    tileMap.clear();


    // Cargar bloques 'miscelaneo'
    const auto& miscelaneoBlocks = node["miscelaneo"];
    if (miscelaneoBlocks.IsSequence())
    {
        for (const auto& blockNode : miscelaneoBlocks)
        {
            int x = blockNode["x"].as<int>();
            int y = blockNode["y"].as<int>();
            QString imagen = QString::fromStdString(blockNode["imagen"].as<std::string>());
            BlockCoordinates coords = { x / 50, y / 50 }; 
            Tile tile = { QPixmap(imagen), 50, "miscelaneo", imagen };

            tileMap[coords].append(tile);
        }
    }

    // Cargar bloques 'solid'
    const auto& solidBlocks = node["solid"];
    if (solidBlocks.IsSequence())
    {
        for (const auto& blockNode : solidBlocks)
        {
            int x = blockNode["x"].as<int>();
            int y = blockNode["y"].as<int>();
            QString imagen = QString::fromStdString(blockNode["imagen"].as<std::string>());

            BlockCoordinates coords = { x / 50, y / 50 }; 
            Tile tile = { QPixmap(imagen), 50, "solid", imagen };

            tileMap[coords].append(tile);
        }
    }

    // Cargar bloques 'triangulo_izquierdo'
    const auto& triangleLeftBlocks = node["triangulo_izquierdo"];
    if (triangleLeftBlocks.IsSequence())
    {
        for (const auto& blockNode : triangleLeftBlocks)
        {
            int x = blockNode["x"].as<int>();
            int y = blockNode["y"].as<int>();
            QString imagen = QString::fromStdString(blockNode["imagen"].as<std::string>());

            BlockCoordinates coords = { x / 50, y / 50 };  
            Tile tile = { QPixmap(imagen), 50, "triangulo_izquierdo", imagen };

            tileMap[coords].append(tile);
        }
    }

    // Cargar bloques 'triangulo_derecho'
    const auto& triangleRightBlocks = node["triangulo_derecho"];
    if (triangleRightBlocks.IsSequence())
    {
        for (const auto& blockNode : triangleRightBlocks)
        {
            int x = blockNode["x"].as<int>();
            int y = blockNode["y"].as<int>();
            QString imagen = QString::fromStdString(blockNode["imagen"].as<std::string>());

            BlockCoordinates coords = { x / 50, y / 50 };  
            Tile tile = { QPixmap(imagen), 50, "triangulo_derecho", imagen };

            tileMap[coords].append(tile);
        }
    }

    // Cargar bloques 'zanahoria'
    const auto& carrotBlocks = node["zanahoria"];
    if (carrotBlocks.IsSequence())
    {
        for (const auto& blockNode : carrotBlocks)
        {
            int x = blockNode["x"].as<int>();
            int y = blockNode["y"].as<int>();
            bool veneno = blockNode["veneno"].as<bool>();
            QString imagen;
            imagen = QString::fromStdString("../src/mapas/tiles/items/zanahoria.png");
            if(veneno){
                imagen = QString::fromStdString("../src/mapas/tiles/items/zanahoria_envenenada.png");
            }
            BlockCoordinates coords = { x / 25, y / 25 };  
            Tile tile = { QPixmap(imagen), 25, "zanahoria", imagen };
            tileMap[coords].append(tile);
        }
    }

    // Cargar bloques 'gema'
    const auto& gemBlocks = node["gema"];
    if (gemBlocks.IsSequence())
    {
        for (const auto& blockNode : gemBlocks)
        {
            int x = blockNode["x"].as<int>();
            int y = blockNode["y"].as<int>();
            bool veneno = blockNode["veneno"].as<bool>();
            QString imagen;
            imagen = QString::fromStdString("../src/mapas/tiles/items/gema.png");
            if(veneno){
                imagen = QString::fromStdString("../src/mapas/tiles/items/gema_envenenada.png");
            }
            BlockCoordinates coords = { x / 25, y / 25 };  
            Tile tile = { QPixmap(imagen), 25, "gema", imagen };
            tileMap[coords].append(tile);
        }
    }

    // Cargar bloques 'moneda'
    const auto& coinBlocks = node["moneda"];
    if (coinBlocks.IsSequence())
    {
        for (const auto& blockNode : coinBlocks)
        {
            int x = blockNode["x"].as<int>();
            int y = blockNode["y"].as<int>();
            bool veneno = blockNode["veneno"].as<bool>();
            QString imagen;
            imagen = QString::fromStdString("../src/mapas/tiles/items/moneda.png");
            if(veneno){
                imagen = QString::fromStdString("../src/mapas/tiles/items/moneda_envenenada.png");
            }
            BlockCoordinates coords = { x / 25, y / 25 };  
            Tile tile = { QPixmap(imagen), 25, "moneda", imagen };
            tileMap[coords].append(tile);
        }
    }

    // Cargar bloques 'bala_veloz'
    const auto& fastBulletBlocks = node["bala_veloz"];
    if (fastBulletBlocks.IsSequence())
    {
        for (const auto& blockNode : fastBulletBlocks)
        {
            int x = blockNode["x"].as<int>();
            int y = blockNode["y"].as<int>();
            QString imagen = QString::fromStdString("../src/mapas/tiles/items/municion_1.png");
            BlockCoordinates coords = { x / 25, y / 25 };  
            Tile tile = { QPixmap(imagen), 25, "bala_veloz", imagen };
            tileMap[coords].append(tile);
        }
    }

    // Cargar bloques 'cohete_rapido'
    const auto& fastRocketBlocks = node["cohete_rapido"];
    if (fastRocketBlocks.IsSequence())
    {
        for (const auto& blockNode : fastRocketBlocks)
        {
            int x = blockNode["x"].as<int>();
            int y = blockNode["y"].as<int>();
            QString imagen = QString::fromStdString("../src/mapas/tiles/items/municion_2.png");
            BlockCoordinates coords = { x / 25, y / 25 };  
            Tile tile = { QPixmap(imagen), 25, "cohete_rapido", imagen };
            tileMap[coords].append(tile);
        }
    }

    const auto& coheteToxicoNode = node["cohete_toxico"];
    if (coheteToxicoNode.IsSequence())
    {
        for (const auto& blockNode : coheteToxicoNode)
        {
            int x = blockNode["x"].as<int>();
            int y = blockNode["y"].as<int>();
            QString imagen = QString::fromStdString("../src/mapas/tiles/items/municion_3.png");
            BlockCoordinates coords = { x / 25, y / 25 };  
            Tile tile = { QPixmap(imagen), 25, "cohete_toxico", imagen };
            tileMap[coords].append(tile);
        }
    }

    // Cargar bloques 'bruja'
    const auto& witchBlocks = node["bruja"];
    if (witchBlocks.IsSequence())
    {
        for (const auto& blockNode : witchBlocks)
        {
            int x = blockNode["x"].as<int>();
            int y = blockNode["y"].as<int>();
            QString imagen = QString::fromStdString("../src/mapas/tiles/enemigos/enemigo_bruja.png");
            BlockCoordinates coords = { x / 50, y / 50 };  
            Tile tile = { QPixmap(imagen), 50, "bruja", imagen };
            tileMap[coords].append(tile);
        }
    }

    // Cargar bloques 'lizzard'
    const auto& lizardBlocks = node["lizzard"];
    if (lizardBlocks.IsSequence())
    {
        for (const auto& blockNode : lizardBlocks)
        {
            int x = blockNode["x"].as<int>();
            int y = blockNode["y"].as<int>();
            QString imagen = QString::fromStdString("../src/mapas/tiles/enemigos/enemigo_lizzard.png");
            BlockCoordinates coords = { x / 50, y / 50 };  
            Tile tile = { QPixmap(imagen), 50, "lizzard", imagen };
            tileMap[coords].append(tile);
        }
    }

    // Cargar bloques 'fencer'
    const auto& fencerBlocks = node["fencer"];
    if (fencerBlocks.IsSequence())
    {
        for (const auto& blockNode : fencerBlocks)
        {
            int x = blockNode["x"].as<int>();
            int y = blockNode["y"].as<int>();
            QString imagen = QString::fromStdString("../src/mapas/tiles/enemigos/enemigo_fencer.png");
            BlockCoordinates coords = { x / 50, y / 50 };  
            Tile tile = { QPixmap(imagen), 50, "fencer", imagen };
            tileMap[coords].append(tile);
        }
    }

    // Cargar bloques 'rat'
    const auto& ratBlocks = node["rat"];
    if (ratBlocks.IsSequence())
    {
        for (const auto& blockNode : ratBlocks)
        {
            int x = blockNode["x"].as<int>();
            int y = blockNode["y"].as<int>() - 20;  
            QString imagen = QString::fromStdString("../src/mapas/tiles/enemigos/enemigo_rat.png");
            BlockCoordinates coords = { x / 50, y / 50 };  
            Tile tile = { QPixmap(imagen), 50, "rat", imagen };
            tileMap[coords].append(tile);
        }
    }

    // Cargar bloques 'spawn'
    const auto& spawnBlocks = node["spawn"];
    if (spawnBlocks.IsSequence())
    {
        for (const auto& blockNode : spawnBlocks)
        {
            int x = blockNode["x"].as<int>();
            int y = blockNode["y"].as<int>();
            QString imagen = QString::fromStdString("../src/mapas/tiles/spawn/spawn_jugador.png");
            BlockCoordinates coords = { x / 50, y / 50 }; 
            Tile tile = { QPixmap(imagen), 50, "spawn", imagen };

            tileMap[coords].append(tile);
        }
    }


    // Cargar fondo
    if (node["fondo"])
    {
        backgroundText = QString::fromStdString(node["fondo"].as<std::string>());
        m_backgroundPixmap = QPixmap(backgroundText);
    }

    update();
}
