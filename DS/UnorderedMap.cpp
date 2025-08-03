#include <iostream>
#include <vector>
#include <forward_list>
#include <functional>
class Unordered_Map
{
private:
    
    
    static constexpr double Max_Load_Factor = 0.75;
    static  constexpr int  PRIMES[3] = {7, 17, 19};


    int size;
    int curr_prime_ind;
    std::vector< std::forward_list< std::pair<std::string, int> > > buckets;
    
    size_t hash(std::string key){
        static std::hash<std::string> hash_string;
        return hash_string(key);
    }
    double  load_factor(){
        return static_cast<double>(size) / buckets.size();
    }

    void rehash(){
        if (curr_prime_ind+1 >= sizeof(PRIMES)/sizeof(PRIMES[0]))
        {
            throw std::runtime_error("Maximum Map size exceeded");
        }
        
        std::vector< std::forward_list< std::pair<std::string, int> > > new_buckets (PRIMES[++curr_prime_ind]);
        
        for (auto& bucket :buckets)
        {
            for (auto &elem : bucket)
            {
                size_t hashval =hash(elem.first);
                int index = hashval % buckets.size();

                new_buckets[index].push_front(elem);
            }
            
        }
        
        buckets = std::move(new_buckets); 
    }

public:
    Unordered_Map() : size(0), curr_prime_ind(0), buckets(PRIMES[curr_prime_ind]) {}

    int& operator[](std::string key){
        size_t hashval = hash(key);
        int index =hashval%buckets.size();

        for (auto & elem : buckets[index])
        {
            if (elem.first == key)
            {
                return elem.second;
            }      
        }

        buckets[index].emplace_front(key,0);
        ++size;
        if (load_factor()  > Max_Load_Factor)
        {
            rehash();
        }        
        return buckets[index].front().second;
    }
    void insert(std::pair<std::string, int> pack){
        size_t hashval = hash(pack.first);
        int index = hashval%buckets.size();

        for (auto & elem : buckets[index])
        {
            if (elem.first == pack.first)
            {
                elem.second=pack.second;
                return;
            }
        }
        buckets[index].push_front(pack);
        ++size;

        if (load_factor() > Max_Load_Factor ) 
        {
             rehash();
        }

    }

    bool contains(std::string key){
        size_t hashval = hash(key);
        int index = hashval % buckets.size();

        for (auto & elem: buckets[index])
        {
            if(elem.first == key){
                return true;
            }
        }

        return false;
    }

    void erase(std::string key){
        size_t hashval = hash(key);
        int index = hashval % buckets.size();

        auto prev = buckets[index].before_begin();
        for(auto it=buckets[index].begin() ;it != buckets[index].end(); ++it){
            if ((*it).first == key)
            {
                buckets[index].erase_after(prev);
                --size;
                return;
            }
            ++prev;
        }
    }
};

using namespace std;

int main(){

    Unordered_Map map;
    map["hello"] = 2;
    cout << map["hello"];
    map.insert({"hello",5});

}