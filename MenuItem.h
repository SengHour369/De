// MenuItem.h
#ifndef RESTAURANT_PROJECT_MENUITEM_H
#define RESTAURANT_PROJECT_MENUITEM_H

#include <string>
using namespace std;

class MenuItem {
private:
    int id;
    string name;
    string description;
    double price;
    bool available;
    int restaurantId;

public:
    MenuItem();
    MenuItem(int id, const string& name, const string& description,
             double price, bool available, int restaurantId);


    int getId() const;
    string getName() const;
    string getDescription() const;
    double getPrice() const;
    bool getAvailable() const;
    int getRestaurantId() const;


    void setId(int id);
    void setName(const string& name);
    void setDescription(const string& description);
    void setPrice(double price);
    void setAvailable(bool available);
    void setRestaurantId(int restaurantId);
};

#endif // RESTAURANT_PROJECT_MENUITEM_H