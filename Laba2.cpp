#include <iostream>
#include <string>

//Бинарное дерево поиска, без повторений, удаление с заменой на минимальный справа
//Посчитать количество ключей в дереве

struct Node
{
    int x;
    Node* left;
    Node* right;
};

struct Tree
{
    Node *root;
};

void init(Tree &T) //инициализация
{
    T.root = NULL;
}

void addNode(Tree &T, int x)  //добавление узла
{
    Node *newNode = new Node;
    newNode->x = x;
    newNode->left = NULL;
    newNode->right = NULL;
    Node *p = NULL;
    Node *cur = T.root;
    while (cur != NULL)
    {
        p = cur;
        if (newNode->x < cur->x)
        {
            cur = cur->left;
        }
        else if (newNode->x == cur->x)
        {
            std::cout << "Элемент " << x << " уже присутствует в дереве" << std::endl;
            return;
        }
        else cur = cur->right;
    }
    if (p == NULL)
    {
        T.root = newNode;
    }
    else if (newNode->x < p->x)
    {
        p->left = newNode;
    }
    else p->right = newNode;
}

void transplant(Tree& T, Node* d, Node* r, Node* p)   
{
    if (p == NULL)
        T.root = r;
    else if (d == p->left)
        p->left = r;
    else p->right = r;
}

Node* min(Node* n, Node*& m)
{
    while (n->left != NULL)
    {
        m = n;
        n = n->left;
    }
    return n;
}

bool foundNode(Tree T, int x, Node*& cur1, Node*& par) //поиск заданного элемента
{
    Node* cur = T.root;
    while (cur != NULL)
    {
        par = cur;
        if ((x < par->x) && (par->left != NULL))
        {
            if (par->left->x == x)
            {
                cur1 = par->left;
                cur = NULL;
                return true;
            }
            else
            {
                cur = cur->left;
                if (cur == NULL)
                {
                    std::cout << "Элемент не найден" << std::endl;
                    return false;
                }
            }

        }
        else if ((x > par->x) && (par->right != NULL))
        {
            if (par->right->x == x)
            {
                cur1 = par->right;
                cur = NULL;
                return true;
            }

            else
            {
                cur = cur->right;
                if (cur == NULL)
                {
                    std::cout << "Элемент не найден" << std::endl;
                    return false;
                }
                    
            }

        }
        else if (((x < par->x) && (par->left == NULL)) || ((x > par->x) && (par->right == NULL)))
        {
            std::cout << "Элемент не найден" << std::endl;
            return false;
        }
        else
        {
            cur1 = par;
            par = NULL;
            cur = NULL;
            return true;
        }
    }
}

void delNode(Tree &T, int x) //удаление заданного элемента из дерева
{
    Node* par = NULL;
    Node* par_min = NULL;
    
    Node* cur1 = NULL;
    Node* r;
    foundNode(T, x, cur1, par);
    
    if (cur1 != NULL)
    {
        if (cur1->left == NULL)
        {
            transplant(T, cur1, cur1->right, par);
            delete(cur1);
        }
        else if (cur1->right == NULL)
        {
            transplant(T, cur1, cur1->left, par);
            delete(cur1);
        }
        else
        {
            par_min = cur1;
            r = min(cur1->right, par_min);
            if (par_min != cur1)
            {
                transplant(T, r, r->right, par_min);
                r->right = cur1->right;
            }
            transplant(T, cur1, r, par);
            r->left = cur1->left;
            delete(cur1);
        }
    }
    
}

void delTreePart(Node* root)
{
    Node* cur = root;
    if (cur == NULL)
        return;
    delTreePart(cur->left);
    delTreePart(cur->right);
    delete(cur);
}

void delTree(Tree& T) //освобождение памяти
{
    delTreePart(T.root->left);
    delTreePart(T.root->right);
    T.root = NULL;
}

void countKeyPart(Node *root, int &count) 
{
    Node* cur = root;
    if (cur == NULL)
        return;
    countKeyPart(cur->left, count);
    countKeyPart(cur->right, count);
    count++;
}

int countKey(Tree T) //количество ключей в дереве
{
    int count = 0;
    countKeyPart(T.root, count);
    std::cout << "Количество ключей в дереве: " << count << std::endl;
    return count;
}

void printNode(int x, int h)
{
    for (int i = 0; i < h; i++)
    {
        std::cout << " ";
    }
        std::cout << x << std::endl;
}

void printPodTree(Node *n, int h)
{
    if (n == NULL)
    {
        return;
    }
    printPodTree(n->right, h+4);
    printNode(n->x, h);
    printPodTree(n->left, h+4);
}

void printTree(Tree T) //печать дерева
{
    std::cout << "------------------------------" << std::endl;
    printPodTree(T.root, 0);
    std::cout << "------------------------------" << std::endl;
}

Tree T, T1, T2;
Node* par,* cur;
int count;

int main()
{
    setlocale(LC_ALL, "Russian");
    init(T);
    addNode(T, 20);
    addNode(T, 8);
    addNode(T, 7);
    addNode(T, 25);
    addNode(T, 23);
    addNode(T, 10);
    addNode(T, 18);
    addNode(T, 1);
    addNode(T, 28);
    addNode(T, 7);
    addNode(T, 21);
    addNode(T, 12);
    addNode(T, 22);
    addNode(T, 9);
    printTree(T);
    //delTree(T);
    //printTree(T);
    //countKey(T);
    //delNode(T, 777);
    //printTree(T);
    //count = countKey(T);
    //delNode(T, 8);
    //printTree(T);
    //count = countKey(T);
    //delNode(T, 20);
    //printTree(T);
    //count = countKey(T);
    //delNode(T, 25);
    //printTree(T);
    //count = countKey(T);

    init(T1);
    printTree(T1);
    addNode(T1, 3);
    //addNode(T1, 17);
    //addNode(T1, 13);
    //addNode(T1, 18);
    //printTree(T1);
    //std::cout << foundNode(T1, 3, cur, par);
    //delNode(T1, 17);
    //printTree(T1);

    /*for (int i = 1; i <=6; i++)
    {
        addNode(T, i);
        addNode(T, 10 - i);

    }*/
    /* count = countKey(T);
    delNode(T, 53);
    printTree(T);
    count = countKey(T);
    delTree(T);
    addNode(T, 53);
    addNode(T, 13);
    addNode(T, 24);
    addNode(T, 61);
    addNode(T, 72);
    addNode(T, 55);
    addNode(T, 54);
    addNode(T, 14);
    addNode(T, 37);
    delNode(T, 53);
    delNode(T, 13);
    delNode(T, 24);
    delNode(T, 61);
    delNode(T, 72);
    delNode(T, 55);
    delNode(T, 54);
    delNode(T, 14);
    delNode(T, 37);*/
    /*for (int i = 1; i <=10; i += 2) {
        std::cout << std::endl << "i=" <<  i <<std:: endl;
        delNode(T,  i);

        printTree(T);
    }*/
}
