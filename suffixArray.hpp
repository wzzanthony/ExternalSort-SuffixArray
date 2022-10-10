#include <vector>
#include <dirent.h>
/*
Generate Suffix Array for one document
vector<int> doc: each document are represented as a sequence of intergers 
*/
void generateSuffixArray(vector<int>& doc, int docid, vector<vector<int>> &sas, int min_len = 1){
    for (int i = 0; i < doc.size() - min_len + 1; i++){
        sas[i].push_back(doc.size() - i + 2); // size 
        sas[i].insert(sas[i].end(), doc.begin() + i, doc.end());
        sas[i].push_back(docid); //docid
        sas[i].push_back(i); //its starting pos
    }
}

void printOutSA(vector<vector<int>> &sas){
    for (auto &sa: sas){
        for (int i = 0; i < sa.size(); i++){
            cout << sa[i] << ", ";
        }
        cout << endl;
    }
}
void writeSAToFile(ofstream &ofs, vector<vector<int>> &sas){
    for (auto &sa: sas){
        ofs.write((char*)&sa[0], sa.size() * sizeof(int));
    }
}

void loadSAFromFile(istream &ifs, vector<vector<int>> &sas){
    while (ifs.peek() != EOF){
        int size = 0;
        ifs.read((char*)&size, sizeof(int));
        vector<int> temp_vec(size+1);
        temp_vec[0] = size;
        ifs.read((char*)&temp_vec[1],  size * sizeof(int));
        sas.push_back(temp_vec);
    }
}
void getFiles(string path, vector<string> &files)
{
  DIR *dr;
  struct dirent *en;
  string file_path;
  if (path.back() != '/') path += "/";
  dr = opendir(path.c_str()); //open all directory
  if (dr)
  {
    while ((en = readdir(dr)) != NULL)
    {
      //ignore hidden files and folders
      if (en->d_name[0] != '.')
      {
        file_path = path + en->d_name;
        files.push_back(file_path);
      }
    }
    closedir(dr); //close all directory
  }
}
void GenerateSAWriteToFile(const string &input_file, ofstream &ofs, int &id, int min_len = 10){
    ifstream ifs(input_file, ios::binary | ios::in);
    while (ifs.peek() != EOF){
        int size = 0;
        ifs.read((char*)&size, sizeof(int));
        vector<int> doc(size);
        ifs.read((char*)&doc[0], size * sizeof(int));
        int sa_num = doc.size() - min_len + 1;
        vector<vector<int>> sas(sa_num);
        generateSuffixArray(doc, id, sas, min_len);
        for (auto &sa: sas){
            ofs.write((char*)&sa[0], sa.size() * sizeof(int));
        }
        id++;
    }
    ifs.close();
}