// MenuItem.cpp
#include "MenuItem.h"

MenuItem::MenuItem() : id(0), name(""), description(""),
                       price(0.0), available(false), restaurantId(0) {
}

MenuItem::MenuItem(int id, const string& name, const string& description,
                   double price, bool available, int restaurantId) :
    id(id), name(name), description(description), price(price),
    available(available), restaurantId(restaurantId) {
}


int MenuItem::getId() const { return id; }
string MenuItem::getName() const { return name; }
string MenuItem::getDescription() const { return description; }
double MenuItem::getPrice() const { return price; }
bool MenuItem::getAvailable() const { return available; }
int MenuItem::getRestaurantId() const { return restaurantId; }


void MenuItem::setId(int id) { this->id = id; }
void MenuItem::setName(const string& name) { this->name = name; }
void MenuItem::setDescription(const string& description) { this->description = description; }
void MenuItem::setPrice(double price) { this->price = price; }
void MenuItem::setAvailable(bool available) { this->available = available; }
void MenuItem::setRestaurantId(int restaurantId) { this->restaurantId = restaurantId; }