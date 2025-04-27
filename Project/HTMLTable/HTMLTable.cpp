#include "HTMLTable.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>

namespace Constants {
    const char TABLE_TAG[] = "<table>";
    const char TABLE_END_TAG[] = "</table>";
    const char TR_TAG[] = "<tr>";
    const char TR_END_TAG[] = "</tr>";
    const char TH_TAG[] = "<th>";
    const char TH_END_TAG[] = "</th>";
    const char TD_TAG[] = "<td>";
    const char TD_END_TAG[] = "</td>";
}

bool HTMLTable::containsString(const std::string& str, const std::string& substr) {
    return str.find(substr) != std::string::npos;
}

std::string HTMLTable::convertReferenceToLetter(const std::string& str) {
    std::string result;
    size_t pos = str.find("&#");
    if (pos != std::string::npos) {
        result = str.substr(0, pos);
        size_t numberStart = pos + 2;
        size_t numberEnd = str.find(';', numberStart);
        if (numberEnd != std::string::npos) {
            int ascii = std::stoi(str.substr(numberStart, numberEnd - numberStart));
            result += static_cast<char>(ascii);
            result += str.substr(numberEnd + 1);
        }
    }
    else {
        result = str;
    }
    return result;
}

size_t HTMLTable::numberOfCellsInRow(std::ifstream& ifs) {
    size_t currentPos = ifs.tellg();
    size_t count = 0;
    std::string line;
    while (std::getline(ifs, line)) {
        if (line.find("</tr>") != std::string::npos)
            break;
        if (line.find("<td>") != std::string::npos || line.find("<th>") != std::string::npos)
            count++;
    }
    ifs.clear();
    ifs.seekg(currentPos);
    return count;
}

bool HTMLTable::isHeaderTag(const std::string& tag) {
    return containsString(tag, "<th>");
}

std::string HTMLTable::trimTagContent(const std::string& tagContent) {
    size_t start = tagContent.find('>') + 1;
    size_t end = tagContent.rfind('<');
    if (start == std::string::npos || end == std::string::npos || start >= end)
        return "";
    return tagContent.substr(start, end - start);
}

void HTMLTable::parseFromFile(const std::string& filename) {
    std::ifstream ifs(filename);
    if (!ifs.is_open()) {
        std::cout << "Could not open file.\n";
        return;
    }

    std::string word;
    bool insideTable = false;
    while (ifs >> word) {
        if (word == Constants::TABLE_TAG) {
            insideTable = true;
        }
        else if (word == Constants::TABLE_END_TAG) {
            insideTable = false;
            break;
        }
        else if (insideTable && word == Constants::TR_TAG) {
            Row newRow;
            while (true) {
                ifs >> word;
                if (word == Constants::TR_END_TAG)
                    break;

                bool isHeader = isHeaderTag(word);
                std::string content = trimTagContent(word);
                content = convertReferenceToLetter(content);
                newRow.addCell(Cell(content, isHeader));
            }
            rows.push_back(newRow);
        }
    }
}

void HTMLTable::saveToFile(const std::string& filename) const {
    std::ofstream ofs(filename);
    if (!ofs.is_open()) {
        std::cout << "Could not save file.\n";
        return;
    }

    ofs << "<table>\n";
    for (const auto& row : rows) {
        ofs << "  <tr>\n";
        for (const auto& cell : row.cells) {
            ofs << "    ";
            ofs << (cell.isHeader ? "<th>" : "<td>") << cell.data << (cell.isHeader ? "</th>" : "</td>") << '\n';
        }
        ofs << "  </tr>\n";
    }
    ofs << "</table>";
}

void HTMLTable::print() const {
    std::priority_queue<size_t> columnWidth; //It's used for the formating of the table
    for (const auto& row : rows) {
        for (const auto& cell : row.cells) {
            columnWidth.push(cell.data.size()); //Calculating which cell is the longest so we can decide what the width would be
        }
    }

    for (const auto& row : rows) {
        for (const auto& cell : row.cells) {
            std::cout << '|';
            if (cell.isHeader) {
                std::cout << '*';
            }
            else {
                std::cout << ' ';
            }

            std::cout << cell.data;
            for (int i = 0; i < columnWidth.top() - cell.data.size(); i++)
                std::cout << ' ';

            if (cell.isHeader) {
                std::cout << '*';
            }
            else {
                std::cout << ' ';
            }
        }
        std::cout << "|\n";
    }
}

void HTMLTable::addRow(size_t index, const std::string& values) {
    if (index > rows.size())
        index = rows.size();

    Row newRow;
    std::stringstream ss(values);
    std::string value;
    while (std::getline(ss, value, ',')) {
        newRow.addCell(Cell(value, false));
    }
    rows.insert(rows.begin() + index, newRow);
    std::cout << "Row added successfully.\n";
}

void HTMLTable::removeRow(size_t index) {
    if (index >= rows.size()) 
        index = rows.size() - 1;

    rows.erase(rows.begin() + index);
    std::cout << "Row removed successfully.\n";
}

void HTMLTable::editCell(size_t row, size_t col, const std::string& value, bool isHeader) {
    if (row >= rows.size() || col >= rows[row].cells.size()) {
        std::cout << "Invalid row or column.\n";
        return;
    }
    rows[row].cells[col].data = value;
    if (isHeader) {
        rows[row].cells[col].isHeader = true;
    }
    else {
        rows[row].cells[col].isHeader = false;
    }
    std::cout << "Value edited successfully.\n";
}

bool HTMLTable::empty() const
{
    return rows.empty();
}
