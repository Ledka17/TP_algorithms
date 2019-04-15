/*Дан массив целых чисел А[0..n-1]. Известно, что на интервале [0, m] 
значения массива строго возрастают, а на интервале [m, n-1] 
строго убывают. Найти m за O( log m ).
2 ≤ n ≤ 10000. 

Ввод	                Вывод
10
1 2 3 4 5 6 7 6 5 4     6
*/

#include <iostream>
using namespace std;

int find(int *A, int start, int end) {
    int i = start;
    int delta = 1;
    while (start + 1 < end) { // Пока границы не сошлись в две смежные точки
        i = start;
        delta = 1;
        while (i < end && A[i] < A[i + 1]) { // Пока следующий элемент больше текущего и следующий входит в размер массива
            i += delta; // Добавляем к текущему дельту
            delta *= 2; // Увеличиваем дельту в 2 раза
        }
        start = i - delta / 2;
        end = i <= end ? i : end;
    }
    return A[start] > A[end] ? start : end; // Возвращаем большую из границ
}

int main() {
    int n; // Считываем массив А
    cin >> n;
    int *A;
    A = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }

    int  m;
    m = find(A, 0, n - 1);//Поиск зачения м задающего унимодальную последовательность
    cout << m;

    delete[] A;
    return 0;
}