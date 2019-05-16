/*Дано число N и N строк. Каждая строка содержащит команду добавления или удаления натуральных чисел, а также запрос на получение
k-ой порядковой статистики. Команда добавления числа A задается положительным числом A, команда удаления числа A задается отрицательным
числом “-A”. Запрос на получение k-ой порядковой статистики задается числом k. Требуемая скорость выполнения запроса - O(log n).
 */

#include <iostream>
using namespace std;

template <class T>
void print_Tree(const T& p, int level);

struct AVLTreeNode {
    int X;
    int Height;
    int Size;
    AVLTreeNode* Left;
    AVLTreeNode* Right;
    AVLTreeNode(int x): X(x), Height(1), Size(1), Left(0), Right(0) {}
    ~AVLTreeNode() {
        delete Left;
        delete Right;
    }
};

class AVLTree {
public:
    AVLTree() : root(0) {}

    ~AVLTree() {
        delete root;
    }

    void Insert(int a) {
        root = insert(root, a);
        //cout << "print" << endl;
        //print_Tree(root, 0);
    }

    void Delete(int a) {
        root = remove(root, a);
        //cout << "print" << endl;
        //print_Tree(root, 0);
    }

    int FindStat(int k) {
        AVLTreeNode* node = root;
        int index = get_size(root->Left);
        while (index != k) { // Пока не найдена к статистика
            if (k > index) { // Ищем в правом поддереве
                node = node->Right;
                index += 1 + get_size(node->Left);
            }
            else { // Ищем в левом поддереве
                node = node->Left;
                index -= 1 + get_size(node->Right);
            }
        }
        return node->X; // Возвращаем значение найденного элемента
    }

private:
    AVLTreeNode *root;

    AVLTreeNode *insert(AVLTreeNode *p, int a) {
        if (!p)
            return new AVLTreeNode(a);
        if (a < p->X)
            p->Left = insert(p->Left, a);
        else
            p->Right = insert(p->Right, a);
        p = balance(p);
        FixSize(p);
        FixHeight(p);
        return balance(p); // Балансируем дерево - когда выходим из рекурсии
    }

    int get_size(const AVLTreeNode *p) { // Узнаем размер узла
        return p ? p->Size : 0;
    }

    unsigned int height(AVLTreeNode *p) { // Узнаем высоту узла
        return p ? p->Height : 0;
    }

    void FixHeight(AVLTreeNode *p) { // Выставляем высоту узла по его детям
        unsigned char hl = height(p->Left);
        unsigned char hr = height(p->Right);
        p->Height = (hl > hr ? hl : hr) + 1;
    }

    void FixSize(AVLTreeNode* node) { // Выставлчем размер узла по его детям
        int l_size = get_size(node->Left);
        int r_size = get_size(node->Right);
        node->Size = l_size + r_size + 1;
    }

    AVLTreeNode *RotateRight(AVLTreeNode *p) { // Правый поворот вокруг p
        AVLTreeNode *q = p->Left;
        p->Left = q->Right;
        q->Right = p;
        FixHeight(p);
        FixSize(p);
        FixHeight(q);
        FixSize(q);
        return q;
    }

    AVLTreeNode *RotateLeft(AVLTreeNode *q) { // Левый поворот вокруг q
        AVLTreeNode *p = q->Right;
        q->Right = p->Left;
        p->Left = q;
        FixHeight(p);
        FixSize(p);
        FixHeight(q);
        FixSize(q);
        return p;
    }

    int bfactor(AVLTreeNode *p) {// Балансировочный фактор
        return height(p->Right) - height(p->Left);
    }

    AVLTreeNode *balance(AVLTreeNode *p) { // Балансировка узла
        FixHeight(p);
        FixSize(p);
        if (bfactor(p) == 2) {
            if (bfactor(p->Right) < 0)
                p->Right = RotateRight(p->Right);
            return RotateLeft(p);
        }
        if (bfactor(p) == -2) {
            if (bfactor(p->Left) > 0)
                p->Left = RotateLeft(p->Left);
            return RotateRight(p);
        }
        return p; // Балансировка не нужна
    }

    AVLTreeNode* findMin(AVLTreeNode* p) { // Поиск узла с минимальным ключом в дереве p
        return p->Left ? findMin(p->Left) : p;
    }

    AVLTreeNode* remove(AVLTreeNode* node, int a) {
        if (node == 0) { // Если узел пустой
            return 0; // То заканчиваем рекурсию
        }
        if (a < node->X) { // Ищем место удаления
            node->Left = remove(node->Left, a);
        }
        else if (a > node->X) {
            node->Right = remove(node->Right, a);
        }
        else { //  Нашли место удаления k == p->key
            if (node->Left == 0 || node->Right == 0) { // Если кто-то из детей отсутсвует
                AVLTreeNode* temp = node->Left ? node->Left : node->Right;
                if (temp == 0) {
                    temp = node;
                    node = 0;
                }
                else {
                    *node = *temp;
                }
                delete temp; // То ставим на место узла его ребенка
            }
            else { // Если оба ребенка есть
                AVLTreeNode* temp = findMin(node->Right); // Ищем минимального в правом поддереве
                node->X = temp->X;
                node->Right = remove(node->Right, temp->X); // Удаляем этот узел
            }
        }
        if (node == 0) {
            return node;
        }
        node = balance(node);
        FixHeight(node);
        FixSize(node);
        return balance(node);
    }
};

template <class T>
void print_Tree(const T& p, int level)
{
    if (p) {
        print_Tree(p->Left, level + 1);
        for (int i = 0; i < level; i++)
            cout << "      ";
        cout << p->X << " " << p->Size << " " << p->Height << endl;
        print_Tree(p->Right, level + 1);
    }
}

int main() {
    int N = 0, a = 0, k = 0;
    AVLTree avl;
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> a >> k;
        if (a > 0)
            avl.Insert(a);
        else
            avl.Delete(-a);
        cout << avl.FindStat(k) << endl;
    }
    return 0;
}