#include <iostream>
#include <vector>
#include <functional>
#include <forward_list>

class UnorderedSet
{

private:
    std::vector<std::forward_list<int>> buckets;
    static constexpr const double Max_Load_Factor=0.75;
    static constexpr int PRIMES[3] = {7, 17, 29};
    size_t size;
    int curr_prime_ind;


    double load_factor(){return static_cast<double>(size) / buckets.size();}
 
    size_t hash(const int& key){
        static std::hash<int> hasher;
        return hasher(key);
    }

    void rehash(){   
        if(curr_prime_ind+1 >= sizeof(PRIMES)/sizeof(PRIMES[0])) {
            throw std::runtime_error("Maximum Set size exceeded");
        }
        int new_bucket_count = PRIMES[++curr_prime_ind];
        std::vector<std::forward_list<int>> new_bucket(new_bucket_count);

        for (auto& bucket : buckets)
        {
            for (auto& elem : bucket)
            {
                size_t hashval = hash(elem);
                int index = hashval % new_bucket_count;
                new_bucket[index].push_front(elem);
            }
        }
        buckets=std::move(new_bucket);
    }

public:
    UnorderedSet(): size(0), curr_prime_ind(0), buckets(PRIMES[curr_prime_ind]) {}
    
    bool insert(int key){
       size_t hash_val = hash(key);
       int index = hash_val%buckets.size();

       for (auto& item : buckets[index])
       {
            if (item == key){ return false;}
       }

        buckets[index].push_front(key);
        size++;

        if (load_factor() > Max_Load_Factor ) 
        {
             rehash();
        }

       return true;
    }

    bool contains(int key){
        size_t hashval =hash(key);
        int index = hashval % buckets.size();
        for (auto& elem : buckets[index])
        {
            if (elem == key)
            {
                return true;
            }
            
        }
        return false;
    }

    bool erase(int key){
        size_t hashval = hash(key);
        int index = hashval%buckets.size();

        auto prev = buckets[index].before_begin();
        for ( auto it = buckets[index].begin(); it != buckets[index].end(); ++it)
        {
            if (*it == key)
            {
                buckets[index].erase_after(prev);
                --size;
                return true;
            }
            ++prev;
        }
        return false;

    }


};

int main(){

    UnorderedSet set;
    set.insert(10);
    set.insert(20);
    set.insert(30);
    std::cout <<set.erase(25)<<"\n";
    std::cout <<set.contains(20)<<"\n";
    std::cout <<set.contains(25)<<"\n";
    std::cout <<set.contains(10)<<"\n";

}

