// Restaurant.cpp
#include "Restaurant.h"
using namespace std;

Restaurant::Restaurant() : id(0), name(""), category(""), rating(0), 
                           phone_number(""), location("") {
}

Restaurant::Restaurant(int id, const string& name, const string& category,
                       int rating, const string& phone_number, const string& location) :
    id(id), name(name), category(category), rating(rating),
    phone_number(phone_number), location(location) {
}

int Restaurant::getId() const {
    return this->id;
}

string Restaurant::getName() const {
    return this->name;
}

string Restaurant::getCategory() const {
    return this->category;
}

int Restaurant::getRating() const {
    return this->rating;
}

string Restaurant::getLocation() const {
    return this->location;
}

string Restaurant::getPhoneNumber() const {
    return this->phone_number;
}

void Restaurant::setId(int id) {
    this->id = id;
}

void Restaurant::setName(const string& name) {
    this->name = name;
}

void Restaurant::setCategory(const string& category) {
    this->category = category;
}

void Restaurant::setRating(int rating) {
    this->rating = rating;
}

void Restaurant::setLocation(const string& location) {
    this->location = location;
}

void Restaurant::setPhoneNumber(const string& phone_number) {
    this->phone_number = phone_number;
}