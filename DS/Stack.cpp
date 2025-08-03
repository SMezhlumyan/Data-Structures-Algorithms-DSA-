#include <iostream>
#include <vector>

template <typename T>
class Stack
{
private:
    std::vector<T> data;
public: 
    
    bool isEmpty() {return data.empty();}

    void push(T x){
        data.push_back(x);
    }

    T pop(){
        if (data.empty())
        {
          throw std::underflow_error("UnderFlow");
        }
        
        T ret = data.back();
        data.pop_back();
        return ret;
        
    }
    
    T top(){
        if (data.empty())
        {
            throw std::underflow_error("UnderFlow");
        }
        return data.back();
    }

    void display(){
        if (data.empty())
        {
            std::cout << "Stack is empty !" <<std::endl;
            return;
        }else{
            std::cout << "{ ";
            for (auto& it: data)
            {
                std::cout << it << ", ";
            }
            std::cout << "}"<<std::endl;
        }
        
    }
};

int main(){
    Stack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.pop();
    stack.display();
}
