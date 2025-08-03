#include <iostream>
template <typename T>
class Queue
{
private:
    struct Node
    {
        T val;
        Node* next;
    };
    void free(){
        while (head)
        {
            Node* node = head;
            head=head->next;
            delete node;
        }
    }

    Node* head{};
    Node* tail{};
public:
    ~Queue(){free();}

    bool empty(){
        return head == nullptr;
    }

    void enqueue(T x){
        if(!tail){
            head=tail=new Node{x,nullptr};
            return;
        }
        tail->next =new Node{x,nullptr};
        tail=tail->next;
    }
    void dequeue(){
        if (!head)
        {
            throw std::underflow_error("UnderFlow");
        }
        
        Node* tmp=head;
        head=head->next;
        if (!head)
        {
            tail=head=nullptr;
        }
        
        delete tmp;
    }
    
    T front(){
        return head != nullptr ? head->val: throw std::underflow_error("UnderFlow");
    }
    T back(){
         return tail != nullptr ? tail->val: throw std::underflow_error("UnderFlow");
    
    }
    
    void display(){
        std::cout << "{ ";
        Node* tmp=head;
        while (tmp)
        {
            std::cout <<tmp->val<<" ,";
            tmp=tmp->next;
        }        
        std::cout << "}"<<std::endl;
    }
   
};

int main(){
    Queue<int> que;
    que.enqueue(1);
    que.enqueue(2);
    que.enqueue(10);
    que.display();
    que.dequeue();
    que.dequeue();
    que.dequeue();
    que.display();
    
    std::cout << "Empty: " << que.empty() << std::endl; 

    std::cout << "Empty: " << que.empty() << std::endl; 
    que.back();

}