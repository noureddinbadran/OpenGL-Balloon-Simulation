#include <iostream>

using namespace std;


//ÊÇÈÚ íÊÃßÏ İíãÇ ÅĞÇ ßÇä ÇáÑŞã ÇáĞí íÑÇÏ ØÈÇÚÊå ÚÔÑí Ãã ÕÍíÍ
bool cheack(string s)
{
	for(unsigned int i=0 ; i<s.length() ; i++)
		if(s[i]=='.')
		   return true;

	return false;
}

//ááÊÍæíá ãä ãÍÑİ áÑŞã
double int_Parse(char c)
{
		switch (c)
	{
	    case '0' : return 0;
		  break;
		case '1' : return 1;
		  break;
		case '2' : return 2;
		  break;
		case '3' : return 3;
	  	  break;
		case '4' : return 4;
		  break;
		case '5' : return 5;
		  break;
		case '6' : return 6;
		  break;
		case '7' : return 7;
		  break;
		case '8' : return 8;
		  break;
		case '9' : return 9;
		  break;
	default:
		  //
		break;
	}
return 0;
}

//ÊÇÈÚ íÃÎĞ Øæá ÇáŞÓã ÇáÚÔÑí æ íÑÏ ŞíãÉ áäŞÓã ÇáÌÒÁ ÇáÚÔÑí ãä ÇáÚÏÏ İíÕÈÍ ÚÔÑí
double fraction_count(double f_length)
{
	int count=f_length;
	switch(count)
	{
	  case 1 : return 10.0;
	  	  break;
	  case 2 : return 100.0;
		  break;
	  case 3 : return 1000.0;
		  break;
	  case 4 : return 10000.0;
		  break;
	  case 5 : return 100000.0;
		  break;
	  case 6 : return 1000000.0;
		  break;
	  case 7 : return 10000000.0;
		  break;
	  case 8 : return 100000000.0;
		  break;
	  case 9 : return 1000000000.0;
		  break;
	  case 10 : return 10000000000.0;
		  break;
	  default : return 0;
		  break;
	}
	return 0;
}

//ÊÇÈÚ ááÊÍæíá ãä ÓáÓáÉ ãÍÇÑİ Åáì ÑŞã
double double_Parse(string s)
{
int num(0);
if(!cheack(s))//Ãí ÇáÑŞã áíÓ İíå ŞÇÕáÉ ÚÔÑíÉ
 {
	for(unsigned int i=0 ; i< s.length() ; i++)
	{
       num=num*10+int_Parse(s[i]);
	}
  return num;
 }
else
{
	double fraction(0);
	unsigned int index=0;
	for(index ; s[index]!='.' ; index++)
	{
		num=num*10+int_Parse(s[index]);
	}
	double fraction_length=s.length()-(++index);
	for(index ; index<s.length() ; index++)
	{
		fraction=fraction*10+int_Parse(s[index]);
	}
	fraction=fraction/fraction_count(fraction_length);

  //ÌãÚ ÇáäÊíÌÉ
	double resault=num+fraction;

	return resault;
}
return 0;

}