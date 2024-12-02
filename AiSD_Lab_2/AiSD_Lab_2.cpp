#include <fstream>
#include <iostream>
#include <cstring>
#include <vector>
#include <random>
#include <set>

class NodeBinTrees {
public:
    int body;
    NodeBinTrees* parent;
    NodeBinTrees* left_child;
    int height;
    NodeBinTrees* right_child;
    NodeBinTrees(int i = -1) {
        this->body = i;
        this->height = 1;
        this->left_child = nullptr;
        this->parent = nullptr;
        this->right_child = nullptr;
    }
    bool operator==(const NodeBinTrees& other) {
        if ((this->body == other.body) && (this->parent == other.parent) && (this->left_child == other.left_child) && this->right_child == other.right_child) {
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
    void append(int i) {
        if (m_tree_head == nullptr) {
            m_tree_head = new NodeBinTrees(i);
            m_tree_head->height = 1;
        }
        else {
            NodeBinTrees* last_node = nullptr;
            NodeBinTrees* temp = this->m_tree_head;
            while (temp != nullptr) {
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
    void pop(NodeBinTrees* temp_dub) {
        NodeBinTrees* temp = temp_dub;
        if (temp->parent == nullptr) {
            this->m_tree_head = nullptr;
            delete[] temp;
        }
        else if (((temp->left_child) == nullptr) && ((temp->right_child) == nullptr)) {
            if ((temp->parent->body) < temp_dub->body) {
                temp->parent->right_child = nullptr;
            }
            else {
                temp->parent->left_child = nullptr;
            }
            delete[] temp;

        }
        else if (temp->left_child == nullptr) {
            if (temp->parent->body < temp->body) {
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
            while (temp_max_left->left_child != nullptr)
            {
                temp_max_left = temp_max_left->left_child;
            }
            std::swap(temp->body, temp_max_left->body);
            temp_max_left->body = temp->body + 1;
            this->pop(temp_max_left);
        }
    } 
   
    BinTrees() {
        this->m_tree_head = nullptr;
        m_tree_height = 1;
    }
    ~BinTrees() {
        if (!(m_tree_head == nullptr)) {
            clear(m_tree_head);
        }
        this->m_tree_head = nullptr;
    }
    void cleartree() {
        if (!(m_tree_head == nullptr)) {
            clear(m_tree_head);
        }
        this->m_tree_head = nullptr;
    }
    void clear(NodeBinTrees* temp) {
        if (temp != nullptr) {
            if (temp->left_child != nullptr) {
                clear(temp->left_child);
            }
            if (temp->right_child != nullptr) {
                clear(temp->right_child);
            }
            temp = nullptr;
            delete[] temp;
        }

    } 
    NodeBinTrees* searchNode(int i) {
        NodeBinTrees* temp = this->m_tree_head;
        while (true) {
            if (temp == nullptr) {
                return temp;
            }
            else if (temp->body == i) {
                return temp;
            }
            else if (temp->body > i) {
                temp = temp->left_child;
            }
            else {
                temp = temp->right_child;
            }
        }
    }
    int getMaxH(NodeBinTrees* temp) {
        if (temp == nullptr) {
            return 0;
        }
        if ((temp->left_child == nullptr) && ((temp->right_child == nullptr))) {
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
    int getHeight(NodeBinTrees* node) {
        return node ? node->height : 0;
    }
    //обходы
    // В глубину 
    //левый узел правый
    void dfsInOrder(NodeBinTrees* node) {
        if (!node) return;
        dfsInOrder(node->left_child);
        std::cout << node->body << " ";
        dfsInOrder(node->right_child);
    }
    //узел левый правый
    void dfsPreOrder(NodeBinTrees* node) {
        if (!node) return;
        std::cout << node->body << " ";
        dfsPreOrder(node->left_child);
        dfsPreOrder(node->right_child);
    }

    //левый правый узел
    void dfsPostOrder(NodeBinTrees* node) {
        if (!node) return;
        dfsPostOrder(node->left_child);
        dfsPostOrder(node->right_child);
        std::cout << node->body << " ";
    }
    //по порядку
    void printTreesHeightSort(NodeBinTrees* node) {
        if (node != nullptr) {
            printTreesHeightSort(node->left_child);
            std::cout << node->body << " ";
            printTreesHeightSort(node->right_child);
        }
    }

    void printTreesHeightSort() {
        printTreesHeightSort(m_tree_head);
    }

    //в ширину 
    void printTreesStruct() {
        printTreesStruct(m_tree_head, 0);
    }
    void printTreesStruct(NodeBinTrees* node, int level) {
        if (node != nullptr) {
            printTreesStruct(node->right_child, level + 1);
            for (int i = 0; i < level; ++i) std::cout << "  ";
            std::cout << node->body << std::endl;
            printTreesStruct(node->left_child, level + 1);
        }
    }
};




class AVLTrees:public BinTrees {
public:

    int getHeight(NodeBinTrees* node) {
        return node ? node->height : 0;
    }

    void updateHeight(NodeBinTrees* node) {
        if (node) {
            node->height = 1 + std::max(getHeight(node->left_child), getHeight(node->right_child));
        }
    }

    int getBalance(NodeBinTrees* node) {
        return node ? getHeight(node->left_child) - getHeight(node->right_child) : 0;
    }

    NodeBinTrees* rotateRight(NodeBinTrees* y) {
        NodeBinTrees* x = y->left_child;
        NodeBinTrees* T = x->right_child;

        x->right_child = y;
        y->left_child = T;

        if (T) T->parent = y;
        x->parent = y->parent;
        y->parent = x;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    NodeBinTrees* rotateLeft(NodeBinTrees* x) {
        NodeBinTrees* y = x->right_child;
        NodeBinTrees* T = y->left_child;

        y->left_child = x;
        x->right_child = T;

        if (T) T->parent = x;
        y->parent = x->parent;
        x->parent = y;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    NodeBinTrees* appendNode(NodeBinTrees* node, int value) {
        if (!node) {
            return new NodeBinTrees(value);
        }

        if (value < node->body) {
            node->left_child = appendNode(node->left_child, value);
            node->left_child->parent = node;
        }
        else if (value > node->body) {
            node->right_child = appendNode(node->right_child, value);
            node->right_child->parent = node;
        }
        else {
            return node; 
        }

        updateHeight(node);

        int balance = getBalance(node);

       
        if (balance > 1 && value < node->left_child->body) {
            return rotateRight(node);
        }

       
        if (balance < -1 && value > node->right_child->body) {
            return rotateLeft(node);
        }

        
        if (balance > 1 && value > node->left_child->body) {
            node->left_child = rotateLeft(node->left_child);
            return rotateRight(node);
        }

        
        if (balance < -1 && value < node->right_child->body) {
            node->right_child = rotateRight(node->right_child);
            return rotateLeft(node);
        }

        return node;
    }


    NodeBinTrees* popNode(NodeBinTrees* node, int value) {
        if (!node) return node;

        if (value < node->body) {
            node->left_child = popNode(node->left_child, value);
        }
        else if (value > node->body) {
            node->right_child = popNode(node->right_child, value);
        }
        else {
            if (!node->left_child || !node->right_child) {
                NodeBinTrees* temp = node->left_child ? node->left_child : node->right_child;
                if (!temp) {
                    temp = node;
                    node = nullptr;
                }
                else {
                    *node = *temp;
                }
                delete temp;
            }
            else {
                NodeBinTrees* temp = getMinValueNode(node->right_child);
                node->body = temp->body;
                node->right_child = popNode(node->right_child, temp->body);
            }
        }

        if (!node) return node;

        updateHeight(node);

        int balance = getBalance(node);

        if (balance > 1 && getBalance(node->left_child) >= 0) {
            return rotateRight(node);
        }

        if (balance > 1 && getBalance(node->left_child) < 0) {
            node->left_child = rotateLeft(node->left_child);
            return rotateRight(node);
        }

        if (balance < -1 && getBalance(node->right_child) <= 0) {
            return rotateLeft(node);
        }

        if (balance < -1 && getBalance(node->right_child) > 0) {
            node->right_child = rotateRight(node->right_child);
            return rotateLeft(node);
        }

        return node;
    }

    NodeBinTrees* getMinValueNode(NodeBinTrees* node) {
        NodeBinTrees* current = node;
        while (current->left_child) {
            current = current->left_child;
        }
        return current;
    }

    AVLTrees() :BinTrees() {}

    void append(int value) {
        m_tree_head = appendNode(m_tree_head, value);
        m_tree_height = getHeight(m_tree_head);
    }

    void pop(int value) {
        m_tree_head = popNode(m_tree_head, value);
        m_tree_height = m_tree_head !=nullptr ? getHeight(m_tree_head) : 0;
    }
};

class NodeRedBlackTrees {
public:
    int color;// 0-red, 1-black
    int body;
    NodeRedBlackTrees* parent;
    NodeRedBlackTrees* left_child;
    NodeRedBlackTrees* right_child;

    NodeRedBlackTrees(int i = -1) {
        this->body = i;
        this->left_child = this->parent = this->right_child = nullptr;
        this->color = 0;
    };
};
class RedBlackTrees {
public:
    NodeRedBlackTrees* m_tree_head;
    int m_tree_height;
    void clear(NodeRedBlackTrees* temp) {
        if (temp != nullptr) {
            if (temp->left_child != nullptr) {
                clear(temp->left_child);
            }
            if (temp->right_child != nullptr) {
                clear(temp->right_child);
            }
            delete[] temp;
            temp = nullptr;
        }
    }
    ~RedBlackTrees() {
        cleartree();
    }
    void cleartree() {
        if (!(m_tree_head == nullptr)) {
            clear(m_tree_head);
        }
        this->m_tree_head = nullptr;
    }
    RedBlackTrees() {
        m_tree_head = nullptr;
        m_tree_height = 1;
    }

    int getMaxH(NodeRedBlackTrees* temp, int i) {
      
        i++;
        
        if ((temp->left_child == nullptr) && ((temp->right_child == nullptr))) {
            return i;
        }
        else if (temp->left_child == nullptr) {
            return getMaxH(temp->right_child,i);
        }
        else if (temp->right_child == nullptr) {
            return getMaxH(temp->left_child,i);
        }
        else {
            return std::max(getMaxH(temp->left_child,i), getMaxH(temp->right_child,i));
        }
    }
    void setHeightTrees() {
        this->m_tree_height = getMaxH(this->m_tree_head,0);
    }
    void leftRotate(NodeRedBlackTrees*& temp_B) {
        NodeRedBlackTrees* child = temp_B->right_child;
        temp_B->right_child = child->left_child;
        if (temp_B->right_child != nullptr)
            temp_B->right_child->parent = temp_B;
        child->parent = temp_B->parent;
        if (temp_B->parent == nullptr)
            m_tree_head = child;
        else if (temp_B == temp_B->parent->left_child)
            temp_B->parent->left_child = child;
        else
            temp_B->parent->right_child = child;
        child->left_child = temp_B;
        temp_B->parent = child;
    }
    void rightRotate(NodeRedBlackTrees*& temp_B) {//B=x A=y
        NodeRedBlackTrees* child = temp_B->left_child;
        temp_B->left_child = child->right_child;
        if (temp_B->left_child != nullptr)
            temp_B->left_child->parent = temp_B;
        child->parent = temp_B->parent;
        if (temp_B->parent == nullptr)
            m_tree_head = child;
        else if (temp_B == temp_B->parent->left_child)
            temp_B->parent->left_child = child;
        else
            temp_B->parent->right_child = child;
        child->right_child = temp_B;
        temp_B->parent = child;
    }
    void colorSwap(NodeRedBlackTrees* temp) {
        if (temp != nullptr) {
            if (temp->color == 1) {
                if ((getColor(temp->left_child) == 0) && (getColor(temp->right_child) == 0)) {
                    temp->left_child->color = 1;
                    temp->right_child->color = 1;
                    if (temp->parent != nullptr) {
                        temp->color = 0;
                    }
                    else {
                        temp->color = 1;
                    }
                }
            }
        }

    }
    int getColor(NodeRedBlackTrees* temp) {
        return (temp == nullptr ? 1 : temp->color);
    }

    void balance(NodeRedBlackTrees*& temp) {
        NodeRedBlackTrees* parent = nullptr;
        NodeRedBlackTrees* grandparent = nullptr;
        while (temp != m_tree_head && temp->color == 0&& temp->parent->color == 0) {
            parent = temp->parent;
            grandparent = parent->parent;
            if (parent == grandparent->left_child) {
                NodeRedBlackTrees* uncle = grandparent->right_child;
                if (uncle != nullptr
                    && uncle->color == 0) {
                    grandparent->color = 0;
                    parent->color = 1;
                    uncle->color = 1;
                    temp = grandparent;
                }
                else {
                    if (temp == parent->right_child) {
                        leftRotate(parent);
                        temp = parent;
                        parent = temp->parent;
                    }
                    rightRotate(grandparent);
                    std::swap(parent->color, grandparent->color);
                    temp = parent;
                }
            }
            else {
                NodeRedBlackTrees* uncle = grandparent->left_child;
                if (uncle != nullptr
                    && uncle->color == 0) {
                    grandparent->color = 0;
                    parent->color = 1;
                    uncle->color = 1;
                    temp = grandparent;
                }
                else {
                    if (temp == parent->left_child) {
                        rightRotate(parent);
                        temp = parent;
                        parent = temp->parent;
                    }
                    leftRotate(grandparent);
                    std::swap(parent->color, grandparent->color);
                    temp = parent;
                }
            }
        }
        m_tree_head->color = 1;
    }
    void popBalance(NodeRedBlackTrees*& temp)
    {
        while (temp != m_tree_head && temp->color == 1) {
            if (temp == temp->parent->left_child) {
                NodeRedBlackTrees* sibling = temp->parent->right_child;
                if (sibling->color == 0) {
                    sibling->color = 1;
                    temp->parent->color = 0;
                    leftRotate(temp->parent);
                    sibling = temp->parent->right_child;
                }
                if ((sibling->left_child == nullptr
                    || sibling->left_child->color == 1)
                    && (sibling->right_child == nullptr
                        || sibling->right_child->color
                        == 1)) {
                    sibling->color = 0;
                    temp = temp->parent;
                }
                else {
                    if (sibling->right_child == nullptr
                        || sibling->right_child->color == 1) {
                        if (sibling->left_child != nullptr)
                            sibling->left_child->color = 1;
                        sibling->color = 0;
                        rightRotate(sibling);
                        sibling = temp->parent->right_child;
                    }
                    sibling->color = temp->parent->color;
                    temp->parent->color = 1;
                    if (sibling->right_child != nullptr)
                        sibling->right_child->color = 1;
                    leftRotate(temp->parent);
                    temp = m_tree_head;
                }
            }
            else {
                NodeRedBlackTrees* sibling = temp->parent->left_child;
                if (sibling->color == 0) {
                    sibling->color = 1;
                    temp->parent->color = 0;
                    rightRotate(temp->parent);
                    sibling = temp->parent->left_child;
                }
                if ((sibling->left_child == nullptr
                    || sibling->left_child->color == 1)
                    && (sibling->right_child == nullptr
                        || sibling->right_child->color
                        == 1)) {
                    sibling->color = 0;
                    temp = temp->parent;
                }
                else {
                    if (sibling->left_child == nullptr
                        || sibling->left_child->color == 1) {
                        if (sibling->right_child != nullptr)
                            sibling->right_child->color = 1;
                        sibling->color = 0;
                        leftRotate(sibling);
                        sibling = temp->parent->left_child;
                    }
                    sibling->color = temp->parent->color;
                    temp->parent->color = 1;
                    if (sibling->left_child != nullptr)
                        sibling->left_child->color = 1;
                    rightRotate(temp->parent);
                    temp = m_tree_head;
                }
            }
        }
        temp->color = 1;
    }
    void append(int key)
    {
        NodeRedBlackTrees* temp = new NodeRedBlackTrees(key);
        NodeRedBlackTrees* parent = nullptr;
        NodeRedBlackTrees* current = m_tree_head;
        while (current != nullptr) {
            parent = current;
            if (temp->body < current->body) {
                current = current->left_child;
            }
            else {
                current = current->right_child;
            }
        }
        temp->parent = parent;
        if (parent == nullptr) {
            m_tree_head = temp;
        }
        else if (temp->body < parent->body) {
            parent->left_child = temp;
        }
        else {
            parent->right_child = temp;
        }
        balance(temp);
    }
    void pop(int key)
    {
        NodeRedBlackTrees* temp = m_tree_head;
        NodeRedBlackTrees* z = nullptr;
        NodeRedBlackTrees* x = nullptr;
        NodeRedBlackTrees* y = nullptr;
        while (temp != nullptr) {
            if (temp->body == key) {
                z = temp;
            }

            if (temp->body <= key) {
                temp = temp->right_child;
            }
            else {
                temp = temp->left_child;
            }
        }

        if (z == nullptr) {
            std::cout << "Нету в дереве" << std::endl;
            return;
        }
        y = z;
        int yOriginalColor = y->color;
        if (z->left_child == nullptr) {
            x = z->right_child;
            swap(z, z->right_child);
        }
        else if (z->right_child == nullptr) {
            x = z->left_child;
            swap(z, z->left_child);
        }
        else {
            NodeRedBlackTrees* current = z->right_child;
            while (current->left_child != nullptr){
                current = current->left_child;
            }
            y = current;
            yOriginalColor = y->color;
            x = y->right_child;
            if (y->parent == z) {
                if (x != nullptr)
                    x->parent = y;
            }
            else {
                swap(y, y->right_child);
                y->right_child = z->right_child;
                y->right_child->parent = y;
            }
            swap(z, y);
            y->left_child = z->left_child;
            y->left_child->parent = y;
            y->color = z->color;
        }
        delete z;
        if (yOriginalColor == 1) {
            popBalance(x);
        }
    }
    void swap(NodeRedBlackTrees*& temp_1, NodeRedBlackTrees*& temp_2)
    {
        if (temp_1->parent == nullptr) {
            this->m_tree_head = temp_2;
        }
        else if (temp_1 == temp_1->parent->left_child) {
            temp_1->parent->left_child = temp_2;
        }
        else {
            temp_1->parent->right_child = temp_2;
        }
        if (temp_2 != nullptr) {
            temp_2->parent = temp_1->parent;
        }
    }
    
    NodeRedBlackTrees* searchNode(int i) {
        NodeRedBlackTrees* temp = this->m_tree_head;
        while (true) {
            if (temp == nullptr) {
                return temp;
            }
            else if (temp->body == i) {
                return temp;
            }
            else if (temp->body > i) {
                temp = temp->left_child;
            }
            else {
                temp = temp->right_child;
            }
        }
    }
    //обходы 
    // В глубину 
    //левый узел правый
    void dfsInOrder(NodeRedBlackTrees* node) {
        if (!node) return;
        dfsInOrder(node->left_child);
        std::cout << node->body << " ";
        dfsInOrder(node->right_child);
    }
    //узел левый правый
    void dfsPreOrder(NodeRedBlackTrees* node) {
        if (!node) return;
        std::cout << node->body << " ";
        dfsPreOrder(node->left_child);
        dfsPreOrder(node->right_child);
    }

    //левый правый узел
    void dfsPostOrder(NodeRedBlackTrees* node) {
        if (!node) return;
        dfsPostOrder(node->left_child);
        dfsPostOrder(node->right_child);
        std::cout << node->body << " ";
    }
    //по порядку
    void printTreesHeightSort(NodeRedBlackTrees* node) {
        if (node != nullptr) {
            printTreesHeightSort(node->left_child);
            std::cout << node->body << " ";
            printTreesHeightSort(node->right_child);
        }
    }

    void printTreesHeightSort() {
        printTreesHeightSort(m_tree_head);
    }

    //в ширину 
    void printTreesStruct() {
        printTreesStruct(m_tree_head, 0);
    }
    void printTreesStruct(NodeRedBlackTrees* node, int level) {
        if (node != nullptr) {
            printTreesStruct(node->right_child, level + 1);
            for (int i = 0; i < level; ++i) std::cout << "  ";
            std::cout << ((node->color == 0) ? "R" : "B") << node->body << std::endl;
            printTreesStruct(node->left_child, level + 1);
        }
    }
};

  


std::vector<int> generateUniqueRandomIntArray(int n, int min, int max) {
    std::vector<int> arr;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(min, max);
    while (arr.size() < n) {
        int num = distrib(gen);
        if (std::find(arr.begin(), arr.end(), num) == arr.end()) {
            arr.push_back(num);
        }
    }
    return arr;
}
std::vector<int> generateSortedIntArray(int n) {
    std::vector<int> arr;
    int num = 1;
    while (arr.size() < n) {
         arr.push_back(num);
         num++;
    }
    return arr;
}






int main()
{
    std::ofstream dataFile("data.txt");
    std::vector<int> random;
    AVLTrees arr_avl;
    for (int x = 1; x <= 1001; x += 20) {
        random = generateUniqueRandomIntArray(x, 1, x * 5);
        for (int i = 0; i < x; i++) {
            arr_avl.append(random[i]);
          /*  std::cout << random[i] << " ";*/
        }
        
        dataFile << x << ' ' << arr_avl.m_tree_height << ' ';
        arr_avl.cleartree();
    }
    arr_avl.cleartree();
    dataFile << '\n';

    for (int x = 1; x <= 1001; x += 20) {
        random = generateSortedIntArray(x);
        for (int i = 0; i < x; i++) {
            arr_avl.append(random[i]);
            /*  std::cout << random[i] << " ";*/
        }
        dataFile << x << ' ' << arr_avl.m_tree_height << ' ';
        arr_avl.cleartree();
    }
    arr_avl.cleartree();
    dataFile << '\n';
    RedBlackTrees arr_redblack;
    for (int x = 1; x <= 1001; x += 20) {
        random = generateUniqueRandomIntArray(x, 1, x * 5);
        for (int i = 0; i < x; i++) {
            arr_redblack.append(random[i]);
            /*  std::cout << random[i] << " ";*/
        }
        arr_redblack.setHeightTrees();
        dataFile << x << ' ' << arr_redblack.m_tree_height << ' ';
        arr_redblack.cleartree();
    }
    dataFile << '\n';

    for (int x = 1; x <= 1001; x += 20) {
        random = generateSortedIntArray(x);
        for (int i = 0; i < x; i++) {
            arr_redblack.append(random[i]);
            /*  std::cout << random[i] << " ";*/
        }
        arr_redblack.setHeightTrees();
        dataFile << x << ' ' << arr_redblack.m_tree_height << ' ';
        arr_redblack.cleartree();
        
    }
    dataFile << '\n';

    BinTrees arr_bin;

    for (int x = 1; x <= 1001; x += 20) {
        random = generateUniqueRandomIntArray(x, 1, x * 5);
        for (int i = 0; i < x; i++) {
            arr_bin.append(random[i]);
            /*  std::cout << random[i] << " ";*/
        }
        arr_bin.setHeightTrees();
        dataFile << x << ' ' << arr_bin.m_tree_height << ' ';
        arr_bin.cleartree();
    }
    dataFile << '\n';

    for (int x = 1; x <= 1001; x += 20) {
        random = generateSortedIntArray(x);
        for (int i = 0; i < x; i++) {
            arr_bin.append(random[i]);
            /*  std::cout << random[i] << " ";*/
        }
        arr_bin.setHeightTrees();
        dataFile << x << ' ' << arr_bin.m_tree_height << ' ';
        arr_bin.cleartree();
    }
    dataFile << '\n';

    dataFile.close();
}