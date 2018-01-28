#ifndef parser_m
#define parser_m


#include"CMatrix.h"
extern vector <CVariables> vars;
extern vector <CMatrix> mats;


using namespace std;




class CParser
{
public:

	static void take_input();
	static string create_mat(string h,int mode=1);
    static string concat(CMatrix A,CMatrix B);
	static string handle_parentheses(string& s, char c = '0');
	static string handle_priorities_2(string &s, string*op, int n_op, int continuee = 1, char cc = '0');
	static string  handle_priorities(string  &s);
	static  void remove_spaces(string&str);
	static string detect_operan(string &s);
	//static float domath(string&a);
	static float vector_cal ( vector <float> v , vector<char>signs );
	static float subcal(string h,int nb);
	static float calculate(string a , enum NoCalling detector);
};

enum NoCalling { First , Other };


#endif