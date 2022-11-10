#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include <string.h>
#include <map>
#include <vector>

using namespace std;

void analysisOJProgram(vector<string> vec, map<string, int> &mapfile, string filename); //分析OJ运行结果
void inputcsv(map<string, int> &mapfile, string filename, bool check);                  //输入结果至csv文件
void deleteFile(string temp, vector<string> vec, bool check);