/* Реализуйте стратегию выбора опорного элемента “случайный элемент”. 
Функцию Partition реализуйте методом прохода двумя итераторами от конца массива к началу.
Ввод	                    Вывод
10 4                        5
1 2 3 4 5 6 7 8 9 10

*/

#include <iostream>
#include <cstring>
using namespace std;

int partition(int *A, int start, int end) {
    int pivot = rand() % (end - start) + start; // Выбираем случайный пивот
    swap(A[start], A[pivot]); // Устанавливаем пивот в начале массива
    int i = end - 1; // Устанавливаем итераторы i j в конце массива
    for (int j = end - 1; j > start;) { // Пока j не дошел до старта
        if (A[j] <= A[start]) { // Если j элемент > пивота
            j--;// То сдвигаем j
        }
        if (A[j] > A[start]) {
            swap(A[i], A[j]);
            i--;
            j--;
        }
    }
    swap(A[start], A[i]);
    return i; // Возвращаем i
}

int find_stat(int *A, int start, int end, int k) {
    int pivot = end;
    while (pivot != k) {
        if (pivot > k) {
            end = pivot;
        }
        else {
            start = pivot + 1;
        }
        pivot = partition(A, start, end);
    }
    return A[k];
}

int main() {
    int n = 0, k = 0;
    cin >> n >> k;
    int *A = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    int k_stat = find_stat(A, 0, n, k); // Поиск k статистики
    cout << k_stat;
    delete[] A;
    return 0;
}