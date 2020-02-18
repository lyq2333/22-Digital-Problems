#include<iostream>
#include<string>
#include<fstream>
#include<queue>
#include<time.h>
using namespace std;
typedef struct node
{
	int matrix[5][5];
	int row, column;
	int last;
	int miss;
	int step;
	string str;
	friend bool operator < (node a, node b)
	{
		return a.miss + a.step > b.miss + b.step;
	}
}*nodeptr;
priority_queue<node> q;
int begin1[5][5], end1[5][5];
int finish, miss;
node target;
void readfile(int begin[5][5], string str);
void writefile(double a);
void move_up(node a);
void move_down(node a);
void move_left(node a);
void move_right(node a);
int main()
{
	int i, j;
	double time;
	node start;
	node m;
	clock_t begintime, endtime;
	begintime = clock();
	miss = 0;
	finish = 0;
	readfile(start.matrix, "input.txt");
	readfile(end1, "target.txt");
	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 5; j++)
		{
			if (start.matrix[i][j] != end1[i][j] && start.matrix[i][j] != 0) miss++;
			if (start.matrix[i][j] == 0)
			{
				start.row = i;
				start.column = j;
			}
		}
	}
	start.miss = miss;
	start.step = 0;
	start.last = 0;
	start.str = "";
	q.push(start);
	while (finish != 1)
	{
		if (q.size() == 9200)
			m = q.top();
		m = q.top();
		if (m.last != 1)
			move_up(m);
		if (finish != 1 && m.last != 2)
			move_down(m);
		if (finish != 1 && m.last != 3)
			move_left(m);
		if (finish != 1 && m.last != 4)
			move_right(m);
		q.pop();
	}
	//while (q.empty())
	//q.pop();
	endtime = clock();
	time = (double)(-begintime + endtime) / CLOCKS_PER_SEC;
	writefile(time);
	return 0;
}
void readfile(int begin[5][5], string str)
{
	int  a, b;
	unsigned int i;
	string in, temp;
	ifstream infile;
	infile.open(str, ios::in);
	a = 0;
	b = 0;
	while (getline(infile, in))
	{
		i = 0;
		while (i < in.length())
		{
			if (in[i] != ' ')
			{
				temp += in[i];
				i++;
			}
			else {
				begin[a][b++] = stoi(temp);
				temp = "";
				while (in[i] == ' '&&i < in.length())
					i++;
			}
		}
		if (temp != "")
		{
			begin[a][b] = stoi(temp);
			temp = "";
		}
		b = 0;
		a++;
	}
	infile.close();
}
void writefile(double a)
{
	ofstream outfile;
	outfile.open("output_Ah1.txt", ios::trunc);
	outfile << a << endl;
	outfile << target.str << endl;
	outfile << target.step << endl;
	outfile.close();

}
void move_up(node a)//up
{
	node b;
	int i, j;
	int miss = 0;
	if (a.row == 0) return;
	if (a.column == 1 && a.row == 3) return;
	if (a.column == 3 && a.row == 3) return;
	b.str = a.str + "U";
	b.column = a.column;
	b.row = a.row - 1;
	b.last = 2;
	b.step = a.step + 1;
	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 5; j++)
		{
			if (i == b.row&&j == b.column) b.matrix[i][j] = 0;
			else if (i == b.row + 1 && j == b.column) b.matrix[i][j] = a.matrix[i - 1][j];
			else b.matrix[i][j] = a.matrix[i][j];
			if (b.matrix[i][j] != end1[i][j] && b.matrix[i][j] != 0) miss++;
		}
	}
	b.miss = miss;
	if (b.miss == 0)
	{
		finish = 1;
		target = b;
	}
	q.push(b);
	return;
}
void move_down(node a)//down
{
	node b;
	int i, j;
	int miss = 0;
	if (a.row == 4) return;
	if (a.column == 1 && a.row == 1) return;
	if (a.column == 3 && a.row == 1) return;
	b.str = a.str + "D";
	b.column = a.column;
	b.row = a.row + 1;
	b.last = 1;
	b.step = a.step + 1;
	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 5; j++)
		{
			if (i == b.row&&j == b.column) b.matrix[i][j] = 0;
			else if (i == b.row - 1 && j == b.column) b.matrix[i][j] = a.matrix[i + 1][j];
			else b.matrix[i][j] = a.matrix[i][j];
			if (b.matrix[i][j] != end1[i][j] && b.matrix[i][j] != 0) miss++;
		}
	}
	b.miss = miss;
	if (b.miss == 0)
	{
		finish = 1;
		target = b;
	}
	q.push(b);
	return;
}
void move_left(node a)//left
{
	node b;
	int i, j;
	int miss = 0;
	if (a.column == 0) return;
	b.str = a.str + "L";
	if (a.row == 2 && (a.column == 2 || a.column == 4))
		b.column = a.column - 2;
	else b.column = a.column - 1;
	b.row = a.row;
	b.last = 4;
	b.step = a.step + 1;
	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 5; j++)
		{
			if (i == b.row&&j == b.column)
			{
				b.matrix[i][j] = 0;
			}
			else if (i == b.row && j == b.column + 1)
			{
				if (a.matrix[i][j] != -1)
					b.matrix[i][j] = a.matrix[i][j - 1];
				else b.matrix[i][j] = a.matrix[i][j];
			}
			else if (i == b.row && j == b.column + 2)
			{
				if (a.matrix[i][j - 1] == -1)  b.matrix[i][j] = a.matrix[i][j - 2];
				else b.matrix[i][j] = a.matrix[i][j];
			}
			else b.matrix[i][j] = a.matrix[i][j];
			if (b.matrix[i][j] != end1[i][j] && b.matrix[i][j] != 0) miss++;
		}
	}
	b.miss = miss;
	if (b.miss == 0)
	{
		finish = 1;
		target = b;
	}
	q.push(b);
	return;
}
void move_right(node a)//right
{
	node b;
	int i, j;
	int miss = 0;
	if (a.column == 4) return;
	b.str = a.str + "R";
	if (a.row == 2 && (a.column == 0 || a.column == 2))
		b.column = a.column + 2;
	else b.column = a.column + 1;
	b.row = a.row;
	b.last = 3;
	b.step = a.step + 1;
	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 5; j++)
		{
			if (i == b.row&&j == b.column)
			{
				b.matrix[i][j] = 0;
			}
			else if (i == b.row && j == b.column - 1)
			{
				if (a.matrix[i][j] != -1)
					b.matrix[i][j] = a.matrix[i][j + 1];
				else b.matrix[i][j] = a.matrix[i][j];
			}
			else if (i == b.row && j == b.column - 2)
			{
				if (a.matrix[i][j + 1] == -1)  b.matrix[i][j] = a.matrix[i][j + 2];
				else b.matrix[i][j] = a.matrix[i][j];
			}
			else b.matrix[i][j] = a.matrix[i][j];
			if (b.matrix[i][j] != end1[i][j] && b.matrix[i][j] != 0) miss++;
		}
	}
	b.miss = miss;
	if (b.miss == 0)
	{
		finish = 1;
		target = b;
	}
	q.push(b);
	return;
}