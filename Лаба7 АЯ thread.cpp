﻿#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
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
        this_thread::sleep_for(chrono::milliseconds(10));

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

    // Создание и запуск трех потоков
    thread t1(insertionSort, ref(arr), "thread1");
    thread t2(insertionSort, ref(arr), "thread2");

    // Ожидание завершения первых двух потоков
    t1.join();
    t2.join();

    // Создание и запуск третьего потока
    thread t3(insertionSort, ref(arr), "thread3");
    t3.join();

    // Вывод отсортированного массива
    cout << "Главный поток завершил работу. Отсортированный массив:" << endl;
    for (double num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}