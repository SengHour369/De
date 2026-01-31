
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

    //  function to save string to binary file
    void saveString(ofstream& outFile, const string& str) {
        size_t length = str.size();
        outFile.write(reinterpret_cast<const char*>(&length), sizeof(length));
        if (length > 0) {
            outFile.write(str.c_str(), length);
        }
    }

    //  function to load string from binary file
    std::string loadString(std::ifstream& inFile) {
        size_t length;
        inFile.read(reinterpret_cast<char*>(&length), sizeof(length));

        if (length > 0) {
            std::string str(length, ' ');
            inFile.read(&str[0], length);
            return str;
        }
        return "";
    }

public:
    FileStorage(const std::string& filename) : filename(filename) {}

    // Save vector of objects to binary file
    template<typename T>
    bool saveToFile(const std::vector<T>& data) {
        std::ofstream outFile(filename, std::ios::binary);
        if (!outFile) {
            std::cerr << "Error: Cannot open file " << filename << " for writing!\n";
            return false;
        }

        size_t size = data.size();
        outFile.write(reinterpret_cast<const char*>(&size), sizeof(size));

        if (size > 0) {
            outFile.write(reinterpret_cast<const char*>(data.data()),
                         size * sizeof(T));
        }

        bool success = outFile.good();
        outFile.close();
        return success;
    }

    // Load vector of objects from binary file
    template<typename T>
    bool loadFromFile(vector<T>& data) {
        ifstream inFile(filename, ios::binary);
        if (!inFile) {
            // File doesn't exist yet  that's okay
            return false;
        }

        size_t size;
        inFile.read(reinterpret_cast<char*>(&size), sizeof(size));

        if (size > 0) {
            data.resize(size);
            inFile.read(reinterpret_cast<char*>(data.data()),
                       size * sizeof(T));
        }

        bool success = inFile.good();
        inFile.close();
        return success;
    }

    // Specialized save for User objects
    bool saveUsers(const vector<class User>& users);

    // Specialized load for User objects
    bool loadUsers(vector<class User>& users);

    // Specialized save for Restaurant objects
    bool saveRestaurants(const vector<class Restaurant>& restaurants);

    // Specialized load for Restaurant objects
    bool loadRestaurants(vector<class Restaurant>& restaurants);

    // Specialized save for MenuItem objects
    bool saveMenuItems(const vector<class MenuItem>& menuItems);

    // Specialized load for MenuItem objects
    bool loadMenuItems(vector<class MenuItem>& menuItems);

    // Check if file exists
    bool fileExists() const {
        ifstream file(filename);
        return file.good();
    }

    // Clear file
    bool clearFile() {
        ofstream outFile(filename,ios::trunc);
        return outFile.good();
    }

    // Get filename
   string getFilename() const { return filename; }

    // Set filename
    void setFilename(const string& newFilename) { filename = newFilename; }
};

#endif // FILE_STORAGE_H