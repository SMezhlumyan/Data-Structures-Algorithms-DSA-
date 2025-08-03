#include <iostream>
#include <stack>
using namespace std;

class AVL
{
private:
    struct Node
    {
        int val;
        Node *left;
        Node *right;
    };

    Node *root{};
    int size{};

    Node *RRotate(Node *node)
    {
        Node *x = node->left;
        node->left = x->right;
        x->right = node;
        return x;
    }

    Node *LRotate(Node *node)
    {
        Node *x = node->right;
        node->right = x->left;
        x->left = node;
        return x;
    }

    void freebs(Node *node)
    {
        if (!node)
            return;
        freebs(node->left);
        freebs(node->right);

        delete node;
    }

    int getBF(Node *node)
    {
        return (helperGetHeight(node->left) - helperGetHeight(node->right));
    }

    Node *mkBalanced(Node *node)
    {

        int bf = getBF(node);

        if (bf > 1 && getBF(node->left) >= 0) // -> LL
        {
            cout << "LL" << endl;
            return RRotate(node);
        }
        if (bf > 1 && getBF(node->left) < 0) // -> LR
        {
            cout << "LR" << endl;
            node->left = LRotate(node->left);
            return RRotate(node);
        }

        if (bf < -1 && getBF(node->right) <= 0) // -> RR
        {
            cout << "RR " << endl;
            return LRotate(node);
        }

        if (bf < -1 && getBF(node->right) > 0) // -> RL
        { 
            cout << "RL" << endl;
            node->right = RRotate(node->right);
            return LRotate(node);
        }
        return node;
    }

    Node *helpInserter(Node *node, int val)
    {
        if (!node)
            return new Node{val};

        if (node->val > val)
            node->left = helpInserter(node->left, val);
        else if (node->val < val)
            node->right = helpInserter(node->right, val);

        return mkBalanced(node);
    }

    Node *helperGetMin(Node *node)
    {
        while (node && node->left)
        {
            node = node->left;
        }
        return node;
    }
    Node *helperGetMax(Node *node)
    {
        while (node && node->right)
        {
            node = node->right;
        }
        return node;
    }

    int helperGetHeight(Node *node)
    {
        if (!node)
            return 0;

        int left = helperGetHeight(node->left);
        int right = helperGetHeight(node->right);

        return max(left, right) + 1;
    }

    Node *helperRemove(Node *node, int val)
    {
        if (!node)
            return node;

        if (node->val > val)
        {
            node->left = helperRemove(node->left, val);
        }
        else if (node->val < val)
        {
            node->right = helperRemove(node->right, val);
        }
        else
        {

            if (!node->left)
            {
                Node *tmp = node->right;
                --size;
                delete node;
                return tmp;
            }
            if (!node->right)
            {
                Node *tmp = node->left;
                --size;
                delete node;
                return tmp;
            }

            Node *pred = helperGetMax(node->left);
            node->val = pred->val;
            node->left = helperRemove(node->left, pred->val);
        }
        return mkBalanced(node);
    }

public:
    ~AVL() { freebs(root); }

    void insert(int val)
    {
        root = helpInserter(root, val);
        ++size;
    }

    Node *GetMin()
    {
        return helperGetMin(root);
    }

    Node *GetMax()
    {
        return helperGetMax(root);
    }

    Node *GetSuccsessor(Node *node)
    {
        if (!node || !root)
            return nullptr;

        if (node->right)
        {
            return helperGetMin(node->right);
        }

        Node *p = nullptr;
        Node *curr = root;

        while (curr && curr->val != node->val)
        {
            if (curr->val > node->val)
            {
                p = curr;
                curr = curr->left;
            }
            else
            {
                curr = curr->right;
            }
        }
        return p;
    }

    Node *GetPredessor(Node *node)
    {
        if (!node || !root)
            return nullptr;

        if (node->left)
            return helperGetMax(node->left);

        Node *p = nullptr;
        Node *curr = root;
        while (curr && curr->val != node->val)
        {
            if (curr->val > node->val)
            {
                curr = curr->left;
            }
            else
            {
                p = curr;
                curr = curr->right;
            }
        }

        return p;
    }

    int GeHeight()
    {
        return helperGetHeight(root);
    }

    void remove(int val)
    {
        root =helperRemove(root, val);
    }

    void preorderIter()
    {
        if (!root)
            return;

        Node *curr;

        stack<Node *> st;
        st.push(root);
        while (!st.empty())
        {
            curr = st.top();
            st.pop();
            cout << curr->val << " ";

            if (curr->right)
                st.push(curr->right);
            if (curr->left)
                st.push(curr->left);
        }
        cout << endl;
    }

    


};

int main()
{

    AVL avl;
    avl.insert(40);
    avl.insert(20);
    avl.insert(50);
    avl.insert(60);
    avl.insert(45);

    avl.remove(40);
    avl.preorderIter();

    // ll.insert(30);
    // ll.insert(20);
    // ll.insert(10);

    // AVL lr;
    // lr.insert(30);
    // lr.insert(10);
    // lr.insert(20);
    // lr.preorderIter();

    // AVL rr;
    // rr.insert(10);
    // rr.insert(20);
    // rr.insert(30);
    // rr.preorderIter();

    // AVL rl;
    // rl.insert(10);
    // rl.insert(30);
    // rl.insert(20);
    // rl.preorderIter();
}