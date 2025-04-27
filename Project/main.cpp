#include <iostream>
#include "HTMLTable.h"

namespace Commands {
    const char ADD_ROW[] = "add";
    const char EDIT_VALUE[] = "edit";
    const char REMOVE_ROW[] = "remove";
    const char PRINT_TABLE[] = "print";
    const char SAVE_TABLE[] = "save";
    const char EXIT[] = "exit";
}

int main() {
    HTMLTable table;
    //Write the name of the txt file you want to use
    table.parseFromFile("html2.txt");

    if (!table.empty()) {
        std::cout << "Table parsed successfully.\n";
        std::cout << "Write down one of the following commands you want: add, remove, edit, print, save, exit\n";
    }

    std::string command;
    while (true) {
        std::cin >> command;

        if (command == Commands::ADD_ROW) {
            std::cout << "Type in row number (starting from 0) and the values separated by commas (Do not leave space after each comma).\n";
            size_t row;
            std::cin >> row;
            std::cin.ignore();
            std::string values;
            std::getline(std::cin, values);
            table.addRow(row, values);
        }
        else if (command == Commands::REMOVE_ROW) {
            std::cout << "Write down the row you want to remove (starting from 0).\n";
            size_t row;
            std::cin >> row;
            table.removeRow(row);
        }
        else if (command == Commands::EDIT_VALUE) {
            std::cout << "Enter row, column (starting from 0), and new value, all separated by spaces.\n";
            size_t row, col;
            std::cin >> row >> col;
            std::cin.ignore();
            std::string value;
            std::getline(std::cin, value);
            std::cout << "Is it a header? (Type in 'y' or 'n')\n";
            bool isHeader;
            char answer;
            std::cin >> answer;
            if (answer == 'y') {
                isHeader = true;
            }
            else {
                isHeader = false;
            }
            table.editCell(row, col, value, isHeader);
        }
        else if (command == Commands::PRINT_TABLE) {
            table.print();
        }
        else if (command == Commands::SAVE_TABLE) {
            table.saveToFile("html2.txt");
            std::cout << "Table saved successfully.\n";
        }
        else if (command == Commands::EXIT) {
            break;
        }
    }
}
