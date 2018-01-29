#include"CMatrix.h"
#include"CParser.h"


int main(int argc,char** argv)
{
L1:	try{
		if(argc==1)
			CParser::take_input();
	}
		 

	catch(const char* error)
	{
		cout<<error<<" at line "<<line<<endl;
		goto L1;
	}

	catch(int n)
  	{		 
		
		if(n==0) cout<<"Can't calculate log(0) or log(-ve)"<<" at line "<<line<<endl;
		if(n==1) cout<<"Can't calculate tan(90)"<<" at line "<<line<<endl;
		if(n==2) cout<<"sqrt(-ve) is an imaginary number"<<" at line "<<line<<endl;
		if(n==3) cout<<"Braces aren't synchronizied"<<" at line "<<line<<endl;
		if(n==4) cout<<"Can't calculate ln(0) or ln(-ve)"<<" at line "<<line<<endl;
		if(n==5) cout<<"error:can't divide by zero"<<" at line "<<line<<endl;
		goto L1;
 	  }

	if(argc==2){
			CParser::take_input_file(argv[1]);
		 }


	return 0;
}