#include <vector>
#include <algorithm>
#include <future>
#include <mutex>
#include <chrono>
#include <locale.h>

using namespace std;

// Mutex для синхронизации доступа к выводу
mutex mtx;

// Функция сортировки массива portion методом прямого включения с отображением имени потока
void insertionSort(vector<double>& arr, const string& threadName, size_t start, size_t end) {
    for (size_t i = start; i < end; ++i) {
        double key = arr[i];
        int j = i - 1;

        // Захватываем мьютекс для вывода
        unique_lock<mutex> lock(mtx);
        cout << threadName << ": " << arr[i] << endl;

        // Имитация задержки в 10 мс
        this_thread::sleep_for(chrono::milliseconds(10));

        // Сортировка методом прямого включения
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
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

    // Создание и запуск асинхронных потоков с использованием std::async
    auto future1 = async(launch::async, insertionSort, ref(arr), "thread1", 0, size / 2);
    auto future2 = async(launch::async, insertionSort, ref(arr), "thread2", size / 2, size);

    // Ожидание завершения первых двух потоков
    future1.get();
    future2.get();

    // Создание и запуск третьего потока
    auto future3 = async(launch::async, insertionSort, ref(arr), "thread3", 0, size);
    future3.get();

    // Вывод отсортированного массива
    cout << "Главный поток завершил работу. Отсортированный массив:" << endl;
    for (double num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}