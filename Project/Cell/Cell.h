#pragma once
#include <string>

class Cell {
public:
    std::string data;
    bool isHeader;

    Cell(const std::string& data = "", bool isHeader = false)
        : data(data), isHeader(isHeader) {}
};
