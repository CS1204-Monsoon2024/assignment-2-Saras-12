#include <iostream>
#include <vector>

class HashTable {
private:
    std::vector<int> table;  
    std::vector<bool> isDeleted;  
    int size;  
    int count;  
    static const double loadFactorThreshold;  // Change here

    // Hash function
    int hashFunction(int key) {
        return key % size;
    }

    // Quadratic probing to resolve collisions
    int quadraticProbing(int key, int i) {
        return (hashFunction(key) + i * i) % size;
    }

    // Check if a number is prime (for resizing)
    bool isPrime(int num) {
        if (num <= 1) return false;
        for (int i = 2; i * i <= num; ++i) {
            if (num % i == 0) return false;
        }
        return true;
    }

    // Find the next prime number larger than the current size
    int nextPrime(int num) {
        while (!isPrime(num)) {
            num++;
        }
        return num;
    }

    // Resize the hash table
    void resize() {
        int newSize = nextPrime(2 * size);
        std::vector<int> oldTable = table;
        std::vector<bool> oldIsDeleted = isDeleted;
        table = std::vector<int>(newSize, -1);
        isDeleted = std::vector<bool>(newSize, false);
        size = newSize;
        count = 0;

        for (int i = 0; i < oldTable.size(); ++i) {
            if (oldTable[i] != -1 && !oldIsDeleted[i]) {
                insert(oldTable[i]);
            }
        }
    }

public:
    // Constructor
    HashTable(int initialSize) {
        size = nextPrime(initialSize);
        table = std::vector<int>(size, -1);
        isDeleted = std::vector<bool>(size, false);
        count = 0;
    }

    // Insert a key into the hash table
    void insert(int key) {
        if ((double)count / size > loadFactorThreshold) {
            resize();
        }

        int i = 0;
        int index;
        while (i < size) {
            index = quadraticProbing(key, i);
            if (table[index] == -1 || isDeleted[index]) {
                table[index] = key;
                isDeleted[index] = false;
                count++;
                return;
            } else if (table[index] == key) {
                std::cout << "Duplicate key insertion is not allowed" << std::endl;
                return;
            }
            i++;
        }

        std::cout << "Max probing limit reached!" << std::endl;
    }

    // Remove a key from the hash table
    void remove(int key) {
        int i = 0;
        int index;
        while (i < size) {
            index = quadraticProbing(key, i);
            if (table[index] == key) {
                table[index] = -1;  
                isDeleted[index] = true;  
                count--;
                return;
            } else if (table[index] == -1 && !isDeleted[index]) {
                std::cout << "Element not found" << std::endl;
                return;
            }
            i++;
        }

        std::cout << "Element not found" << std::endl;
    }

    // Search for a key and return its index
    int search(int key) {
        int i = 0;
        int index;
        while (i < size) {
            index = quadraticProbing(key, i);
            if (table[index] == key) {
                return index;  
            } else if (table[index] == -1 && !isDeleted[index]) {
                return -1;  
            }
            i++;
        }
        return -1;  
    }

    // Print the hash table
    void printTable() {
        for (int i = 0; i < size; ++i) {
            if (table[i] == -1 || isDeleted[i]) {
                std::cout << "- ";
            } else {
                std::cout << table[i] << " ";
            }
        }
        std::cout << std::endl;
    }
};

// Initialize static const member
const double HashTable::loadFactorThreshold = 0.8;
