#include "OrderService.h"
#include "User.h"
#include "Restaurant.h"
#include <sstream>
#include <iomanip>
#include <iostream>
#include <algorithm>
using namespace std;

OrderService::OrderService() {
}

OrderService::~OrderService() {
    for (Order* order : orders) {
        delete order;
    }
    for (Payment* payment : payments) {
        delete payment;
    }
}

Order* OrderService::createOrder(User* user, Restaurant* restaurant,
                                const vector<MenuItem>& selectedItems,
                                const string& paymentType) {
    if (!user || !restaurant || selectedItems.empty()) {
        cout << "Invalid order details!\n";
        return nullptr;
    }


    for (const MenuItem& item : selectedItems) {
        if (!item.getAvailable()) {
            cout << "Item " << item.getName() << " is not available!\n";
            return nullptr;
        }
    }

    double total = calculateOrderTotal(selectedItems);

    if (total <= 0) {
        cout << "No valid items selected!\n";
        return nullptr;
    }

    Payment* payment = createPayment(total, paymentType);
    if (!payment) {
        cout << "Failed to create payment!\n";
        return nullptr;
    }

    Order* newOrder = new Order(generateOrderId(), total, user, restaurant,
                               selectedItems, payment, "Pending");
    orders.push_back(newOrder);

    cout << "Order created successfully! Order ID: " << newOrder->getId() << "\n";
    cout << "Total: $" << fixed << setprecision(2) << total << "\n";

    return newOrder;
}

bool OrderService::cancelOrder(int orderId) {
    Order* order = getOrderById(orderId);
    if (order && order->getStatus() == "Pending") {
        order->setStatus("Cancelled");


        Payment* payment = order->getPayment();
        if (payment && payment->isProcessed()) {
            cout << "Payment refunded: $" << payment->getAmount() << "\n";
            payment->setProcessed(false);
        }

        cout << "Order cancelled successfully!\n";
        return true;
    }

    if (order && order->getStatus() == "Cancelled") {
        cout << "Order already cancelled!\n";
    } else {
        cout << "Order not found or cannot be cancelled!\n";
    }
    return false;
}

bool OrderService::updateOrderStatus(int orderId, const string& status) {
    Order* order = getOrderById(orderId);
    if (order) {
        order->setStatus(status);
        cout << "Order status updated to: " << status << "\n";
        return true;
    }
    return false;
}

Order* OrderService::getOrderById(int id) const {
    for (Order* order : orders) {
        if (order->getId() == id) {
            return order;
        }
    }
    return nullptr;
}

vector<Order*> OrderService::getOrdersByUser(const string& userId) const {
    vector<Order*> userOrders;
    for (Order* order : orders) {
        if (order->getUser() && order->getUser()->getId() == userId) {
            userOrders.push_back(order);
        }
    }
    return userOrders;
}

vector<Order*> OrderService::getOrdersByRestaurant(int restaurantId) const {
    vector<Order*> restaurantOrders;
    for (Order* order : orders) {
        if (order->getRestaurant() && order->getRestaurant()->getId() == restaurantId) {
            restaurantOrders.push_back(order);
        }
    }
    return restaurantOrders;
}

vector<Order*> OrderService::getAllOrders() const {
    return orders;
}

Payment* OrderService::createPayment(double amount, const string& paymentType) {
    if (amount <= 0) {
        cout << "Invalid payment amount!\n";
        return nullptr;
    }

    if (paymentType != "Cash" && paymentType != "Card") {
        cout << "Invalid payment type! Must be Cash or Card\n";
        return nullptr;
    }

    Payment* newPayment = new Payment(generatePaymentId(), amount, paymentType, false);
    payments.push_back(newPayment);
    return newPayment;
}

bool OrderService::processPayment(int paymentId) {
    for (Payment* payment : payments) {
        if (payment->getId() == paymentId) {
            if (payment->isProcessed()) {
                cout << "Payment already processed!\n";
                return false;
            }

            cout << "Processing payment of $" << payment->getAmount()
                 << " via " << payment->getPaymentType() << "\n";
            payment->setProcessed(true);
            cout << "Payment processed successfully!\n";
            return true;
        }
    }
    cout << "Payment not found!\n";
    return false;
}

vector<Payment*> OrderService::getPaymentHistory(const string& userId) const {
    vector<Payment*> userPayments;
    for (Order* order : orders) {
        if (order->getUser() && order->getUser()->getId() == userId) {
            Payment* payment = order->getPayment();
            if (payment) {
                userPayments.push_back(payment);
            }
        }
    }
    return userPayments;
}

double OrderService::calculateTotalRevenue() const {
    double total = 0.0;
    for (Order* order : orders) {
        if (order->getStatus() != "Cancelled" && order->getPayment() &&
            order->getPayment()->isProcessed()) {
            total += order->getTotalPrice();
        }
    }
    return total;
}

double OrderService::calculateRestaurantRevenue(int restaurantId) const {
    double total = 0.0;
    for (Order* order : orders) {
        if (order->getRestaurant() && order->getRestaurant()->getId() == restaurantId &&
            order->getStatus() != "Cancelled" && order->getPayment() &&
            order->getPayment()->isProcessed()) {
            total += order->getTotalPrice();
        }
    }
    return total;
}

vector<Order*> OrderService::getRecentOrders(int limit) const {
    vector<Order*> recentOrders;
    int count = min(static_cast<int>(orders.size()), limit);


    int start = max(0, static_cast<int>(orders.size()) - limit);
    for (int i = start; i < orders.size(); i++) {
        recentOrders.push_back(orders[i]);
    }

    return recentOrders;
}

double OrderService::calculateOrderTotal(const vector<MenuItem>& items, int quantity) const {
    double total = 0.0;
    for (const MenuItem& item : items) {
        if (item.getAvailable()) {
            total += item.getPrice();
        }
    }
    return total * quantity;
}

string OrderService::generateOrderSummary(const Order* order) const {
    if (!order) {
        return "Invalid order!";
    }
    return order->getOrderSummary();
}

int OrderService::generateOrderId() {
    static int counter = 10000;
    return counter++;
}

int OrderService::generatePaymentId() {
    static int counter = 90000;
    return counter++;
}