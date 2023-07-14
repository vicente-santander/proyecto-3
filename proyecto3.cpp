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

void BubbleSort(vector<int>& arr, bool ascendente) {
    int n = arr.size();

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if ((ascendente && arr[j] > arr[j + 1]) || (!ascendente && arr[j] < arr[j + 1])) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void InsertionSort(vector<int>& arr, bool ascendente) {
    int n = arr.size();

    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && ((ascendente && arr[j] > key) || (!ascendente && arr[j] < key))) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

void Merge(vector<int>& arr, int left, int middle, int right, bool ascendente) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    vector<int> L(n1);
    vector<int> R(n2);

    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }

    for (int j = 0; j < n2; j++) {
        R[j] = arr[middle + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if ((ascendente && L[i] <= R[j]) || (!ascendente && L[i] >= R[j])) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void MergeSort(vector<int>& arr, int left, int right, bool ascendente) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        MergeSort(arr, left, middle, ascendente);
        MergeSort(arr, middle + 1, right, ascendente);

        Merge(arr, left, middle, right, ascendente);
    }
}

int Partition(vector<int>& arr, int low, int high, bool ascendente) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if ((ascendente && arr[j] < pivot) || (!ascendente && arr[j] > pivot)) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void QuickSort(vector<int>& arr, int low, int high, bool ascendente) {
    if (low < high) {
        int pi = Partition(arr, low, high, ascendente);

        QuickSort(arr, low, pi - 1, ascendente);
        QuickSort(arr, pi + 1, high, ascendente);
    }
}

void heapify(vector<int>& arr, int n, int i) {
    int largest = i; // Inicializar el nodo raíz como el más grande
    int left = 2 * i + 1; // Índice del hijo izquierdo
    int right = 2 * i + 2; // Índice del hijo derecho

    // Si el hijo izquierdo es más grande que el nodo raíz
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    // Si el hijo derecho es más grande que el nodo raíz
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // Si el nodo raíz no es el más grande, intercambiar con el más grande
    if (largest != i) {
        swap(arr[i], arr[largest]);

        // Recursivamente hacer heapify en el subárbol afectado
        heapify(arr, n, largest);
    }
}

void ShellSort(vector<int>& arr, bool ascendente) {
    int n = arr.size();

    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j = i;

            while (j >= gap && ((ascendente && arr[j - gap] > temp) || (!ascendente && arr[j - gap] < temp))) {
                arr[j] = arr[j - gap];
                j -= gap;
            }

            arr[j] = temp;
        }
    }
}


void heapSort(vector<int>& arr) {
    int n = arr.size();

    // Construir el heap (reorganizar el arreglo)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // Extraer elementos del heap uno por uno
    for (int i = n - 1; i > 0; i--) {
        // Mover la raíz actual al final
        swap(arr[0], arr[i]);

        // Llamar a heapify en el subárbol reducido
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

double getTimeTakenBubbleSort(vector<int>& arr, bool ascendente) {
    auto start = chrono::high_resolution_clock::now();
    ios_base::sync_with_stdio(false);
    BubbleSort(arr, ascendente);
    auto end = chrono::high_resolution_clock::now();
    double time_taken = chrono::duration<double>(end - start).count();
    return time_taken;
}

double getTimeTakenInsertionSort(vector<int>& arr, bool ascendente) {
    auto start = chrono::high_resolution_clock::now();
    ios_base::sync_with_stdio(false);
    InsertionSort(arr, ascendente);
    auto end = chrono::high_resolution_clock::now();
    double time_taken = chrono::duration<double>(end - start).count();
    return time_taken;
}

double getTimeTakenMergeSort(vector<int>& arr, bool ascendente) {
    auto start = chrono::high_resolution_clock::now();
    ios_base::sync_with_stdio(false);
    MergeSort(arr, 0, arr.size() - 1, ascendente);
    auto end = chrono::high_resolution_clock::now();
    double time_taken = chrono::duration<double>(end - start).count();
    return time_taken;
}

double getTimeTakenQuickSort(vector<int>& arr, bool ascendente) {
    auto start = chrono::high_resolution_clock::now();
    ios_base::sync_with_stdio(false);
    QuickSort(arr, 0, arr.size() - 1, ascendente);
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

    unordered_map<int, int> numerosSinRepetir = generarNumerosAleatoriosSinRepetir(0, 1000000, num_count);
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
    double time_taken_bubble_sort = getTimeTakenBubbleSort(numerosSinRepetirVec, ascendente);
    double time_taken_insertion_sort = getTimeTakenInsertionSort(numerosSinRepetirVec, ascendente);
    double time_taken_merge_sort = getTimeTakenMergeSort(numerosSinRepetirVec, ascendente);
    double time_taken_quick_sort = getTimeTakenQuickSort(numerosSinRepetirVec, ascendente);
    double time_taken_heap_sort = getTimeTakenHeapSort(numerosSinRepetirVec);
    double time_taken_shell_sort = getTimeTakenShellSort(numerosSinRepetirVec, ascendente);
	double time_taken_shell_sort_dup = getTimeTakenShellSort(numerosConDuplicados, ascendente);

    cout << "Carrera por el Tablero: Modo aleatorio sin repetición" << endl;
    cout << "1. Selection Sort, " << time_taken_selection_sort << " segundos." << endl;
    cout << "2. Bubble Sort, " << time_taken_bubble_sort << " segundos." << endl;
    cout << "3. Insertion Sort, " << time_taken_insertion_sort << " segundos." << endl;
    cout << "4. Merge Sort, " << time_taken_merge_sort << " segundos." << endl;
    cout << "5. Quick Sort, " << time_taken_quick_sort << " segundos." << endl;
    cout << "6. Heap Sort, " << time_taken_heap_sort << " segundos." << endl;
    cout << "7. Shell Sort, " << time_taken_shell_sort << " segundos." << endl;

    double tiempo_ganador_sin_repetir = min(time_taken_selection_sort,
	    min(time_taken_bubble_sort,
	        min(time_taken_insertion_sort,
	            min(time_taken_merge_sort,
	                min(time_taken_quick_sort,
	                    min(time_taken_heap_sort, time_taken_shell_sort)
	                )
	            )
	        )
	    )
	);

    if (tiempo_ganador_sin_repetir == time_taken_selection_sort) {
        cout << "El ganador es: Selection Sort con un tiempo de " << tiempo_ganador_sin_repetir << " segundos." << endl;
    } else if (tiempo_ganador_sin_repetir == time_taken_bubble_sort) {
        cout << "El ganador es: Bubble Sort con un tiempo de " << tiempo_ganador_sin_repetir << " segundos." << endl;
    } else if (tiempo_ganador_sin_repetir == time_taken_insertion_sort) {
        cout << "El ganador es: Insertion Sort con un tiempo de " << tiempo_ganador_sin_repetir << " segundos." << endl;
    } else if (tiempo_ganador_sin_repetir == time_taken_merge_sort) {
        cout << "El ganador es: Merge Sort con un tiempo de " << tiempo_ganador_sin_repetir << " segundos." << endl;
    } else if (tiempo_ganador_sin_repetir == time_taken_quick_sort) {
        cout << "El ganador es: Quick Sort con un tiempo de " << tiempo_ganador_sin_repetir << " segundos." << endl;
    } else if(tiempo_ganador_sin_repetir == time_taken_heap_sort){
        cout << "El ganador es: Heap Sort con un tiempo de " << tiempo_ganador_sin_repetir << " segundos." << endl;
    }else{
    	cout << "El ganador es: Shell Sort con un tiempo de " << tiempo_ganador_sin_repetir << " segundos." << endl;
	}

    double time_taken_selection_sort_dup = getTimeTakenSelectionSort(numerosConDuplicados, ascendente);
    double time_taken_bubble_sort_dup = getTimeTakenBubbleSort(numerosConDuplicados, ascendente);
    double time_taken_insertion_sort_dup = getTimeTakenInsertionSort(numerosConDuplicados, ascendente);
    double time_taken_merge_sort_dup = getTimeTakenMergeSort(numerosConDuplicados, ascendente);
    double time_taken_quick_sort_dup = getTimeTakenQuickSort(numerosConDuplicados, ascendente);
    double time_taken_heap_sort_dup = getTimeTakenHeapSort(numerosConDuplicados);

    cout << "Carrera por el Tablero: Modo aleatorio con duplicados" << endl;
    cout << "1. Selection Sort, " << time_taken_selection_sort_dup << " segundos." << endl;
    cout << "2. Bubble Sort, " << time_taken_bubble_sort_dup << " segundos." << endl;
    cout << "3. Insertion Sort, " << time_taken_insertion_sort_dup << " segundos." << endl;
    cout << "4. Merge Sort, " << time_taken_merge_sort_dup << " segundos." << endl;
    cout << "5. Quick Sort, " << time_taken_quick_sort_dup << " segundos." << endl;
    cout << "6. Heap Sort, " << time_taken_heap_sort_dup << " segundos." << endl;
    cout << "7. Shell Sort, " << time_taken_shell_sort << " segundos." << endl;

    double tiempo_ganador_duplicados = min(time_taken_selection_sort_dup,
	    min(time_taken_bubble_sort_dup,
	        min(time_taken_insertion_sort_dup,
	            min(time_taken_merge_sort_dup,
	                min(time_taken_quick_sort_dup,
	                    min(time_taken_heap_sort_dup, time_taken_shell_sort_dup)
	                )
	            )
	        )
	    )
	);

    if (tiempo_ganador_duplicados == time_taken_selection_sort_dup) {
        cout << "El ganador es: Selection Sort con un tiempo de " << tiempo_ganador_duplicados << " segundos." << endl;
    } else if (tiempo_ganador_duplicados == time_taken_bubble_sort_dup) {
        cout << "El ganador es: Bubble Sort con un tiempo de " << tiempo_ganador_duplicados << " segundos." << endl;
    } else if (tiempo_ganador_duplicados == time_taken_insertion_sort_dup) {
        cout << "El ganador es: Insertion Sort con un tiempo de " << tiempo_ganador_duplicados << " segundos." << endl;
    } else if (tiempo_ganador_duplicados == time_taken_merge_sort_dup) {
        cout << "El ganador es: Merge Sort con un tiempo de " << tiempo_ganador_duplicados << " segundos." << endl;
    } else if (tiempo_ganador_duplicados == time_taken_quick_sort_dup) {
        cout << "El ganador es: Quick Sort con un tiempo de " << tiempo_ganador_duplicados << " segundos." << endl;
    } else if(tiempo_ganador_duplicados == time_taken_heap_sort_dup){
        cout << "El ganador es: Heap Sort con un tiempo de " << tiempo_ganador_duplicados << " segundos." << endl;
    }else{
    	cout << "El ganador es: Shell Sort con un tiempo de " << tiempo_ganador_duplicados << " segundos." << endl;
	}

    return 0;
}
