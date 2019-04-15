/* Задача 1.3 Нужная сумма
Даны два строго возрастающих массива целых чисел A[0..n) и B[0..m) 
и число k. Найти количество таких пар индексов (i, j), что A[i] + B[j] = k. 
Время работы O(n + m). n, m ≤ 100000.

Указание. Обходите массив B от конца к началу.

Ввод	        Вывод
4               3
-5 0 3 18
5
-10 -2 4 7 12
7
*/

#include <iostream>
using namespace std;

int find_pairs(int *A, int n, int *B, int m, int k) {
    int i = 0, j = m - 1; // Обходим массив А с начали, В - с конца
    int k_pairs = 0;// Количество совпадений = 0
    while (i < n && j >= 0) {
        if (A[i] + B[j] == k) {
            k_pairs++;
            j--;
            i++;
        }
        else {
            if (A[i] + B[j] > k)
                j--;
            else
                i++;
        }
    }
    return k_pairs;
}

int main() {
    int n; // Считываем массив А
    cin >> n;
    int *A;
    A = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }

    int m; // Считываем массив В
    cin >> m;
    int *B;
    B = new int[m];
    for (int i = 0; i < m; i++) {
        cin >> B[i];
    }

    int k;// Считываем число k
    cin >> k;

    int k_pairs = find_pairs(A, n, B, m, k);// Количество совпадений

    delete[] A;
    delete[] B;
    cout << k_pairs;// Вывод количества пар

    return 0;
}