#include<iostream>
#include<math.h>
#include<string>
#include<stdarg.h>
#include<stdlib.h>
#include<vector>
#include<time.h>

using namespace std;
float vector_cal ( vector <float> v , vector<char>signs );

bool checkchar(char x)
{
	if( x=='0' || x =='1' || x=='2'||x=='3'||x=='4'||x=='5'||x=='6'||x=='7'||x=='8'||x=='9'||x=='.')
	{
		return true;
	}
	else return false;
}

float domath(string&a)
{
	string n1 = ""; float result=0;
	unsigned int length = a.length();
	 int no_of_char = 0;
	  string last="";
	vector <float> v;
	vector<char> signs;
	string function="";
	while(no_of_char < length)
	{
		if( checkchar(a[no_of_char]) ||(a[no_of_char]=='-' && n1==""&&last!=")") )
		{
			if(last=="^") 
			{
				while( (checkchar(a[no_of_char]))||(a[no_of_char]=='-'&&n1==""))
				{
					n1+=a[no_of_char];
					no_of_char++;
				}
			v.push_back(pow(result , atof( n1.c_str())));
			last = ")";
			n1="";
			}
			else
			{
			n1+=a[no_of_char];
			no_of_char++;
			last="!";
			}
		}

		else if (a[no_of_char]=='^')
		{
			result = atoi (n1.c_str());
			last = "^";
			n1="";
			no_of_char++;
		}
		else if(a[no_of_char]=='+' ||(a[no_of_char]=='-')||a[no_of_char]=='*'||a[no_of_char]=='/')
		{
			
			if(n1!="")
			{
				result = atof(n1.c_str());
				v.push_back(result);
				result = 0;
				n1="";
			}
			signs.push_back(a[no_of_char]);
			no_of_char++;
			last = "$";
		}
		else if( (a[no_of_char] == 'l'&&a[no_of_char+1]=='o'&&a[no_of_char+2]=='g')||(a[no_of_char] == 's'&&a[no_of_char+1]=='i'&&a[no_of_char+2]=='n')
			||(a[no_of_char] == 'c'&&a[no_of_char+1]=='o'&&a[no_of_char+2]=='s')||(a[no_of_char] == 't'&&a[no_of_char+1]=='a'&&a[no_of_char+2]=='n')||
			(a[no_of_char] == 's'&&a[no_of_char+1]=='e'&&a[no_of_char+2]=='c')||(a[no_of_char] == 'c'&&a[no_of_char+1]=='s'&&a[no_of_char+2]=='c') ||
			a[no_of_char] == 'e'&&a[no_of_char+1]=='x'&&a[no_of_char+2]=='p')
		{
			bool flag=0;
			string function="";
			function += a[no_of_char];
			function+=a[no_of_char+1];
			function+=a[no_of_char+2];
			no_of_char = no_of_char +3;
			if(n1!="")
			{
				result = atof(n1.c_str());
				v.push_back(result);
				result = 0;n1="";
			}
			while((checkchar(a[no_of_char])||(a[no_of_char]=='-'&&n1==""))&&no_of_char < length)
					{
						n1+=a[no_of_char];
						no_of_char++;
					}
			result = atof(n1.c_str());
			n1="";
			if(function=="sin") v.push_back(sin(result));
			if(function=="cos")v.push_back(cos(result));
			if(function=="tan")v.push_back(tan(result));
			if(function=="log"){if (result<=0 ) throw(0); else {v.push_back(log10(result));}}
			if(function=="sec")v.push_back(1.0/cos(result));
			if(function=="csc")v.push_back(1.0/sin(result));
			if(function=="exp")v.push_back(exp(result));
			result =0;
			last=")";

		}
		else
			no_of_char++;
	}
l1:	if(n1 != "")
	{
		float ni=stof(n1);
		v.push_back(ni);
	}

	return vector_cal ( v , signs );
}

float vector_cal ( vector <float> v , vector<char>signs )
{
	float result = 0;
	int size = v.size();
	bool flag = false;int i,j;
	float *p=new float[size];
	if(size==1)
	{
		result = v[0];
		return result;
	}
	for(int r =0;r<size;r++)
	{
		p[r] = v[r];
	}

	char *sign = new char[signs.size()];
	for(int q =0;q<signs.size();q++)
	{
		sign[q] = signs[q];
	}
	float total;
	while(size > 1)
	{
		for(i=0;i<size-1;i++)
		{
			if(sign[i]=='*' || sign[i]=='/')
			{
				flag = true;
				break;
			}
		}
		if(flag == true)
		{
			flag = false;
			size--;
			float *temp = new float[size];
			for(j=0;j<size;j++)
			{
				if(j==i && sign[i] == '*')
				{temp[j] = p[j]*p[j+1];if(size==1) return temp[j];}
				else if(j==i && sign[i] == '/')
					{temp[j] = p[j]/p[j+1];if(size==1) return temp[j];}
				else if ( j<i)
					temp[j] = p[j];
				else
					temp[j] = p[j+1];
			}
			p=temp;
			char*temps = new char [size-1];
			for(j=0;j<size-1;j++)
			{
				if(j<i)
					temps[j] = sign[j];
				else
					temps[j]=sign[j+1];
			}
			sign = temps;
		}
		else
		{
			size--;
			float *temp = new float[size];
			if(sign[0] == '-') {temp[0] = p[0]-p[1];result = temp[0];}
			if(sign[0] == '+') {temp[0] = p[0]+p[1];result = temp[0];}
			if(size>1)
			{
				for(j=1;j<size;j++)
				{
					temp[j] = p[j+1];
				}
				p=temp;
			}
			if(size-1 >=1)
			{
				char*temps = new char [size-1];
				for(j=0;j<size-1;j++)
				{
					temps[j]=sign[j+1];
				}
				sign = temps;
			}
		}
	}
	return result;
}








float subcal(string h,int nb)
{
	//cout<<nb<<endl;
	if(nb==0)
		return domath(h);
	else
	{
		float result;
		string part="";
		int *pos=new int[nb];
		int length=h.length();
		int d=0;int i;int count=0;
		for(i=0;i<length;i++)
		{
			i=h.find('(',i);
			if(i==-1)break;
			pos[d]=i;
			cout<<pos[d]<<endl;
			d++;count++;
		}
		d=0;i=0;bool flag=true;
		for(i=0;i<count;i++)
		{
			d=pos[i];
			d++;
			while(d<length)
			{
				if(h[d]=='(')
				{part="";break;}
				else if(h[d]==')')
				{
					flag=false;
					break;
				}
				else part+=h[d];
				d++;
			}
			if(flag==false)
			{
				flag=true;
				break;
			}
		}
		 h=h.replace(pos[i],d-pos[i]+1,to_string(domath(part)));
		cout<<"my favourite part is "<<h<<endl;
		if(h.find('(',0)==-1)
			return domath(h);
		else
		{
			int l=0, count2=0;
			while(l<h.length())
			{
				if(h.find('(',l)!=-1)
				{
					count2++;
					l=h.find('(',l)+1;
					cout<<l<<endl;
				}
				else break;
			}
			 result = subcal(h,count2);
		}
		return result;
	}
}




float calculate(string a)
{
	string w="";int no_of_char=0;string last;string mod;unsigned int coo=0;
	int length = a.length();vector<float> v;vector<char>signs;float result=0;
	while(no_of_char<length)
	{
		if(checkchar(a[no_of_char]) || (a[no_of_char]=='-' &&w==""&&last!=")") )
		{
			w+=a[no_of_char];
			if(last!="^")last = "!";
			else last="^";
			if(no_of_char+1 == length&&last=="^") { v.push_back(pow(result,atof(w.c_str())));w="";result=0;}
			no_of_char++;
		}
		else if(a[no_of_char]=='+' ||(a[no_of_char]=='-')||a[no_of_char]=='*'||a[no_of_char]=='/')
		{
			if(result!=0&&last==")")
			{
				v.push_back(result);
				result=0;
				coo=0;
			}
			if(last=="^" && w!="")
			{
				v.push_back(pow(result,atof(w.c_str())));
				w="";
				result=0;
			}
			if(w!="")
			{
			result=atof(w.c_str());
			v.push_back(result);
			result=0;w="";
			}
			signs.push_back(a[no_of_char]);
			no_of_char++;
			last="$";
		}


		else if(a[no_of_char]=='^')
		{
			if(w!="")
			{
				result = atof(w.c_str());
				w="";
			}
			no_of_char++;
			last="^";
		}

		else if( (a[no_of_char] == 'l'&&a[no_of_char+1]=='o'&&a[no_of_char+2]=='g')||(a[no_of_char] == 's'&&a[no_of_char+1]=='i'&&a[no_of_char+2]=='n')
			||(a[no_of_char] == 'c'&&a[no_of_char+1]=='o'&&a[no_of_char+2]=='s')||(a[no_of_char] == 't'&&a[no_of_char+1]=='a'&&a[no_of_char+2]=='n')||
			(a[no_of_char] == 's'&&a[no_of_char+1]=='e'&&a[no_of_char+2]=='c')||(a[no_of_char] == 'c'&&a[no_of_char+1]=='s'&&a[no_of_char+2]=='c') 
			||(a[no_of_char] == 'e'&&a[no_of_char+1]=='x'&&a[no_of_char+2]=='p'))
		{
			if(result!=0&&last==")")
			{
				v.push_back(result);
				result=0;
			}
			string function="";
			function+=a[no_of_char];
			function+=a[no_of_char+1];
			function+=a[no_of_char+2];
			no_of_char=a.find('(',no_of_char);
			if(w!="")
			{
				v.push_back(atof(w.c_str()));
				w="";
				signs.push_back('*');
				last= function;
			}
			int beginning = no_of_char;
			w+=a[no_of_char];
			no_of_char++;
			int noopen=1;
			int noclosed=0 ;
			while(1)
			{
				w+=a[no_of_char];
				if(a[no_of_char]=='(')noopen++;
				if(a[no_of_char]==')')noclosed++;
				if(noopen==noclosed)break;
				else 
				{
					no_of_char++;
					continue;
				}
			}
			int end = no_of_char;
			w=w.erase(0,1);w=w.erase(w.length()-1,1);
			float res = subcal(w,noopen-1);
			w="";
			if(function=="sin") v.push_back(sin(res));
			if(function=="cos")v.push_back(cos(res));
			if(function=="tan")v.push_back(tan(res));
			if(function=="log"){ if (res<=0 ) throw(0);else { v.push_back(log10(res));}}
			if(function=="sec")v.push_back(1.0/cos(res));
			if(function=="csc")v.push_back(1.0/sin(res));
			if(function=="exp")v.push_back(exp(res));
			result =0;
			last = ")";
			no_of_char=end+1;
		}

		else if ( a[no_of_char]=='s' && a[no_of_char+1]=='q')
		{
			no_of_char=a.find('(',no_of_char);
			int beginning = no_of_char;
			w+=a[no_of_char];
			no_of_char++;
			int noopen=1;
			int noclosed=0 ;
			while(1)
			{
				w+=a[no_of_char];
				if(a[no_of_char]=='(')noopen++;
				if(a[no_of_char]==')')noclosed++;
				if(noopen==noclosed)break;
				else 
				{
					no_of_char++;
					continue;
				}
			}
			int end = no_of_char;
			w=w.erase(0,1);w=w.erase(w.length()-1,1);
			float res = subcal(w,noopen-1);
			w="";
			if (res < 0) throw (1) ;
			else v.push_back(sqrt(res));
			result =0;
			last = ")";
			no_of_char=end+1;
		}

		else if(a[no_of_char]=='(')
		{
			coo++;
			if(w!="")
			{
				result = atof(w.c_str());
				v.push_back(result);
				signs.push_back('*');
				result=0;last="(";w="";
			}
			w+=a[no_of_char];
			int beginning = no_of_char;
			no_of_char++;
			int noopen=1;
			int noclosed=0 ;
			while(1)
			{
				w+=a[no_of_char];
				if(a[no_of_char]=='(')noopen++;
				if(a[no_of_char]==')')noclosed++;
				if(noopen==noclosed)break;
				else 
				{
					no_of_char++;
					continue;
				}
			}
			int end = no_of_char;
			cout<<noclosed<<"       "<<noopen<<" "<<w<<endl;
			w=w.erase(0,1);w=w.erase(w.length()-1,1);
			if(last!="^")
			{
				if(coo==1) result=subcal(w,noopen-1);
				if(coo==2) {if(result!=0){v.push_back(result);}result=subcal(w,noopen-1);v.push_back(result);coo=0;}
			}
			if(last=="^")
			{
				float e = subcal(w,noopen-1);
				v.push_back( pow( result,e ));
				coo=0;result = 0;
			}
			w="";
			last=")";
			no_of_char=end+1;
		}
		else
		{
			no_of_char++;
			continue;
		}
	}
	if(result!=0)
	{
		v.push_back(result);
	}

	result=0;
	if(w != "")
	{
		float ni=stof(w);
		v.push_back(ni);
	}
	return vector_cal ( v , signs );
	}
	

int main()
{
	try
	{
	string h ="1-2*sin(10)/4+log(5)*2^2-2";
	cout<<"final result is " <<calculate(h)<<endl;
	return 0;
	}
	catch (int n )
	{
		if(n == 0 ){cout<<"log -ve or zero cant be calculated "<<endl;}
		if ( n==1){cout<<"sqrt of negative number is complex"<<endl;}
	}
}