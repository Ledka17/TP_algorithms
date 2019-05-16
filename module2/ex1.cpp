/* Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией.
 * Хранимые строки непустые и состоят из строчных латинских букв. Хеш-функция строки должна быть реализована
 * с помощью вычисления значения многочлена методом Горнера. Начальный размер таблицы должен быть равным 8-ми.
 * Перехеширование выполняйте при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 3/4.
 * Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества и проверки
 * принадлежности данной строки множеству.
 * Для разрешения коллизий используйте квадратичное пробирование. i-ая проба g(k, i)=g(k, i-1) + i (mod m). m - степень двойки.
 */
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

#define ALPHA 0.75
#define START_SIZE 8

class HashTable {
public:
    HashTable(int size) : N(0), M(size), table(new string[size]) {};
    ~HashTable() {
        delete[] table;
    };
    bool Has(const string& key) { // Проверка на наличие
        int h = Hash(key);
        if (N > 0) {
            for (int i = 0; i < M; i++) { // Пока не пройдена вся таблица
                h = (h + i) % M; // Квадратичное пробирование
                if (table[h] == key) { // Если ключ есть
                    return true; // Возвращаем true
                }
                if (table[h].size() == 0) { // Если стоит пусто
                    break;// Прекращаем цикл
                }
            }
        }
        return false;// Возвращаем false
    };
    bool Add(const string& key) { // Добавить элемент
        if ((float)N / M >= ALPHA) { // Если таблица заполнена
            ReHash(); // Перехешируем ее
        }
        int h = Hash(key); // Вычисляем хеш функцию для эелемента
        for (int i = 0; i < M; i++) { // Пока не пройдена вся таблица
            h = (h + i) % M; // Квадратичное пробирование
            if (table[h] == key) { // Если ключ есть
                return false; // Возвращаем false
            }
            if (table[h].size() == 0 || table[h] == "DELETED") { // Если стоит пусто или удаленный элемент
                break; // Прекращаем цикл
            }
        }
        table[h] = key;// Добавляем его
        N++; // Увеличиваем число элементов
        return true; // Возвращаем true
    };
    bool Remove(const string& key) { // Удалить элемент
        int h = Hash(key); // Вычисляем хеш функцию
        if (N > 0) {
            for (int i = 0; i < M; i++) { // Пока не пройдена вся таблица
                h = (h + i) % M; // Квадратичное пробирование
                if (table[h] == key) { // Если ключ есть
                    table[h] = "DELETED";// Удаляем его
                    N--;
                    return true; // Возвращаем true
                }
                if (table[h].size() == 0) { // Если стоит пусто
                    break; // Прекращаем цикл
                }
            }
        }
        return false;
    };
private:
    unsigned int Hash(const string& key) { // Хеш функция
        unsigned int hash = 0, a = 997;
        for (int i = 0; i < key.size(); i++)
            hash = (a * hash + key[i]) % M;
        return hash;
    }
    void ReHash() { // Перехеширование
        /*cout << "Rehash" << "  N = " << N << "  M = " << M << endl;
        for (int i = 0; i < M; i++) {
            cout << table[i] << " ";
        }
        cout << endl;*/
        M *= 2;
        string* NewTable = new string[M];
        for (int i = 0; i < M / 2; i++) {// Проходим по всем элементам таблицы
            if (table[i] != "DELETED" && table[i].size() != 0) {// Если элемент не пуст и не удален
                unsigned int h = Hash(table[i]); // Пересчитываем его хеш функцию
                for (int j = 0; NewTable[h].size() != 0; j++) { // Если элемент уже заполнен
                    h = (h + j) % M; // Квадратичное пробирование
                }
                NewTable[h] = table[i]; // Добавляем элемент в новую таблицу
            }
        }
        delete[] table;
        table = NewTable;
        /*cout << "NewTable" << "  N = " << N << "  M = " << M << endl;
        for (int i = 0; i < M; i++) {
            cout << table[i] << " ";
        }
        cout << endl;*/
    }
    int M;
    int N;
    string* table;
};

int main() {
    HashTable hash_table(START_SIZE); // Выделение памяти
    char command;
    string key;
    while (cin >> command >> key) {
        switch (command) {
            case '?':
                cout << (hash_table.Has(key) ? "OK" : "FAIL") << endl;
                break;
            case '+':
                cout << (hash_table.Add(key) ? "OK" : "FAIL") << endl;
                break;
            case '-':
                cout << (hash_table.Remove(key) ? "OK" : "FAIL") << endl;
                break;
            default:
                break;
        }
    }
    return 0;
}