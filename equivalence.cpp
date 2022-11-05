#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <sstream>
using namespace std;

string dir = "abcdefghijklmnopqrstuvwxzyABCDEFGHIJKLMNOPQRSTUVWXYZ";

int main()
{
    srand((unsigned)time(NULL));
    fstream file;
    fstream outfile;
    file.open("./input/4A/stdin_format.txt", ios::in);
    outfile.open("./input/4A/output.txt", ios::out);
    if (!file.is_open())
    {
        cout << "File open failed!" << endl;
        return -1;
    }
    if (!outfile.is_open())
    {
        cout << "OutFile open failed!" << endl;
        return -1;
    }
    string buf;
    while (getline(file, buf))
    {
        for (int i = 0; i < buf.length();)
        {
            if (buf[i] == 'i') // int type
            {
                int min = 0;
                int max = 0;
                i += 4;
                string temp;
                while (buf[i] != ',')
                {
                    temp += buf[i];
                    i++;
                }
                stringstream ss;
                ss << temp;
                ss >> min;
                ss.clear();
                temp.clear();
                i++;
                while (buf[i] != ')')
                {
                    temp += buf[i];
                    i++;
                }
                ss << temp;
                ss >> max;
                i += 2;
                int ans = (rand() % (max - min + 1) + min);
                outfile << ans << " ";
            }
            else if (buf[i] == 'c') // char type
            {
                i += 5;
                int ans = (rand() % 52);
                outfile << dir[ans] << " ";
            }
            else // string type
            {
                int min = 0;
                int max = 0;
                i += 7;
                string temp;
                while (buf[i] != ',')
                {
                    temp += buf[i];
                    i++;
                }
                stringstream ss;
                ss << temp;
                ss >> min;
                ss.clear();
                temp.clear();
                i++;
                while (buf[i] != ')')
                {
                    temp += buf[i];
                    i++;
                }
                ss << temp;
                ss >> max;
                i += 2;
                int ans = (rand() % (max - min + 1) + min);
                while (ans--)
                {
                    int a = (rand() % 52);
                    outfile << dir[a];
                }
                outfile << " ";
            }
        }
    }

    return 0;
}