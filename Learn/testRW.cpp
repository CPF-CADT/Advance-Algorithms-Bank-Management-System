#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class User {
private:
    int id;
    string name;
    string address;

public:
    User() : id(0), name(""), address("") {}
    User(int id, string name, string add) : id(id), name(name), address(add) {}

    // Getters for id, name, and address
    int getId() const { return id; }
    string getName() const { return name; }
    string getAddress() const { return address; }

    // Setters for id, name, and address
    void setId(int id) { this->id = id; }
    void setName(string name) { this->name = name; }
    void setAddress(string address) { this->address = address; }

    // Function to write string data to the binary file
    void writeString(ofstream &outFile, const string &str) const {
        size_t length = str.size();
        outFile.write(reinterpret_cast<const char*>(&length), sizeof(length));
        outFile.write(str.c_str(), length);
    }

    // Function to write User object data to a binary file
    void writeToFile(ofstream &outFile) const {
        outFile.write(reinterpret_cast<const char*>(&id), sizeof(id));
        writeString(outFile, name);    // Write name
        writeString(outFile, address); // Write address
    }

    // Function to read string data from the binary file
    string readString(ifstream &inFile) {
        size_t length;
        inFile.read(reinterpret_cast<char*>(&length), sizeof(length));
        char* buffer = new char[length + 1];
        inFile.read(buffer, length);
        buffer[length] = '\0';  // Null-terminate the string
        string str(buffer);
        delete[] buffer;
        return str;
    }

    // Function to read User object data from the binary file
    void readFromFile(ifstream &inFile) {
        inFile.read(reinterpret_cast<char*>(&id), sizeof(id));
        name = readString(inFile);    // Read name
        address = readString(inFile); // Read address
    }

    // Function to display User object data
    void display() const {
        cout << "ID: " << id << ", Name: " << name << ", Address: " << address << endl;
    }
};

int main() {
    // Open the binary file for writing
    ofstream outFile("users.dat", ios::binary);
    
    // Check if file is open
    if (!outFile) {
        cerr << "Error opening file for writing!" << endl;
        return 1;
    }
    
    // Array of User objects
    User users[] = {
        User(1, "Alice", "123 Wonderland"),
        User(2, "Bob", "456 Nowhere"),
        User(3, "Charlie", "789 Someplace")
    };
    
    // Write each User object to the binary file
    for (const auto& user : users) {
        user.writeToFile(outFile);
    }

    outFile.close();  // Close the file after writing

    cout << "Data written to users.dat successfully." << endl;

    // Reading data from the binary file
    ifstream inFile("users.dat", ios::binary);
    
    // Check if file is open
    if (!inFile) {
        cerr << "Error opening file for reading!" << endl;
        return 1;
    }
    
    // Read and display User objects from the file
    User user;
    while (inFile.peek() != EOF) {  // Continue until the end of the file
        user.readFromFile(inFile);
        user.display();  // Display the read data
    }

    inFile.close();  // Close the file after reading
    return 0;
}
