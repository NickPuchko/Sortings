#include "Empolyee.h"

//Перегрузка операторов сравнения. Лектор рекоммендовал избегать прямых сравнений на равенство, \
//ввиду их неэффективности для строк. Вместо этого используются условные конструкции. Таким образом, прирост
//производительности составлял от 5% до 1000% (в случае частично/польностью отсортирвоанного массива
bool Employee::operator > (const Employee &E){
    if (department > E.department){
        return true;
    }
    else if (department < E.department){
        return false;
    }
    else{
        if (name > E.name){
            return true;
        }
        else{
            return false;
        }
    }
}

//Аналогично с оператором >
bool Employee::operator < (const Employee &E){
    if (department < E.department){
        return true;
    }
    else if (department > E.department){
        return false;
    }
    else{
        if (name < E.name){
            return true;
        }
        else{
            return false;
        }
    }
}

//Некторые операторы не использованы, но по заданию решено добавить в функционал
bool Employee::operator == (const Employee &E) {
    if (name == E.name and department == E.department){
        return true;
    } else{
        return false;
    }
}

bool Employee::operator != (const Employee &E) {
    if (name != E.name or department != E.department){
        return true;
    }else{
        return false;
    }
}

bool Employee::operator >= (const Employee &E) {
    if (department > E.department){
        return true;
    }
    else if (department < E.department){
        return false;
    }
    else{
        if (name > E.name){
            return true;
        }
        else if (name < E.name){
            return false;
        } else{
            return true;
        }
    }
}

bool Employee::operator <= (const Employee &E) {
    if (department < E.department){
        return true;
    }
    else if (department > E.department){
        return false;
    }
    else{
        if (name < E.name){
            return true;
        }
        else if (name > E.name){
            return false;
        }
        else{
            return true;
        }
    }
}

//Считывание .csv текстового файла в вектор. Сама база данных генерировалась стронними инструментами
// (готовый рандомайзер на 24206400 объектов класса Employee)
vector <string> FileToStrings(int n){
    vector <string> lines(n * 6);   //6 слов в строке
    ifstream file; //Открыли!
    file.open("/Users/nick/CLionProjects/laba2/Data1.csv", ios_base::in);
    if (file.is_open()){    //На всякий случай проверка (хотя файл в проекте по умолчанию)
        for (int i = 0; i < n; ++i) {
            if (i % 6 == 5){        //Слова, кроме последнего
                getline(file, lines[i]);
            } else{
                getline(file, lines[i], ' ');       //Последнее слово в каждой строке
            }
        }
    }
    else{
        cout << "Fail! File is unreachable";
        file.close();
        exit(1);        //Если файла нет, идем копаться в .csv, сразу экономя время
    }
    file.close(); //Закрыли!
    return lines;       //Вектор строк (слов)
}

//Читаем каждое слово в объект класса Employee, используя делимость индексов элементов
vector <Employee> StringsToVector(vector <string> &lines, int n){
    string space = " ";         //Aesthetic
    int count = 0;
    vector <Employee> data(n, Employee());  //Создали вектор
    for (int i = 0; i < n * 6; ++i) {
        data[count].name.append(lines[i]);      //С помощью метода append удобно получать ФИО из Ф+И+О
        //лучше, чем прямая конкатенация строк, проверено опытным путем:)

        i++;
        data[count].name.append(space);
        data[count].name.append(lines[i]);
        i++;
        data[count].name.append(space);
        data[count].name.append(lines[i]);
        i++;

        data[count].department = lines[i][0] - 48;      //По аски коду, по заветам старой школы
        i++;

        data[count].post.append(lines[i]);
        i++;

        data[count].year.append(lines[i]);

        count++;
    }
    return data;        //Вернули слепок БД
}

//Описание BubbleSort в отчете
void BubbleSortSucks(vector <Employee> &temp){
    int size = temp.size();
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (temp[j] > temp[j+1]){
                swap(temp[j], temp[j+1]);
            }
        }
    }
}

//Сначала попробовал написать просеивание через пирамиду снизу вверх, но получилось экстремально медлительно
//Моя гипотеза: это связано с тем, что при каждом превосхождении ребенка над родителем приходится заново начинать целый
//слой. Пусть он и уже отсортированный, но HeapSort не выигрывает из-за этого в скорости.
//Пришлось использовать более шаблонную сортирвку сверху :(
//bool Heapify(vector <Employee> data, int papa){
//    for (papa; papa < 99; ++papa) {
//        if (data[papa] < data[2 * papa + 1]){
//            if (data[2 * papa + 2] < data[2 * papa + 1]){
//                swap(data[papa], data[2 * papa + 1]);
//                if (papa % 2 == 1){
//                    Heapify(data, papa / 2);
//                }else{
//                    Heapify(data, papa / 2 - 1);
//                }
//            } else{
//                swap(data[papa], data[2 * papa + 2]);
//                if (papa % 2 == 1){
//                    Heapify(data, papa / 2);
//                }else{
//                    Heapify(data, papa / 2 - 1);
//                }
//            }
//        }
//        else if (data[papa] < data[2 * papa + 2]){
//            swap(data[papa], data[2 * papa + 2]);
//            if (papa % 2 == 1){
//                Heapify(data, papa / 2);
//            }else{
//                Heapify(data, papa / 2 - 1);
//            }
//        }
//    }
//    return 1;
//}

//Вспомогательная функция для HeapSortCooler
void Heapify(vector <Employee> &temp, int root, int bottom) {
//Что любопытно, при передаче вектора по значению, а не по ссылке, HeapSort становится даже медленнее, чем BubbleSort
    int maxChild; // индекс старшего сына
    int flag = 0; // если куча готова
// Пока не дошли до последнего ряда
    while ((root * 2 <= bottom) && (!flag))
    {
        if (root * 2 == bottom) // если последнее поколение
            maxChild = root * 2; // левый сын
// иначе принимается старший сын
        else if (temp[root * 2] > temp[root * 2 + 1])
            maxChild = root * 2;
        else
            maxChild = root * 2 + 1;
// если элемент меньше большего сына
        if (temp[root] < temp[maxChild]) {
            swap(temp[root], temp[maxChild]);   //Чудесная функция обмена - быстрая и компактная
            root = maxChild;
        }
        else
            flag = 1; // куча готова
    }
}

//Описание HeapSort в отчете
void HeapSortCooler(vector <Employee> &temp) {
    int size = temp.size();
// Формируем последнее поколение
    for (int i = (size / 2) - 1; i >= 0; i--)
        Heapify(temp, i, size - 1);
// Просеиваем остальные элементы
    for (int i = size - 1; i >= 1; i--)
    {
        swap(temp[0], temp[i]);     //Чудесная функция обмена - быстрая и компактная
        Heapify(temp, 0, i - 1);    //Рекурсия
    }

}

//Вспомогательная функция проверки корректности сортировок.
//Нужна только при рефакторинге! Не трогать!
bool SortsChecker(vector <Employee> &first, vector <Employee> &second){
    int size1 = first.size();
    int size2 = second.size();
    cout << "Comparing sorted vectors..." << endl;
    if (size1 == size2){
        cout << "Sizes are equal. Keep on comparing...\n";
        for (int i = 0; i < size1; ++i) {
            cout << first[i].name << " "<< first[i].department  << "    ####    "  << second[i].name << ' ' << second[i].department << endl;
            if (first[i] != second[i]){
                cout << "Something differs!";
                return false;
            }
        }
        cout << "Sortings work well, vectors are completely equal!" << endl;
        return true;
    }else{
        cout << "Sizes differ!" << endl;
        cout << "Bubble:    " << size1 << endl << "Heap:    " << size2 << endl;
        return false;
    }
}

//Вывод результата (таймер)
void CheckTime(int a1, int a2, int b1, int b2){
    double BubbleTime = double(a2 - a1) / CLOCKS_PER_SEC;   //Посчитали время BubbleSort
    double HeapTime = double(b2 - b1) / CLOCKS_PER_SEC;     //Посчитали время HeapSort
    cout << "BubbleSort time:   " << BubbleTime * 1000 << "ms" << endl;     //Вывод результата в милисекундах
    cout << "HeapSort time:    " << HeapTime * 1000 << "ms" << endl;
}
