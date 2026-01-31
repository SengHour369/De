#include "Payment.h"

Payment::Payment() : id(0), amount(0.0), payment_type(""), processed(false) {
}

Payment::Payment(int id, double amount, const string& payment_type, bool processed) :
    id(id), amount(amount), payment_type(payment_type), processed(processed) {
}

int Payment::getId() const { return id; }
double Payment::getAmount() const { return amount; }
string Payment::getPaymentType() const { return payment_type; }
bool Payment::isProcessed() const { return processed; }


void Payment::setId(int id) { this->id = id; }
void Payment::setAmount(double amount) { this->amount = amount; }
void Payment::setPaymentType(const string& payment_type) { this->payment_type = payment_type; }
void Payment::setProcessed(bool processed) { this->processed = processed; }