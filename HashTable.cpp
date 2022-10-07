#include "HashTable.h"
#include <bits/stdc++.h>
#include <string>
using namespace std;


HashTable::HashTable()
{
    soua = 101;
    curr_items = 0;
    prime_gt_arr = nextPrime(soua/2);
    arr_p = new string[101];
    for(int i = 0; i<101; i++)
        arr_p[i] = "";
}


// hash table created to store n items, size of the array should be the smallest prime #
// equal to or greater than 2n
HashTable::HashTable(int n_items)
{
int sz_of_arr = generate_gteprime(2*n_items);
soua = sz_of_arr;
curr_items = 0;
prime_gt_arr = nextPrime(soua/2);
arr_p = new string[sz_of_arr];
for(int i = 0; i<sz_of_arr; i++)
    arr_p[i] = "";
}

HashTable::HashTable(const HashTable& htable)
{
    copy_hash(htable);
}

HashTable::~HashTable()
{
    delete_hash_helper();
    soua = 0;
    curr_items = 0;
}

HashTable& HashTable::operator=(const HashTable& htable)
{
    if(this != &htable)
    {
        delete_hash_helper();
        copy_hash(htable);
    }
    return *this;
}

//need to fix
void HashTable::insert(string elem)
{
    int arr_index = index_string(elem);
    if(arr_p[arr_index] != "")
        {
            while(1)
            {
                //double hashing
                int index_distance = prime_gt_arr - (mod_p2(elem));
                arr_index+=index_distance;
                if(arr_index > soua)
                {
                    //if the index extends beyond the max size
                    arr_index = arr_index - soua;
                }
                if (arr_p[arr_index] == "")
                    {
                    arr_p[arr_index] = elem;
                    curr_items++;
                    break;
                    }
            }
        }

    else
    {
        arr_p[arr_index] = elem;
        curr_items++;
    }
    double LF = loadFactor();
    if(LF > (.67))
    {
        h2();
    }

}

bool HashTable::find(string elem) const
{
    int arr_index = index_string(elem);
    if(arr_p[arr_index] == elem)
        return true;
    else
    {
        int index_distance = prime_gt_arr - (mod_p2(elem));

        // guarantees every index+1 is checked
        // in case many collisions occured
        // at best O(1) , at worst O(n)
        for(int i = 0; i <= curr_items; i++)
        {
            arr_index += index_distance;
            if(arr_index > soua)
                    {
                    //if the index extends beyond the max size
                    arr_index = arr_index - soua;
                    }
            if(arr_p[arr_index] == elem)
                return true;
            if(i == curr_items && arr_p[arr_index] != elem)
                return false;
        }
    }
}

int HashTable::size() const
{
    return curr_items;
}

int HashTable::maxSize() const
{
    return soua;
}

double HashTable::loadFactor() const
{
    double curr = (double) curr_items;
    double max_arr_size = (double) soua;
    return (curr/max_arr_size);
}

//prime number greater or equal to N
int HashTable::generate_gteprime(int N) const
{
    bool sieve[N*10];
    memset(sieve, true, sizeof(sieve));
    sieve[0] = sieve[1] = false;
    for (long long i = 2; i <= N*10; i++) {
        if (sieve[i]) {

            for (long long j = i * i; j <= N*10; j += i) {
                sieve[j] = false;
            }
        }
    }

    // There is always an answer possible
    while (true) {
        if (isPrime(sieve, N)) {
            return N;
        }
        else
            N++;
    }
}

//helper for generate_gteprime(int N)
bool HashTable::isPrime(bool* sieve, int num) const
{
    while (num) {
        if (!sieve[num]) {
            return false;
        }
        num /= 10;
    }
    return true;
}

//helper for copying one hash table to another
void HashTable::copy_hash(const HashTable& htable)
{
    soua = htable.maxSize();
    curr_items = htable.size();
    arr_p = new string[soua];
    for(int i = 0; i<soua; i++)
    {
        arr_p[i] = htable.arr_p[i];
    }
}

void HashTable::delete_hash_helper()
{
    for(int i = 0; i<soua; i++)
    {
        delete &arr_p[i];
    }
    arr_p = nullptr;
}

//compute the index of a given string using mod of the max size of the array
int HashTable::index_string(string word) const
{
    //making a shallow copy of the word param
    //into an array of char for processing
    char* word_arr;
    word_arr = &word[0];
    int result = word_arr[0] - 96;
    int x = 32;
    //word_arr contains the word param as an arr of char
    for (int i  = 1; i < (unsigned)strlen(word_arr); i++)
        {
            result = (result*x + (word_arr[i]-96))%soua;
        }
    return result;
}

//compute int % prime_gt_arr
int HashTable::mod_p2(string word) const
{
    //making a shallow copy of the word param
    //into an array of char for processing
    char* word_arr;
    word_arr = &word[0];
    int result = word_arr[0] - 96;
    int x = 32;
    //word_arr contains the word param as an arr of char
    for (int i  = 1; i < (unsigned)strlen(word_arr); i++)
        {
            result = (result*x + (word_arr[i]-96))%prime_gt_arr;
        }
    return result;
}

// helper for nextPrime(int n)
bool HashTable::isPrime_greater(int n) const
{
     // Corner cases
    if (n <= 1)  return false;
    if (n <= 3)  return true;

    // This is checked so that we can skip
    // middle five numbers in below loop
    if (n%2 == 0 || n%3 == 0) return false;

    for (int i=5; i*i<=n; i=i+6)
        if (n%i == 0 || n%(i+2) == 0)
           return false;

    return true;
}

// prime number greater than n
int HashTable::nextPrime(int n) const
{
     // Base case
    if (n <= 1)
        return 2;

    int prime = n;
    bool found = false;

    // Loop continuously until isPrime returns
    // true for a number greater than n
    while (!found) {
        prime++;

        if (isPrime_greater(prime))
            found = true;
    }

    return prime;
}

//second hash function
void HashTable::h2()
{
    int temp_max = soua;
    soua = nextPrime(2*soua);
    string* temp = new string[soua];
    for(int i = 0; i<soua; i++)
        temp[i] = "";
    prime_gt_arr = nextPrime(soua/2);

    for(int i = 0; i <temp_max; i++)
    {
        //if the original hash table index is non empty
        if(arr_p[i] != "")
        {
            //new index value based on new size of underlying array
            int arr_index = index_string(arr_p[i]);

            //if the index in temp is already occupied
            if(temp[arr_index] != "")
                    {
                        while(1)
                            {
                        int index_distance = prime_gt_arr - (mod_p2(arr_p[i]));
                        arr_index+=(index_distance);
                            if(arr_index > soua)
                                {
                                //if the index extends beyond the max size
                                arr_index = arr_index - soua;
                                }
                            if (temp[arr_index] == "")
                                {
                                temp[arr_index] = arr_p[i];
                                break;
                                }
                            }
                    }
            else
                temp[arr_index] = arr_p[i];
        }
        //if the index in the original hashtable is empty, next iteration
            else
                continue;
    }

    //delete original hash table
    for(int i = 0; i<temp_max; i++)
        {
        delete &arr_p[i];
        }
    arr_p = temp;
}

void HashTable::printHash() const
{
    for(int i = 0; i<soua;i++)
    {
        cout << i << ":  " << arr_p[i] << endl;
    }
}

string HashTable::string_at_index(int num) const
{
    string word = arr_p[num];
    return word;
}
