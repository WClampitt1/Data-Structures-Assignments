//
// Created by william on 2/13/19.
//

#ifndef HOMEWORK_2_BOOK_H
#define HOMEWORK_2_BOOK_H

#include <iostream>
#include <string>

class book{
private:
    std::string id = "";
    std::string title = "";
    std::string author = "";
public:
    std::string getID() { return id; };
    std::string getAuthor() { return author; };
    std::string getTitle() { return title; };

    void setID(std::string id) { this->id = id; };
    void setTitle(std::string title) { this->title = title; };
    void setAuthor(std::string author) {this->author = author; };

    std::string toString() { return ("book_id:" + id + ", book_name:" + title+ ", book_author:" + author); };
/*
    book();
    book(std::string id, std::string title, std::string author){
        this->setID(id);
        this->setTitle(title);
        this->setAuthor(author);
    }
    */
};

#endif //HOMEWORK_2_BOOK_H
