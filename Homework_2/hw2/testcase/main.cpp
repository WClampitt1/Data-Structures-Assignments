#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "ArgumentManager.h"
#include "LinkedList.h"
#include "book.h"

void bubbleSort(LinkedList<book> &list, std::string cat){
    int n = list.len();
    for(int i = 0; i < n - 1; i++)
        for(int j = 0; j < n - i - 1; j++){
            if(cat == "book_id") {
                if (list.access(j).getID().compare(list.access(j + 1).getID()) > 0)
                    list.swap(j, j + 1);
            }
            else if(cat == "book_name") {
                  if (list.access(j).getTitle().compare(list.access(j + 1).getTitle()) > 0)
                      list.swap(j, j + 1);
              }
            else if (cat == "book_author") {
                  if (list.access(j).getID().compare(list.access(j + 1).getID()) > 0)
                      list.swap(j, j + 1);
              }
        }
}

bool operator == (book a, book b){ // Overloads the == operator to work with book objects
    return a.getID() == b.getID() && a.getTitle() == b.getTitle() && a.getAuthor() == b.getAuthor();
}

bool isDuplicate(book a, book b){ // Returns true if two books are the same
    return a == b;
}

book makeBook(std::string info){ // Reads in book information and creates a book object

    //book_id:book id, book_name:book name, book_author:author name
    while(isspace(info.at(0))) {
        info = info.substr(1, info.length());
    }

    info.erase(0, info.find(":") + 1);
    std::string id = info.substr(0, info.find(","));

    info.erase(0, info.find(":") + 1);
    std::string title = info.substr(0, info.find(","));

    info.erase(0, info.find(":") + 1);
    std::string author = info.substr(0, info.length());

    book tmp;
    tmp.setID(id);
    tmp.setTitle(title);
    tmp.setAuthor(author);

    return tmp;
}

void command(std::string command, LinkedList<book> &shelf){ // Reads in and interprets commands
    while (isspace(command.at(0))) {
        command = command.substr(1, command.length());
    }

    if (command.substr(0, command.find(" ")) == "add"){ // adds a book to the list
        command.erase(0, command.find(" ") + 1);
        int pos = std::stoi(command.substr(command.find(":") + 1, command.find(" ")));
        command.erase(0, command.find(" ") + 1);

        if(pos > shelf.len() - 1){
            shelf.append(makeBook(command));
        }

        else {
            book a = makeBook(command);
            for(int i = 0; i < shelf.len(); i++){
                if(isDuplicate(a, shelf.access(i)))
                    break;
            }
            shelf.insert(pos, makeBook(command));
        }
    } else if (command.substr(0, command.find(" ")) == "remove"){
        command.erase(0, command.find(" ") + 1);

        if (command.substr(0, command.find(":")) == "pos"){
            command.erase(0, command.find(":") + 1);
            shelf.remove(std::stoi(command));
        } else if (command.substr(0, command.find(":")) == "book_id"){
            command.erase(0, command.find(":") + 1);
            for(int i = 0; i < shelf.len(); i ++)
                if(shelf.access(i).getID() == command)
                    shelf.remove(i);
        } else if (command.substr(0, command.find(":")) == "book_name"){
            command.erase(0, command.find(":") + 1);
            for(int i = 0; i < shelf.len(); i ++)
                if(shelf.access(i).getTitle() == command)
                    shelf.remove(i);
        } else if (command.substr(0, command.find(":")) == "book_author"){
            command.erase(0, command.find(":") + 1);
            for(int i = 0; i < shelf.len(); i ++)
                if(shelf.access(i).getAuthor() == command)
                    shelf.remove(i);
        }
    } else if (command.substr(0, command.find(" ")) == "sort"){
        command.erase(0, command.find(" ") + 1);

        if(command.substr(0, command.find(" ")) == "book_id"){
            bubbleSort(shelf, "book_id");
        } else if (command.substr(0, command.find(" ")) == "book_name"){
            bubbleSort(shelf, "book_name");
        } else if (command.substr(0, command.find(" ")) == "book_author"){
            bubbleSort(shelf, "book_author");
        }
    }
}

int main(int argc, char *argv[]) {
    ArgumentManager am(argc, argv);

    std::string inputPath = am.get("input");
    std::string commandsPath = am.get("command");
    std::string outputPath = am.get("output");

    ifstream input;
    input.open(inputPath);
    std::string line;
    LinkedList<book> ll;
    if(input.is_open()) {
        while (getline(input, line)) {
            if (!line.empty()) {
                ll.append(makeBook(line));
            }

        }
        input.close();
    }
    input.open(commandsPath);
    if(input.is_open()){
        while (getline(input, line)){
            if(!line.empty())
                command(line, ll);
        }
        input.close();
    }
    ofstream output;
    output.open(outputPath);
    if(output.is_open()){
        for(int i = 0; i < ll.len(); i++){
            output << ll.access(i).toString() << std::endl;
        }
        output.close();
    }


}

