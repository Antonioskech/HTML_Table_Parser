# 📋 HTML Table Parser and Formatter

## 📝 Project Description

This project is a **C++ HTML Table Parser and Formatter**.  
It reads basic HTML-like table data, parses it into a structured internal representation, and prints it out in a neatly formatted and human-readable way.

---

## ✨ Functionalities Implemented

Here’s a list of everything currently working in the project:

- ✅ **Parsing** an HTML table structure from a `.txt` file
- ✅ **Adding** table rows and header cells (`<th>`)
- ✅ **Removing** rows by selecting the number of the row
- ✅ **Editing** rows by selecting the number of the row and column
- ✅ **Visualising** the table into the C++ console terminal
- ✅ **Saving** an HTML table into `.txt` file
- ✅ **Exiting** the program without saving any changes you made (unless you typed in "save" before exiting)


---

## 📂 Example Usage

Look at the html2.txt file in the project folder. You can see an example html table code. When you start the program, it will ask you to type in the name of the `.txt` file you want to use. Then you have a choice to use the following commands: add, remove, edit, print, save, exit

---

## Print
When you type in "print" in the console, you will see the visualisation of you table. 
The original table looks like this:

![Table example](Project/images/HTML_Table.png)

In C++, it would look like this:

![C++ Table](Project/images/C++_Table.png)

## Add
The syntax of this command is: add <rowNumber> <value1>,<value2>,<value3>...
This command lets you add a new row into your table.

//insert add example image

## Remove
The syntax of this command is: remove <rowNumber>
This command removes a row you choose in your table.

//insert remove example image


## Edit
The syntax of this command is: edit <rowNumber> <colNumber> <newValue>
This command lets you change the value in a cell, chosen by the user.

//insert edit example image

## Save
When typing in "save", the program will ask you in which `.txt` you want to save the table to. After choosing the file, it will save your table in html code format in your txt file so you can load it again if you want to.

## Exit
"Exit" stops the program. If you didnt type "save" before exiting, the changes would be lost, so make sure to save the changes before exiting the program.








