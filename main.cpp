#include "HashTable.cpp"

int main() {
    HashTable ht(7);  // Initial size

    ht.insert(3);
    ht.printTable();
    
    ht.insert(12);
    ht.printTable();
    
    ht.insert(3);  // This should not be allowed
    ht.printTable();
    
    ht.insert(9);
    ht.printTable();
    
    ht.insert(1);
    ht.printTable();
    
    ht.insert(6);
    ht.printTable();
    
    ht.insert(5);
    ht.printTable();
    
    ht.insert(7);
    ht.printTable();
    
    ht.insert(23);
    ht.printTable();
    
    ht.insert(10);
    ht.printTable();
    
    ht.remove(12);
    ht.printTable();
    
    ht.insert(12);
    ht.printTable();

    return 0;
}
// int main() {
//     int initialSize = 7; 
//     HashTable ht(initialSize);
//     // Example test case
//     ht.insert(1);
//     ht.printTable();
//     ht.insert(6);
//     ht.printTable();
//     ht.insert(15);
//     ht.printTable(); 
//     ht.insert(25);
//     ht.printTable();
//     ht.remove(15);
//     ht.printTable();
//     ht.insert(29);  
//     ht.printTable(); 
//     int find = ht.search(22);
//     std::cout << "Found at:" << find << std::endl;
//     return 0;
// }
