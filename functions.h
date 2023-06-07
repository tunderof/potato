#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QByteArray>
#include <QVector>
#include <QStringList>

#include <algorithm>

#include <QDebug>

class functions
{
public:
    QByteArray parse(const QByteArray &array);
    void heapSort( QVector<int>& arr, int step);
private:
    void heapify( QVector<int>& arr, int n, int i);
};

#endif // FUNCTIONS_H
