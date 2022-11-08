#include "localfile.h"
#include "equivalence.h"

void getLocalFileName()
{
    system("ls ./input > inputName.txt");
    cout << "ls ./input > inputName.txt" << endl;
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
    cout << command << endl;
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
    while (getline(file, temp))
    {
        getSpecificFileName(temp);
        makeFile(temp);
        runOJProgram(temp);
    }
    file.close();
    return;
}

void runOJProgram(string name)
{
    fstream file;
    string temp = name + "FileName.txt";
    file.open(temp, ios::in);
    if (file.fail())
    {
        cout << temp << "open failed!" << endl;
        return;
    }
    while (getline(file, temp))
    {
        if (temp[temp.length() - 1] == 'p')
        {
            char command[200];
            string t = "g++ ./input/" + name + "/" + temp;
            strcpy(command, t.c_str());
            cout << command << endl;
            system(command);
            t = "./a.out < ./input/" + name + "/output.txt > " + "./input/" + name + "/" + temp + ".txt 2>&1";
            strcpy(command, t.c_str());
            cout << command << endl;
            system(command);
        }
    }
    system("rm -f a.out");
    cout << "rm -f a.out" << endl;
    return;
}