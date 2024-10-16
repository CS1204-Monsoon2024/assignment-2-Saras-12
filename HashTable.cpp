#include "HashTable.cpp"
#include <iostream>
#include <vector>
#include <cmath>

class HashTable {
private:
    std::vector<int> table;   // The hash table itself
    int size;                 // Current size of the hash table (number of slots)
    int count;                // Number of elements inserted
    double loadFactorThreshold = 0.8;

    // Helper function to check if a number is prime
    bool isPrime(int n) {
        if (n <= 1) return false;
        if (n == 2 || n == 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (int i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }

    // Helper function to find the next prime number greater than a given number
    int nextPrime(int n) {
        while (!isPrime(n)) {
            n++;
        }
        return n;
    }

    // Hash function h(k) = k % size
    int hashFunction(int key) {
        return key % size;
    }

    // Function to handle quadratic probing
    int quadraticProbe(int key) {
        int idx = hashFunction(key);
        int i = 1;
        while (table[idx] != -1 && table[idx] != key) {
            idx = (hashFunction(key) + i * i) % size;
            i++;
        }
        return idx;
    }

    // Resize the hash table when the load factor exceeds the threshold
    void resize() {
        int newSize = nextPrime(size * 2);  // Find the next prime greater than double the current size
        std::vector<int> oldTable = table;
        table = std::vector<int>(newSize, -1);
        size = newSize;
        count = 0;

        for (int key : oldTable) {
            if (key != -1) {
                insert(key);  // Reinsert all existing keys into the resized table
            }
        }
    }

public:
    // Constructor to initialize the hash table with a given size
    HashTable(int initialSize) {
        size = nextPrime(initialSize);
        table = std::vector<int>(size, -1);
        count = 0;
    }

    // Insert a key into the hash table
    void insert(int key) {
        if (double(count) / size >= loadFactorThreshold) {
            resize();  // Resize if load factor exceeds the threshold
        }

        int idx = quadraticProbe(key);
        if (table[idx] == -1) {
            table[idx] = key;
            count++;
        }
    }

    // Search for a key in the hash table and return the index
    int search(int key) {
        int idx = hashFunction(key);
        int i = 1;
        while (table[idx] != -1) {
            if (table[idx] == key) {
                return idx;
            }
            idx = (hashFunction(key) + i * i) % size;
            i++;
        }
        return -1;  // Key not found
    }

    // Remove a key from the hash table
    void remove(int key) {
        int idx = search(key);
        if (idx != -1) {
            table[idx] = -1;  // Mark the slot as empty
            count--;
        }
    }

    // Print the current state of the hash table
    void printTable() {
        for (int i = 0; i < size; i++) {
            if (table[i] != -1) {
                std::cout << i << ": " << table[i] << std::endl;
            } else {
                std::cout << i << ": " << "-" << std::endl;
            }
        }
        std::cout << std::endl;
    }
};
