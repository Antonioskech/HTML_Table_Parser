#pragma once
#include <vector>
#include "Cell.h"

class Row {
public:
    std::vector<Cell> cells;

    Row(size_t columns = 0) {
        cells.resize(columns);
    }

    void addCell(const Cell& cell) {
        cells.push_back(cell);
    }

    Cell& getCell(size_t index) {
        return cells.at(index);
    }
};
