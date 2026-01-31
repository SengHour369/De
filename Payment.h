#ifndef RESTAURANT_PROJECT_PAYMENT_H
#define RESTAURANT_PROJECT_PAYMENT_H

#include <string>
using namespace std;

class Payment {
private:
    int id;
    double amount;
    string payment_type;
    bool processed;

public:
    Payment();
    Payment(int id, double amount, const string& payment_type, bool processed = false);


    int getId() const;
    double getAmount() const;
    string getPaymentType() const;
    bool isProcessed() const;


    void setId(int id);
    void setAmount(double amount);
    void setPaymentType(const string& payment_type);
    void setProcessed(bool processed);
};

#endif // RESTAURANT_PROJECT_PAYMENT_H