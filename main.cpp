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
    clock_t StartBubble, EndBubble, StartHeap, EndHeap;     //���������� ���������� �������
    string tmp;     //������ ��� ����������� ����� int
    cout << "How many boys shall we sort?" << endl;
    getline(cin, tmp);
    int n = stoi(tmp);      //�������� int

    //������ �����, �������� ���� ������, ���������� ��������������� �����
    vector <string> lines = FileToStrings(n);
    vector <Employee> data = StringsToVector(lines, n);
    vector <Employee> HeapData = data;
    vector <Employee> BubbleData = data;

    StartBubble = clock();      //������
    BubbleSortSucks(BubbleData);        //BubbleSort
    EndBubble = clock();        //������
    StartHeap = clock();        //������
    HeapSortCooler(HeapData);       //HeapSort
    EndHeap = clock();      //������

    //�������� ������������ ����������������. ����� ������ ��� ������������� ���� ��� �������� ����������
//    if (SortsChecker(BubbleData, HeapData)){
//        cout << "Well done!" << endl;
//    }else{
//        cout << "There kids are not alright!" << endl;
//    }
    CheckTime(StartBubble, EndBubble, StartHeap, EndHeap);      //����� ���������� ������������
    return 0;
}