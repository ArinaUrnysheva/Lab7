#include <iostream>
#include <vector>
#include <algorithm>
#include <future>
#include <chrono>
#include <locale.h>

using namespace std;

// Функция сортировки методом прямого включения
void insertionSort(vector<double>& arr, const string& threadName) {
    for (size_t i = 1; i < arr.size(); ++i) {
        double key = arr[i];
        int j = i - 1;

        // Печать имени потока перед сортировкой элемента
        cout << threadName << ": ";

        // Имитация задержки в 10 мс
        //this_thread::sleep_for(chrono::milliseconds(10));

        // Сортировка массива
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;

        // Печать отсортированного элемента с новой строки
        cout << arr[i] << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    const int size = 10;
    vector<double> arr(size);

    // Заполнение массива случайными числами
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 100;
    }

    cout << "Начальный массив: " << endl;

    for (int i = 0; i < size; ++i) {
        cout << arr[i] << ' ';
    }

    cout << endl;

    // Использование async и future для запуска сортировки в отдельных потоках
    auto future1 = async(insertionSort, ref(arr), "thread1");
    auto future2 = async(insertionSort, ref(arr), "thread2");

    // Ожидание завершения первых двух потоков
    future1.get();
    future2.get();

    // Сортировка массива в третьем потоке
    insertionSort(arr, "thread3");

    // Вывод отсортированного массива
    cout << "Главный поток завершил работу. Отсортированный массив:" << endl;
    for (double num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}