#include "basic.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

// 默认值
int DRAB = 3;
int DFOX = 4;
int DLION = 8;
int TMRAB = 8;
int TMFOX = 8;
int TMLION = 3;
int CYCLES = 5;

void writeDefaultConfig(const char *filename)
{
    ofstream file(filename);
    if (!file)
    {
        cerr << "打开文件失败：" << filename << endl;
        return;
    }
    file << "DRAB=" << DRAB << endl;
    file << "DFOX=" << DFOX << endl;
    file << "DLION=" << DLION << endl;
    file << "TMRAB=" << TMRAB << endl;
    file << "TMFOX=" << TMFOX << endl;
    file << "TMLION=" << TMLION << endl;
    file << "CYCLES=" << CYCLES << endl;
    file.close();
}

void readConfig(const char *filename)
{
    ifstream file(filename);
    if (!file)
    {
        cerr << "找不到配置文件，现创建一个默认配置文件：" << filename << endl;
        writeDefaultConfig(filename);
        file.open(filename);
        if (!file)
        {
            cerr << "打开文件失败：" << filename << endl;
            return;
        }
    }

    string line;
    while (getline(file, line))
    {
        istringstream iss(line);
        string key;
        int value;
        if (getline(iss, key, '=') && iss >> value)
        {
            if (key == "DRAB")
                DRAB = value;
            else if (key == "DFOX")
                DFOX = value;
            else if (key == "DLION")
                DLION = value;
            else if (key == "TMRAB")
                TMRAB = value;
            else if (key == "TMFOX")
                TMFOX = value;
            else if (key == "TMLION")
                TMLION = value;
            else if (key == "CYCLES")
                CYCLES = value;
        }
    }
    file.close();
}

void modifyConfig(const char *filename, const char *key, int value)
{
    ifstream file(filename);
    if (!file)
    {
        cerr << "打开文件失败：" << filename << endl;
        return;
    }

    stringstream buffer;
    buffer << file.rdbuf();
    string content = buffer.str();
    file.close();

    string line;
    string newContent;
    istringstream iss(content);
    bool keyFound = false;

    while (getline(iss, line))
    {
        if (line.find(key) != string::npos && line.find('=') != string::npos)
        {
            istringstream lineStream(line);
            string currentKey;
            if (getline(lineStream, currentKey, '=') && currentKey == key)
            {
                newContent += key + string("=") + to_string(value) + "\n";
                keyFound = true;
            }
            else
            {
                newContent += line + "\n";
            }
        }
        else
        {
            newContent += line + "\n";
        }
    }

    if (!keyFound)
    {
        newContent += key + string("=") + to_string(value) + "\n";
    }

    ofstream outFile(filename);
    if (!outFile)
    {
        cerr << "打开文件失败：" << filename << endl;
        return;
    }
    outFile << newContent;
    outFile.close();
}

void ShowConfig()
{
    cout << "当前配置如下：" << endl;
    ifstream file("config.txt");
    int i = 1;
    while (file)
    {
        string line;
        getline(file, line);
        if (!line.empty())
        {
            cout << i << " - " << line << endl;
            ++i;
        }
    }
    file.close();
}