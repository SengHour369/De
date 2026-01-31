#ifndef RESTAURANT_PROJECT_ORDERSERVICE_H
#define RESTAURANT_PROJECT_ORDERSERVICE_H

#include <vector>
#include <string>
#include "Order.h"
#include "OrderItem.h"
#include "Payment.h"
#include "MenuItem.h"

class OrderService {
private:
    vector<Order*> orders;
    vector<OrderItem*> orderItems;
    vector<Payment*> payments;

public:
    OrderService();
    ~OrderService();


    Order* createOrder(User* user, Restaurant* restaurant,
                      const vector<MenuItem>& selectedItems,
                      const string& paymentType);

    bool cancelOrder(int orderId);
    bool updateOrderStatus(int orderId, const string& status);


    Order* getOrderById(int id) const;
    vector<Order*> getOrdersByUser(const string& userId) const;
    vector<Order*> getOrdersByRestaurant(int restaurantId) const;
    vector<Order*> getAllOrders() const;


    OrderItem* createOrderItem(const vector<MenuItem>& items, int quantity);
    bool updateOrderItemQuantity(int itemId, int newQuantity);


    Payment* createPayment(double amount, const string& paymentType);
    bool processPayment(int paymentId);
    vector<Payment*> getPaymentHistory(const string& userId) const;


    double calculateTotalRevenue() const;
    double calculateRestaurantRevenue(int restaurantId) const;
    vector<Order*> getRecentOrders(int limit = 10) const;


    double calculateOrderTotal(const vector<MenuItem>& items, int quantity) const;
    string generateOrderSummary(const Order* order) const;

private:
    int generateOrderId();
    int generateOrderItemId();
    int generatePaymentId();
};

#endif // RESTAURANT_PROJECT_ORDERSERVICE_H