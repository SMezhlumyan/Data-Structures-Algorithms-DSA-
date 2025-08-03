#include <iostream>

class SOLL
{
private:
    struct Node {
        int val;
        Node* prev;
        Node* next;

        Node* des;
        Node* asc;
    };

    int size;

    Node* head;
    Node* tail;

    Node* asc_head;
    Node* des_head;

    void Coments(){
 
    // void PutInOrderBack(){
    //     Node* tmp = asc_head;
    //     while (tmp && tmp->val < tail->val)
    //     {
    //         tmp = tmp->asc;
    //     }
    //     if (tmp)
    //     {
    //         tail->des=tmp->des;
    //         tmp->des =tail;
    //         tail->asc=tmp;    
    //         while (asc_head->des)
    //         {
    //             asc_head =asc_head->des;
    //         }
    //     }else{
    //         tail->des = des_head;
    //         des_head->asc = tail;
    //         des_head = tail;
    //     }
    // }
    
    // void PutInOrderFront(){
         //     Node* tmp = asc_head;
         //     while (tmp && tmp->val < head->val)
         //     {
         //         tmp = tmp->asc;
         //     }
         //     if (tmp)
         //     {
         //         head->des=tmp->des;
         //         tmp->des =head;
         //         head->asc=tmp;
         //         while (asc_head->des)
         //         {
         //             asc_head =asc_head->des;
         //         }
         //     }else{
         //         head->des = des_head;
         //         des_head->asc = head;
         //         des_head = head;
         //     }
    // }

    // void PopInOrderFront(){
    //     if (head->asc && head->des)
    //     {
    //         head->asc->des=head->des;
    //         head->des->asc=head->asc; 
    //         std::cout <<1<<std::endl;
    //     }
    //     else if (!head->asc && !head->des)
    //     {
    //         des_head = asc_head=nullptr;
    //         std::cout <<2<<std::endl;
    //     }
    //     else if (head->asc && !head->des)
    //     {
    //         asc_head=asc_head->asc;
    //         asc_head->des=nullptr;
    //         std::cout <<3<<std::endl;
    //     }
    //     else if (head->des && !head->asc)
    //     {
    //        des_head=des_head->des;
    //        des_head->asc=nullptr;
    //        std::cout <<4<<std::endl;
    //     }
    // }
   
}

    void PutInOrder(Node* nn){
        if (nn->val<=asc_head->val)
        {
            asc_head->des=nn;
            nn->asc=asc_head;
            asc_head=nn;
        }else if (nn->val >= des_head->val){
            des_head->asc=nn;
            nn->des=des_head;
            des_head=nn;
        }else{
            Node* tmp = asc_head;
            while (tmp && tmp->val < nn->val)
            {
                tmp = tmp->asc;
            }
            nn->asc=tmp;
            nn->des = tmp->des;
            nn->des->asc=nn;
            nn->asc->des=nn;
        }
        
    }
    void PopInOrder(Node* nn ){
        if (nn->asc && nn->des)
        {
            nn->asc->des=nn->des;
            nn->des->asc=nn->asc; 
        }
        else if (!nn->asc && !nn->des)
        {
            des_head = asc_head=nullptr;
        }
        else if (nn->asc && !nn->des)
        {
            asc_head=asc_head->asc;
            asc_head->des=nullptr;
        }
        else if (nn->des && !nn->asc)
        {
           des_head=des_head->des;
           des_head->asc=nullptr;
        }
    }


public:
    SOLL(){
        size=0;
        head=nullptr;
        tail=nullptr;
        des_head=nullptr;
        asc_head=nullptr;
    }
    ~SOLL(){
        while (head)
        {
            Node* smth=head->next;
            delete head;
            head=smth;
        }
   
    }
    
    int getSize() {return size;}

    void push_back(int x){
        if (!tail)
        {
            head=tail=des_head=asc_head=new Node{x,nullptr,nullptr,nullptr,nullptr};
        }else{
            tail->next = new Node{x,tail,nullptr,nullptr,nullptr};
            tail = tail->next;
            PutInOrder(tail);
        } 
        size++;
    }
    void push_front(int x){
        if (!head)
        {
            tail= head = des_head=asc_head=new Node{x,nullptr,nullptr,nullptr,nullptr};
        }else{
            head->prev = new Node{x,nullptr,head,nullptr,nullptr};
            head=head->prev;
            PutInOrder(head);
        }
        size++;
    }

    void pop_front(){
        if (!head) throw std::underflow_error("UnderFlow");
        PopInOrder(head);
        Node* tmp = head;
        head=head->next;
        if (head)
        {
            head->prev=nullptr;
        }else{
            head=tail=nullptr;
        }
        --size;
        delete tmp;
    }
    void pop_back(){
        if (!tail) std::underflow_error("UnderFlow");
        PopInOrder(tail);
        Node* tmp =tail;
        tail=tail->prev;
        if (tail)
        {
            tail->next=nullptr;
        }else{
            head=tail=nullptr;
        }
        --size;
        delete tmp;
    }

    void InsertPos(int val, int pos){
        if (pos==0)
        {
            std::cout <<"Push_Front "<<std::endl;
            push_front(val);
        }
        else if (pos == size+1)
        {
            std::cout <<"Push_Back "<<std::endl;
            push_back(val);
        }
        else{
            Node* tmp = head;
            while (--pos)
            {
                tmp=tmp->next;
            }
            Node* nn=new Node{val,tmp,tmp->next,nullptr,nullptr};
            tmp->next=nn;
            tmp= tmp->next->next;
            if (tmp)
            {
                tmp->prev=nn;
            }
            ++size;
            PutInOrder(nn);
        } 
    }

    void display(){
        Node* tmp = head;
        std::cout << "{ ";
        while (tmp)
        {
            std::cout << tmp->val<<" ,";
            tmp=tmp->next;
        }
        std::cout <<"}"<<std::endl;
    }
    void displayBack(){
        Node* tmp = tail;
        std::cout << "{ ";
        while (tmp)
        {
            std::cout << tmp->val<<" ,";
            tmp=tmp->prev;
        }
        std::cout <<"}"<<std::endl;
    }
    void displayOrderAj(){
        Node* tmp = asc_head;
        std::cout << "Aj-> { ";
        while (tmp)
        {
            std::cout << tmp->val<<" ,";
            tmp=tmp->asc;
        }
        std::cout <<"}"<<std::endl;   
    }
    void displayOrderNv(){
        Node* tmp = des_head;
        std::cout << "Nv-> { ";
        while (tmp)
        {
            std::cout << tmp->val<<" ,";
            tmp=tmp->des;
        }
        std::cout <<"}"<<std::endl;   
    }
};

int main(){

    SOLL sol;

    
}
