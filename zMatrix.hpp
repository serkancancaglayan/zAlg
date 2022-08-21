#pragma once
#include <iostream>
#include <vector>
#include <math.h>
template <class T>
class zMatrix{
    public:
        zMatrix();
        zMatrix(int nRows, int nCols);
        zMatrix(int nRows, int nCols, const T* data);
        zMatrix(const zMatrix<T> & otherMatrix);
        zMatrix(int nRows, int nCols, const std::vector<T> & v);
        zMatrix(const std::vector<std::vector<T>> &v);
        zMatrix(int nRows, int nCols, T** arr);
        ~zMatrix();

        T getElement(int row, int col) const;
        bool setElement(int row, int col, T data);
        int getnRows() const;
        int getnCols() const;
        
        bool isEqual(T val1, T val2);
        bool compare(const zMatrix<T> & otherMatrix, double tolerance);
        zMatrix<T> transpose() const;
        void toIdentity();
        int rank();
        zMatrix<T> rowEchelon();
        T determinant();
        zMatrix<T> find_sub_matrix(int row, int col);        
        bool isSquare();
        bool isRowEchelon();
        bool isNonZero();
        bool isSymmetric();


        template<class U> friend std::ostream& operator<<(std::ostream& outStream, const zMatrix<U> & m);

        bool operator==(const zMatrix<T> &r);
        zMatrix<T> operator=(const zMatrix<T> &r);

        template<class U> friend zMatrix<U> operator+(const zMatrix<U> &l, const zMatrix<U> &r);
        template<class U> friend zMatrix<U> operator+(const U &l, const zMatrix<U> &r);
        template<class U> friend zMatrix<U> operator+(const zMatrix<U> &l, const U &r);

        template<class U> friend zMatrix<U> operator-(const zMatrix<U> &l, const zMatrix<U> &r);
        template<class U> friend zMatrix<U> operator-(const U &l, const zMatrix<U> &r);
        template<class U> friend zMatrix<U> operator-(const zMatrix<U> &l, const U &r);

        template<class U> friend zMatrix<U> operator*(const zMatrix<U> &l, const zMatrix<U> &r);
        template<class U> friend zMatrix<U> operator*(const U &l, const zMatrix<U> &r);
        template<class U> friend zMatrix<U> operator*(const zMatrix<U> &l, const U &r);

    private:
        inline int linearIndex(int row, int col) const;
        int nRows;
        int nCols;
        int nElements;
        T * mData;

};
