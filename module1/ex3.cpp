/* Реализовать дек с динамическим зацикленным буфером.

Обрабатывать команды push * и pop *.

Формат ввода
В первой строке количество команд n. n ≤ 1000000.

Каждая команда задаётся как 2 целых числа: a b.
a = 1 - push front
a = 2 - pop front
a = 3 - push back
a = 4 - pop back
Если дана команда pop *, то число b - ожидаемое значение. 
Если команда pop * вызвана для пустой структуры данных, то ожидается “-1”.
*/

#include <iostream>
#include <cstring>
using namespace std;

class Deque
{
public:
    Deque(int Nsize) : bufSize(Nsize), size(0), head(0), tail(0), buffer(new int[Nsize]) {}
    ~Deque()
    {
        delete[] buffer;
    }
    void push_front(int val) {
        if (tail == head && size != 0) // Если массив полный
            grow(); // то увеличить его
        buffer[head] = val;
        head = (head - 1 + bufSize) % bufSize; // указатель на голову - пустой элемент
        size++;
    }
    int pop_front() {
        if (size != 0) {
            head = (head + 1) % bufSize;
            size--;
            return buffer[head];
        }
        return -1;
    }
    void push_back(int val) {
        if (tail == head && size != 0) // Если массив полный
            grow(); // то увеличить его  
        tail = (tail + 1) % bufSize;
        buffer[tail] = val; // указатель на хвост - занятый элемент
        size++;
    }
    int pop_back() {
        if (size != 0) {
            int result = buffer[tail];
            tail = (tail - 1 + bufSize) % bufSize;
            size--;
            return result;
        }
        return -1;
    }
    void grow() {
        int newSize = bufSize * 1.5;
        int *newBuffer = new int[newSize];
        int j = 0;
        for (int i = head + 1; i < bufSize; i++, j++)
            newBuffer[j] = buffer[i];// Копируем часть от head до конца
        for (int i = 0; i <= head; i++, j++)
            newBuffer[j] = buffer[i];// Копируем часть от 0 до head
        delete[] buffer;
        head = newSize - 1;
        tail = bufSize - 1;
        buffer = newBuffer;
        bufSize = newSize;
    }
    /*void ShowDeque() {
        for (int i = 0; i < bufSize; i++) {
            cout << buffer[i] << " ";
        }
        cout << endl;
    }*/
private: 
    int bufSize; // Размер массива
    int size; // Текущий размер дека
    int head; // Номер элемента куда положить голову
    int tail; // Номер последнего элемента, где лежит хвост
    int *buffer; // Сам, собственно, дек
};

int main() {
    int n = 0;
    cin >> n;
    if (n > 0 && n <= 1000000) {
        Deque d(10);
        bool flag = true;
        int op = 0, val = 0;
        for (int i = 0; i < n; i++) {
            cin >> op >> val;
            switch (op) {
                case 1:
                    d.push_front(val);
                    break;
                case 2:
                    if (d.pop_front() != val)
                        flag = false;
                    break;
                case 3:
                    d.push_back(val);
                    break;
                case 4:
                    if (d.pop_back() != val)
                        flag = false;
                    break;
                default:
                    break;
            }
        }
        if (flag == true)
            cout << "YES";
        else
            cout << "NO";
    }
    return 0;
}