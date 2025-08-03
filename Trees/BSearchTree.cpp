#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;
class BSearchTree
{
private:
    struct Node
    {
        int val;
        Node *left;
        Node *right;
    };
    Node *root{};
    int size {};

    void freebs(Node *node)
    {
        if (!node)
            return;
        freebs(node->left);
        freebs(node->right);

        delete node;
    }
    void PreDisplayhelper(Node *node)
    {
        if (!node)
            return;

        cout << node->val << " ";
        PreDisplayhelper(node->left);
        PreDisplayhelper(node->right);
    }
    void PostDisplayhelper(Node* node){
        if (!node)
            return;
        
        PostDisplayhelper(node->left);
        PostDisplayhelper(node->right);
        cout << node->val<< " ";
    }
    void InDisplayhelper(Node* node){
        if (!node) 
            return;

        InDisplayhelper(node->left);
        cout << node->val << " ";
        InDisplayhelper(node->right);
    }
    
    
    Node *getHelperMin(Node* node)
    {
        if (!node)
            return nullptr;

        Node *tmp = node;
        while (tmp->left)
        {
            tmp = tmp->left;
        }
        return tmp;
    }
    Node *getHelperMax(Node* node)
    {
        if (!node)
            return nullptr;
        Node *tmp = node;
        while (tmp->right)
        {
            tmp = tmp->right;
        }
        return tmp;
    }

    Node *helperinsert(Node *node, int val)
    {
        if (node == nullptr)
            return new Node{val, nullptr, nullptr};

        if (val < node->val)
            node->left = helperinsert(node->left, val);
        else if (val > node->val)
            node->right = helperinsert(node->right, val);

        return node;
    }

    int helperGetHigh(Node *node)
    {
        if (!node)
            return -1;
        int left = helperGetHigh(node->left);
        int right = helperGetHigh(node->right);
        return left > right ? left + 1 : right + 1; // std::max(left,right)+1
    }
    
    Node* helperRemove(Node* node, int val){
        if(!node) return nullptr; 

        if (val < node->val)
        {
            node->left = helperRemove(node->left,val);
        }
        else if (val > node->val)
        {
            node->right = helperRemove(node->right,val);
        }else{
            if(!node->right){ // return node -> left;
                Node* tmp = node->left; 
                delete node;
                return tmp;
            }
            if(!node->left) {  // return node -> right ;
                Node* tmp = node->right;
                delete node;
                return tmp;
            }
            
            Node* succ = getHelperMin(node->right);

            node->val =succ->val;
            node->right = helperRemove(node->right,succ->val);
        }

        return node;
      
    }
    bool getSearchHelper(Node* node, int val){
        if (!node)
            return false;
        if (node->val == val)
            return true;
        

        if (node->val > val)
            return getSearchHelper(node->left,val);
        else
            return getSearchHelper(node->right,val);
    }

     Node* getHelperSuccessor(Node* node){
        
        if (!root || !node)
            return nullptr;
               
        if (node && node->right )
        {
            return getHelperMin(node->right);
        }
        Node* anc = nullptr; 
        Node* curr = root; 

        while (curr && curr->val != node->val)
        {
            if ( curr->val > node->val)
            {
                anc = curr;
                curr = curr->left;
            }
            else{
                curr = curr->right;
            }
            
        }
        return  anc;
    }
    Node* getHelperPredessor(Node* node){
        if (!root || !node)
            return nullptr;
        
        if (node->left)
        {
            return getHelperMax(node->left);
        }
        Node* dec = nullptr;
        Node* curr = root;
        while (curr && curr->val != node->val)
        {
            if (curr->val > node->val)
            {
                curr = curr->left;    
            }
            else{
                dec = curr;
                curr = curr->right;
            }
            
        }
        return dec;
    }

public:
    ~BSearchTree()
    {
        freebs(root);
        root = nullptr;
    }

    void insert(int val)
    {
        root = helperinsert(root, val);
        ++size;
    }

    void display()
    {
        cout <<"Pre -> "; 
        PreDisplayhelper(root);
        cout << endl;
        // cout <<"Post -> ";
        // PostDisplayhelper(root);
        // cout << endl;
        // cout << "In -> ";
        // InDisplayhelper(root);
    }
    
   
    Node* getMin(){
        return getHelperMin(root);
    }
    Node* getMax(){
        return getHelperMax(root);
    }
    int getHigh()
    {
        return helperGetHigh(root);
    }
    int getSize(){
        return size;
    }
    void remove(int val){
        root = helperRemove(root,val);
        --size;
    }
    bool empty(){
        return size == 0 ;
    }
    Node* getSuccessor(){
        if(!root ) return nullptr ;
        return getHelperSuccessor(root);
    }
    Node* getPredessor(){
        if(!root ) return nullptr ;
        return getHelperPredessor(root);
    }
    
    Node* getSuccessor(Node* node){
        if(!root || !node) return nullptr ;
        return getHelperSuccessor(node);
    }
    Node* getPredessor(Node* node){
        if(!root || !node) return nullptr ;
        return getHelperPredessor(node);
    }
   
    bool search(int val){
        return getSearchHelper(root, val);
    }

    void preorderIter(){
        if (!root)
            return;
        
        Node* curr;

        stack<Node*> st;
        st.push(root);
        while (!st.empty())
        {
            curr = st.top();
            st.pop();
            cout << curr->val << " ";

            if (curr->right) st.push(curr->right);
            if (curr->left)  st.push(curr->left);

        }
        cout << endl;
    }

    void InorderIter(){
        if (!root)
            return;
        
        Node* curr = root;
        stack<Node*> st;

        while (curr || !st.empty())
        {
            while (curr){
                st.push(curr);
                curr = curr->left;
            }
            
            curr = st.top();
            st.pop();
            cout << curr->val << " ";
            curr =  curr->right;   
        }
        
        
    }
    void PostOrderIterative(){
        stack<Node* > s;
        Node* curr = root;
        Node* lastvisit = nullptr;

        while (!s.empty() || curr)
        {
            if (curr)
            {
                s.push(curr);
                curr = curr->left;
            }else{
                Node* node = s.top();

                if (node->right  && node->right != lastvisit)
                {
                    curr = node->right;
                }else{
                
                    cout <<node->val<<" ";
                    lastvisit = node;
                    s.pop();
                }
            }
            
        }
        
    }

    void BFSTraversal(){
        queue<Node*> q;
        q.push(root);
        while (!q.empty())
        {
            int size = q.size();
            while (size--) { 
                Node* tmp = q.front();
                q.pop();
                cout << tmp->val << " ";
                if(tmp->left) q.push(tmp->left);
                if(tmp->right) q.push(tmp->right);                
            }   
            cout << endl;
        }

    }

};

int main()
{
    BSearchTree bst;
    
    bst.insert(40);
    bst.insert(30);
    bst.insert(35);
    bst.insert(20);
    bst.insert(45);
    bst.insert(42);
    bst.insert(60);
    
    bst.BFSTraversal();


    // bst.PostOrderIterative();

    // bst.display();

    // cout << bst.search(40) << endl; 
    // cout <<"pre -> " <<  bst.getSuccessor(bst.getMax())->val<<endl;
    // cout << "Pre -> " << bst.getPredessor()<<endl;
    // bst.remove(40);
    // bst.display();
}