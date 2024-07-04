#include <iostream>
#include <fstream>
#include <yaml-cpp/yaml.h>
#include <unordered_map>

#include "gridCell.h"


struct Coordinate {
    uint32_t x;
    uint32_t y;
};

using GrillaJuego = std::unordered_map<int32_t, std::unordered_map<int32_t, GridCell>>;

class Map {
public:
    Map(const std::string& yamlFile, uint32_t cell_size = 50) : cell_size(cell_size) {
        loadMapFromYAML(yamlFile);
        initializeGrid();
    }

    void loadMapFromYAML(const std::string& yamlFile) {
        YAML::Node mapNode = YAML::LoadFile(yamlFile);

        for (const auto& coord : mapNode["map_coordinates"]) {
            coordinates.push_back({ coord["x"].as<uint32_t>(), coord["y"].as<uint32_t>() });
        }
    }

    void printMapCoordinates() const {
        for (const auto& coord : coordinates) {
            std::cout << "x: " << coord.x << ", y: " << coord.y << std::endl;
        }
    }

    void initializeGrid() {
        for (const auto& coord : coordinates) {
            int32_t cell_x = coord.x / cell_size;
            int32_t cell_y = coord.y / cell_size;
            grid[cell_x][cell_y].tiene_objeto_solido = true; // Example: Mark cell as occupied
        }
    }

    // Example method to check if a cell is occupied
    bool isCellOccupied(int32_t x, int32_t y) const {
        int32_t cell_x = x / cell_size;
        int32_t cell_y = y / cell_size;
        if (grid.count(cell_x) > 0 && grid.at(cell_x).count(cell_y) > 0) {
            return grid.at(cell_x).at(cell_y).tiene_objeto_solido;
        }
        return false; // Default: cell is not occupied
    }

private:
    GrillaJuego grid;
    std::vector<Coordinate> coordinates;
    uint32_t cell_size;
};