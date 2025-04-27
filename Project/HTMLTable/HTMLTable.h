#pragma once
#include <vector>
#include <string>
#include "Row.h"

class HTMLTable {
private:
    std::vector<Row> rows;

public:
    HTMLTable() = default;

    void parseFromFile(const std::string& filename);
    void saveToFile(const std::string& filename) const;
    void print() const;
    void addRow(size_t index, const std::string& values);
    void removeRow(size_t index);
    void editCell(size_t row, size_t col, const std::string& value, bool isHeader);
    bool empty() const;

private:
    bool containsString(const std::string& str, const std::string& substr);
    std::string convertReferenceToLetter(const std::string& str);
    size_t numberOfCellsInRow(std::ifstream& ifs);
    bool isHeaderTag(const std::string& tag);
    std::string trimTagContent(const std::string& tagContent);
};
