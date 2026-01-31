#include "Order.h"
#include "OrderItem.h"
#include "Payment.h"
#include "Restaurant.h"
#include "User.h"
#include <sstream>
#include <iomanip>

Order::Order() : id(0), totalPrice(0.0), user(nullptr),
                 restaurant(nullptr), orderItem(nullptr),
                 payment(nullptr), status("Pending") {
}

Order::Order(int id, double price, User* user, Restaurant* restaurant,
             OrderItem* orderItem, Payment* payment, const string& status) :
    id(id), totalPrice(price), user(user), restaurant(restaurant),
    orderItem(orderItem), payment(payment), status(status) {
}
Order::~Order() {

}


int Order::getId() const { return id; }
double Order::getTotalPrice() const { return totalPrice; }
User* Order::getUser() const { return user; }
Restaurant* Order::getRestaurant() const { return restaurant; }
OrderItem* Order::getOrderItem() const { return orderItem; }
Payment* Order::getPayment() const { return payment; }
string Order::getStatus() const { return status; }


void Order::setId(int id) { this->id = id; }
void Order::setTotalPrice(double price) { this->totalPrice = price; }
void Order::setUser(User* user) { this->user = user; }
void Order::setRestaurant(Restaurant* restaurant) { this->restaurant = restaurant; }
void Order::setOrderItem(OrderItem* orderItem) { this->orderItem = orderItem; }
void Order::setPayment(Payment* payment) { this->payment = payment; }
void Order::setStatus(const string& status) { this->status = status; }

void Order::calculateTotal() {
    if (orderItem) {
        totalPrice = orderItem->calculateSubtotal();
    }
}

string Order::getOrderSummary() const {
    stringstream ss;
    ss << fixed << setprecision(2);
    ss << "\n=== ORDER SUMMARY ===\n";
    ss << "Order ID: " << id << "\n";
    ss << "Status: " << status << "\n";
    ss << "Total Price: $" << totalPrice << "\n";

    if (user) {
        ss << "Customer: " << user->getUsername() << "\n";
    }

    if (restaurant) {
        ss << "Restaurant: " << restaurant->getName() << "\n";
    }

    if (orderItem) {
        ss << "Items: " << orderItem->getQuantity() << "\n";
    }

    ss << "=====================\n";
    return ss.str();
}