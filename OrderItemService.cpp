#include "OrderItemService.h"
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <iostream>
#include "Order.h"
using namespace std;

OrderItemService::OrderItemService() {

}

OrderItemService::~OrderItemService() {
    for (OrderItem* item : orderItems) {
        delete item;
    }
}

OrderItem* OrderItemService::createOrderItem(const vector<MenuItem>& items, int quantity) {
    if (items.empty() || quantity <= 0) {
        cout << "Invalid order item details!\n";
        return nullptr;
    }

    if (!checkItemAvailability(items)) {
        cout << "Some items are not available!\n";
        return nullptr;
    }

    double price = calculateTotalForItems(items, quantity);
    OrderItem* newItem = new OrderItem(generateOrderItemId(), quantity, price, nullptr, items);
    orderItems.push_back(newItem);

    cout << "Order item created successfully!\n";
    return newItem;
}

bool OrderItemService::updateOrderItem(OrderItem* orderItem,
                                      const vector<MenuItem>& newItems,
                                      int newQuantity) {
    if (!orderItem || newItems.empty() || newQuantity <= 0) {
        cout << "Invalid update details!\n";
        return false;
    }

    if (!checkItemAvailability(newItems)) {
        cout << "Some items are not available!\n";
        return false;
    }

    orderItem->setMenuItems(newItems);
    orderItem->setQuantity(newQuantity);
    orderItem->setPrice(calculateTotalForItems(newItems, newQuantity));

    cout << "Order item updated successfully!\n";
    return true;
}

bool OrderItemService::deleteOrderItem(int itemId) {
    auto it = remove_if(orderItems.begin(), orderItems.end(),
        [itemId](OrderItem* item) { return item->getId() == itemId; });

    if (it != orderItems.end()) {

        delete *it;
        orderItems.erase(it, orderItems.end());
        cout << "Order item deleted successfully!\n";
        return true;
    }

    cout << "Order item not found!\n";
    return false;
}

OrderItem* OrderItemService::getOrderItemById(int id) const {
    for (OrderItem* item : orderItems) {
        if (item->getId() == id) {
            return item;
        }
    }
    return nullptr;
}

vector<OrderItem*> OrderItemService::getOrderItemsByOrder(int orderId) const {
    vector<OrderItem*> result;
    for (OrderItem* item : orderItems) {
        if (item->getOrder() && item->getOrder()->getId() == orderId) {
            result.push_back(item);
        }
    }
    return result;
}

vector<OrderItem*> OrderItemService::getAllOrderItems() const {
    return orderItems;
}

double OrderItemService::calculateSubtotal(const OrderItem* orderItem) const {
    if (!orderItem) {
        return 0.0;
    }
    return orderItem->getPrice() * orderItem->getQuantity();
}

double OrderItemService::calculateTotalForItems(const vector<MenuItem>& items, int quantity) const {
    double total = 0.0;
    for (const MenuItem& item : items) {
        total += item.getPrice();
    }
    return total * quantity;
}

bool OrderItemService::validateOrderItem(const OrderItem* orderItem) const {
    if (!orderItem) {
        return false;
    }

    if (orderItem->getQuantity() <= 0) {
        return false;
    }

    if (orderItem->getPrice() < 0) {
        return false;
    }

    vector<MenuItem> items = orderItem->getMenuItems();
    if (items.empty()) {
        return false;
    }

    return checkItemAvailability(items);
}

bool OrderItemService::checkItemAvailability(const vector<MenuItem>& items) const {
    for (const MenuItem& item : items) {
        if (!item.getAvailable()) {
            return false;
        }
    }
    return true;
}

string OrderItemService::generateOrderItemDetails(const OrderItem* orderItem) const {
    if (!orderItem) {
        return "Invalid order item!";
    }

    stringstream ss;
    ss << fixed << setprecision(2);
    ss << "\n--- Order Item Details ---\n";
    ss << "ID: " << orderItem->getId() << "\n";
    ss << "Quantity: " << orderItem->getQuantity() << "\n";
    ss << "Price per item: $" << orderItem->getPrice() << "\n";
    ss << "Subtotal: $" << calculateSubtotal(orderItem) << "\n";

    vector<MenuItem> items = orderItem->getMenuItems();
    if (!items.empty()) {
        ss << "Items included:\n";
        for (const MenuItem& item : items) {
            ss << "  - " << item.getName() << " ($" << item.getPrice() << ")\n";
        }
    }

    ss << "-------------------------\n";
    return ss.str();
}

int OrderItemService::countItemsInOrder(const vector<OrderItem*>& orderItems) const {
    int total = 0;
    for (const OrderItem* item : orderItems) {
        total += item->getQuantity();
    }
    return total;
}

int OrderItemService::generateOrderItemId() {
    static int counter = 60000;
    return counter++;
}