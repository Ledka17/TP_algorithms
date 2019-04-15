#include <iostream>
using namespace std;

int main()
{
    int size;
    int *dan;
    cin >> size;
    dan = new int[size];
    for (int i = 0; i<size; i++) {
        cout << "dan[" << i << "] = ";
        cin >> dan[i];
    }
    for (int i = 0; i < size; i++) {
        cout << dan[i] << " ";
    }
    delete[] dan;
    cin.get(); cin.get();
    return 0;
}