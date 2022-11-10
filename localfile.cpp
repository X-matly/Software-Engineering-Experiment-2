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
    system("mkdir output");
    fstream file;
    file.open("./inputName.txt", ios::in);
    if (file.fail())
    {
        cout << "inputName.txt open fail!" << endl;
        return;
    }
    string temp;
    bool vis = false;
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
                string o = vec[i] + ".cpp," + vec[j] + ".cpp";
                mapfile[o] = 1;
            }
        }
        bool check = false;
        for (int times = 0; times < TIMES; times++)
        {
            makeFile(temp);                        //制作输入文件
            runOJProgram(temp, vec, check);        //运行OJ文件
            analysisOJProgram(vec, mapfile, temp); //分析输出文件
            check = true;
        }
        inputcsv(mapfile, temp, vis); //输入结果至csv文件
        deleteFile(temp, vec, vis);   //删除运行中产生的文件
        vis = true;
    }
    file.close();
    return;
}

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

void runOJProgram(string name, vector<string> &vec, bool check) //运行文件并产生结果
{
    char command[200];
    for (int i = 0; i < vec.size(); i++)
    {
        if (!check)
        {
            string t = "g++ -o ./input/" + name + "/" + vec[i] + " ./input/" + name + "/" + vec[i] + ".cpp";
            strcpy(command, t.c_str());
            // cout << command << endl;
            system(command);
        }
        string t = "./input/" + name + "/" + vec[i] + " < ./input/" + name + "/output.txt > " + "./input/" + name + "/" + vec[i] + ".txt 2>&1";
        strcpy(command, t.c_str());
        // cout << command << endl;
        system(command);
    }

    // cout << "rm -f a.out" << endl;
    return;
}