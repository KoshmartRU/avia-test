#include <iostream>
#include <ctime>
#include <algorithm>

using namespace std;

template<class T>
class CDArray {
    T *m_pData;
    int m_Number;
    int m_Size;

public:
    CDArray() :
        m_Number(0),
        m_Size(1)
    {
        m_pData = new T[m_Size];
    }

    CDArray(int size) :
        m_Number(0),
        m_Size(size)
    {
        m_pData = new T[m_Size];
    }

    virtual ~CDArray() {
        delete[] m_pData;
    }

    int Add(const T &t) {
        *(m_pData + m_Number) = t;
        m_Number++;
        if(m_Number == m_Size) {
            m_pData = (T*)realloc(m_pData, sizeof(T) * m_Size * 2);
            m_Size *= 2;
        }
        return m_Number;
    }

    int Delete(int number) {
        if(number < 0 || number >= m_Number)
            return -1;

        for(int i = number; i < m_Number - 1; i++)
            *(m_pData + i) = *(m_pData + i + 1);

        m_Number--;
        m_Size--;
        m_pData = (T*)realloc(m_pData, sizeof(T) * m_Size);

        return 0;
    }

    int Modify(int n, const T &t) {
        if(n < 0 || n >= m_Number)
            return -1;

        *(m_pData + n) = t;
        return 0;
    }

    int Resize(int size) {
        if(size < 0)
            return -1;

        if(size == 0) {
            Clear();
            return 0;
        }

        m_pData = (T*)realloc(m_pData, sizeof(T) * size * 2);
        m_Size = size * 2;
        m_Number = size;

        return 0;
    }

    void Clear() {
        m_pData = (T*)realloc(m_pData, sizeof(T));
        m_Number = 0;
        m_Size = 1;
    }

    T &operator[]( int i ) const { return m_pData[i]; }

    int Number() const { return m_Number; }

    int Size() const { return m_Size; }

    T *Ptr() { return m_pData; }
};

const int valueCount = 700;

int main() {
    CDArray<int> values(valueCount);

    //generate values
    srand(time(nullptr));
    int min, max;
    cout << "Set random value range:";
    scanf_s("%i %i", &min, &max);

    for(int i = 0; i < valueCount; i++)
        values.Add(min + rand() % max);

    cout << "Results:" << endl;

    //sort values
    sort(values.Ptr(), values.Ptr() + values.Number());

    //calc mean
    double m = 0.0;
    for(int i = 0; i < valueCount; i++)
        m += values[i];
    m /= valueCount;
    cout << "M = " << m << endl;

    //calc variance
    double d = 0.0;
    for(int i = 0; i < valueCount; i++)
        d += pow(values[i] - m, 2);
    d /= valueCount;
    cout << "D = " << d << endl;

    //calc deviation
    double s = 0.0;
    s = sqrt(d);
    cout << "S = " << s << endl;

    return 0;
}
