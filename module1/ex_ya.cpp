#include <iostream>
#include <cstring>
using namespace std;

struct Cust // Структура посетителя
{
    int In;
    int Out;
    int k;
};

bool operator <(Cust first, Cust second) { // Компаратор
    if (first.Out < second.Out) {
        return true;
    }
    else if (first.Out == second.Out) {
        if (first.In > second.In) {
            return true;
        }
    }
    return false;
}

void add_man(Cust *A, int *People, int j, int n, int time) {
    int k = j;
    for (int i = j; i < n; i++) { // Проходим по всем элементам
        if (A[i].In <= time && time <= A[i].Out) // Если время лежит между времен прихода и ухода посетителя
            People[k] += A[i].k + 1;// То добавляем посетителю + 1
    }
}

int find_show(Cust *A, int n) {
    int *People = new int[n]; // Создать массив с количеством человек
    for (int i = 0; i < n; i++) {
        People[i] = 0;
    }
    for (int i = 0; i < n; i++) { // Проходим по всем элементам времени ухода
        add_man(A, People, i, n, A[i].Out); // Добавляем на это время встречи
    }
    int max = 0;
    for (int i = 0; i < n; i++) {
        if (People[i] > max) {
            max = People[i];
        }
    }
    delete[] People;
    return max;
}

void merge(Cust *A, int n1, int n2, int n) {
    Cust *NewA = new Cust[n - n1];// Выделяем память под данные
    int i = 0, j = 0; // Индексы указывают на первые элементы
    for (; i + n1 < n2 && j + n2 < n;) { // Пока один из массивов не закончился
        if (A[i + n1] < A[j + n2]) {
            NewA[i + j] = A[i + n1];
            i++;
        }
        else {
            NewA[i + j] = A[j + n2];
            j++;
        }
    }
    for (; i + n1 < n2; i++) {
        NewA[i + j] = A[i + n1];
    }
    for (; j + n2 < n; j++) {
        NewA[i + j] = A[j + n2]; // Добавляем в новый массив оставшиеся элементы 1 или второго массива
    }
    for (int k = 0; k < i + j; k++) {
        A[n1 + k] = NewA[k]; // Изменяем в исходном массиве значения элементов
    }
    delete[] NewA;
}

void MyMergeSort(Cust *A, int n) {
    for (int n_merge = 1; n_merge < n; n_merge *= 2) { // Пока размер массива для сливания < размера исходного массива
        for (int i = 0; i < n - n_merge; i += 2 * n_merge) { // Пока не прошлись по всем массивам
            merge(A, i, i + n_merge, min(i + n_merge * 2, n)); // Сливаем массивы
        }
    }
}

int main() {
    int n = 0;
    cin >> n; // Считываем количество строк
    Cust *A = new Cust[n]; // Выделяем память под данные
    for (int i = 0; i < n; i++) {
        int in = 0, out = 0;
        cin >> A[i].In >> A[i].Out;
    }
    MyMergeSort(A, n); // Сортируем с помощью mergesort
    int k = find_show(A, n); // Ищем количество человек
    cout << k; // Выводим это количество
    delete[] A; // Освобождаем память
    return 0;
}