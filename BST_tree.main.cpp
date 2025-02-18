//ALGO2 IS1 222A LAB03
//Łukasz Kasztelan
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <sstream>
using namespace std;
template<typename T>
class BST
{
    public:
    BST() noexcept
        : root(nullptr), size(0){}
    struct pole
    {
        pole(const T& date, pole* left = nullptr, pole* right = nullptr)
            : date(date), left(left), right(right)
        {}
        ~pole()
        {
        }
        T date;
        pole* left;
        pole* right;
        pole* up;
        int key;
    }; 
    pole* root;
    int size;
    void add(const T& date, int a)
    {
        pole* t = new pole(date);
        pole* tmp;
        t->key = a;
        tmp = root;
        if (size == 0)
        {
            root = new pole(date);
            t = root;  
            t->key = a;
            t->up = NULL;
        }
        else
        {
            while (true)
            {
                if (a < tmp->key)
                {
                    if (!tmp->left)
                    {
                        tmp->left = t;
                        break;
                    }
                    else tmp = tmp->left;
                }
                else
                {
                    if (!tmp->right)
                    {
                        tmp->right = t;
                        break;
                    }
                    else tmp = tmp->right;
                }
            }
            t->up = tmp;
        }
        size++;
    }
    unsigned pobierz_size() const noexcept
    {
        return size;
    }
    pole* find(pole* polee, int key)
    {  
        if ((polee == NULL) || (polee->key == key))
        {
            return polee;
        }
        if (polee->key < key)
        {
            return find(polee->left, key);
        }
        return find(polee->right, key);
    }
    pole* check(pole* polee, int key)
    {
        find(root, key);
        if (polee->key == key)
        {
            return polee;
        }
        else return NULL;
    }
    pole* remove(pole* root, int key) 
    {
        if (root == NULL) return root;
        if (key < root->key) root->left = remove(root->left, key);
        else if (key > root->key) root->right = remove(root->right, key);
        else 
        {
            if (root->left == NULL) 
            {
                pole* temp = root->right;
                size--;
                return temp;
            }
            else if (root->right == NULL) 
            {
                pole* temp = root->left;
                size--;
                return temp;
            }
            pole* temp = findMin(root->right);
            root->key = temp->key;
            root->right = remove(root->right, temp->key);
        }
        return root;
    }
    pole* findMin(pole* tmp) {
        if (tmp->left == NULL) {
            return tmp;
        }
        else {
            return findMin(tmp->left);
        }
    }
    pole* preorder(pole* root)
    {
        if (root)
        {
            cout << to_string(root);
            preorder(root->left);
            preorder(root->right);
        }
        return root;
    }
    pole* inorder(pole* root)
    {
        if (root)
        {
            inorder(root->left);
            cout << to_string(root);
            inorder(root->right);
        }
        return root;
    }
    string to_string(pole* root) const
    {
        if (size == 0)
            return "[]";
        ostringstream str; // pamiętaj o #include <sstream>
        pole* p = root;
        int left;
        if (p->left) left = p->left->key;
        else left = -1;
        int right;
        if (p->right) right = p->right->key;
        else right = -1;
        int up;
        if (p->up) up = p->up->key;
        else up = -1;
        str << "[ Klucz: " << p->key << " dane: " << p->date << " rodzic: " << up << " Potomek l: " << left << " Potomek r: " << right << " ]" << endl;
        return str.str(); // wydobycie napisu ze strumienia
    }
    void printt(pole* root)
    {
        if (root)
        {
            cout << to_string(root);
            printt(root->left);
            printt(root->right);
        }
    }
    void tree_height(pole* root) 
    {
        int left_h, right_h;
        if (root == NULL)
        {
            return 0;
        }            
        else 
        {
            left_h = tree_height(root->left);
            right_h = tree_height(root->right);
            return max(left_h, right_h) + 1;
        }
    }
    void DelTree(pole* root)
    {
        if (root)
        {
            DelTree(root->left);
            DelTree(root->right);
            size--;
            delete root;
        }
    }
};
struct some_object
{
    int a;
    char b;
    bool operator<(const some_object& data) const
    {
        return a < data.a || a == data.a && b < data.b;
    }
};
ostream& operator<<(ostream& out, const some_object& date)
{
    return out << date.a << " " << date.b;
}
bool operator==(const some_object& a, const some_object& b)
{
    return a.a == b.a && a.b == b.b;
}
#include<vector>
#include <numeric>
#include <algorithm>

int main()
{
    {
        std::vector<int> v(8);
        std::iota(v.begin(), v.end(),0);
        do
        {
            BST<int> t;
            for (int i : v)
                t.add(i, i);
            for (int i : v)
                t.remove(t.root, i);
        } while (std::next_permutation(v.begin(), v.end()));
        return 0;
    }
    /*BST<int> l;
    l.add(4,3);
    l.add(8,2);
    l.add(3,1);
    l.add(7,4);
    l.find(3);
    l.preorder(l.root);
    l.inorder(l.root);
    l.printt(l.root);
    l.tree_height(l.root);
    l.remove(l.root, 7);
    l.DelTree(l.root);
    return 0;*/
    srand(time(NULL));
    char random;
    const int MAX_ORDER = 3; // maksymalny rzad wielkosci dodawanych danych
    BST <some_object>* bst = new BST <some_object>(); // stworzenie
        for (int o = 1; o <= MAX_ORDER; o++)
        {
            const int n = pow(10, o); // rozmiar danych
            clock_t t1 = clock();
            for (int i = 0; i < n; i++)
            {
                random = ((rand() % ('z' + 1 - 'a')) + 'a');
                some_object so = some_object{ rand() % 10001, random };
                bst->add(so, (rand() % 100) + 1);
            }
            clock_t t2 = clock();
            bst->printt(bst->root); // wypis na ekran aktualnej postaci drzewa ( skrotowej ) wraz z pomiarami czasowymi i w / w wielkosciami
            cout << "Czas 1: " << t2 - t1 << endl;
                // wyszukiwanie
            const int m = pow(10, 2); // liczba prob wyszukiwania
            int hits = 0; // liczba trafien
            t1 = clock();
            for (int i = 0; i < m; i++)
            {
                random = ((rand() % ('z' + 1 - 'a')) + 'a');
                //some_object so = some_object{ rand() % 10001, random };// losowe dane jako wzorzec do wyszukiwania ( obiekt chwilowy )
                if (bst->remove(bst->root,(rand() % 100) + 1) != NULL)
                    hits++;
                //delete so;
            }
            t2 = clock();
            cout << "Czas 2:" << t2 - t1 << endl; // wypis na ekran pomiarow czasowych i liczby trafien
            cout << "Trafienia : " << hits;
            bst->DelTree(bst->root); // czyszczenie drzewa wraz z uwalnianiem pamieci danych
        }
    delete bst;
    return 0;

}


