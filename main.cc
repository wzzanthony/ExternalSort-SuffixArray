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
    vector<string> files;
    string dir_path = "/common/users/zw393/openwebtext_64K_vocal/";
    getFiles(dir_path, files);
    string output_file = "/common/users/zw393/all_sas.bin";
    ofstream ofs(output_file, ios::out | ios::binary);
    int id = 0;
    int min_len = 10;
    for (auto &f: files){
        GenerateSAWriteToFile(f, ofs, id, 10);
    }
    return 0;
    /*
    int num_ways = 2; // number of documents
    int run_size = 4; // maximum items in each document 
    SuffixArray max_sa(INT_MAX);
    ExternalSort es(max_sa);
    char* ori_file = "ret.bin";
    char* output_file = "sort.bin";
    es.externalSort(ori_file, output_file, num_ways, run_size);
    return 0;
    */
    /*
    vector<vector<int>> sas;
    ifstream ifs("./temp/0", ios::binary | ios::in);
    loadSAFromFile(ifs, sas);
    printOutSA(sas);
    */
}