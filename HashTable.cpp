#include <iostream>
#include <vector>

class HashTable {
private:
    std::vector<int> table;  // Hash table to store elements
    std::vector<bool> isDeleted;  // To keep track of deleted elements
    int size;  // Current size of the hash table
    int count;  // Number of elements in the table
    const double loadFactorThreshold = 0.8;  // Load factor for resizing

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
        int newSize = nextPrime(2 * size);  // Find the next prime size
        std::vector<int> oldTable = table;  // Backup the old table
        std::vector<bool> oldIsDeleted = isDeleted;  // Backup deleted markers
        table = std::vector<int>(newSize, -1);  // Initialize new table with -1
        isDeleted = std::vector<bool>(newSize, false);  // Reset deleted markers
        size = newSize;
        count = 0;

        // Rehash all the elements from the old table
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
        table = std::vector<int>(size, -1);  // Initialize table with -1
        isDeleted = std::vector<bool>(size, false);  // Initialize deleted flags
        count = 0;
    }

    // Insert a key into the hash table
    void insert(int key) {
        if ((double)count / size > loadFactorThreshold) {
            resize();  // Resize if the load factor is exceeded
        }

        int i = 0;
        int index;
        while (i < size) {
            index = quadraticProbing(key, i);
            if (table[index] == -1 || isDeleted[index]) {
                table[index] = key;  // Insert the key
                isDeleted[index] = false;  // Mark as not deleted
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
                table[index] = -1;  // Mark as removed
                isDeleted[index] = true;  // Set the deleted flag
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
                return index;  // Return the index of the key
            } else if (table[index] == -1 && !isDeleted[index]) {
                return -1;  // Not found
            }
            i++;
        }
        return -1;  // Not found after probing
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
