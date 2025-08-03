#include <iostream>
#include <vector>
#include <functional>

template <
    typename T,
    typename Container = std::vector<T>,
    typename Compare = std::less<T>
    >
class PQ   
{
private:

    Compare compare;
    Container heap;

    size_t getParent(int i) {return (i-1)/2;}
    size_t getLeftch(int i) {return 2*i+1;}
    size_t getRightch(int i) {return 2*i+2;}

    void heapifyDown(int i){
        int left = getLeftch(i);
        int right = getRightch(i);

        int index = i;
        if (left < heap.size() && compare(heap[left],heap[index]))
        {
            index = left;
        }
        if (right < heap.size() && compare(heap[right],heap[index]))
        {
            index = right;
        }


        if (index!=i)
        {
            std::swap(heap[index], heap[i]);
            heapifyDown(index);
        }
        
    }
    void heapifyUp(int i){ 
        while (i > 0 && compare(heap[i],heap[getParent(i)]))
        {
            std::swap(heap[i],heap[getParent(i)]);
            i = getParent(i);
        }    
    }

public:
   
    void make_heap(std::vector<T> vec){
        heap = vec;
        for (int i = (heap.size()/2) - 1; i >=0 ; --i)
        {
            heapifyDown(i);
        }
    }

    void pop(){
        if (heap.empty()) throw std::runtime_error("UnderFlow");
        
        heap[0] = heap.back();
        heap.pop_back();

        if (!heap.empty()){
            heapifyDown(0);
        }
    }

    void push(const T & value){
        heap.push_back(value);
        heapifyUp(heap.size()-1);
    }

    T top(){
        if (heap.empty()) throw std::runtime_error("UnderFlow");

        return  heap.front();
    }


    void display(){
        for (auto& it : heap)
        {
            std::cout <<it << ",";
        }
        std::cout << std::endl;
    }
};



int main(){
    PQ<int> pq; // less -> minheap
    
    pq.push(10);
    pq.push(5);
    pq.push(20);
    pq.push(15);
    pq.pop();
    pq.display();

    PQ<int,std::vector<int>,std::greater<int>>  pq2; // greter->maxheap
    // pq2.make_heap({10,5,20,15,3});
    pq2.push(10);
    pq2.push(5);
    pq2.push(20);
    pq2.push(15);
    pq2.push(3);
    pq2.display();
    return 0;
}