/*5_1. Реклама
Ограничение времени	0.05 секунд
Ограничение памяти	64Mb
Ввод	стандартный ввод или input.txt
Вывод	стандартный вывод или output.txt
В супермаркете решили оптимизировать показ рекламы. Известно расписание прихода и ухода покупателей (два целых числа). 
Каждому покупателю необходимо показать минимум 2 рекламы. Рекламу можно транслировать только в целочисленные моменты времени. 
Покупатель может видеть рекламу от момента прихода до момента ухода из магазина. В каждый момент времени может показываться 
только одна реклама. Считается, что реклама показывается мгновенно. Если реклама показывается в момент ухода или прихода, 
то считается, что посетитель успел её посмотреть. 
Требуется определить минимальное число показов рекламы.
Пример
Ввод	Вывод
5       5
1 10
10 12
1 10
1 10
23 24
*/

#include <iostream>
#include <cstring>
using namespace std;

struct Cust // Структура посетителя
{
    int In;
    int Out;
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

/*<template class T>
class DefaultComparator(const T& left, const T& right) {
    return left > right;
}

<template class T, const class DefaultComparator> */
void add_adv(Cust *A, int *Adv, int j, int n, int time) {
    for (int i = j; i < n; i++) { // Проходим по всем элементам
        if (A[i].In <= time && time <= A[i].Out) // Если время лежит между времен прихода и ухода посетителя
            Adv[i] += 1;// То добавляем посетителю + 1
    }
}

int find_show(Cust *A, int n) {
    int k = 0;
    int *Adv = new int[n]; // Создать массив с количеством рекламы для каждого пользователя
    for (int i = 0; i < n; i++) {
        Adv[i] = 0;
    }
    for (int i = 0; i < n; i++) { // Проходим по всем элементам времени ухода
        if (Adv[i] < 2) { // Если количество реклам у пользователя < 2
            add_adv(A, Adv, i, n, A[i].Out); // Добавляем на это время рекламу
            k++; // Счетчик реклам ++
        }
        if (Adv[i] < 2) { // Если количество реклам у пользователя все равно < 2
            add_adv(A, Adv, i, n, A[i].Out - 1); // Добавляем на время-1 рекламу
            k++; // Счетчик реклам ++
        }
    }
    delete[] Adv;
    return k;
}

void merge(Cust *A, int n1, int n2, int n) {
    Cust *NewA = new Cust[n - n1];// Выделяем память под данные
    int i = 0, j = 0; // Индексы указывают на первые элементы
    for (; i + n1 < n2 && j + n2 < n;) { // Пока один из массивов не закончился
        if (A[i + n1] < A[j + n2]) { // Если время ухода посетителей одинаково
            NewA[i + j] = A[i + n1];// То записываем в порядке убывания времени прихода
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
    int k = find_show(A, n); // Ищем количество времен для показа рекламы
    cout << k; // Выводим это количество
    delete[] A; // Освобождаем память
    return 0;
}