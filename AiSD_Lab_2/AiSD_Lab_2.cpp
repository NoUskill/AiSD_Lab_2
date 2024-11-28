
#include <iostream>

class NodeBinTrees {
    public:
    int body;
    NodeBinTrees* parent;
    NodeBinTrees* left_child;
    int height;

    NodeBinTrees* right_child;
    NodeBinTrees(int i) {
        this->body = i;
        this->height = -1;
        this->left_child = this->parent = this->right_child = nullptr;
    }
    bool operator==(const NodeBinTrees& other) {
        if ((this->body==other.body)&&(this->parent==other.parent)&&(this->left_child==other.left_child)&&this->right_child==other.right_child) {
            return true;
        }
        else {
            return false;
        }
    }
    NodeBinTrees& operator=(const NodeBinTrees& other) {
        NodeBinTrees* temp = this->parent;
        delete[] this;

        this->body = other.body;
        this->left_child = other.left_child;
        this->right_child = other.right_child;
        this->parent = temp;
        return *this;
    }
};
class BinTrees {
    public:
    NodeBinTrees* m_tree_head;
    int m_tree_height;

    BinTrees() {
        this->m_tree_head = nullptr;
        m_tree_height = 1;
    }
    ~BinTrees() {
        if (!(m_tree_head==nullptr)) {
            clear(m_tree_head);
        }
    }
    void clear(NodeBinTrees* temp) {
        if (temp != nullptr) {
            if (temp->left_child != nullptr) {
                clear(temp->left_child);
            }
            if (temp->right_child != nullptr) {
                clear(temp->right_child);
            }
            std::cout << "\ndelete(" << temp->body << ")\n";
            delete[] temp;
            temp = nullptr;
        }

    }
    void appende(int i) {
        if (m_tree_head==nullptr) {
            m_tree_head = new NodeBinTrees(i);
            m_tree_head->height = 1;
        }
        else {
            NodeBinTrees* last_node = nullptr;
            NodeBinTrees* temp = this->m_tree_head;
            while (temp != nullptr){
                if (temp->body > i) {
                    last_node = temp;
                    temp = temp->left_child;
                }
                else {
                    last_node = temp;
                    temp = temp->right_child;
                }
            }
            temp = new NodeBinTrees(i);
            temp->height = last_node->height + 1;
            if (last_node->body > i) {
                last_node->left_child = temp;
                temp->parent = last_node;
            }
            else {
                last_node->right_child = temp;
                temp->parent = last_node;
            }
        }
    }
    NodeBinTrees* searchNode(int i) {
        NodeBinTrees* temp = this->m_tree_head;
        while (true){
            if (temp == nullptr) {
                return temp;
            }
            else if (temp->body==i) {
                return temp;
            }
            else if (temp->body>i) {
                temp = temp->left_child;
            }
            else {
                temp = temp->right_child;
            }
        }
    }
    void pop(NodeBinTrees* temp_dub){
        NodeBinTrees* temp = temp_dub;
        if (temp->parent==nullptr) {
            this->m_tree_head = nullptr;
            delete[] temp;
        }
        else if (((temp->left_child)==nullptr)&&((temp->right_child)==nullptr)) {
            if ((temp->parent->body)< temp_dub->body) {
                temp->parent->right_child = nullptr;
            }
            else {
                temp->parent->left_child = nullptr;
            }
            delete[] temp;

        }
        else if(temp->left_child==nullptr){
            if (temp->parent->body<temp->body) {
                temp->parent->right_child = temp->right_child;
            }
            else {
                temp->parent->left_child = temp->right_child;
            }
            delete[] temp;
        }
        else if (temp->right_child == nullptr) {
            if (temp->parent->body < temp->body) {
                temp->parent->right_child = temp->left_child;
            }
            else {
                temp->parent->left_child = temp->left_child;
            }
            delete[] temp;
        }
        else {
            NodeBinTrees* temp_max_left = temp->right_child;
            while (temp_max_left->left_child!=nullptr)
            {
                temp_max_left = temp_max_left->left_child;
            }
            std::swap(temp->body, temp_max_left->body);
            temp_max_left->body = temp->body + 1;
            this->pop(temp_max_left);
        }
    }
    int getMaxH(NodeBinTrees* temp) {
        if ((temp->left_child==nullptr)&&((temp->right_child == nullptr))) {
            return temp->height;
        }
        else if (temp->left_child == nullptr) {
            return getMaxH(temp->right_child);
        }
        else if (temp->right_child == nullptr) {
            return getMaxH(temp->left_child);
        }
        else {
            return std::max(getMaxH(temp->left_child), getMaxH(temp->right_child));
        }
    }
    void setHeightTrees() {
        this->m_tree_height = getMaxH(this->m_tree_head);
    }


    void printTreesStruct(NodeBinTrees* node,int level) {
        if (node != nullptr) {
            printTreesStruct(node->right_child, level + 1);
            for (int i = 0; i < level; ++i) std::cout << "  ";
            std::cout << node->body << std::endl;
            printTreesStruct(node->left_child, level + 1);
        }
    }
    void printTreesHeightSort(NodeBinTrees* node) {
        if (node != nullptr) {
            printTreesHeightSort(node->left_child);
            std::cout << node->body << " ";
            printTreesHeightSort(node->right_child);
        }
    }


    
};

class AVLTrees:public BinTrees {
public:
    using BinTrees::BinTrees;

    int getbalanceFacto(NodeBinTrees* temp) {
        if (temp == nullptr) {
            return 0;
        }
        else {
            int l_h;
            if (temp->left_child==nullptr) {
                l_h = temp->height;
            }
            else {
                l_h = temp->left_child->height;
            }
            int r_h;
            if (temp->right_child == nullptr) {
                r_h = temp->height;
            }
            else {
                r_h = temp->right_child->height;
            }
            return l_h-r_h;
        }
    }
    void leftRotate(NodeBinTrees* temp_B) {
        NodeBinTrees* temp_A = temp_B->parent;
        NodeBinTrees* temp_C = temp_B->right_child;

        temp_B->parent = temp_A->parent;
        if (temp_A->parent== nullptr) {
            this->m_tree_head = temp_B;
        }
        else {
            temp_A->parent->right_child = temp_B;
        }
        temp_A->right_child = nullptr;
        temp_B->left_child = temp_A;
        temp_A->parent = temp_B;
        if (temp_B->parent!=nullptr) {
            temp_B->height = temp_B->parent->height + 1;
        }
        else {
            temp_B->height = 1;
        }
        temp_A->height = temp_A->parent->height + 1;
        temp_C->height = temp_C->height - 1;
    }
    void rightRotate(NodeBinTrees* temp_B) {
        NodeBinTrees* temp_A = temp_B->parent;
        NodeBinTrees* temp_C = temp_B->left_child;

        temp_B->parent = temp_A->parent;
        if (temp_A->parent== nullptr) {
            this->m_tree_head = temp_B;
        }
        else {
            temp_A->parent->left_child = temp_B;
        }
        temp_A->left_child = nullptr;
        temp_B->right_child = temp_A;
        temp_A->parent = temp_B;
        if (temp_B->parent != nullptr) {
            temp_B->height = temp_B->parent->height + 1;
        }
        else {
            temp_B->height = 1;
        }
        temp_A->height = temp_A->parent->height + 1;
        temp_C->height = temp_C->height - 1;
    }
    void leftrightRotate(NodeBinTrees* temp_B) {
        NodeBinTrees* temp_A = temp_B->parent;
        NodeBinTrees* temp_C = temp_A->parent;
        temp_C->left_child = temp_B;
        temp_B->parent = temp_C;
        temp_A->right_child = nullptr;
        temp_B->left_child = temp_A;
        temp_A->parent = temp_B;
        temp_B->height = temp_B->parent->height + 1;
        temp_A->height = temp_A->parent->height + 1;
        rightRotate(temp_B);
    }
    void rightleftRotate(NodeBinTrees* temp_B) {
        NodeBinTrees* temp_C = temp_B->parent;
        NodeBinTrees* temp_A = temp_C->parent;

        temp_A->right_child = temp_B;
        temp_B->parent = temp_A;
        temp_C->left_child = nullptr;
        temp_B->right_child = temp_C;
        temp_C->parent = temp_B;

        temp_B->height = temp_B->parent->height + 1;
        temp_C->height = temp_C->parent->height + 1;


        leftRotate(temp_B);
    }
    void balance(NodeBinTrees* temp) {
        if (temp != nullptr) {
            int temp_factor = getbalanceFacto(temp);
            if (temp_factor == 0) {
                balance(temp->left_child);
                balance(temp->right_child);
            }
            else if (temp_factor == -1) {
                int temp_rightchild_factor = getbalanceFacto(temp->right_child);
                if (temp_rightchild_factor == 0) {
                    balance(temp->right_child);
                }
                else if (temp_rightchild_factor ==-1) {
                    leftRotate(temp->right_child);
                }
                else if (temp_rightchild_factor == 1) {
                    rightleftRotate(temp->right_child->left_child);
                }       
            }
            else if (temp_factor == 1) {
                int temp_leftchild_factor = getbalanceFacto(temp->left_child);
                if (temp_leftchild_factor == 0) {
                    balance(temp->left_child);
                   
                }
                else if (temp_leftchild_factor == -1) {
                    leftrightRotate(temp->left_child->right_child);
                }
                else if (temp_leftchild_factor == 1) {
                    
                    rightRotate(temp->left_child);
                }



            }
        }
    }


    void appende(int i) {
        BinTrees::appende(i);
        //метод балансировки
        balance(this->m_tree_head);
    }
    void pop(NodeBinTrees* temp) {
        BinTrees::pop(temp);
        //метод балансировки
        balance(this->m_tree_head);
    }


};


int main()
{
    AVLTrees test;
    test.appende(2);
    test.appende(4);
    test.appende(3);
    test.appende(1);
    test.appende(8);
    test.appende(5);
    test.appende(7);
    test.appende(9);
    test.printTreesStruct(test.m_tree_head,1);
    test.printTreesHeightSort(test.m_tree_head);
  


}
