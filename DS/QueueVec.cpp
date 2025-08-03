#include <iostream>
#include <vector>
template <typename T>
class Queue
{
private:
    std::vector<T> data;
public:
    bool empty(){
        return data.empty();
    }

    void display(){
        if (data.empty())
        {
            throw std::underflow_error("UnderFlow");
        }
        std::cout << "{ ";
        
        for (const auto& it: data)
        {
            std::cout <<it << ", ";
        }

        std::cout << "}"<<std::endl;
    }

    void enqueue(T x){
        data.push_back(x);
    }
    void dequeue(){
        if(empty()){
           throw std::underflow_error("UnderFlow"); 
        }

        data.erase(data.begin());
    }

    T top(){
        if (empty())
        {
          return -1;
        }

        return data.front();
    }
};

int main(){
    Queue<int> queue;

    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);

    std::cout << "Queue contents: ";
    queue.display();

    std::cout << "Front element: " << queue.top() << "\n";

    queue.dequeue();
    std::cout << "Queue after dequeue: ";
    queue.display();

}




