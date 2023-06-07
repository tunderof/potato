#include "functions.h"

QByteArray functions::parse(const QByteArray &array){
    QByteArray res = "";
        if(array.contains("stop")) {
            res= "stop";
        }
        else if(array.contains("sort")){
             QStringList args = QString(array).split('&');
             if (args[1].contains('<')) args[1].replace("<","");
             if (args[1].contains('>')) args[1].replace(">","");
             int step = args[1].toInt();
             QStringList numbers = args[2].split(' ');
             QVector<int> array;
             for(int i =0; i < numbers.length(); i++){
                array.append(numbers[i].toInt());
             }
             heapSort(array, step);
             res = "Sorted array for " + QString(step).toUtf8() + "value ";
             for(int i =0; i < numbers.length(); i++){
                res+= QByteArray::number(array[i]);
             }
        }
        else{
            res="Wrong command";
        }
        return res;
}

void functions::heapify( QVector<int>& arr, int n, int i) {
    int largest = i; // Инициализируем наибольший элемент как корень
    int left = 2*i + 1; // левый = 2*i + 1
    int right = 2*i + 2; // правый = 2*i + 2

    // Если левый дочерний элемент больше корня
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // Если правый дочерний элемент больше, чем самый большой элемент до сих пор
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // Если самый большой элемент не корень
    if (largest != i) {
        std::swap(arr[i], arr[largest]);

        // Рекурсивно просеиваем влияющее поддерево
        heapify(arr, n, largest);
    }
}

void functions::heapSort( QVector<int>& arr, int step) {
    int n = step;
    // Построение кучи (перегруппируем массив)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Один за другим извлекаем элементы из кучи
    for (int i=n-1; i>=0; i--) {
        // Перемещаем текущий корень в конец
        std::swap(arr[0], arr[i]);

        // вызываем процедуру heapify на уменьшенной куче
        heapify(arr, i, 0);
    }
}

