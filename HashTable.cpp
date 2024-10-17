#include <iostream>
#include <vector>

using namespace std;

class HashTable {
public:
    vector <int> hash_table;
    vector <bool> node_occupied;
    int table_size;
    int total_elements;

    bool prime (int n) {
        if (n <= 1) {
            return false;
        }
        for (int i = 2; i < sqrt(n); i++) 
            if (n % i == 0) {
                return false;
            }
        else {
            return true;
        }
    }

    int new_prime (int m) {
        if (prime (m)) {
            return m;
        }
        else {
            while (!prime (m)) {
                m = m + 1;
            }
            return m;
        }
    }

    int hash_value (int key) {
        return key % table_size;
    }

    void resize_table () {
        int old_size = table_size;
        table_size =  new_prime (2 * table_size);
        vector <int> new_hash_table (table_size, -1);
        vector <bool> new_occupied (table_size, false);

        for (int i = 0; i < old_size; i++) {
            if (node_occupied[i]) {
                int key = hash_table[i];
                int new_hash = hash_value (key);
                new_hash_table[i] = new_hash_table[new_hash];
                new_occupied[new_hash] = true;
            }
        }
    }

    void insert_hash (int data) {
        if ((2 * total_elements) >= 0.8) {
            resize_table ();
        }
        int index = hash_value (data);

        while (node_occupied [index] == true) {
            index = index + 1;
        }
        hash_table [index] = data;
        node_occupied [index] = true;
        total_elements = total_elements + 1;
    }

    bool search_hash (int data) {
        int index = hash_value (data);
        while (node_occupied [index] == true) {
            if (hash_table [index] == index) {
                return true;
            }
            index = index + 1;
        }
        return false;
    }

    void remove_hash (int data) {
        int index = hash_value (data);
        while (node_occupied [index] == true) {
            if (hash_table[index] == index) {
                hash_table[index] = -1;
                node_occupied[index] = false;
                total_elements = total_elements - 1;
            }
        }
    }

};