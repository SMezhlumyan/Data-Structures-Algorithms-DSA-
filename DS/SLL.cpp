#include <iostream>

class Node 
{
public:
    friend class List;
    Node* next;
    int val;
public:
    Node(int _val, Node* node = nullptr): val{_val}, next{node}{}
};
class List 
{
private:
    Node* head {};
    Node* tail {};
public:
    List() : head {nullptr} ,tail{nullptr} {};

    void push_front(int val){
        Node* temp = new Node(val);
        if (!head){
            head = temp;
            tail = head;
        }else{
            temp->next=head;
            head=temp;
        }
    }

    void push_back(int val){
        Node* temp= new Node(val);
        if(!tail){
            tail=head=temp;
        }else{
            tail->next=temp;
            tail=temp;
        }
    }


    void delete_front(){
        if(head){
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }

    }
    void display(){
        Node* tmp=head;
        while (tmp)
        {
            std::cout << tmp->val <<" ";
            tmp=tmp->next;
        }
        std::cout <<std::endl;
    }

    ~List(){
        while (head)
        {
            delete_front();
        }
    }

    Node* get_tail() {return tail;}
    Node* get_head() {return head;}

};

Node* getMidElement(Node* head){
    if(!head) return nullptr;
    Node* fast=head->next;
    Node* slow=head;
    while (fast && fast->next)
    {
        fast=fast->next->next;
        slow=slow->next;
    }
    return slow;
}

bool isCycled(Node* head){
    if(!head) return false;
    Node* fast=head;
    Node* slow=head;
    
    while (fast && fast->next)
    {
        if(slow==fast) return true;
        slow =slow->next;
        fast = fast->next->next;
    }
    return false;
}

Node* helper(Node* head){
    if(!head) return nullptr;
    Node* fast=head;
    Node* slow=head;
    
    while (fast && fast->next)
    {
        if(slow==fast) return slow;
        slow =slow->next;
        fast = fast->next->next;
    }
    return nullptr;
}
Node* getCycleFirstNode(Node* head){
    Node* cross= helper(head);
    Node* tmp = head;
    while (cross && cross != tmp)
    {
        cross = cross->next;
        tmp = tmp->next;
    }
    return cross;
    
}

Node* reverse(Node* head){
    Node* prev = nullptr;
    Node* curr = head;
    Node* next = nullptr;

    while (curr)
    {
        next=curr->next;
        curr->next = prev;
        prev=curr;
        curr=next;
    }

    return prev;
}
Node* recreverse(Node* head){
    if(!(head->next)) return head;

    Node* tmp = recreverse(head->next);

    head->next->next =head;
    head->next =nullptr;

    return tmp;
}

Node* merge(Node* h1,Node* h2){
    Node* dumy = new Node(0);
    Node* ptr=dumy;
    while (h1 && h2)
    {
        if(h1->val > h2->val){
            ptr->next=h2;
            h2=h2->next;
        }else{
            ptr->next=h1;
            h1=h1->next;    
        }
        ptr = ptr->next;
    }
    if (h1)
    {
        ptr->next=h1;
        ptr = ptr->next;
    }
    if (h2)
    {
        ptr->next=h2;
        ptr = ptr->next;
    }
    Node* ret=dumy->next;
    delete dumy;
    return ret;
}
Node* mergerec(Node* h1,Node* h2){
    if(!h1) return h2;
    if(!h2) return h1;

    if(h1->val < h2->val){
        h1->next = mergerec(h1->next,h2);
        return h1;
    }else{
        h2->next =mergerec(h1,h2->next);
        return h2;
    }
}

void printList(Node* head) {
    while (head) {
        std::cout << head->val << " ";
        head = head->next;
    }
    std::cout << std::endl;
}

Node* Mergesort(Node* head){
    if(!head || !head->next) return head;
    
    Node* tmp = getMidElement(head);
    Node* mid = tmp->next;
    tmp ->next =nullptr;
    
    head = Mergesort(head);
    mid = Mergesort(mid);
    return merge(head,mid);
}






int main(){



}