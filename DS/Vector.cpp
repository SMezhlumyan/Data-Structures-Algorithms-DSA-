#include <iostream>

template <typename T>
class Vector
{
private:
    T* data;
    size_t size;
    size_t capacity;

    void _reallocate(size_t new_cap){
        T* temp = new T[new_cap]; 
        for (int  i = 0; i < size; i++)
        {
            temp[i]=data[i];
        }
        delete data;
        data=temp;
        capacity=new_cap; 
    }
public:
    Vector() : data{nullptr} , size{0} , capacity {0}{};
    ~Vector(){
        delete data;
        data=nullptr;
        size=0;
        capacity=0;
    };

    void push_back(T el) { 
        if(capacity == size) _reallocate(capacity == 0 ? 1 : 2 * capacity );

        data[size++] = el;
    }
    void pop_back(){
        if(size>0) --size;
    }

    size_t _size() {
        return size;
    }
    size_t _capacity(){
        return capacity;
    }

    T& operator[](size_t index){
            if(index > size){
                throw std::out_of_range("Out of Range");
            }
            return data[index];
    }

    const T & operator[](size_t index) const{
            if(index > size){
                throw std::out_of_range("Out of Range");
            }
            return data[index];
    }
};


int main(){
    Vector <int> vec;
    vec.push_back(1);
    std::cout << vec[0];
}

