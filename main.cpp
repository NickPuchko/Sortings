#include <iostream>
#include <ctime>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include "Empolyee.h"
#include "Empolyee.cpp"
using namespace std;


int main() {
    clock_t StartBubble, EndBubble, StartHeap, EndHeap;     //Объявление переменных таймера
    string tmp;     //Строка для корректного ввода int
    cout << "How many boys shall we sort?" << endl;
    getline(cin, tmp);
    int n = stoi(tmp);      //Получаем int

    //Чтание файла, создание базы данных, объявление вспомогательных копий
    vector <string> lines = FileToStrings(n);
    vector <Employee> data = StringsToVector(lines, n);
    vector <Employee> HeapData = data;
    vector <Employee> BubbleData = data;

    StartBubble = clock();      //Таймер
    BubbleSortSucks(BubbleData);        //BubbleSort
    EndBubble = clock();        //Таймер
    StartHeap = clock();        //Таймер
    HeapSortCooler(HeapData);       //HeapSort
    EndHeap = clock();      //Таймер

    //Проверка корректности закомментирована. Нужна только для рефактроринга кода при создании сортировок
//    if (SortsChecker(BubbleData, HeapData)){
//        cout << "Well done!" << endl;
//    }else{
//        cout << "There kids are not alright!" << endl;
//    }
    CheckTime(StartBubble, EndBubble, StartHeap, EndHeap);      //Вывод результата исследования
    return 0;
}