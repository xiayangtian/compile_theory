// compiletest2.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
using namespace std;

string test = {};//一个存放整个字符串的string
int line = 1;//查错行数
int location = 0;//当前读取的位置记录

//二元式结构
struct dual {
	int num;//种别
	string value;//单词符号
	
};

//关键字表
struct dual mainword[11] = { { 1,"begin" } ,{ 2, "end" },{ 3,"integer" } ,{ 4,"if" } ,{ 5,"then" } ,{ 6,"else" } ,{ 7,"function" } ,{ 8,"read" } ,{ 9,"write" } ,{24,"EOLN"},{25,"EOF"} };

//标识符表
struct dual signalword[100];
int location_s = 0;

//常量表
struct dual constantword[100];
int location_c = 0;

//变量名
struct variable_name {
	string vname;
	string vproc;
	bool vkind;
	char vtype[9] = "interger";
	int vlev;
	int vadr;
};
//变量名表
struct variable_name variabel_name_table[100];
int location_v = 0;
int vlevel = 0;

//过程名
struct progress_name {
	string pname;
	char ptype[9] = "interger";
	int plev;
	int fadr;
	int ladr;
};
//过程名表
struct progress_name progress_name_table[100];
int location_p = 0;


//二元式表
struct dual dualtable[200];
int location_d = 0;
int maxlocation_d = 0;

//函数声明
void error(int num);
void a();
void b();
void c();
void d();
void e();
void g();
void h(string str);
void l();
void h2(string str);
bool i(string str);
bool j(char cha);
bool k(char cha);
void m();
void n();
void s();
void t();
void u();
bool v(string str);
void w();
bool x(string str);
void y();
void z();
struct dual getchar2();
//一次读取一行的方法
void getchar1() {
	ifstream fin("test.txt");
	string s;
	
	while (getline(fin, s)) {
		test.append(s);
		test.append(" EOLN ");
	}
	test.append(" EOF");
	
	
}


//读取下一个字符
char getchar3() {
	return(test[location++]);
}

//读取一个非空字符
char getnbc() {
	while (test[location] == ' ')
		location++;
	return(getchar3());
}

//在token后面添加cha里面的当前字符
string concat(char cha,string token) {
	token += cha;
	return token;
}

//检测是否为字母
bool letter(char cha) {
	
	if (((cha >= 'A') && (cha <= 'Z')) || ((cha >= 'a') && (cha <= 'z')))
		return true;
	else
		return false;
}

//检测是否为数字
bool digit(char cha) {
	if ((cha >= '0') && (cha <= '9'))
		return true;
	else
		return false;
}

//回退函数
void retract() {
	location--;
}

//查关键字表
int reserve(string token) {
	for (int i1 = 0; i1 <= 10; i1++) {
		if (!(token.compare(mainword[i1].value)))
			return mainword[i1].num;
	}
	return 0;
}

//查标识符表
int buildlist(string token) {
	for (int i1 = 0; i1 <= 99; i1++) {
		if (!(token.compare(signalword[i1].value)))
			return 1;
	}
	if (token.length() > 16) {
		error(3);
	}
	else {
		signalword[location_s].num = 10;
		signalword[location_s].value = token;
		location_s++;
	}
	return 0;
	
}

//查常量表
int dtb(string token) {
	for (int i1 = 0; i1 <= 99; i1++) {
		if (!(token.compare(constantword[i1].value))) {
			
			return 1;
		}
	}
	
	constantword[location_c].num = 11;
	constantword[location_c].value = token;
	location_c++;
	return 0;
}

//出错处理程序
void error(int num) {
	string err = {};
	err += "***LINE:";
	char lin[10];
	_itoa_s(line, lin, 10);
	int n = 0;
	while (lin[n] != '\0') {
		
		err += lin[n];
		n++;
	}
	err += "  ";
	switch (num)
	{
	case(1): {
		ofstream errout("test.err", ios::app);
		err += "The follow of  ':' are not '=' !!!";
		errout << err << '\n';
		errout << flush;
		errout.close();
		break;
	}
	case(2): {
		ofstream errout("test.err", ios::app);
		err += "Unknown signal!!!";
		errout << err << '\n';
		errout << flush;
		errout.close();
		break;
	}
	case(3): {
		ofstream errout("test.err", ios::app);
		err += "The name of your variable is too long!!!";
		errout << err << '\n';
		errout << flush;
		errout.close();
		break;
	}
	case(4): {
		ofstream errout("test.err", ios::app);
		err += "Missing symbol!!!";
		errout << err << '\n';
		errout << flush;
		errout.close();
		break;
	}
	case(5): {
		ofstream errout("test.err", ios::app);
		err += "Bad match for symbol!!!";
		errout << err << '\n';
		errout << flush;
		errout.close();
		break;
	}
	case(6): {
		ofstream errout("test.err", ios::app);
		err += "The symbol is not define or too much define!!!";
		errout << err << '\n';
		errout << flush;
		errout.close();
		break;
	}
	default: {
		ofstream errout("test.err");
		err.erase(0);
		errout << err;
		errout << flush;
		errout.close();
		break;
	}
	}
	
	

	
}

//分析出一个词语
struct dual oneword() {
	char cha;
	string token;
	if (location <= test.length()) {
		//读一个非空字符
		cha = getnbc();
		//第一个字符为字母
		if (letter(cha)) {
			//检测后面的是不是字母
			while (letter(cha) || digit(cha)) {
				token = concat(cha, token);
				cha = getchar3();
			}
			retract();
			//看这个字符串是不是关键字
			int resv = reserve(token);
			if (!resv) {
				//写入标识符表中
				buildlist(token);
				return  { 10, token };
			}
			else
				return { resv,token };
		}
		//第一个字符为数字
		else if (digit(cha)) {
			while (digit(cha)) {
				token = concat(cha, token);
				cha = getchar3();
			}
			retract();
			dtb(token);
			return{ 11,token };
		}
		//第一个字符为符号，按照符号分类将其编号
		else {
			switch (cha)
			{
			case('='):
				return{ 12,"=" };
			case('-'):
				return{ 18,"-" };
			case('*'):
				return{ 19,"*" };
			case('('):
				return{ 21,"(" };
			case(')'):
				return{ 22,")" };
			case(';'):
				return{ 23,";" };
			case('<'):
			{
				cha = getchar3();
				if (cha == '=')
					return { 14,"<=" };
				else if (cha == '>')
					return { 13,"<>" };
				else {
					retract();
					return{ 15,"<" };

				}
			}
			case('>'): {
				cha = getchar3();
				if (cha == '=')
					return{ 16,">=" };
				else {
					retract();
					return{ 17, ">" };
				}
			}
			case(':'): {
				cha = getchar3();
				if (cha == '=')
					return{ 20,":=" };
				else
					//：后面不是=报错
					error(1);
				return{ 0,"0" };
					
			}
			default:
				//检测不出，报错
				error(2);
				return{ 0,"0" };
				
			}

		}
	}

}

//分析所有词语并返回文本，完成出错处理，完成词法分析
void lexanalyze() {
	error(0);
	ofstream fout("test.dyd");
	dual temp;
	char str[3];
	while (location < test.length()) {
		temp = oneword();
		if (temp.num == 24) {
			line++;
		}
		string out = {};
		int n = 16;
		if (temp.value.length() > 16) {
			temp.value.erase(16);
		}
		//按照标准格式输出，添加空格
		while ((n - temp.value.length()) > 0) {
			out += ' ';
			n--;
		}
		out += temp.value;
		out += ' ';

		_itoa_s(temp.num, str, 10);
		if (str[1] == '\0') {
			str[1] = ' ';
		}
		out += str[0];
		out += str[1];
		if (temp.num != 25)
			fout << out << '\n';
	
		else
			fout << out;
	}
	fout << flush;
	fout.close();
	

}

//读取词法分析的结果并将其存入二元式表中
void extract() {
	ifstream fin("test.dyd");
	string s1;
	line = 1;
	dual temp;
	while (getline(fin, s1)) {
		int i1 = 0;
		string s2 = {};
		while (i1 < 16) {
			if (s1[i1] == ' ')
				i1++;
			else {
				s2 += s1[i1];
				i1++;
			}
		}
		temp.value = s2;
		char str[3];
		str[0] = s1[17];
		str[1] = s1[18];
		str[2] = '\0';
		temp.num = atoi(str);
		dualtable[location_d] = temp;
		location_d++;
	}
	maxlocation_d = location_d - 1;
	location_d = 0;
}

//超前搜索的回退
void retract2() {
	location_d--;
	dual temp;
	temp = dualtable[location_d];
	if (temp.num == 24) {
		line --;
	}
	if (temp.num == 2) {
		vlevel ++;
	}
	if (temp.num == 1) {
		vlevel --;
	}
	
}

//读取下一个单词
struct dual getchar2() {
	dual temp;
	if (location_d <= maxlocation_d) {
		temp = dualtable[location_d];
		location_d++;
		if (temp.num == 1) {
			vlevel++;
		}
		if (temp.num == 2) {
			vlevel--;
		}
		if (temp.num == 24) {
			temp = getchar2();
			line++;
		}
		return temp;
	}
	else
		return{ 0,"0" };
}


//程序
void a() {
	b();
	cout << "Finished!!!" << endl;
}

//分程序
void b() {
	//检测是否为begin
	dual temp = getchar2();
	if (temp.num != 1) {
		error(5);
	}
	c();
	//检测分号
	temp = getchar2();
	if (temp.num != 23) {
		error(4);
	}
	d();
	//检测end
	temp = getchar2();
	if (temp.num != 2) {
		error(5);
	}
}

//说明语句表
void c() {
	e();
	dual temp = getchar2();
	while (temp.num == 23) {
		e();
		temp = getchar2();
	}
	//因为说明语句表后面一定有分号，所以会有超前搜索的回退
	retract2();
	retract2();
	retract2();
}

//说明语句
void e() {
	dual temp = getchar2();
	//检测interger
	if (temp.num == 3) {
		temp = getchar2();
		//检测function
		if (temp.num != 7) {
			h(temp.value);
		}
		else {
			g();
		}
	}
	else {
		//出错处理
		if (temp.num == 10) {
			error(4);
			temp = getchar2();
			temp = getchar2();
		}
		retract2();
	}
	
	
}

//函数说明
void g() {
	dual temp = getchar2();
	//对于函数表示符，分别存变量名表和过程名表
	if (i(temp.value)) {
		h(temp.value);
		progress_name_table[location_p].pname = temp.value;
		progress_name_table[location_p].plev = vlevel;
		progress_name_table[location_p].fadr = -1;
		progress_name_table[location_p].ladr = -1;
		location_p++;
	}
	//检测（
	temp = getchar2();
	if (temp.num != 21) {
		error(4);
	}
	m();
	//检测）
	temp = getchar2();
	if (temp.num != 22) {
		error(4);
	}
	//检测；
	temp = getchar2();
	if (temp.num != 23) {
		error(4);
	}
	l();
}

//参数
void m() {
	dual temp = getchar2();
	h(temp.value);
}
//函数体
void l() {
	dual temp = getchar2();
	if (temp.num != 1) {
		error(5);
	}
	c();
	temp = getchar2();
	if (temp.num != 23) {
		error(4);
	}
	d();
	temp = getchar2();
	if (temp.num != 2) {
		error(5);
	}
}
//变量，存变量名表
void h(string str) {
	if (i(str)) {
		for (int i1 = 0; i1 < location_v; i1++) {
			if (!(variabel_name_table[i1].vname.compare(str))) {
				if (variabel_name_table[i1].vkind==false)
					error(6);
			}
		}
		variabel_name_table[location_v].vname = str;
		variabel_name_table[location_v].vlev = vlevel;
		variabel_name_table[location_v].vadr = location_v;
		if (vlevel == 1) {
			variabel_name_table[location_v].vproc = "main";//所属过程为主函数
		}
		else {
			variabel_name_table[location_v].vproc = progress_name_table[vlevel-2].pname;
		}
		dual temp = getchar2();
		if (temp.num == 22) {
			variabel_name_table[location_v].vkind = 1;
		}
		else {
			variabel_name_table[location_v].vkind = 0;
		}
		retract2();
		location_v++;
	}
	else {
		error(6);
	}
}
//标识符
bool i(string str) {
	if (j(str[0])) {
		for (int i1 = 0; i1 < str.length(); i1++) {
			if (!(j(str[i1]) || k(str[i1]))) {
				return false;
			}
		}

		return true;
	}
	return false;
}
//检测是否为字母
bool j(char cha) {
	return(letter(cha));
}
//执行语句表
void d() {
	n();
	dual temp = getchar2();
	while (temp.num == 23) {
		n();
		temp = getchar2();
	}
	retract2();
}
//使用时判定变量是否定义过
void h2(string str) {
	bool bol = 0;
	if (i(str)) {
		for (int i1 = 0; i1 < location_v; i1++) {
			if (!(variabel_name_table[i1].vname.compare(str))) {
				bol = 1;
			}
		}
		if (!bol)
			error(6);
	}
	else
		error(6);
}
//执行语句
void n() {
	dual temp = getchar2();
	switch (temp.num)
	{
	//read情况
	case(8): {
		temp = getchar2();
		if (temp.num != 21) {
			error(4);
			retract2();
		}
		temp = getchar2();
		h(temp.value);
		temp = getchar2();
		if (temp.num != 22) {
			error(4);
			retract2();
		}
		break;
	}
	//write情况
	case(9): {
		temp = getchar2();
		if (temp.num != 21) {
			error(5);
			retract2();
		}
		temp = getchar2();
		h2(temp.value);
		temp = getchar2();
		if (temp.num != 22) {
			error(5);
			retract2();
		}
		break;
	}
	//赋值情况
	case(10): {


		h2(temp.value);
		temp = getchar2();
		if (temp.num != 20) {
			error(4);
			retract2();
		}
		s();
		break;
	}
	//条件语句情况
	case(4): {
		y();
		temp = getchar2();
		if (temp.num != 5) {
			error(4);
		}
		n();
		temp = getchar2();
		if (temp.num != 6) {
			error(4);
		}
		n();
		break;
	}
	default:
		error(5);
		break;
	}
}
//算术表达式
void s() {
	t();
	dual temp = getchar2();
	while (temp.num == 18) {
		t();
		temp = getchar2();
	}
	retract2();
}
//项
void t() {
	u();
	dual temp = getchar2();
	while (temp.num == 19) {
		u();
		temp = getchar2();
	}
	retract2();
}
//因子
void u() {
	dual temp = getchar2();
	if (temp.num == 11) {
		if (!v(temp.value)) {
			error(5);
		}
	}
	else {
			temp = getchar2();
			if (temp.num == 21) {
				retract2();
				w();
			}
			else {
				retract2();
				retract2();
				temp = getchar2();
				h2(temp.value);
			}
	}
}
//常数
bool v(string str) {
	return(x(str));
}
//无符号整数
bool x(string str) {
	for (int i1 = 0; i1 < str.length(); i1++) {
		if (!k(str[i1])) {
			return false;
		}
	}
	return true;

}
//检测是否为数字
bool k(char cha) {
	return (digit(cha));
}
//条件表达式
void y() {
	s();
	z();
	s();
}
//关系表达式
void z() {
	dual temp = getchar2();
	if (!((temp.num >= 13) && (temp.num <= 17))) {
		error(4);
	}
}
//函数调用
void w() {
	dual temp = getchar2();
	if (temp.num != 21) {
		error(4);
	}
	s();
	temp = getchar2();
	if (temp.num != 22) {
		error(4);
		retract2();
	}
	
}

//将过程名表的项补充完整
void supplement() {
	for (int i1 = 0; i1 < location_p; i1++) {
		int temp1[10];
		int i3 = 0;
		for (int i2 = 0; i2 < location_v; i2++) {
			if (!(variabel_name_table[i2].vproc.compare(progress_name_table[i1].pname))) {
				temp1[i3] = variabel_name_table[i2].vadr;
				i3++;
			}
		}
		progress_name_table[i1].fadr = temp1[0];
		progress_name_table[i1].ladr = temp1[i3-1];
	}
}
//检查前面的过程是否有错误发生
void errorcheck() {
	ifstream infile;
	string temp1 = "test.err";
	string temp2 = {};
	infile.open(temp1.data());
	char c;
	while (!infile.eof())
	{
		infile >> c;
		temp2 += c;
	}
	if (temp2.length()) {
		assert(1);
	}

	infile.close();             
}

//语法分析，并按照标准格式输出
void grammaranalyze() {
	errorcheck();
	error(0);
	extract();
	a();
	supplement();
	ofstream varout("test.var");
	string temp1[100] = {};
	string temp2 = {};
	for (int i1 = 0; i1 < location_v; i1++) {
		temp1[i1] += "vname:";
		temp1[i1] += variabel_name_table[i1].vname;
		for (int i2 = 0; i2 < 16 - variabel_name_table[i1].vname.length(); i2++) {
			temp1[i1] += ' ';
		}
		temp1[i1] += '\n';
		temp1[i1] += "vproc:";
		temp1[i1] += variabel_name_table[i1].vproc;
		for (int i2 = 0; i2 < 16 - variabel_name_table[i1].vproc.length(); i2++) {
			temp1[i1] += ' ';
		}
		temp1[i1] += '\n';
		temp1[i1] += "vkind:";
		temp1[i1] += to_string(variabel_name_table[i1].vkind);
		temp1[i1] += '\n';
		temp1[i1] += "vtype:";
		temp1[i1] += variabel_name_table[i1].vtype;
		temp1[i1] += '\n';
		temp1[i1] += "vlev:";
		temp1[i1] += to_string(variabel_name_table[i1].vlev);
		temp1[i1] += '\n';
		temp1[i1] += "vadr:";
		temp1[i1] += to_string(variabel_name_table[i1].vadr);
		temp1[i1] += '\n';
		temp1[i1] += '\n';
	}
	for (int i1 = 0; i1 < location_v; i1++) {
		temp2 += temp1[i1];
	}
	varout << temp2;
	varout << flush;
	varout.close();

	ofstream proout("test.pro");
	string temp3[100] = {};
	string temp4= {};
	for (int i1 = 0; i1 < location_p; i1++) {
		temp3[i1] += "pname:";
		temp3[i1] += progress_name_table[i1].pname;
		for (int i2 = 0; i2 < 16 - progress_name_table[i1].pname.length(); i2++) {
			temp3[i1] += ' ';
		}
		temp3[i1] += '\n';
		temp3[i1] += "ptype:";
		temp3[i1] += progress_name_table[i1].ptype;
		temp3[i1] += '\n';
		temp3[i1] += "plev:";
		temp3[i1] += to_string(progress_name_table[i1].plev);
		temp3[i1] += '\n';
		temp3[i1] += "fadr:";
		temp3[i1] += to_string(progress_name_table[i1].fadr);
		temp3[i1] += '\n';
		temp3[i1] += "ladr:";
		temp3[i1] += to_string(progress_name_table[i1].ladr);
		temp3[i1] += '\n';
		temp3[i1] += '\n';
	}
	for (int i1 = 0; i1 < location_v; i1++) {
		temp4 += temp3[i1];
	}
	proout << temp4;
	proout << flush;
	proout.close();
}
int main()
{
	
	getchar1();
	lexanalyze();
	grammaranalyze();
	getchar();
    return 0;
}

