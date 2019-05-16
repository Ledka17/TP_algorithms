/* Дано число N < 106 и последовательность пар целых чисел из [-231, 231] длиной N.
 * Построить декартово дерево из N узлов, характеризующихся парами чисел (Xi, Yi). Каждая пара чисел (Xi, Yi)
 * определяет ключ Xi и приоритет Yi в декартовом дереве. Добавление узла в декартово дерево выполняйте второй версией алгоритма,
 * рассказанного на лекции: При добавлении узла (x, y) выполняйте спуск по ключу до узла P с меньшим приоритетом.
 * Затем разбейте найденное поддерево по ключу x так, чтобы в первом поддереве все ключи меньше x, а во втором больше или равны x.
 * Получившиеся два дерева сделайте дочерними для нового узла (x, y). Новый узел вставьте на место узла P.
 * Построить также наивное дерево поиска по ключам Xi. Равные ключи добавляйте в правое поддерево.
 * Вычислить количество узлов в самом широком слое декартового дерева и количество узлов в самом широком слое наивного дерева поиска.
 * Вывести их разницу. Разница может быть отрицательна.
 */

#include <iostream>
#include <queue>
using namespace std;

template<class T>
int Get_Width(const T& root);

template <class T>
void print_Tree(const T& p, int level);

struct TreapNode { // Узел Декартова дерева
    long X;
    long Y;
    TreapNode* Left;
    TreapNode* Right;
    TreapNode(long x, long y): X(x), Y(y), Left(0), Right(0) {}
    ~TreapNode() {
        delete Left;
        delete Right;
    }
};

struct BTreeNode { // Узел бинарного дерева
    long X;
    BTreeNode* Left;
    BTreeNode* Right;
    BTreeNode(long x): X(x), Left(0), Right(0) {}
    ~BTreeNode() {
        delete Left;
        delete Right;
    }
};

class Treap { // Класс Декарова дерева
public:
    Treap() : root(0) {}
    ~Treap() {
        delete root;
    }
    void Insert(long x, long y) {
        TreapNode* NewNode = new TreapNode(x, y);
        if (root == 0) { // Если дерево пустое
            root = NewNode;  // То записываем в корень данные
            return;
        }
        // Спускаемся по ключу , но чтобы приоритет был больше или равен
        TreapNode* inode = root; // Текущий узел - корень
        TreapNode* prevNode = root;
        while (inode != 0 && inode->Y >= y) {
            prevNode = inode;
            if (x <= inode->X) { // Идем налево
                inode = inode->Left;
            }
            else { // Идем направо
                inode = inode->Right;
            }
        }
        Split(inode, x, NewNode->Left, NewNode->Right); // Делаем сплит по х
        // T1 - левый сын добавляемого элемента, T2 - правый сын добавляемого элемента
        if (inode == root) {// Вставляем в первое место добавляемый элемент
            root = NewNode;
        }
        else if (x <= prevNode->X) {
            prevNode->Left = NewNode;
        }
        else {
            prevNode->Right = NewNode;
        }
    }
    int Width() {
        return Get_Width(root);
    }
    void Show() {
        TreapNode* NewNode = root;
        print_Tree(NewNode, 0);
    }

private:
    TreapNode* root;
    void Split(TreapNode* inode, int key, TreapNode*& left, TreapNode*& right) {
        if (inode == 0) {
            left = 0;
            right = 0;
        } else if (inode->X <= key) {
            Split(inode->Right, key, inode->Right, right);
            left = inode;
        } else {
            Split(inode->Left, key, left, inode->Left);
            right = inode;
        }
    }
};

class BTree { // Класс наивного дерева
public:
    BTree() : root(0) {}
    ~BTree() {
        delete root;
    }
    void Insert(long value) {
        BTreeNode* newNode = new BTreeNode(value);
        if (root == 0) { // Если дерево пустое
            root = newNode;  // То записываем в корень данные
            return;
        }
        BTreeNode* inode = root; // Текущий узел - корень
        while (true) {
            if (value < inode->X) { // Идем налево
                if (inode->Left == 0) {
                    inode->Left = newNode;
                    return;
                }
                else
                    inode = inode->Left;
            }
            else { // Идем направо
                if (inode->Right == 0) {
                    inode->Right = newNode;
                    return;
                }
                else
                    inode = inode->Right;
            }
        }
    }
    int Width() {
        return Get_Width(root);
    }

    void Show() {
        BTreeNode* NewNode = root;
        print_Tree(NewNode, 0);
    }
private:
    BTreeNode* root;
};

template <class T>
int Get_Width(const T& root) {
    int maxWidth = 0, curWidth = 0;

    queue<T> queueNodes;
    T cur = 0;
    queueNodes.push(root);

    while(!queueNodes.empty()) {
        if((curWidth = queueNodes.size()) > maxWidth) {
            maxWidth = curWidth;
        }

        for(int i = 0; i < curWidth; i++) {
            cur = queueNodes.front();
            if(cur->Left != 0) {
                queueNodes.push(cur->Left);
            }
            if(cur->Right != 0) {
                queueNodes.push(cur->Right);
            }
            queueNodes.pop();
        }
    }
    return maxWidth;
}

template <class T>
void print_Tree(const T& p, int level)
{
    if(p)
    {
        print_Tree(p->Left, level + 1);
        for (int i = 0; i< level; i++)
            cout << "   ";
        cout << p->X << endl;
        print_Tree(p->Right, level + 1);
    }
}

int main() {
    Treap treap;
    BTree btree;
    int N = 0;
    long x = 0, y = 0;
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> x >> y;
        treap.Insert(x, y);
        btree.Insert(x);
    }
    cout << (treap.Width() - btree.Width());
    return 0;
}