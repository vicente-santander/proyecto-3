#include <iostream>
#include <string>
#include <random>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

unordered_map<int, int> generarNumerosAleatoriosSinRepetir(int min, int max, int cantidad) {
    unordered_map<int, int> numeros;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(min, max);

    while (numeros.size() < cantidad) {
        int numero = dis(gen);
        numeros[numero]++;
    }

    return numeros;
}

void SelectionSort(vector<int>& arr, bool ascendente) {
    int n = arr.size();

    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if ((ascendente && arr[j] < arr[minIndex]) || (!ascendente && arr[j] > arr[minIndex])) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

void ShellSort(vector<int>& arr, bool ascendente) {
    int n = arr.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && ((ascendente && arr[j - gap] > temp) || (!ascendente && arr[j - gap] < temp)); j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

double getTimeTakenSelectionSort(vector<int>& arr, bool ascendente) {
    auto start = chrono::high_resolution_clock::now();
    ios_base::sync_with_stdio(false);
    SelectionSort(arr, ascendente);
    auto end = chrono::high_resolution_clock::now();
    double time_taken = chrono::duration<double>(end - start).count();
    return time_taken;
}

double getTimeTakenShellSort(vector<int>& arr, bool ascendente) {
    auto start = chrono::high_resolution_clock::now();
    ios_base::sync_with_stdio(false);
    ShellSort(arr, ascendente);
    auto end = chrono::high_resolution_clock::now();
    double time_taken = chrono::duration<double>(end - start).count();
    return time_taken;
}

double getTimeTakenHeapSort(vector<int>& arr) {
    auto start = chrono::high_resolution_clock::now();
    ios_base::sync_with_stdio(false);
    heapSort(arr);
    auto end = chrono::high_resolution_clock::now();
    double time_taken = chrono::duration<double>(end - start).count();
    return time_taken;
}

int main() {
    cout << "Carreras de algoritmos" << endl;
    cout << "1. Ascendente." << endl;
    cout << "2. Descendente." << endl;
    cout << "Opción elegida: ";
    int opcion;
    cin >> opcion;

    bool ascendente = false;
    if (opcion == 1) {
        ascendente = true;
    } else if (opcion != 2) {
        cout << "Opción inválida." << endl;
        return 0;
    }

    int num_count = 100000; // Cantidad de números aleatorios

    unordered_map<int, int> numerosSinRepetir = generarNumerosAleatoriosSinRepetir(90000, 100000, num_count);
    vector<int> numerosSinRepetirVec(num_count);
    int index = 0;
    for (const auto& pair : numerosSinRepetir) {
        numerosSinRepetirVec[index++] = pair.first;
    }

    vector<int> numerosConDuplicados(num_count);
    for (int i = 0; i < num_count; i++) {
        numerosConDuplicados[i] = i % 10001 + 90000; // Genera números del 90000 al 100000 repetidos
    }

    double time_taken_selection_sort = getTimeTakenSelectionSort(numerosSinRepetirVec, ascendente);
    double time_taken_shell_sort = getTimeTakenShellSort(numerosConDuplicados, ascendente);
    double time_taken_heap_sort = getTimeTakenHeapSort(numerosConDuplicados);

    cout << "Carrera por el Tablero: Modo aleatorio sin repetición" << endl;
    cout << "1. Selection Sort, " << time_taken_selection_sort << " segundos." << endl;
    cout << "2. Shell Sort, " << time_taken_shell_sort << " segundos." << endl;

    string ganador_sin_repetir = (time_taken_selection_sort < time_taken_shell_sort) ? "Selection Sort" : "Shell Sort";
    double tiempo_ganador_sin_repetir = min(time_taken_selection_sort, time_taken_shell_sort);

    cout << "El ganador es: " << ganador_sin_repetir << " con un tiempo de " << tiempo_ganador_sin_repetir << " segundos." << endl;

    cout << "Carrera por el Tablero: Modo aleatorio con duplicados" << endl;
    cout << "1. Selection Sort, " << time_taken_selection_sort << " segundos." << endl;
    cout << "2. Shell Sort, " << time_taken_shell_sort << " segundos." << endl;
    cout << "3. Heap Sort, " << time_taken_heap_sort << " segundos." << endl;

    string ganador_duplicados;
    double tiempo_ganador_duplicados;

    if (time_taken_selection_sort <= time_taken_shell_sort && time_taken_selection_sort <= time_taken_heap_sort) {
        ganador_duplicados = "Selection Sort";
        tiempo_ganador_duplicados = time_taken_selection_sort;
    } else if (time_taken_shell_sort <= time_taken_selection_sort && time_taken_shell_sort <= time_taken_heap_sort) {
        ganador_duplicados = "Shell Sort";
        tiempo_ganador_duplicados = time_taken_shell_sort;
    } else {
        ganador_duplicados = "Heap Sort";
        tiempo_ganador_duplicados = time_taken_heap_sort;
    }

    cout << "El ganador es: " << ganador_duplicados << " con un tiempo de " << tiempo_ganador_duplicados << " segundos." << endl;

    return 0;
}
