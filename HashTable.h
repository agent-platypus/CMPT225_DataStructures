#pragma once
#ifndef HASHTABLE_H_INCLUDED
#define HASHTABLE_H_INCLUDED
#include <string>
using namespace std;

class HashTable
{
public:
    HashTable();
    HashTable(int n_items);
    HashTable(const HashTable& htable);
    ~HashTable();
    HashTable& operator=(const HashTable& htable);
    void insert(string elem);
    bool find(string elem) const;
    int size() const;
    int maxSize() const;
    double loadFactor() const;
    void printHash() const;
    string string_at_index(int num) const;
private:
    //HELPER FUNCTIONS
    int generate_gteprime(int n) const;
    bool isPrime(bool* sieve, int num) const;
    void copy_hash(const HashTable& htable);
    void delete_hash_helper();
    int index_string(string word) const;
    bool isPrime_greater(int n) const;
    int nextPrime(int n) const;
    void h2();
    int mod_p2(string word) const;

    //ATTRIBUTES
    string* arr_p;
    int soua;
    int curr_items;
    int prime_gt_arr;
};

#endif // HASHTABLE_H_INCLUDED
