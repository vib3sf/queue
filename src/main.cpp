#include "array_queue.h"
#include "list_queue.h"
#include "queue.h"

#include <cstdlib>
#include <map>
#include <stdexcept>
#include <vector>
#include <cstring>
#include <string>

struct Handler
{
	void (*func) (const std::vector<std::string> &, 
		std::map<std::string, Queue<std::string> *> &);

	std::string full_name;
	std::string short_name;
	std::string prompt;

	int right_count;
	bool more_than;
};

bool check_arg_count(std::string cmd, std::string right_usage, int arg_count, 
		int right_count, bool more_than = false)
{
	if(arg_count != right_count && !(more_than && arg_count >= right_count))
	{
		std::cout << "Usage of " << cmd << ": " << right_usage << "\n";
		return false;
	}

	return true;
}

inline bool var_exist(const std::string &var_name, 
		const std::map<std::string, Queue<std::string> *> variables)
{
	return variables.count(var_name);
}

void create_var(const std::vector<std::string> &args, 
		std::map<std::string, Queue<std::string> *> &variables)
{
	if(!check_arg_count("create", "c <aq/lq> <var name>", args.size(), 3))
		return;

	Queue<std::string> *queue;
	if(!args[1].compare("aq"))
		queue = new ArrayQueue<std::string>;
	else if(!args[1].compare("lq"))
		queue = new ListQueue<std::string>;
	else
	{
		std::cout << "Available types to create: aq, lq\n";
		return;
	}

	if(!var_exist(args[2], variables))
		variables[args[2]] = queue;
	else
		std::cout << "The variable has been existed.\n";
}

bool var_check(const std::string &var_name,
		const std::map<std::string, Queue<std::string> *> variables)
{
	if(!var_exist(var_name, variables))
	{
		std::cout << "Var doesn't exist.\n";
		return false;
	}
	return true;
}

void enqueue(const std::vector<std::string> &args, 
		std::map<std::string, Queue<std::string> *> &variables)
{
	if(!check_arg_count("enqueue", "e <var name> <values ...>", 
				args.size(), 3, true))
		return;

	if(var_check(args[1], variables))
		for(int i = 2; i < (int)args.size(); i++)
			*variables[args[1]] += args[i];
}

void dequeue(const std::vector<std::string> &args, 
		std::map<std::string, Queue<std::string> *> &variables)
{
	if(!check_arg_count("dequeue", "d <var name>", args.size(), 2))
		return;
	
	if(var_check(args[1], variables))
		std::cout << variables[args[1]]->dequeue() << '\n';
}

void print_var(const std::vector<std::string> &args, 
		std::map<std::string, Queue<std::string> *> &variables)
{
	if(!check_arg_count("print", "p <var name>", args.size(), 2))
		return;

	if(var_check(args[1], variables))
		std::cout << *variables[args[1]];
}

void remove_var(const std::vector<std::string> &args, 
		std::map<std::string, Queue<std::string> *> &variables)
{
	if(!check_arg_count("remove", "r <var name>", args.size(), 2))
		return;
	
	if(var_check(args[1], variables))
		variables.erase(args[1]);
}

void append_queue(const std::vector<std::string> &args, 
		std::map<std::string, Queue<std::string> *> &variables)
{
	if(!check_arg_count("append", "a <var name to> <var name from>", 
				args.size(), 3))
		return;

	if(var_check(args[1], variables) && var_check(args[2], variables))
		*variables[args[1]] += *variables[args[2]];
}

void multiple(const std::vector<std::string> &args, 
		std::map<std::string, Queue<std::string> *> &variables)
{
	if(!check_arg_count("multiple", "m <var name> <multiplier>", 
				args.size(), 3))
		return;

	try
	{
		*variables[args[1]] *= stoi(args[2]);
	}
	catch(std::invalid_argument &e)
	{
		std::cout << "Invalid multipler\n";
	}
}

void execute_command(const std::vector<std::string> &args, 
		std::map<std::string, Queue<std::string> *> &variables, 
		std::map<std::string, void (*) (const std::vector<std::string> &, 
		std::map<std::string, Queue<std::string> *> &)> &handlers)
{
	if(handlers.count(args[0]))
		handlers[args[0]](args, variables);
	else 
		std::cout << "Wrong command\n";
}

std::vector<std::string> split_input(const std::string &input)
{
	std::vector<std::string> res;

    std::string::size_type prev_pos = 0, pos = 0;
	while((pos = input.find(' ', pos)) != std::string::npos)
    {
        std::string substring(input.substr(prev_pos, pos-prev_pos));
        res.push_back(substring);

		pos++;
        prev_pos = pos;
    }
    res.push_back(input.substr(prev_pos, pos-prev_pos));

	return res;
}

void init_handlers(std::map<std::string, void (*) (const std::vector<std::string> &, 
		std::map<std::string, Queue<std::string> *> &)> &handlers)
{
	handlers["c"] = create_var;
	handlers["e"] = enqueue;
	handlers["d"] = dequeue;
	handlers["p"] = print_var;
	handlers["r"] = remove_var;
	handlers["a"] = append_queue;
	handlers["m"] = multiple;
}

int main()
{
	std::map<std::string, Queue<std::string> *> variables;

	std::map<std::string, void (*) (const std::vector<std::string> &, 
		std::map<std::string, Queue<std::string> *> &)> handlers;

	std::string input;

	init_handlers(handlers);
	while(true)
	{
		std::getline(std::cin, input);
		std::vector<std::string> args = split_input(input);
		
		execute_command(args, variables, handlers);
	}
	
	return 0;
}
