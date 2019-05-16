/* Дано число N ≤ 104 и последовательность целых чисел из [-231..231] длиной N.
 * Требуется построить бинарное дерево, заданное наивным порядком вставки.
 * Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то узел K добавляется в правое поддерево root;
 * иначе в левое поддерево root. Выведите элементы в порядке post-order (снизу вверх).

Рекурсия запрещена.
 */

#include <iostream>
#include <stack>
using namespace std;
//using std::stack;

struct BTNode{ // Узел дерева
    int Key;
    BTNode* Left;
    BTNode* Right;
    BTNode(int value): Key(value), Right(0), Left(0) {}
    ~BTNode() {
        delete Left;
        delete Right;
    }
};

class BinaryTree { // Бинарное дерево
public:
    BinaryTree() : root(0) {}
    ~BinaryTree() {
        delete root;
    }
    void Insert(int value) {
        BTNode* newNode = new BTNode(value);
        if (root == 0) { // Если дерево пустое
            root = newNode;  // То записываем в корень данные
            return;
        }
        BTNode* inode = root; // Текущий узел - корень
        while (true) {
            if (value < inode->Key) { // Идем налево
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
    void WritePostOrder() {
        PostOrder(root);
    }
private:
    BTNode* root;

    void PostOrder(BTNode* top) {
        stack<BTNode*> Stack;
        while (top != 0 || !Stack.empty()) {
            if (!Stack.empty()) {
                top = Stack.top();
                Stack.pop();
                if (!Stack.empty() && top->Right == Stack.top()) {
                    top = Stack.top();
                    Stack.pop();
                }
                else {
                    cout << top->Key << " ";
                    top = 0;
                }
            }
            while (top != 0) {
                Stack.push(top);
                if (top->Right != 0) {
                    Stack.push(top->Right);
                    Stack.push(top);
                }
                top = top->Left;
            }
        }
    }
};

int main() {
    int N = 0, a = 0;
    cin >> N;
    BinaryTree bt;
    for (int i = 0; i < N; i++) { // Вставка элементов в дерево
        cin >> a;
        bt.Insert(a);
    }
    bt.WritePostOrder(); // Вывод дерева снизу вверх
    return 0;
}