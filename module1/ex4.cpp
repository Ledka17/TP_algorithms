/* Тупики
На вокзале есть некоторое количество тупиков, куда прибывают электрички. 
Этот вокзал является их конечной станцией. Дано расписание движения электричек, в котором для 
каждой электрички указано время ее прибытия, а также время отправления в следующий рейс. Электрички 
в расписании упорядочены по времени прибытия. Когда электричка прибывает, ее ставят в свободный тупик с минимальным номером. 
При этом если электричка из какого-то тупика отправилась в момент времени X, то электричку, которая прибывает в момент времени X, 
в этот тупик ставить нельзя, а электричку, прибывающую в момент X+1 — можно. В данный момент на вокзале достаточное количество тупиков 
для работы по расписанию. Напишите программу, которая по данному расписанию определяет, какое минимальное количество тупиков требуется для работы вокзала.

Формат ввода
Вначале вводится n - количество электричек в расписании. Затем вводится n строк для каждой электрички, в строке - время прибытия и время отправления. 
Время - натуральное число от 0 до 1 000 000 000. Строки в расписании упорядочены по времени прибытия.

Формат вывода
Натуральное число - минимальное количеством тупиков.

Пример 1
Ввод	Вывод
1
10 20   1
Пример 2
Ввод	Вывод
2
10 20
20 25   2
Пример 3
Ввод	Вывод
3
10 20
20 25
21 30   2
*/

#include <iostream>
#include <cstring>
using namespace std;

class MinHeap 
{
public:
    MinHeap() : maxsize(0), size(0), buffer(new int[10]), bufSize(10) {}
    ~MinHeap() {
        delete[] buffer; 
    }
    void DeleteElem() { // Удалить элемент сверху
        if (size > 0) {
            buffer[0] = buffer[size - 1];
            buffer[size - 1] = 0;
            size--;
            SiftDown(0);
        }
    }
    void AddElem(int val) { // Добавить элемент
        size++;
        if (size > bufSize)
            Grow();
        buffer[size - 1] = val;
        SiftUp(size - 1);
        if (size > maxsize)
            maxsize = size;
    }
    void Grow() { // Увеличить размер буфера
        int newSize = bufSize * 1.5;
        int *newBuffer = new int[newSize];
        for (int i = 0; i < bufSize; i++) {
            newBuffer[i] = buffer[i];
        }
        delete[] buffer;
        buffer = newBuffer;
        bufSize = newSize;
    }
    int ShowUp() { // Показать наименьший элемент
        if (size > 0)
            return buffer[0];
        return -1;
    }
    void SiftDown(int i) {
        int tmp = buffer[i];
        while ((i * 2 + 1 < size && buffer[i] > buffer[i * 2 + 1])
        || (i * 2 + 2 < size && buffer[i] > buffer[i * 2 + 2])) { // Пока элемент больше своих детей
            if (buffer[i * 2 + 1] < buffer[i * 2 + 2]) { // Меняем его с наименьшим ребенком
                buffer[i] = buffer[i * 2 + 1];
                buffer[i * 2 + 1] = tmp; 
                i = i * 2 + 1; // Меняем индекс эелемента
            }
            else {
                buffer[i] = buffer[i * 2 + 2];
                buffer[i * 2 + 2] = tmp; 
                i = i * 2 + 2; // Меняем индекс эелемента
            }
        }
    }
    void SiftUp(int i) {
        int tmp = buffer[i];
        while ((i - 1) / 2 >= 0 && buffer[i] < buffer[(i - 1) / 2]) { // Пока элемент меньше своего родителя
            buffer[i] = buffer[(i - 1) / 2];
            buffer[(i - 1) / 2] = tmp;// Меняем их местами
            i = (i - 1) / 2;
        }
    }
    void ShowHeap() {
        cout << "Куча: ";
        for (int i = 0; i < size; i++) {
            cout << buffer[i] << " ";
        }
        cout << endl;
    }
public:
    int maxsize;
private:
    int size;
    int *buffer;
    int bufSize;
};

int main() {
    int n = 0;
    MinHeap railway;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int time_start = 0, time_end = 0;
        cin >> time_start >> time_end;
        while (railway.ShowUp() != -1 && railway.ShowUp() < time_start) {
            railway.DeleteElem(); // Удалить поезда до времени прибытия текущего
        }
        railway.AddElem(time_end); // Добавить поезд в тупик
    }
    cout << railway.maxsize;
    return 0;
}