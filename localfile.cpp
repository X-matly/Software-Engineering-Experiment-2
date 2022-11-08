#include "localfile.h"
#include "equivalence.h"

void getLocalFileName()
{
    system("ls ./input > inputName.txt");
    // cout << "ls ./input > inputName.txt" << endl;
    return;
}

void getSpecificFileName(string filename)
{
    char command[200] = {0};
    string temp = "ls ./input/";
    strcpy(command, temp.c_str());
    strcat(command, filename.c_str());
    temp = " > ";
    strcat(command, temp.c_str());
    strcat(command, filename.c_str());
    temp = "FileName.txt";
    strcat(command, temp.c_str());
    // cout << command << endl;
    system(command);
    return;
}

void dealLocalFileName()
{

    fstream file;
    file.open("./inputName.txt", ios::in);
    if (file.fail())
    {
        cout << "inputName.txt open fail!" << endl;
        return;
    }
    string temp;
    while (getline(file, temp)) //获取dir文件夹名称
    {
        getSpecificFileName(temp); //获取dir文件夹内容
        map<string, int> mapfile;
        vector<string> vec;
        string t = temp + "FileName.txt";
        fstream f;
        string m;
        f.open(t, ios::in);
        while (getline(f, m))
        {
            if (m[m.length() - 1] == 'p')
            {
                string w = m.substr(0, m.length() - 4);
                vec.push_back(w);
            }
        }
        f.close();
        for (int i = 0; i < vec.size(); i++)
        {
            for (int j = i + 1; j < vec.size(); j++)
            {
                string o = vec[i] + ',' + vec[j];
                mapfile[o] = 0;
            }
        }
        /*for (auto &it : mapfile)
        {
            cout << it.first << " " << it.second << endl;
        }*/
        bool check = false;
        for (int times = 0; times < TIMES; times++)
        {
            makeFile(temp);
            runOJProgram(temp, vec, check);
            check = true;
        }
    }
    file.close();
    return;
}

void runOJProgram(string name, vector<string> &vec, bool check)
{
    char command[200];
    for (int i = 0; i < vec.size(); i++)
    {
        if (!check)
        {
            string t = "g++ -o ./input/" + name + "/" + vec[i] + " ./input/" + name + "/" + vec[i] + ".cpp";
            strcpy(command, t.c_str());
            cout << command << endl;
            system(command);
        }
        string t = "./input/" + name + "/" + vec[i] + " < ./input/" + name + "/output.txt > " + "./input/" + name + "/" + vec[i] + ".txt 2>&1";
        strcpy(command, t.c_str());
        cout << command << endl;
        system(command);
    }

    // cout << "rm -f a.out" << endl;
    return;
}