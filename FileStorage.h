
#ifndef FILE_STORAGE_H
#define FILE_STORAGE_H

#include <fstream>
#include <vector>
#include <string>
#include <iostream>
using namespace std;
class FileStorage {
private:
    string filename;


    void saveString(ofstream& outFile, const string& str) {
        size_t length = str.size();
        outFile.write(reinterpret_cast<const char*>(&length), sizeof(length));
        if (length > 0) {
            outFile.write(str.c_str(), length);
        }
    }


    string loadString(ifstream& inFile) {
        size_t length;
        inFile.read(reinterpret_cast<char*>(&length), sizeof(length));

        if (length > 0) {
            string str(length, ' ');
            inFile.read(&str[0], length);
            return str;
        }
        return "";
    }

public:
    FileStorage(const string& filename) : filename(filename) {}


    bool saveUsers(const vector<class User>& users);


    bool loadUsers(vector<class User>& users);


    bool saveRestaurants(const vector<class Restaurant>& restaurants);


    bool loadRestaurants(vector<class Restaurant>& restaurants);


    bool saveMenuItems(const vector<class MenuItem>& menuItems);


    bool loadMenuItems(vector<class MenuItem>& menuItems);


    bool fileExists() const {
        ifstream file(filename);
        return file.good();
    }


    bool clearFile() {
        ofstream outFile(filename,ios::trunc);
        return outFile.good();
    }


   string getFilename() const { return filename; }


    void setFilename(const string& newFilename) { filename = newFilename; }
};

#endif // FILE_STORAGE_H