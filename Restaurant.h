// Restaurant.h
#ifndef RESTAURANT_PROJECT_RESTAURANT_H
#define RESTAURANT_PROJECT_RESTAURANT_H

#include <string>
using namespace std;

class Restaurant {
private:
    int id;
    string name;
    string category;
    int rating;
    string phone_number;
    string location;

public:
    Restaurant();
    Restaurant(int id, const string& name, const string& category,
               int rating, const string& phone_number, const string& location);


    int getId() const;
    string getName() const;
    string getCategory() const;
    int getRating() const;
    string getLocation() const;
    string getPhoneNumber() const;


    void setId(int id);
    void setName(const string& name);
    void setCategory(const string& category);
    void setRating(int rating);
    void setLocation(const string& location);
    void setPhoneNumber(const string& phone_number);
};

#endif // RESTAURANT_PROJECT_RESTAURANT_H