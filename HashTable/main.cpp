//
//  main.cpp
//  HashTable
//
//  Created by Kevin Liu on 2024-02-10.
//

#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>

// used for hashing
#include <functional>

// for insertion purposes only
#include <vector>
#include <iterator>

template <typename K, typename V>
class HashTable 
{
private:
    
    // node definition
    struct Node
    {
        K key;
        V value;
        Node* next;

        // default constructor
        Node(K k={}, V v={}, Node *n = nullptr) : key(k), value(v), next(n) {}
    };

    // max capacity
    int capacity;
    
    // 2D list
    Node** table;

    // hash function, generic type K
    int hash(K key)
    {
        return std::hash<K>{}(key) % capacity;
    }

public:
    
    // parametric constructor, capacity is 101 by default
    HashTable(int cap = 101) : capacity(cap)
    {
        table = new Node *[capacity] {};
    }

    // insert a new (key, value) pair, Theta(1)
    void Insert(K key, V value)
    {
        int index = hash(key);
        Node* newNode = new Node(key, value, table[index]);
        table[index] = newNode;
    }

    // delete a (key, value) pair, O(n) worst time, but unlikely
    bool Delete(K key, V value)
    {
        int index = hash(key);
        Node* current = table[index];
        Node* prev = nullptr;
        
//        std::cout << key << "\t" << value << "\n\n";
        
        while (current != nullptr)
        {
            // i found the key!
            if (current->key == key && current->value == value)
            {
                
                // if there are more than 1 elements in the chain
                if (prev)
                {
                    prev->next = current->next;
                } 
                
                // if there is only 1 element in the chain
                else
                {
                    table[index] = current->next;
                }
                
                // delete that (key, value) pair
                
                
                delete current;
                return true;
            }
            
            // keeps iterating to search for the key for deletion
            prev = current;
            current = current->next;
        }
        return false;
    }
    
    // finds the (key, value)
    void Find(K key, V value)
    {
        int index = hash(key);
        Node *current = table[index];
        bool flag = false;
        
        // iterating through the bucket
        while(current != nullptr)
        {
            if(current->key == key && current->value == value)
                flag = true;
            
            current = current->next;
        }
        
        if(flag)
            std::cout << "key -> " << key << " exists and its value is -> " << value << std::endl;
        else
            std::cout << "key -> " << key << " does not exist." << std::endl;
    }
    
    // update a pair
//    bool Update(K key, V value, V value_new)
//    {
//        int index = hash(key);
//        Node* current = table[index];
//        Node* prev = nullptr;
//        
//        while (current != nullptr)
//        {
//            // i found the key!
//            if (current->key == key && current->value == value)
//            {
//                
//                // if there are more than 1 elements in the chain
//                if (prev)
//                {
//                    prev->next = current->next;
//                }
//                
//                // if there is only 1 element in the chain
//                else
//                {
//                    table[index] = current->next;
//                }
//                
//                current->value = value_new;
//                return true;
//            }
//
//            prev = current;
//            current = current->next;
//        }
//        return false;
//    }
    
    
    bool Update(K key, V old_value, V new_value)
    {
        int index = hash(key);
        Node* current = table[index];
        
        while (current != nullptr)
        {
            // Check for matching key (and optionally old value)
            if (current->key == key && current->value == old_value)
            {
                // Update the value
                current->value = new_value;
                return true; // Update successful
            }
            current = current->next; // Move to the next node
        }
        return false; // Key not found or old value did not match
    }

    
    void Enumerate(void)
    {
        Node *iterator;
        bool has_data = false;
        
        for(int i = 0; i < capacity; i++)
        {
            iterator = table[i];
            
            while(iterator != nullptr)
            {
                if(iterator->value != "")
                {
                    std::cout << std::setw(20) << std::left << iterator->value;
                    iterator = iterator->next;
                    has_data = true;
                }
                if(has_data)
                {
                    puts("");
                    has_data = false;
                }
            }
            
        }
    }
    
    ~HashTable()
    {
        for (int i = 0; i < capacity; i++)
        {
            // pointer to the table of pointers
            Node *iterator = table[i];
            
            // delete the field
            while (iterator != nullptr)
            {
                Node *prev = iterator;
                iterator = iterator->next;
                delete prev;
            }
        }
        
        // delete the record
        delete[] table;
    }
};

//template <typename K, typename V>
//void InsertData(HashTable<K, V> &obj)
//{
//    std::vector<std::string> key = {"Directors", "Movie Titles", "Released Year", "Scores"};
//    std::vector<std::string> value = {
//        "Rob Minkoff", "Bill Condon", "Josh Cooley", "Brad Bird", "Lake Bell",
//        "The Lion King", "Beauty and the Beast", "The Story 4", "Mission Impossible", "The Secret Life of Pets",
//        "2019", "2017", "2019", "2018", "2016",
//        "3.50", "4.20", "4.50", "5.00", "3.90"
//    };
//    
//    
//    int counter_lower_bound = 0;
//    int counter_upper_bound = 5;
////    std::vector<std::string>::iterator i;
////    std::vector<std::string>::iterator j = value.begin();
//    
//    for(int i = 0; i < key.size()+1; i++)
//    {
//        for(int j = counter_lower_bound; (j < counter_upper_bound) && (j < value.size()); j++)
//        {
//            obj.Insert(key[i], value[j]);
//            
//            std::cout << "inserting key -> " << key[i] << "  value -> " << value[j] << std::endl;
//            
//            counter_lower_bound++;
//        }
//        counter_upper_bound += counter_lower_bound;
//    }
//    
//    puts("");
//    puts("");
//}

template <typename K, typename V>
void InsertData(HashTable<K, V> &obj)
{
    std::vector<std::string> keys = {"Directors", "Movie Titles", "Released Year", "Scores"};
    std::vector<std::vector<std::string>> values = 
    {
        {"Rob Minkoff", "Bill Condon", "Josh Cooley", "Brad Bird", "Lake Bell"},
        {"The Lion King", "Beauty and the Beast", "Toy Story 4", "Mission Impossible", "The Secret Life of Pets"},
        {"2019", "2017", "2019", "2018", "2016"},
        {"3.50", "4.20", "4.50", "5.00", "3.90"}
    };

    for (size_t i = 0; i < keys.size(); i++)
    {
        for (size_t j = 0; j < values[i].size(); ++j) 
        {
            obj.Insert(keys[i], values[i][j]);
        }
    }
}


template <typename K, typename V>
void DeleteData(HashTable<K, V> &obj)
{
    obj.Delete("Movie Titles", "The Secret Life of Pets");
    obj.Delete("Scores", "3.90");
    obj.Delete("Released Year", "2016");
    obj.Delete("Directors", "Lake Bell");
}


template <typename K, typename V>
void UpdateData(HashTable<K, V> &obj)
{
    obj.Update("Movie Titles", "Toy Story 4", "Toy Story 3");
    obj.Update("Released Year", "2019", "2010");
    obj.Update("Directors", "Josh Cooley", "Lee Unkrich");
    obj.Update("Scores", "4.50", "5");
}


template <typename K, typename V>
void FindData(HashTable<K, V> &obj)
{
    obj.Find("Movie Titles", "Mission Impossible");
    obj.Find("Directors", "Bill Condon");
    obj.Find("Released Year", "2018");
    obj.Find("Scores", "3.50");
}


int main()
{
    HashTable<std::string, std::string> table;
    HashTable<std::string, std::string> table_new;
    HashTable<std::string, std::string> table_new_new;
    
    // Insert() test case
    InsertData(table);
    table.Enumerate();
    
    puts("");
    puts("");
    
    // Delete() test case
    DeleteData(table);
    table.Enumerate();
    
    puts("");
    puts("");
    
    // Update() test case
    InsertData(table_new);
    UpdateData(table_new);
    table_new.Enumerate();
    
    puts("");
    puts("");
    
    // Find() test case
    InsertData(table_new_new);
    FindData(table_new_new);
    
    puts("");
    puts("");
    
    // Enumerate() test case
    table_new_new.Enumerate();
    
    puts("");
    return 0;
}
