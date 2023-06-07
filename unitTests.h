#ifndef UNITTESTS_H
#define UNITTESTS_H
#include <QtTest/QtTest>
#include "functions.h"

class TestFunctions : public QObject
{
    Q_OBJECT
public:
    explicit TestFunctions(QObject *parent = 0);

private slots:
    void test_heapSort();
};


#endif // UNITTESTS_H
