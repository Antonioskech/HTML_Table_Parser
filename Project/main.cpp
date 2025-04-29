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

    std::cout << "Enter the name of the .txt file you want to parse (example: html2.txt): ";
    std::string filename;
    std::getline(std::cin, filename);

    table.parseFromFile(filename);

    if (!table.empty()) {
        std::cout << "Table parsed successfully from '" << filename << "'.\n";
    }
    else {
        std::cout << "Warning: Table could not be parsed or file is empty.\n";
    }

    std::cout << "Write down one of the following commands you want: add, remove, edit, print, save, exit\n";

    std::string command;
    while (true) {
        std::cout << "\n> "; // Little prompt for better UX
        std::cin >> command;

        if (command == Commands::ADD_ROW) {
            std::cout << "Type in row number (starting from 0) and the values separated by commas (No spaces after commas).\n";
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

            std::cout << "Is it a header? (Type 'y' for yes, 'n' for no): ";
            char answer;
            std::cin >> answer;
            bool isHeader = (answer == 'y');

            table.editCell(row, col, value, isHeader);
        }
        else if (command == Commands::PRINT_TABLE) {
            table.print();
        }
        else if (command == Commands::SAVE_TABLE) {
            std::cout << "Enter the filename you want to save the table to (e.g., output.txt):\n";
            std::string filename;
            std::cin >> filename;
            table.saveToFile(filename);
            std::cout << "Table saved successfully to " << filename << ".\n";
        }

        else if (command == Commands::EXIT) {
            std::cout << "Exiting program. Goodbye!\n";
            break;
        }
        else {
            std::cout << "Unknown command. Please try again.\n";
        }
    }
}
