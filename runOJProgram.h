#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include <string.h>
#include <map>
#include <vector>
#define TIMES 10

using namespace std;

void getLocalFileName(); //获取本地文件文件名
void getSpecificFileName(string filename);
void dealLocalFileName();                                        //获取各个文件夹内部OJ文件名
void runOJProgram(string temp, vector<string> &vec, bool check); //运行OJ程序