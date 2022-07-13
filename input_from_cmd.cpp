#include <iostream>
#include <queue>
#include <string>
#include <cstring>
#include <fstream>
#include "user.h"
using namespace std;

void print_usage()
{
	string str = 
"### 系统使用示例\n"
"\n"
"### 打开系统使用说明\n"
"$./test -h\n"
"\n"
"### 调试系统\n"
"$./test -d\n"
"\n"
"### 运行系统\n"
"$./test run\n"
"\n"
"### 登录或注册用户\n"
"\n"
"$ 1. [新用户名] [新用户密码] [再次输入新用户密码]（注册新账号）\n"
"\n"
"$ 2. [用户名] [用户密码]（登录账号）\n"
"\n"
"$ 3. （退出系统）\n"
"\n"
"### 管理用户\n"
"\n"
"1. **普通用户**\n"
"\n"
"   $ 1. [用户密码] （打印账号信息）\n"
"\n"
"   $ 2. [用户密码] [新用户名] [新用户密码]（修改账号信息）\n"
"\n"
"   $ 3. [用户密码] （删除账号）\n"
"\n"
"   $ 4.（进行任务管理）\n"
"\n"
"   $ 5.（退出登录）\n"
"\n"
"2. **超级用户**\n"
"\n"
"   $ 1. [用户密码] （打印账号信息）\n"
"\n"
"   $ 2. （进行任务管理）\n"
"\n"
"   $ 3.  （打印所有账号）\n"
"\n"
"   $ 4. [指定用户名]（删除指定账号）\n"
"\n"
"   $ 5.（退出登录）\n"
"\n"
"### 管理任务\n"
"\n"
"$ addtask [任务名称] [任务类型] [任务优先级] [任务提醒时间] [任务时间]\n"
"\n"
"   [任务名称]：任意长度字符串，以回车键结束\n"
" \n"
"   [任务类型]：Study | Entertainment | Living\n"
"       不区分大小写\n"
"       不能为空，输入其他字符串默认为Living\n"
"             \n"
"   [任务优先级]：High | Medium | Low \n"
"       不区分大小写\n"
"       不能为空，输入其他字符串默认为Low \n"
"\n"
"   [任务提醒时间]：格式为dd/mm[/yyyy]_[hh][:mm][:ss], [日期/月份/年份_小时:分钟:秒]\n"
"       例: 14/07/2022  表示 2022年 7月 14日\n"
"       14/07       表示 2022年 7月 14日\n"
"       14/08_12:00 表示 2022年 8月 14日 12时 00分\n"
"       14/08_12    表示 2022年 8月 14日 12时 00分\n"
"       其中 [日期/月份] 必填\n"
"       [年份]      缺省为 2022年\n"
"       [小时:分钟]  缺省为当天 08时 00分\n"
"       [分钟]      缺省设定小时的 00分\n"
"       [秒]        缺省为 00秒\n"
"\n"
"   [任务时间]：时间格式同 [任务提醒时间]\n"
"\n"
"\n"
"$ showtask [任务时间范围] [任务排列方式]\n"
"\n"
"   [任务时间范围]：0 | 1 | 2\n"
"                 0：全部；1：当月；2：当天\n"
"   [任务排列方式]：0 | 1 | 2\n"
"                 0：时间；1：优先级；2：类型\n"
" \n"
"$ deltask [任务id] \n"
" \n"
"  任务id会在“$showtask”功能中给出\n"
"\n"
"$ donetask [任务id]\n"
"\n"
"  任务id会在“$showtask”功能中给出\n"
"\n"
"$ exit \n"
"\n";
   cout<<str;
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
