#include <iostream>
#include <vector>
template <typename T>
class DLL
{
private:
    struct Node
    {
        T val;
        Node *prev;
        Node *next;
    };
    int size{};
    Node* head{};
    Node* tail{};
public:
    ~DLL(){freeDll();}

    int getsize() {return size;}
    void push_back(T x) {
        if (!tail)
        {
            tail=head=new Node{x,nullptr,nullptr};
            ++size;
            return;
        }
        tail->next = new Node{x,tail,nullptr};
        tail = tail->next;
        ++size;
    }
    void push_front(T x){
        if (!head)
        {
            head=tail= new Node{x,nullptr,nullptr};
            ++size;
            return;
        }
            Node* node = new Node{x,nullptr,head};
            head->prev=node;
            head=node;
        
    }

    void pop_back(){
        if (!tail)
        {
           throw std::underflow_error("UnderFlow");
        }
        
        if (!tail->prev)
        {
            delete tail;
            tail=head=nullptr;
        }else{
            tail=tail->prev;
            delete tail->next; 
            tail->next=nullptr;
        }
        --size;
    }
    void pop_front(){
        if (!head) throw std::underflow_error("UnderFlow");
        Node* tmp = head;
        head=head->next;
        if (head)
        {
            head->prev=nullptr;
        }else{
            head=tail=nullptr;
        }
        delete tmp;
        --size;
    }

    void insert(int val,int k){
        Node* tmp=head;
        if (k == 0)
        {
            push_front(val);
            return;
        }
        if(k == size+1){
            push_back(val);
            return;
        }
        while (tmp && --k) tmp=tmp->next;
        if (!tmp)
        {
            push_back(val);
            return;
        }
        
        Node* node = new Node{val,tmp,tmp->next};
        tmp->next=node;
        if (node->next) node->next->prev = node;
    }

    void display(){
        Node* tmp = head;
        std::cout <<"{ ";
        while (tmp)
        {
            std::cout << tmp->val << " ";
            tmp=tmp->next;
        }
        std::cout <<"}"<<std::endl;
    }
    void displayback(){
        Node* tmp = tail;
        std::cout <<"{ ";
        while (tmp)
        {
            std::cout << tmp->val << " ";
            tmp= tmp->prev;
        }
        std::cout <<"}"<<std::endl;
    }
    void freeDll(){
        while (head)
        {
        Node* tmp=head;
        head=head->next;
        delete tmp;
        }
        
    }
    void reverse() {
        if (!head) {
            throw std::underflow_error("UnderFlow");
        }
    
    Node* curr = head;
    Node* node=nullptr;

    while (curr)
    {
        node = curr->prev;
        curr->prev = curr->next;
        curr->next = node;

        curr=curr->prev;
    }
    
    if (node)
    {
        tail =head;
        head = node->prev;
    }

}

};

int main(){
    DLL<int> dll;
    dll.push_back(3);
    dll.push_back(2);
    dll.push_back(3);
    dll.display();
    dll.pop_front();
    dll.display();
    std::cout << dll.getsize();
    
}
