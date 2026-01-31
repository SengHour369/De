#ifndef RESTAURANT_PROJECT_ORDERITEMSERVICE_H
#define RESTAURANT_PROJECT_ORDERITEMSERVICE_H

#include <vector>
#include <string>
#include "OrderItem.h"
#include "MenuItem.h"
using namespace std;

class OrderItemService {
private:
    vector<OrderItem*> orderItems;

public:
    OrderItemService();
    ~OrderItemService();


    OrderItem* createOrderItem(const vector<MenuItem>& items, int quantity);
    bool updateOrderItem(OrderItem* orderItem, const vector<MenuItem>& newItems, int newQuantity);
    bool deleteOrderItem(int itemId);

    OrderItem* getOrderItemById(int id) const;
    vector<OrderItem*> getOrderItemsByOrder(int orderId) const;
    vector<OrderItem*> getAllOrderItems() const;


    double calculateSubtotal(const OrderItem* orderItem) const;
    double calculateTotalForItems(const vector<MenuItem>& items, int quantity) const;


    bool validateOrderItem(const OrderItem* orderItem) const;
    bool checkItemAvailability(const vector<MenuItem>& items) const;


    string generateOrderItemDetails(const OrderItem* orderItem) const;
    int countItemsInOrder(const vector<OrderItem*>& orderItems) const;

private:
    int generateOrderItemId();
};

#endif // RESTAURANT_PROJECT_ORDERITEMSERVICE_H