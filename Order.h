#ifndef RESTAURANT_PROJECT_ORDER_H
#define RESTAURANT_PROJECT_ORDER_H

#include <string>
using namespace std;


class OrderItem;
class Payment;
class Restaurant;
class User;

class Order {
private:
    int id;
    double totalPrice;
    User* user;
    Restaurant* restaurant;
    OrderItem* orderItem;
    Payment* payment;
    string status;

public:
    Order();
    Order(int id, double price, User* user, Restaurant* restaurant,
          OrderItem* orderItem, Payment* payment, const string& status = "Pending");
    ~Order();


    int getId() const;
    double getTotalPrice() const;
    User* getUser() const;
    Restaurant* getRestaurant() const;
    OrderItem* getOrderItem() const;
    Payment* getPayment() const;
    string getStatus() const;


    void setId(int id);
    void setTotalPrice(double price);
    void setUser(User* user);
    void setRestaurant(Restaurant* restaurant);
    void setOrderItem(OrderItem* orderItem);
    void setPayment(Payment* payment);
    void setStatus(const string& status);


    void calculateTotal();
    string getOrderSummary() const;
};

#endif // RESTAURANT_PROJECT_ORDER_H