#include "judgeOJProgram.h"

void deleteFile(string temp, vector<string> vec, bool check)
{
    if (!check)
    {
        system("rm -f inputName.txt");
    }
    string name = "rm -f " + temp + "FileName.txt";
    system(name.c_str());
    string w = "rm -f ./input/" + temp + "/output.txt";
    system(w.c_str());
    for (int i = 0; i < vec.size(); i++)
    {
        string q = "rm -f ./input/" + temp + "/" + vec[i];
        system(q.c_str());
        q += ".txt";
        system(q.c_str());
    }
    system("rm -f main judgeOJProgram");
    return;
}

void inputcsv(map<string, int> &mapfile, string filename, bool check) //输入结果至csv文件
{
    fstream file1;
    fstream file2;
    file1.open("./output/equal.csv", ios::out | ios::app);
    file2.open("./output/inequal.csv", ios::out | ios::app);
    if (file1.fail())
    {
        cout << "equal.csv open fail!" << endl;
        exit(0);
    }
    if (file2.fail())
    {
        cout << "inequal.csv open fail!" << endl;
        exit(0);
    }
    if (!check)
    {
        file1 << "file1,file2\n";
        file2 << "file1,file2\n";
    }
    for (auto &it : mapfile)
    {
        if (it.second)
        {
            file1 << it.first << '\n';
        }
        else
        {
            file2 << it.first << '\n';
        }
    }
    file1.close();
    file2.close();
    return;
}

void analysisOJProgram(vector<string> vec, map<string, int> &mapfile, string filename)
{
    for (int i = 0; i < vec.size(); i++)
    {
        for (int j = i + 1; j < vec.size(); j++)
        {
            string temp = "diff ./input/" + filename + "/" + vec[i] + ".txt ./input/" + filename + "/" + vec[j] + ".txt > answer.txt";
            // cout << temp << endl;
            system(temp.c_str());
            fstream file;
            file.open("answer.txt", ios::in);
            if (file.fail())
            {
                cout << "answer.txt open fail!" << endl;
                exit(0);
            }
            char a;
            file >> a;
            string name = vec[i] + ".cpp," + vec[j] + ".cpp";
            if (!file.eof())
            {
                mapfile[name] = 0;
            }
            file.close();
            system("rm -f answer.txt");
        }
    }
}