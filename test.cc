#include <iostream>
#include "externalSort.hpp"
#include "suffixArray.hpp"
#include "omp.h"


int main(int argc, char **argv){
    /*
    int min_len = 1;
    vector<int> doc{1,13,54,23,33,56,34,67};
    int sa_num = doc.size() - min_len + 1;
    vector<vector<int>> sas(sa_num);
    generateSuffixArray(doc, 0, sas, min_len);
    ofstream ofs("ret.bin", ios::out | ios::binary);
    printOutSA(sas);
    writeSAToFile(ofs, sas);
    */

    
    vector<vector<int>> sas;
    ifstream ifs("./sort.bin", ios::binary | ios::in);
    loadSAFromFile(ifs, sas);
    printOutSA(sas);
    return 0;
    
}