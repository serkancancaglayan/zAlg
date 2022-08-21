#include "zMatrix.hpp"

template <class T>
zMatrix<T>::zMatrix(){
    this->nCols = 0;
    this->nRows = 0;
    this->nElements = 0;
    this->mData = nullptr;
}

template <class T>
zMatrix<T>::zMatrix(int nRows, int nCols){
    this->nRows = nRows;
    this->nCols = nCols;
    nElements = nRows * nCols;

    mData = new T[nElements];
    if(mData == nullptr){
        std::cerr << "Memory allocation error!" << std::endl;
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < nElements; i++){
        mData[i] = 0.0;
    }
}

template <class T>
zMatrix<T>::zMatrix(int nRows, int nCols, const T* data){
    this->nRows = nRows;
    this->nCols = nCols;
    nElements = nRows * nCols;

    mData = new T[nElements];
    if(mData == nullptr){
        std::cerr << "Memory allocation error!" << std::endl;
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < nElements; i++){
        mData[i] = data[i];
    }
}

template <class T>
zMatrix<T>::zMatrix(const zMatrix<T> & otherMatrix){
    nRows = otherMatrix.nRows;
    nCols = otherMatrix.nCols;
    nElements = otherMatrix.nElements;

    mData = new T[nElements];
    if(mData == nullptr){
        std::cerr << "Memory allocation error!" << std::endl;
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < nElements; i++){
        mData[i] = otherMatrix.mData[i];
    }
}

template <class T>
zMatrix<T>::zMatrix(int nRows, int nCols, const std::vector<T> & v){
    this->nRows = nRows;
    this->nCols = nCols;
    nElements = nRows * nCols;

    mData = new T[nElements];
    if(mData == nullptr){
        std::cerr << "Memory allocation error!" << std::endl;
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < nElements; i++){
        mData[i] = v[i];
    }
}

template <class T>
zMatrix<T>::zMatrix(const std::vector<std::vector<T>> &v){
    nRows = v.size();
    nCols = v[0].size();
    nElements = nRows * nCols;
    
    mData = new T[nElements];
    if(mData == nullptr){
        std::cerr << "Memory allocation error!" << std::endl;
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < nRows; i++){
        for(int j = 0; j < nCols; j++){
            int idx = linearIndex(i, j);
            mData[idx] = v[i][j]; 
        }
    }
}

template <class T>
zMatrix<T>::zMatrix(int nRows, int nCols, T** arr){
    this->nRows = nRows;
    this->nCols = nCols;
    nElements = nRows * nCols;

    mData = new T[nElements];
    if(mData == nullptr){
        std::cerr << "Memory allocation error!" << std::endl;
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < nRows; i++){
        for(int j = 0; j < nCols; j++){
            int idx = linearIndex(i, j);
            mData[idx] = arr[i][j];
        }
    }
}
template <class T>
zMatrix<T>::~zMatrix(){
    if(mData != nullptr){
        delete[] mData;
    }
    mData = nullptr;
}

template <class T>
inline int zMatrix<T>::linearIndex(int row, int col) const{
    if ((row < nRows) && (row >= 0) && (col < nCols) && (col >= 0)){
        return (row * nCols) + col;
    }else{
        std::cerr << "Matrix index out of bounds !" << std::endl;
        exit(EXIT_FAILURE);
    }
}

template <class T>
T zMatrix<T>::getElement(int row, int col) const{
    if(mData != nullptr){
        int idx = linearIndex(row, col);
        return mData[idx];
    }
    return -1;
}

template <class T>
bool zMatrix<T>::setElement(int row, int col, T data){
    if(mData != nullptr){
        int idx = linearIndex(row, col);
        mData[idx] = data;
        return true;
    }
    return false;
}

template <class T>
int zMatrix<T>::getnCols() const{
    return nCols;
}

template <class T>
int zMatrix<T>::getnRows() const{
    return nRows;
}

template <class T>
bool zMatrix<T>::isEqual(T val1, T val2){
    return fabs(val1 - val2) < 1e-15;
}

template <class T>
bool zMatrix<T>::compare(const zMatrix<T> &otherMatrix, double tolerance){
    if((nRows != otherMatrix.nRows) || (nCols != otherMatrix.nCols)){
        return false;
    }
    else if(mData == nullptr || otherMatrix.mData == nullptr){
        return false;
    }else{
        double cumSum = 0.0;
        for(int i = 0; i < nElements; i++){
            T val1 = mData[i];
            T val2 = otherMatrix.mData[i];
            cumSum += ((val1 - val2) * (val1 - val2));
        }
        double simularity = sqrt(cumSum / ((nCols * nRows) - 1));
        std::cout << simularity;
        if(simularity < tolerance){
            return true;
        }
        return false;
    }
}

template <class T>
zMatrix<T> zMatrix<T>::transpose() const{
    if(mData == nullptr){
        return *this;
    }
    zMatrix<T> result = zMatrix<T>(nCols, nRows);
    for(int i = 0; i < nRows; i++){
        for(int j = 0; j < nCols; j++){
            result.setElement(j, i, this->getElement(i, j));
        }
    }
    return result;
}

template <class T>
void zMatrix<T>::toIdentity(){
    if(!this->isSquare()){
        std::cerr << "Cannot set non square matrix to identity !" << std::endl;
        exit(EXIT_FAILURE);
    }
    else if(mData == nullptr){
        return;
    }
    for(int i = 0; i < nRows; i++){
        for(int j = 0; j < nCols; j++){
            if(i == j){
                this->setElement(i, j, static_cast<T>(1.0));
            }else{
                this->setElement(i, j, static_cast<T>(0.0));
            }
        }
    }
}

template <class T>
zMatrix<T> zMatrix<T>::find_sub_matrix(int row, int col){
    if(mData == nullptr){
        std::cerr << "Cannot find sub matrix from empty matrix !" << std::endl;
    }
    zMatrix<T> sub_matrix(nRows - 1, nCols - 1);
    int count = 0;
    for(int i = 0; i < nRows; i++){
        for(int j = 0; j < nCols; j++){
            if((i != row) && (j != col)){
                sub_matrix.mData[count] = this->getElement(i, j);
                count ++;
            }
        }
    }
    return sub_matrix;
}

template <class T>
T zMatrix<T>::determinant(){
    if(!this->isSquare()){
        std::cerr << "Cannot calculate determinant of non square matrix !" << std::endl;
        exit(EXIT_FAILURE);
    }
    else if(nElements == 1){
        return mData[0];
    }    

    T _determinant = static_cast<T>(0.0);
    if(nRows == 2){
        _determinant = (mData[0] * mData[3]) - (mData[1] * mData[2]);
    }else{
        T sign = static_cast<T>(1.0);
        for(int j = 0; j < nCols; j++){
            zMatrix<T> sub_matrix = this->find_sub_matrix(0, j);
            _determinant += sign * this->getElement(0, j)* sub_matrix.determinant();
            sign = sign * -1;
        }
    }
    return _determinant;
}
/*
zMatrix<T> zMatrix<T>::rowEchelon(){
    if(nCols < nRows){
        std::cerr << "Matrix must have at least as many columns as rows ! (rowEchelon)" << std::endl;
        exit(EXIT_FAILURE);
    }
    T* temp_data;
    temp_data = new T[nElements];
    if(temp_data == nullptr){
        std::cerr << "Memory allocation error !" << std::endl;
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < nElements; i++){
        temp_data[i] = mData[i];
    }

    int cRow, cCol;
    int maxCount = 100;
    int count = 0;
    bool completeFlag = false;
    while((!completeFlag) && (count < maxCount)){
        for(int diagIdx = 0; diagIdx < nRows; diagIdx++){
            cRow = diagIdx;
            cCol = diagIdx;
            int maxIdx = find_row_wmax_element(cCol, cRow);
            for(int rowIdx = cRow + 1; rowIdx < nRows; rowIdx++){
                int idx = linearIndex(rowIdx, cCol);
                if(!isEqual(mData[i], 0.0)){
                    int rowOneIdx = cCol;
                    T currentElement = mData[linearIndex(rowIdx, cCol)];
                }
            }
        }
    }
}
*/

template <class T>
bool zMatrix<T>::isSquare(){
    return nCols == nRows;
}

template <class T>
bool zMatrix<T>::isNonZero(){
    if(mData == nullptr){ 
        return false;
    }
    int nonZero = 0;
    for(int i = 0; i < nElements; i++){
        if(!isEqual(mData[i], 0.0)){
            nonZero++;
        }
    }
    return (nonZero != 0);
}

template <class T>
bool zMatrix<T>::isRowEchelon(){
    if(mData == nullptr){
        return false;
    }
    T cumSum = static_cast<T>(0.0);
    for(int i = 1; i < nRows; i++){
        for(int j = 0; j < i; j++){
            int idx = linearIndex(i, j);
            cumSum += mData[idx];
        }
    }
    return isEqual(cumSum, 0.0);
}

template <class T>
bool zMatrix<T>::isSymmetric(){
    if(mData == nullptr){
        return false;
    }else if(!this->isSquare()){
        return false;
    }
    zMatrix<T> temp = this->transpose();
    for(int i = 0; i < nRows; i++){
        for(int j = 0; j < nCols; j++){
            if(this->getElement(i, j) != temp.getElement(i, j)){
                return false;
            } 
        }
    }
    return true;
}

template <class T>
std::ostream& operator<<(std::ostream& outStream, const zMatrix<T> & m){
    if(m.mData == nullptr){
        return outStream;
    }
    for(int i = 0; i < m.nRows; i++){
        std::cout << "| ";
        for(int j = 0; j < m.nCols; j++){
            outStream << m.getElement(i, j) << " ";
        }
        outStream << "|\n";
    }
    return outStream;
}

template <class T>
bool zMatrix<T>::operator==(const zMatrix<T> &r){
    if((nRows != r.nRows) || (nCols != r.nCols)){
        return false;
    }else if(mData == nullptr && r.mData == nullptr){ // both empty
        return true;
    }else if(mData == nullptr || r.mData == nullptr){ //one of them is empty
        return false;
    }
    for(int i = 0; i < nElements; i++){
        if(!isEqual(mData[i], r.mData[i])){
            return false;
        }
    }
    return true;
}

template <class T>
zMatrix<T> zMatrix<T>::operator=(const zMatrix<T> &r){
    if(!(this == &r)){
        nRows = r.nRows;
        nCols = r.nCols;
        nElements = r.nElements;

        if(mData != nullptr){
            delete[] mData;
        }
        
        mData = new T[nElements];
        if(mData == nullptr){
            std::cerr << "Memory allocation error !" << std::endl;
            exit(EXIT_FAILURE);
        }

        for(int i = 0; i < nElements; i++){
            mData[i] = r.mData[i];
        }
    }
    return *this;
}

template <class T>
zMatrix<T> operator+(const zMatrix<T> &l, const zMatrix<T> &r){
    if((l.nRows != r.nRows) || (l.nCols != r.nCols)){
        std::cerr << "The matrices have to have the same dimensions(Matrix addition)" << std::endl;
        exit(EXIT_FAILURE);
    }
    int nRows = l.nRows;
    int nCols = l.nCols;
    int nElements = nCols * nRows;
    
    T * mResult = new T[nElements];
    if(mResult == nullptr){
        std::cerr << "Memory allocation error !" << std::endl;
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < nElements; i++){
        mResult[i] = l.mData[i] + r.mData[i];
    }

    zMatrix<T> result(nRows, nCols, mResult);
    delete[] mResult;
    return result;
}

template <class T>
zMatrix<T> operator+(const T &l, const zMatrix<T> &r){
    int nRows = r.nRows;
    int nCols = r.nCols;
    int nElements = nRows * nCols;

    T * mResult = new T[nElements];
    if(mResult == nullptr){
        std::cerr << "Memory allocation error !" << std::endl;
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < nElements; i++){
        mResult[i] = r.mData[i] + l;
    }
    zMatrix<T> result(nRows, nCols, mResult);
    delete[] mResult;
    return result;
}

template <class T>
zMatrix<T> operator+(const zMatrix<T> &r, const T &l){
    int nRows = r.nRows;
    int nCols = r.nCols;
    int nElements = nRows * nCols;

    T * mResult = new T[nElements];
    if(mResult == nullptr){
        std::cerr << "Memory allocation error !" << std::endl;
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < nElements; i++){
        mResult[i] = r.mData[i] + l;
    }
    zMatrix<T> result(nRows, nCols, mResult);
    delete[] mResult;
    return result;
}


template <class T>
zMatrix<T> operator-(const zMatrix<T> &l, const zMatrix<T> &r){
    if((l.nRows != r.nRows) || (l.nCols != r.nCols)){
        std::cerr << "The matrices have to have the same dimensions(Matrix substraction)" << std::endl;
        exit(EXIT_FAILURE);
    }
    int nRows = l.nRows;
    int nCols = l.nCols;
    int nElements = nCols * nRows;
    
    T * mResult = new T[nElements];
    if(mResult == nullptr){
        std::cerr << "Memory allocation error !" << std::endl;
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < nElements; i++){
        mResult[i] = l.mData[i] - r.mData[i];
    }

    zMatrix<T> result(nRows, nCols, mResult);
    delete[] mResult;
    return result;
}

template <class T>
zMatrix<T> operator-(const T &l, const zMatrix<T> &r){
    int nRows = r.nRows;
    int nCols = r.nCols;
    int nElements = nRows * nCols;

    T * mResult = new T[nElements];
    if(mResult == nullptr){
        std::cerr << "Memory allocation error !" << std::endl;
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < nElements; i++){
        mResult[i] = l - r.mData[i];
    }
    zMatrix<T> result(nRows, nCols, mResult);
    delete[] mResult;
    return result;
}

template <class T>
zMatrix<T> operator-(const zMatrix<T> &r, const T &l){
    int nRows = r.nRows;
    int nCols = r.nCols;
    int nElements = nRows * nCols;

    T * mResult = new T[nElements];
    if(mResult == nullptr){
        std::cerr << "Memory allocation error !" << std::endl;
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < nElements; i++){
        mResult[i] = r.mData[i] - l;
    }
    zMatrix<T> result(nRows, nCols, mResult);
    delete[] mResult;
    return result;
}

template<class T>
zMatrix<T> operator*(const zMatrix<T> &l, const zMatrix<T> &r){
    int r_nRows = r.nRows;
    int r_nCols = r.nCols;
    int l_nRows = l.nRows;
    int l_nCols = l.nCols;

    if(l_nCols != r_nRows){
        std::cerr << "Number of columns of left hand side matrix must be equal to number of rows of right hand side matrix!" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    int nRows = l_nRows;
    int nCols = r_nCols;
    int nElements = nRows * nCols;

    T *mResult = new T[nElements];
    if(mResult == nullptr){
        std::cerr << "Memory allocation error !" << std::endl;
        exit(EXIT_FAILURE);
    }

    for(int lRow = 0; lRow < l_nRows; lRow++){
        for(int rCol = 0; rCol < r_nCols; rCol++){
            T elementResult = static_cast<T>(0.0);
            for(int lCol = 0; lCol < l_nCols; lCol++){    
                int l_idx = (lRow * l_nCols) + lCol;
                int r_idx = (lCol * r_nCols) + rCol;
                elementResult += l.mData[l_idx] * r.mData[r_idx];
            }
            int result_idx = (lRow * r_nCols) + rCol;
            mResult[result_idx] = elementResult;
        }
    }
    zMatrix<T> result(nRows, nCols, mResult);
    delete[] mResult;
    return result;
}

template <class T>
zMatrix<T> operator*(const T &l, const zMatrix<T> &r){
    int nRows = r.nRows;
    int nCols = r.nCols;
    int nElements = nRows * nCols;
    
    T * mResult = new T[nElements];
    if(mResult == nullptr){
        std::cerr << "Memory  allocation error !" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    for(int i = 0; i < nElements; i++){
        mResult[i] = l * r.mData[i];
    }
    
    zMatrix<T> result(nRows, nCols, mResult);
    delete[] mResult;
    return result;
}

template <class T>
zMatrix<T> operator*(const zMatrix<T> &r, const T &l){
    int nRows = r.nRows;
    int nCols = r.nCols;
    int nElements = nRows * nCols;
    
    T * mResult = new T[nElements];
    if(mResult == nullptr){
        std::cerr << "Memory  allocation error !" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    for(int i = 0; i < nElements; i++){
        mResult[i] = l * r.mData[i];
    }
    
    zMatrix<T> result(nRows, nCols, mResult);
    delete[] mResult;
    return result;
}

/*
int main(){
    int a[16] = {1, 0, 2, -1, 3, 0, 0, 5, 2, 1, 4, -3, 1, 0, 5, 0};
    //int a[9] = {3, 3, 3, 3, 3, 3, 3, 3, 3};
    zMatrix<int> z(4,4, a);
    z.toIdentity();
    std::cout << z;
    return 1;
}
*/