#ifndef RESTAURANT_PROJECT_ORDERITEM_H
#define RESTAURANT_PROJECT_ORDERITEM_H

#include <vector>
#include <string>
#include "MenuItem.h"
using namespace std;


class Order;

class OrderItem {
private:
    int id;
    int quantity;
    double price;
    Order* order;
    vector<MenuItem> menu_items;

public:
    OrderItem();
    OrderItem(int id, int quantity, double price, Order* order,
              const vector<MenuItem>& menu_items);


    int getId() const;
    int getQuantity() const;
    double getPrice() const;
    Order* getOrder() const;
    vector<MenuItem> getMenuItems() const;


    void setId(int id);
    void setQuantity(int quantity);
    void setPrice(double price);
    void setOrder(Order* order);
    void setMenuItems(const vector<MenuItem>& menu_items);


    double calculateSubtotal() const;
};

#endif // RESTAURANT_PROJECT_ORDERITEM_H