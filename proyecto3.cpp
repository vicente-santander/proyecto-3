#include <iostream>
#include <string>
#include <random>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <chrono>


using namespace std;

// Función para generar números aleatorios sin repetir en el rango [min, max]
unordered_map<int, int> generarNumerosAleatoriosSinRepetir(int min, int max, int cantidad) {
    unordered_map<int, int> numeros;

	// Crear un generador de números aleatorios
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(min, max);

	// Generar números hasta alcanzar la cantidad deseada sin repetir
    while (numeros.size() < cantidad) {
        int numero = dis(gen);
        numeros[numero]++;
    }

    return numeros;
}

// Función para generar números aleatorios con duplicados en el rango [min, max]
vector<int> generarNumerosAleatoriosConDuplicados(int min, int max, int cantidad) {
    vector<int> numeros;

	// Crear un generador de números aleatorios
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(min, max);
	
	// Generar números aleatorios y agregarlos al vector
    for (int i = 0; i < cantidad; i++) {
        int numero = dis(gen);
        numeros.push_back(numero);
    }

    return numeros;
}

void SelectionSort(vector<int>& arr, bool ascendente) {
    // Obtener la cantidad de elementos en el arreglo
	int n = arr.size();

	// Recorrer el arreglo para encontrar el valor mínimo o máximo en cada iteración
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
        	// Comprobar si el elemento actual es menor (o mayor, según ascendente) que el mínimo (o máximo)
            if ((ascendente && arr[j] < arr[minIndex]) || (!ascendente && arr[j] > arr[minIndex])) {
                minIndex = j;
            }
        }
        // Intercambiar el elemento actual con el mínimo (o máximo) encontrado
        swap(arr[i], arr[minIndex]);
    }
}

void BubbleSort(vector<int>& arr, bool ascendente) {
    int n = arr.size();

	// Recorrer el arreglo y comparar elementos adyacentes, intercambiándolos si es necesario
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
        	// Comprobar si el elemento actual es mayor (o menor, según ascendente) que el siguiente
            if ((ascendente && arr[j] > arr[j + 1]) || (!ascendente && arr[j] < arr[j + 1])) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void InsertionSort(vector<int>& arr, bool ascendente) {
    int n = arr.size();

	// Recorrer el arreglo e insertar cada elemento en la posición correcta del arreglo ordenado
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
		
		// Mover elementos mayores (o menores, según ascendente) hacia la derecha para insertar el elemento actual
        while (j >= 0 && ((ascendente && arr[j] > key) || (!ascendente && arr[j] < key))) {
            arr[j + 1] = arr[j];
            j--;
        }
		// Insertar el elemento actual en su posición correcta
        arr[j + 1] = key;
    }
}

void Merge(vector<int>& arr, int left, int middle, int right, bool ascendente) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    vector<int> L(n1);
    vector<int> R(n2);
	
	// Copiar los elementos de los subarreglos en arreglos temporales
    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }

    for (int j = 0; j < n2; j++) {
        R[j] = arr[middle + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;
    
	// Comparar y mezclar los elementos de los subarreglos
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
	// Copiar los elementos restantes de los subarreglos en el arreglo original
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
		// Dividir el arreglo en dos mitades y ordenar cada mitad recursivamente
        MergeSort(arr, left, middle, ascendente);
        MergeSort(arr, middle + 1, right, ascendente);
		
		// Mezclar las dos mitades ordenadas
        Merge(arr, left, middle, right, ascendente);
    }
}

// Función auxiliar para el algoritmo Quick Sort, particiona el arreglo en dos subarreglos
int Partition(vector<int>& arr, int low, int high, bool ascendente) {
    // Elegir un pivote aleatorio dentro del rango de partición
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(low, high);
    int random_pivot_index = dis(gen);

    // Intercambiar el pivote con el último elemento
    swap(arr[random_pivot_index], arr[high]);

    int pivot = arr[high];
    int i = low - 1;
    
	// Recorrer el arreglo y colocar los elementos menores (o mayores, según ascendente) que el pivote a la izquierda
    for (int j = low; j <= high - 1; j++) {
        if ((ascendente && arr[j] < pivot) || (!ascendente && arr[j] > pivot)) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    
	// Colocar el pivote en su posición correcta
    swap(arr[i + 1], arr[high]);
    return i + 1;
}


void QuickSort(vector<int>& arr, int low, int high, bool ascendente) {
    if (low < high) {
    	// Obtener el índice de partición
        int pivotIndex = Partition(arr, low, high, ascendente);

        // Ordenar recursivamente los subarreglos antes y después del pivote
        QuickSort(arr, low, pivotIndex - 1, ascendente);
        QuickSort(arr, pivotIndex + 1, high, ascendente);
    }
}

// Función auxiliar para el algoritmo Heap Sort, asegura que el subárbol con raíz en el índice i sea un heap
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

	// Calcular el espacio (gap) inicial
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
        	// Insertion Sort con el espacio (gap) actual
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

    // Generar un número aleatorio entre 90,000 y 100,000
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> count_dis(90000, 100000);
	int num_count = count_dis(gen);	
	
    // Generar conjunto de datos ordenado
    vector<int> datosOrdenados(num_count);
    for (int i = 0; i < num_count; i++) {
        datosOrdenados[i] = i;
        
    }
    
    // Determinar el total de elementos en num_count
	int total_elementos = datosOrdenados.size();
	
	cout << "Total de elementos en num_count: " << total_elementos << endl;

    // Generar conjunto de datos inversamente ordenado
    vector<int> datosInversos(num_count);
    for (int i = 0; i < num_count; i++) {
        datosInversos[i] = num_count - i - 1;
        //cout << datosInversos[i] << endl;
    }

    // Generar conjunto de datos aleatorios sin repetición
    unordered_map<int, int> numerosSinRepetir = generarNumerosAleatoriosSinRepetir(0, num_count, num_count);
    vector<int> datosAleatoriosSinRepetir(num_count);
    int index = 0;
    for (const auto& pair : numerosSinRepetir) {
        datosAleatoriosSinRepetir[index++] = pair.first;
    }

    // Generar conjunto de datos aleatorios con duplicados
    vector<int> datosAleatoriosConDuplicados(num_count);
    for (int i = 0; i < num_count; i++) {
        datosAleatoriosConDuplicados[i] = i % (num_count); 
    }

    double time_taken_selection_sort, time_taken_bubble_sort, time_taken_insertion_sort,
        time_taken_merge_sort, time_taken_quick_sort, time_taken_heap_sort, time_taken_shell_sort;

    // Carrera por el Tablero: Modo Ordenado
    time_taken_selection_sort = getTimeTakenSelectionSort(datosOrdenados, ascendente);
    time_taken_bubble_sort = getTimeTakenBubbleSort(datosOrdenados, ascendente);
    time_taken_insertion_sort = getTimeTakenInsertionSort(datosOrdenados, ascendente);
    time_taken_merge_sort = getTimeTakenMergeSort(datosOrdenados, ascendente);
    time_taken_quick_sort = getTimeTakenQuickSort(datosOrdenados, ascendente);
    time_taken_heap_sort = getTimeTakenHeapSort(datosOrdenados);
    time_taken_shell_sort = getTimeTakenShellSort(datosOrdenados, ascendente);

    cout << "Carrera por el Tablero: Modo Ordenado" << endl;
    cout << "1. Selection Sort, " << time_taken_selection_sort << " segundos." << endl;
    cout << "2. Bubble Sort, " << time_taken_bubble_sort << " segundos." << endl;
    cout << "3. Insertion Sort, " << time_taken_insertion_sort << " segundos." << endl;
    cout << "4. Merge Sort, " << time_taken_merge_sort << " segundos." << endl;
    cout << "5. Quick Sort, " << time_taken_quick_sort << " segundos." << endl;
    cout << "6. Heap Sort, " << time_taken_heap_sort << " segundos." << endl;
    cout << "7. Shell Sort, " << time_taken_shell_sort << " segundos." << endl;

    double tiempo_ganador_ordenado = min(time_taken_selection_sort,
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

    if (tiempo_ganador_ordenado == time_taken_selection_sort) {
        cout << "El ganador es: Selection Sort con un tiempo de " << tiempo_ganador_ordenado << " segundos." << endl;
    } else if (tiempo_ganador_ordenado == time_taken_bubble_sort) {
        cout << "El ganador es: Bubble Sort con un tiempo de " << tiempo_ganador_ordenado << " segundos." << endl;
    } else if (tiempo_ganador_ordenado == time_taken_insertion_sort) {
        cout << "El ganador es: Insertion Sort con un tiempo de " << tiempo_ganador_ordenado << " segundos." << endl;
    } else if (tiempo_ganador_ordenado == time_taken_merge_sort) {
        cout << "El ganador es: Merge Sort con un tiempo de " << tiempo_ganador_ordenado << " segundos." << endl;
    } else if (tiempo_ganador_ordenado == time_taken_quick_sort) {
        cout << "El ganador es: Quick Sort con un tiempo de " << tiempo_ganador_ordenado << " segundos." << endl;
    } else if(tiempo_ganador_ordenado == time_taken_heap_sort){
        cout << "El ganador es: Heap Sort con un tiempo de " << tiempo_ganador_ordenado << " segundos." << endl;
    }else{
        cout << "El ganador es: Shell Sort con un tiempo de " << tiempo_ganador_ordenado << " segundos." << endl;
    }

    // Carrera por el Tablero: Modo Inversamente Ordenado
    time_taken_selection_sort = getTimeTakenSelectionSort(datosInversos, ascendente);
    time_taken_bubble_sort = getTimeTakenBubbleSort(datosInversos, ascendente);
    time_taken_insertion_sort = getTimeTakenInsertionSort(datosInversos, ascendente);
    time_taken_merge_sort = getTimeTakenMergeSort(datosInversos, ascendente);
    time_taken_quick_sort = getTimeTakenQuickSort(datosInversos, ascendente);
    time_taken_heap_sort = getTimeTakenHeapSort(datosInversos);
    time_taken_shell_sort = getTimeTakenShellSort(datosInversos, ascendente);

    cout << "Carrera por el Tablero: Modo inversamente ordenado" << endl;
    cout << "1. Selection Sort, " << time_taken_selection_sort << " segundos." << endl;
    cout << "2. Bubble Sort, " << time_taken_bubble_sort << " segundos." << endl;
    cout << "3. Insertion Sort, " << time_taken_insertion_sort << " segundos." << endl;
    cout << "4. Merge Sort, " << time_taken_merge_sort << " segundos." << endl;
    cout << "5. Quick Sort, " << time_taken_quick_sort << " segundos." << endl;
    cout << "6. Heap Sort, " << time_taken_heap_sort << " segundos." << endl;
    cout << "7. Shell Sort, " << time_taken_shell_sort << " segundos." << endl;

    double tiempo_ganador_inverso = min(time_taken_selection_sort,
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

    if (tiempo_ganador_inverso == time_taken_selection_sort) {
        cout << "El ganador es: Selection Sort con un tiempo de " << tiempo_ganador_inverso << " segundos." << endl;
    } else if (tiempo_ganador_inverso == time_taken_bubble_sort) {
        cout << "El ganador es: Bubble Sort con un tiempo de " << tiempo_ganador_inverso << " segundos." << endl;
    } else if (tiempo_ganador_inverso == time_taken_insertion_sort) {
        cout << "El ganador es: Insertion Sort con un tiempo de " << tiempo_ganador_inverso << " segundos." << endl;
    } else if (tiempo_ganador_inverso == time_taken_merge_sort) {
        cout << "El ganador es: Merge Sort con un tiempo de " << tiempo_ganador_inverso << " segundos." << endl;
    } else if (tiempo_ganador_inverso == time_taken_quick_sort) {
        cout << "El ganador es: Quick Sort con un tiempo de " << tiempo_ganador_inverso << " segundos." << endl;
    } else if(tiempo_ganador_inverso == time_taken_heap_sort){
        cout << "El ganador es: Heap Sort con un tiempo de " << tiempo_ganador_inverso << " segundos." << endl;
    }else{
        cout << "El ganador es: Shell Sort con un tiempo de " << tiempo_ganador_inverso << " segundos." << endl;
    }

    // Carrera por el Tablero: Modo Aleatorio sin repetición
    time_taken_selection_sort = getTimeTakenSelectionSort(datosAleatoriosSinRepetir, ascendente);
    time_taken_bubble_sort = getTimeTakenBubbleSort(datosAleatoriosSinRepetir, ascendente);
    time_taken_insertion_sort = getTimeTakenInsertionSort(datosAleatoriosSinRepetir, ascendente);
    time_taken_merge_sort = getTimeTakenMergeSort(datosAleatoriosSinRepetir, ascendente);
    time_taken_quick_sort = getTimeTakenQuickSort(datosAleatoriosSinRepetir, ascendente);
    time_taken_heap_sort = getTimeTakenHeapSort(datosAleatoriosSinRepetir);
    time_taken_shell_sort = getTimeTakenShellSort(datosAleatoriosSinRepetir, ascendente);

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

    // Carrera por el Tablero: Modo Aleatorio con duplicados
    time_taken_selection_sort = getTimeTakenSelectionSort(datosAleatoriosConDuplicados, ascendente);
    time_taken_bubble_sort = getTimeTakenBubbleSort(datosAleatoriosConDuplicados, ascendente);
    time_taken_insertion_sort = getTimeTakenInsertionSort(datosAleatoriosConDuplicados, ascendente);
    time_taken_merge_sort = getTimeTakenMergeSort(datosAleatoriosConDuplicados, ascendente);
    time_taken_quick_sort = getTimeTakenQuickSort(datosAleatoriosConDuplicados, ascendente);
    time_taken_heap_sort = getTimeTakenHeapSort(datosAleatoriosConDuplicados);
    time_taken_shell_sort = getTimeTakenShellSort(datosAleatoriosConDuplicados, ascendente);

    cout << "Carrera por el Tablero: Modo aleatorio con duplicados" << endl;
    cout << "1. Selection Sort, " << time_taken_selection_sort << " segundos." << endl;
    cout << "2. Bubble Sort, " << time_taken_bubble_sort << " segundos." << endl;
    cout << "3. Insertion Sort, " << time_taken_insertion_sort << " segundos." << endl;
    cout << "4. Merge Sort, " << time_taken_merge_sort << " segundos." << endl;
    cout << "5. Quick Sort, " << time_taken_quick_sort << " segundos." << endl;
    cout << "6. Heap Sort, " << time_taken_heap_sort << " segundos." << endl;
    cout << "7. Shell Sort, " << time_taken_shell_sort << " segundos." << endl;

    double tiempo_ganador_con_duplicados = min(time_taken_selection_sort,
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

    if (tiempo_ganador_con_duplicados == time_taken_selection_sort) {
        cout << "El ganador es: Selection Sort con un tiempo de " << tiempo_ganador_con_duplicados << " segundos." << endl;
    } else if (tiempo_ganador_con_duplicados == time_taken_bubble_sort) {
        cout << "El ganador es: Bubble Sort con un tiempo de " << tiempo_ganador_con_duplicados << " segundos." << endl;
    } else if (tiempo_ganador_con_duplicados == time_taken_insertion_sort) {
        cout << "El ganador es: Insertion Sort con un tiempo de " << tiempo_ganador_con_duplicados << " segundos." << endl;
    } else if (tiempo_ganador_con_duplicados == time_taken_merge_sort) {
        cout << "El ganador es: Merge Sort con un tiempo de " << tiempo_ganador_con_duplicados << " segundos." << endl;
    } else if (tiempo_ganador_con_duplicados == time_taken_quick_sort) {
        cout << "El ganador es: Quick Sort con un tiempo de " << tiempo_ganador_con_duplicados << " segundos." << endl;
    } else if(tiempo_ganador_con_duplicados == time_taken_heap_sort){
        cout << "El ganador es: Heap Sort con un tiempo de " << tiempo_ganador_con_duplicados << " segundos." << endl;
    }else{
        cout << "El ganador es: Shell Sort con un tiempo de " << tiempo_ganador_con_duplicados << " segundos." << endl;
    }

    return 0;
}
