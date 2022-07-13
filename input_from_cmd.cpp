#include <iostream>
#include <queue>
#include <string>
#include <cstring>
#include <fstream>
#include "user.h"
using namespace std;

void print_usage()
{
    printf("Utilities\n");
}

queue<string> cmdseq;
void input2cmdseq()
{
    string tmp = "";
    char c;
    while(1)
    {
        cin >> tmp;
        cmdseq.push(tmp);
        c = getchar();
        if (c == '\n')
        {
            break;
        }
    }
}

void clear_queue(queue<string>& q)
{
    queue<string> empty;
    swap(empty, q);
}

string CharToStr(char * contentChar)
{
	string tempStr;
	for (int i=0;contentChar[i]!='\0';i++)
	{
		tempStr+=contentChar[i];
	}
	return tempStr;
}

void DelLineData(string fileName)
{
	ifstream in;
	in.open(fileName);
    int lineNum = 1;
	
	string strFileData = "";
	int line = 1;
	char lineData[128] = {0};
	while(in.getline(lineData, sizeof(lineData)))
	{
		if (line == lineNum)
		{
			// strFileData += "\n";
		}
		else
		{
			strFileData += CharToStr(lineData);
			strFileData += "\n";
		}
		line++;
	}
	in.close();
 
	//写入文件
	ofstream out;
	out.open(fileName);
	out.flush();
	out<<strFileData;
	out.close();
}


void ReadLineData(string fileName, int lineNum, string& command)
{
    char* data=NULL;
	ifstream in;
	in.open(fileName);
 
	int line = 1;
    if (lineNum == 1)
        in >> command;
    else 
    {
        while (in.getline(data, 32))
        {
            if (lineNum - 1== line)
            {
                break;
            }
            line ++ ;
        }
        in >> command;
    }
    free(data);
	in.close();
}