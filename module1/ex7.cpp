/*Binary MSD для long long.
Дан массив неотрицательных целых 64-разрядных чисел. Количество чисел не больше 106.
 Отсортировать массив методом MSD по битам (бинарный QuickSort).
In                Out
3
4 1000000 7       4 7 1000000
*/

#include <cmath>
#include <iostream>
using namespace std;
#define MostBit 63

bool digit(unsigned long long number, int rank) // Наличие 1 в разряде rank
{
    return number & ((unsigned long long int)1 << rank);
}

int partition(unsigned long long *A, int start, int end, int rank) {
    int i = start, j = end - 1; // Устанавливаем итераторы с двух сторон
    while(i < j) // Пока итераторы не сошлись
    {
        while (digit(A[i], rank) == 0 && (i < j)) // Пока элементы меньше фиктивного пивота
            i++; // Перемещаем итератор i
        while (digit(A[j], rank) == 1 && (i < j)) // Пока элементы больше фиктивного пивота
            j--; // Перемещаем итератор j
        swap(A[i], A[j]); // Меняем местами меньший и больший жлементы
    }
    if (digit(A[end - 1], rank) == 0)
        j++;
        //swap(A[i], A[j]);
    return j; // Возвращаем i
}

void B_MSD(unsigned long long* A, int start, int end, int rank) { // Бинарная сортировка
    if (start >= end - 1 || rank < 0) // Если массив отсортирован
        return; // ТО выходим из процедуры
    int pivot = partition(A, start, end, rank);// Вызываем partition
    B_MSD(A, start, pivot, rank - 1);// Вызываем сортировку до pivot c rank - 1
    B_MSD(A, pivot, end, rank - 1);// Вызываем сортировку после pivot с rank - 1
}

int main() {
    int n = 0; // Ввод данных
    cin >> n;
    unsigned long long* A = new unsigned long long[n];
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    B_MSD(A, 0, n, MostBit);
    for (int i = 0; i < n; i++) {
        cout << A[i] << " ";
    }
    delete[] A;
    return 0;
}
