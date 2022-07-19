#include <iostream>
using namespace std;


struct Node
{
    int id = 0;
    int bf = 0;
    int WEI = 0;
    int RNK = 0;
    Node *left = nullptr;
    Node *right = nullptr;
};
struct Boode
{
    bool hc = 0;
    int wei = 0;
    Node *root = nullptr;
};

class avl
{
private:
    int data_RNK = 0;
    int total_data = 0;
    Node *Root = nullptr;

    Node *RL(Node *&root)
    {
        Node *R = root->right;
        Node *RL = R->left;
        R->left = root;
        root->right = RL;

        R->RNK = R->RNK + root->WEI + root->RNK;

        if (R->bf <= 0)
            root->bf = root->bf - 1;
        else
            root->bf = root->bf - 1 - R->bf;

        if (root->bf >= 0)
            R->bf = R->bf - 1;
        else
            R->bf = R->bf - 1 + root->bf;
        return R;
    }

    Node *RR(Node *&root)
    {
        Node *R = root->left;
        Node *RR = R->right;
        R->right = root;
        root->left = RR;

        root->RNK = root->RNK - R->RNK - R->WEI;

        if (R->bf >= 0)
            root->bf = root->bf + 1;
        else
            root->bf = root->bf + 1 - R->bf;

        if (root->bf <= 0)
            R->bf = R->bf + 1;
        else
            R->bf = R->bf + 1 + root->bf;
        return R;
    }

    Boode Insertion(int id, Boode comp)
    {
        if (comp.root == nullptr)
        {
            comp.root = new Node;
            comp.root->id = id;
            comp.root->WEI = comp.root->WEI + comp.wei;
            comp.hc = 1;
            return comp;
        }
        else if (id < comp.root->id)
        {
            comp.root->RNK += comp.wei;
            Boode temp;
            temp.hc = comp.hc;
            temp.root = comp.root->left;
            temp.wei = comp.wei;
            temp = Insertion(id, temp);
            comp.root->left = temp.root;
            comp.hc = temp.hc;
            comp.root->bf = comp.root->bf - comp.hc;
        }
        else if (id > comp.root->id)
        {
            Boode temp;
            temp.hc = comp.hc;
            temp.root = comp.root->right;
            temp.wei = comp.wei;
            temp = Insertion(id, temp);
            comp.root->right = temp.root;
            comp.hc = temp.hc;
            comp.root->bf = comp.root->bf + temp.hc;
        }
        else
        {
            comp.hc = 0;
            comp.root->WEI = comp.root->WEI + comp.wei;
            return comp;
        }

        if (comp.hc == 0)
        {
            comp.hc = 0;
            return comp;
        }

        else if (comp.root->bf == 0)
        {
            comp.hc = 0;
            return comp;
        }

        else if (comp.root->bf == 1 || comp.root->bf == -1)
        {
            comp.hc = 1;
            return comp;
        }

        else
        {
            if (comp.root->bf == -2)
            {
                if (comp.root->left->bf == 1)
                    comp.root->left = RL(comp.root->left);
                comp.root = RR(comp.root);
                comp.hc = 0;
                return comp;
            }
            else
            {
                if (comp.root->right->bf == -1)
                    comp.root->right = RR(comp.root->right);
                comp.root = RL(comp.root);
                comp.hc = 0;
                return comp;
            }
        }
    }


    int findDepth(int id, Node *root, int depth)
    {
        if (root->id == id)
        {
            return depth;
        }
        else if (root->id < id)
        {
            return findDepth(id, root->right, depth + 1);
        }
        else
        {
            return findDepth(id, root->left, depth + 1);
        }
    }

    Node* BinarySearch(int id, Node *root)
    {
        if (root == nullptr)
        {
            return root;
        }
        if (root->id == id)
        {
            return root;
        }
        else if (root->id < id)
        {
            return BinarySearch(id, root->right);
        }
        else
        {
            return BinarySearch(id, root->left);
        }
    }

    void EBinarySearch(int id, Node *root)
    {
        if (root == nullptr)
        {
            return;
        }
        if (root->id == id)
        {
            data_RNK += root->RNK;
            return;
        }
        else if (root->id < id)
        {
            data_RNK += root->RNK + root->WEI;
            EBinarySearch(id, root->right);
        }
        else
        {
            EBinarySearch(id, root->left);
        }
    }

public:
    void ADD(int id, int data)
    {
        Boode In;
        In.root = Root;
        In.wei = data;
        Root = Insertion(id, In).root; 
        total_data = total_data + data;
        cout << total_data << endl;
    }
    void WEI(int id)
    {
        Node *BS = BinarySearch(id, Root);
        if (BS == nullptr)
        {
            cout << "0 -1" << endl;
            return;
        }
        cout << BS->WEI << " " << findDepth(id, Root, 0) << endl;
    }
    void RNK(int id, int total)
    {
        EBinarySearch(id, Root);
        cout << data_RNK << endl;
        data_RNK = 0;
    }

};

int main()
{
    avl Tree;
    string operation = "";
    int id, data;
    string dataV;

    while(true)
    {
        cin >> operation;
        if(operation ==  "END"){break;}

        cin >> id;
        

        if (operation == "ADD") 
        {
            getline(cin, dataV);

            if(dataV == " ")
                data = 0;
            else
                data = stoi(dataV);
            
            Tree.ADD(id, data);
            
        }
        else if(operation == "WEI"){Tree.WEI(id);}
        else if(operation == "RNK"){Tree.RNK(id, 0);}
        
    }
    
}