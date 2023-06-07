#include <QtTest/QtTest>
#include "unitTests.h"
#include "functions.h"

TestFunctions::TestFunctions(QObject *parent) :
    QObject(parent)
{
}

void TestFunctions::test_heapSort()
{
    QVector<int> arr;
    arr = {3, 2, 1, 5, 4};
    functions func;
    func.heapSort(arr, 5);
    QCOMPARE(arr, (QVector<int>{1, 2, 3, 4, 5}));
    arr = {10, -10, 20, -20, 0};
    func.heapSort(arr, 5);
    QCOMPARE(arr, (QVector<int>{-20, -10, 0, 10, 20}));
    arr = {100, 200, 300, 400, 500};
    func.heapSort(arr, 5);
    QCOMPARE(arr, (QVector<int>{100, 200, 300, 400, 500}));
    arr = {500, 400, 300, 200, 100};
    func.heapSort(arr, 5);
    QCOMPARE(arr, (QVector<int>{100, 200, 300, 400, 500}));
    arr = {0, 0, 0, 0, 0};
    func.heapSort(arr, 5);
    QCOMPARE(arr, (QVector<int>{0, 0, 0, 0, 0}));
    arr = {1, 1, 1, 1, 1};
    func.heapSort(arr, 5);
    QCOMPARE(arr, (QVector<int>{1, 1, 1, 1, 1}));
    arr = {-1, -1, -1, -1, -1};
    func.heapSort(arr, 5);
    QCOMPARE(arr, (QVector<int>{-1, -1, -1, -1, -1}));
    arr = {-5, -4, -3, -2, -1};
    func.heapSort(arr, 5);
    QCOMPARE(arr, (QVector<int>{-5, -4, -3, -2, -1}));
    arr = {-1, -2, -3, -4, -5};
    func.heapSort(arr, 5);
    QCOMPARE(arr, (QVector<int>{-5, -4, -3, -2, -1}));
    arr = {1, 3, 2, 5, 4};
    func.heapSort(arr, 5);
    QCOMPARE(arr, (QVector<int>{1, 2, 3, 4, 5}));
}
