#include "array_queue.h"
#include "list_queue.h"
#include "queue.h"

#include <cstdlib>
#include <iostream>
#include <map>


static int split_string(char **buf);
static void str_extend(char **str, int& size);
static bool str_equal(const char *str1, const char *str2);

struct cmp_str
{
   bool operator()(char const *a, char const *b) const
   {
      return !str_equal(a, b);
   }
};

enum vars { aq, lq };
static void create_var(char **buf, int count, vars var, 
		std::map<char *, Queue<int> *, cmp_str>& variables);
static void print_var(char **buf, int count, 
		std::map<char *, Queue<int> *, cmp_str>& variables);
static void enqueue(char **buf, int count, 
		std::map<char *, Queue<int> *, cmp_str>& variables);
static void dequeue(char **buf, int count, 
		std::map<char *, Queue<int> *, cmp_str>& variables);


int main()
{
	std::map<char *, Queue<int> *, cmp_str> variables;
	char *buf[3];
	int count;

	while(true)
	{
		count = split_string(buf);

		if(count)

		{
			if(str_equal(buf[0], "aq"))
				create_var(buf, count, aq, variables);

			else if(str_equal(buf[0], "lq"))
				create_var(buf, count, lq, variables);

			else if(str_equal(buf[0], "p"))
				print_var(buf, count, variables);

			else if(str_equal(buf[0], "e"))
				enqueue(buf, count, variables);

			else if(str_equal(buf[0], "d"))
				dequeue(buf, count, variables);
		}
	}

	return 0;
}

static int split_string(char **buf)
{
	int count = 0, len = 0, arg_size = 4;
	char c, *arg = new char[arg_size];

	while((c = getchar()) != '\n')
	{
		if(c == EOF)
			return -1;

		if(c == ' ')
		{
			if(count == 3)
				return 0;

			buf[count] = arg;
			arg_size = 4;
			arg = new char[arg_size];
			count++;
			len = 0;

			continue;
		}
		else if(arg_size == len)
			str_extend(&arg, arg_size);

		arg[len] = c;
		len++;
	}

	buf[count] = arg;
	return count + 1;
}

static void str_extend(char **str, int& size)
{
	char *tmp;
	size *= 2;
	tmp = new char[size];

	for(int i = 0; i < size / 2; i++)
		tmp[i] = *str[i];

	delete str;
	*str = tmp;
}

static bool str_equal(const char *str1, const char *str2)
{
	if(*str1 == '\0' && *str2 == '\0')
		return true;

	return *str1 == *str2 ? str_equal(str1 + 1, str2 + 1) : false;
}

static void create_var(char **buf, int count, vars var, 
		std::map<char *, Queue<int> *, cmp_str>& variables)
{
	if(count != 2)
	{
		const char *q_tag = (var == aq) ? "aq" : "eq";

		std::cerr << "Usage of " << q_tag << ": " << q_tag << " <var name>\n";
		return;
	}

	Queue<int> *q;
	switch(var)
	{
		case aq:
			q = new ArrayQueue<int>();
			break;
		case lq:
			q = new ListQueue<int>();
			break;
	}
	variables[buf[1]] = q;
}

static void print_var(char **buf, int count, 
		std::map<char *, Queue<int> *, cmp_str>& variables)
{
	if(count != 2)
	{
		std::cerr << "Usage of p: p <var name>\n";
		return;
	}
	std::cout << *variables[buf[1]];
}

static void enqueue(char **buf, int count, 
		std::map<char *, Queue<int> *, cmp_str>& variables)
{
	if(count != 3)
	{
		std::cerr << "Usage of e: e <var name> <num:int>\n";
		return;
	}
	*variables[buf[1]] += atoi(buf[2]);
}

static void dequeue(char **buf, int count, 
		std::map<char *, Queue<int> *, cmp_str>& variables)
{
	if(count != 3)
	{
		std::cerr << "Usage of e: e <var name>\n";
		return;
	}
	std::cout << variables[buf[1]]->dequeue() << '\n';
}
