#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "zMatrix.hpp"
#include "zMatrix.cpp"

std::vector<float> stringParser(const std::string &str){
    std::stringstream ss(str);
    std::vector<float> result;
    while(ss.good()){
        std::string sub_str;
        std::getline(ss, sub_str, ',');
        result.push_back(std::stof(sub_str));
    }
    return result;
}
std::vector<std::string> getFileContent(const std::string &fileName){
    std::vector<std::string> vecOfStrs;
    std::ifstream in(fileName.c_str());
    std::string str;
    while (std::getline(in, str))
    {
        if(str.size() > 0)
            vecOfStrs.push_back(str);
    }
    in.close();
    return vecOfStrs;
}

std::vector<std::vector<float>> getMatrix(const std::string &filename){
    std::vector<std::vector<float>> resultMatrix;
    std::vector<std::string> lines = getFileContent(filename);
    for(int i = 0; i < lines.size(); i++){
        std::vector<float> row = stringParser(lines[i]);
        resultMatrix.push_back(row);
    }
    return resultMatrix;
}

int main(){
    std::string data_path = "/home/serkan/Desktop/zMatrix/pythonTest/testData/";
    for(int i = 0; i < 100; i++){
        std::string abs_path = data_path + std::to_string(i) + ".txt";
        std::string mul_path = data_path + std::to_string(i) + "mul.txt";

        std::vector<std::vector<float>> vec = getMatrix(abs_path);
        std::vector<std::vector<float>> mul_vec = getMatrix(mul_path);
    
        zMatrix<float> z(vec);
        zMatrix<float> multiplied(mul_vec);
        std::cout << (z * z).compare(mul_vec, 0.01) << std::endl;
    }
}