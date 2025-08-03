#include <iostream>
#include <queue>
using namespace std;

enum Color
{
    RED,
    BLACK
};

struct Node
{
    int val;
    Color color;
    Node *left;
    Node *right;
    Node *par;

    Node() : val(0), color(BLACK), left(this), right(this), par(this) {}

    Node(int val, Node *NIL)
        : val(val), color(RED), left(NIL), right(NIL), par(NIL) {}
};

Node *NIL = new Node();

class RBTree
{

private:
    Node *root;

    void destroyTree(Node *node)
    {
        if (node != NIL)
        {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    void LeftRotate(Node *x)
    {
        Node *y = x->right;

        x->right = y->left;
        if (y->left != NIL)
        {
            y->left->par = x;
        }

        y->par = x->par;
        if (x->par == NIL)
        {
            root = y;
        }
        else if (x == x->par->left)
        {
            x->par->left = y;
        }
        else
        {
            x->par->right = y;
        }
        y->left = x;
        x->par = y;
    }

    void RightRotate(Node *x)
    {
        Node *y = x->left;

        x->left = y->right;
        if (y->right != NIL)
        {
            y->right->par = x;
        }

        y->par = x->par;
        if (x->par == NIL)
        {
            root = y;
        }
        else if (x == x->par->left)
        {
            x->par->left = y;
        }
        else
        {
            x->par->right = y;
        }
        y->right = x;
        x->par = y;
    }

    void RB_Insert_Fixup(Node *z)
    {
        while (z->par->color == RED)
        {
            if (z->par->par->left == z->par)
            {
                Node *y = z->par->par->right;
                if (y->color == RED)
                {
        // Case1
                    z->par->color = BLACK;
                    y->color = BLACK;
                    z->par->par->color = RED;
                    z = z->par->par;
                }
                else
                {
        // Case2
                    if(z == z->par->right){
                        z = z->par;
                        LeftRotate(z->par);
                    }
        //Case3
                    z->par->color = BLACK;
                    z->par->par->color = RED;
                    RightRotate(z->par->par);
                }
            }
            else
            {
                Node* y = z->par->par->left;
                if(y->color == RED){
        // Case1                    
                    z->par->color =BLACK;
                    y->color =BLACK;
                    z->par->par->color = RED;
                    z = z->par->par;
                }else{
        // Case2
                    if(z == z->par->left){
                        z = z->par;
                        RightRotate(z);
                    }
        // Case3
                    z->par->color = BLACK;
                    z->par->par->color = RED;
                    LeftRotate(z->par->par);
                }
            }
        }

        root->color = BLACK;
    }

    void Transplant(Node* u, Node* v){
        if(u->par == NIL){
            root = v;
        }else if(u == u->par->left){
            u->par->left = v;
        }else{ 
            u->par->right = v;
        }

        v->par = u->par;
    }

    Node* TreeMinimum(Node* x){
        Node* y = x;
        
        while(y->left != NIL){
            y = y->left;
        }

        return y;
    }

    void DeleteFixup(Node* x){
        while(x != root && x->color == BLACK){
            if(x == x->par->left){
                Node* w = x->par->right;
                
                if(w->color == RED){
                    w->color = BLACK;
                    x->par->color = RED;
                    LeftRotate(x->par);
                    w = x->par->right;
                }

                if(w->left->color== BLACK && w->right->color==BLACK){
                    w->color = RED;
                    x=x->par;
                }else{
                    if(w->right->color == BLACK){
                        w->left->color = BLACK;
                        w->color = RED;
                        RightRotate(w);
                        w =x->par->right;
                    }
                    
                    w->color = x->par->color;
                    x->par->color = BLACK;
                    w->right->color = BLACK;
                    LeftRotate(x->par);

                    x = root;
                }
            }else{
                Node* w = x->par->left;
                
                if(w->color == RED){
                    w->color = BLACK;
                    x->par->color =RED;
                    RightRotate(x->par);
                    w =x->par->left;
                }

                if(w->left->color == BLACK && w->right->color == BLACK){
                    w->color = RED;
                    x=x->par;
                }else{
                    if(w->left->color == BLACK){
                        w->right->color = BLACK;
                        w->color = RED;
                        LeftRotate(w);
                        w = x->par->left;
                    }

                    w->color = x->par->color;
                    x->par->color = BLACK;
                    w->left->color = BLACK;
                    RightRotate(x->par);
                
                    x=root;
                }
            }
        }

        x->color = BLACK;
    }



public:
    RBTree()
    {
        root = NIL;
    }

    ~RBTree()
    {
        destroyTree(root);
        delete NIL;
    }

    void Insert(int nval)
    {
        Node *z = new Node(nval, NIL);
        Node *x = root;
        Node *y = NIL;

        while (x != NIL)
        {
            y = x;
            if (x->val > z->val)
            {
                x = x->left;
            }
            else
            {
                x = x->right;
            }
        }

        z->par = y;

        if (y == NIL)
        {
            root = z;
        }
        else if (y->val > z->val)
        {
            y->left = z;
        }
        else
        {
            y->right = z;
        }

        RB_Insert_Fixup(z);
    }

    


    void  DeleteHelper(Node* z){ 
        Node* y = z;
        Color y_original_color = y->color;
        
        Node* x = NIL;

        if(z->left == NIL){
            x = z->right;
            Transplant(z,z->right);
        }else if(z->right == NIL){
            x = z->left;
            Transplant(z,z->left);
        }else{
            
            y = TreeMinimum(y->right);
            y_original_color = y->color;
            x = y->right;

            if(y != z->right){
                Transplant(y,y->right);
                y->right = z->right;
                y->right->par = y; 
            }else{
                x->par = y;
            }
            
            Transplant(z,y);
            y->left = z->left;
            y->left->par = y;
            y->color =z->color;
        }
        
        delete z; 

        if(y_original_color == BLACK){
            DeleteFixup(x);
        }
    }

    void Delete(int data){
        Node* z = root;
        while(z != NIL && z->val != data ){
            if(z->val > data){
                z = z->left;
            }else{
                z = z->right;
            }
        }

        if(z == NIL) return;

        DeleteHelper(z);
    }




    void printTree(Node* node, int indent = 0) {
        if (node == NIL) return;  

        printTree(node->right, indent + 6);

        cout << string(indent, ' ') << node->val 
            << "(" << (node->color == BLACK ? "B" : "R") << ")" << endl;

        printTree(node->left, indent + 6);
    
    }
    void display() {
        if (root == NIL) {
            cout << "Empty Tree" << endl;
            return;
        }
        printTree(root);
    }
};

int main(){
    RBTree rbt;
    rbt.Insert(15);
    rbt.Insert(10);
    rbt.Insert(20);
    rbt.Insert(30);
    rbt.Insert(25);
    rbt.Insert(17);
    
    rbt.Delete(25);
    rbt.display();
}