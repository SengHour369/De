#include "OrderItem.h"
#include "Order.h"

OrderItem::OrderItem() : id(0), quantity(0), price(0.0), order(nullptr) {
}

OrderItem::OrderItem(int id, int quantity, double price,
                     Order* order, const vector<MenuItem>& menu_items) :
    id(id), quantity(quantity), price(price),
    order(order), menu_items(menu_items) {
}

int OrderItem::getId() const { return id; }
int OrderItem::getQuantity() const { return quantity; }
double OrderItem::getPrice() const { return price; }
Order* OrderItem::getOrder() const { return order; }
vector<MenuItem> OrderItem::getMenuItems() const { return menu_items; }


void OrderItem::setId(int id) { this->id = id; }
void OrderItem::setQuantity(int quantity) { this->quantity = quantity; }
void OrderItem::setPrice(double price) { this->price = price; }
void OrderItem::setOrder(Order* order) { this->order = order; }
void OrderItem::setMenuItems(const vector<MenuItem>& menu_items) { this->menu_items = menu_items; }

double OrderItem::calculateSubtotal() const {
    return quantity * price;
}