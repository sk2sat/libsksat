#include <sksat/common.hpp>

namespace sksat {

using opt_func = int (*)(int, char**);
class optparse {
public:
	struct option {
		char s_opt;
		sksat::string l_opt, desc;
		opt_func func;
	};

	optparse() : argc(0), argv(nullptr) {}

	void add_opt(optparse::option o){
		opts.push_back(o);
	}

	void add_opt(char s_opt, sksat::string l_opt, sksat::string desc, opt_func func){
		option o = {
			.s_opt = s_opt,
			.l_opt = l_opt,
			.desc  = desc,
			.func  = func
		};

		add_opt(o);
	}

	int search_short_opt(char c){
		for(int i=0;i<opts.size();i++){
			if(opts[i].s_opt == c) return i;
		}
		return -1;
	}

	bool parse(int argc, char **argv){
		this->argc = argc;
		this->argv = argv;
		if(argc == 1) return false;
//		argv++;
		for(int i=0;i<argc;i++){
			int opt_num = -1;
			if(argv[0][0] == '-'){ // option?
				if(argv[0][1] == '-'){ // long option
					throw "not implemented";
				}else{ // short option
					opt_num = search_short_opt(argv[0][1]);
				}
			}
			if(opt_num > -1){ // option found
				opt_func f = opts[opt_num].func;
				int ret = f(argc-i, argv);
				i += ret;
				argv+=ret;
			}
			argv++;
		}
	}

private:
	int argc;
	char **argv;
	sksat::vector<option> opts;
};

}
