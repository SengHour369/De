#include "Order.h"
#include "User.h"
#include "Restaurant.h"
#include "Payment.h"
#include <sstream>
#include <iomanip>
using namespace std;

Order::Order() : id(0), totalPrice(0.0), user(nullptr),
                 restaurant(nullptr), payment(nullptr), status("Pending") {
}

Order::Order(int id, double price, User* user, Restaurant* restaurant,
             const vector<MenuItem>& items, Payment* payment, const string& status) :
    id(id), totalPrice(price), user(user), restaurant(restaurant),
    items(items), payment(payment), status(status) {
}

Order::~Order() {

}

int Order::getId() const { return id; }
double Order::getTotalPrice() const { return totalPrice; }
User* Order::getUser() const { return user; }
Restaurant* Order::getRestaurant() const { return restaurant; }
vector<MenuItem> Order::getItems() const { return items; }
Payment* Order::getPayment() const { return payment; }
string Order::getStatus() const { return status; }

void Order::setId(int id) { this->id = id; }
void Order::setTotalPrice(double price) { this->totalPrice = price; }
void Order::setUser(User* user) { this->user = user; }
void Order::setRestaurant(Restaurant* restaurant) { this->restaurant = restaurant; }
void Order::setItems(const vector<MenuItem>& items) {
    this->items = items;
    calculateTotal();
}
void Order::setPayment(Payment* payment) { this->payment = payment; }
void Order::setStatus(const string& status) { this->status = status; }

void Order::calculateTotal() {
    totalPrice = 0.0;
    for (const MenuItem& item : items) {
        totalPrice += item.getPrice();
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

    if (!items.empty()) {
        ss << "Items (" << items.size() << "):\n";
        for (const MenuItem& item : items) {
            ss << "  - " << item.getName() << " ($" << item.getPrice() << ")\n";
        }
    }

    if (payment) {
        ss << "Payment Type: " << payment->getPaymentType() << "\n";
        ss << "Payment Status: " << (payment->isProcessed() ? "Processed" : "Pending") << "\n";
    }

    ss << "=====================\n";
    return ss.str();
}