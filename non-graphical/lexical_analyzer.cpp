#include<iostream>
#include<string>
#include<vector>
////////////////token marking///////////////////////
#define $int	1
#define $void	2
#define $if		3
#define $else	4
#define $while	5
#define $return 6
#define $ID		7
#define $ASSIGN 8
#define $PLUS	9
#define $MINUS	10
#define $MULT	11
#define $DIV	12
#define $EQUAL	13
#define $GREATER 14
#define $GREATER_EQ 15
#define $LOWER	16
#define $LOWER_EQ 17
#define $UNEQUAL 18
#define $BOUND	19
#define $COMMA	20
#define $LEFT_COMM 21
#define $RIGHT_COMM 22
#define $LINE_COMM 23
#define $LPAR	24
#define $RPAR	25
#define $LBRACE 26
#define $RBARCE 27
#define $VALUE	28
//////////////////////////////////
using namespace std;
vector<string> id_table;
vector<string> result;

bool IsLetter(char ch)
{
	if (ch >= 'a'&&ch <= 'z' || ch >= 'A'&&ch <= 'Z')
		return true;
	else
		return false;
}

bool IsDigit(char ch)
{
	if (ch>='0'&&ch<='9')
		return true;
	else
		return false;
}

int scanner(string str)
{
	int i = 0;
	string strToken = "";
	while (i<str.length())
	{
		if (IsLetter(str[i]))
		{
			while (IsLetter(str[i]) || IsDigit(str[i]))
			{
				strToken.push_back(str[i]);
				i++;
			}
			if ("int" == strToken)
			{
				result.push_back("<$int,->\n");
			}
			else if ("void" == strToken)
			{
				result.push_back("<$void,->\n");
			}
			else if ("if" == strToken)
			{
				//cout << strToken << endl;
				//cout << "<$if,->" << endl;
				result.push_back("<$if,->\n");
			}
			else if ("else" == strToken)
			{
				//cout << strToken << endl;
				//cout << "<$else,->" << endl;
				result.push_back("<$else,->\n");
			}
			else if ("while" == strToken)
			{
				//cout << strToken << endl;
				//cout << "<$while,->" << endl;
				result.push_back("<$while,->\n");
			}
			else if ("return" == strToken)
			{
				result.push_back("<$return,->\n");
			}
			else if ("char" == strToken)
			{
				result.push_back("<$char,->\n");
			}
			else if ("const" == strToken)
			{
				result.push_back("<$const,->\n");
			}
			else if ("unsigned" == strToken)
			{
				result.push_back("<$unsigned,->\n");
			}
			else if ("bool" == strToken)
			{
				result.push_back("<$bool,->\n");
			}
			else if ("true" == strToken)
			{
				result.push_back("<$true,->\n");
			}
			else if ("false" == strToken)
			{
				result.push_back("<$false,->\n");
			}
			else
			{
				int index=0;
				for (int i = 0; i < id_table.size(); i++)
				{
					if (strToken == id_table[i])
					{
						index = i + 1;
					}
				}
				if (index == 0)
				{
					id_table.push_back(strToken);
					index = id_table.size();
				}
				result.push_back("<$ID,"+to_string(index)+">\n");
				i--;
			}
			strToken = "";
			i++;
		}
		else if (IsDigit(str[i]))
		{
			while (IsDigit(str[i]))
			{
				strToken.push_back(str[i]);
				i++;
			}
			//cout << strToken << endl;
			result.push_back("<$VALUE,"+strToken+">\n");
			//cout << "<$VALUE," << strToken << ">" << endl;
			strToken = "";
			//i++;
		}
		else if ('=' == str[i])
		{
			if ('=' == str[i + 1])
			{
				i++;
				strToken = "==";
				//cout << strToken<<endl;
				strToken = "";
				//cout << "<$EQUAL,->" << endl;
				result.push_back("<$EQUAL,->\n");
			}
			else
			{
				//cout << str[i] << endl;
				//cout << "<$ASSIGN,->" << endl;
				result.push_back("<$ASSIGN,->\n");
				i++;
			}
		}
		else if ('+' == str[i])
		{
			//cout << str[i] << endl;
			//cout << "<$PLUS,->" << endl;
			result.push_back("<$PLUS,->\n");
			i++;
		}
		else if ('-' == str[i])
		{
			//cout << str[i] << endl;
			//cout << "<$MINUS,->" << endl;
			result.push_back("<$MINUS,->\n");
			i++;
		}
		else if ('*' == str[i])
		{
			if ('/' == str[i + 1])
			{
				i++;
				strToken = "*/";
				//cout << strToken<<endl;
				strToken = "";
				//cout << "<$RIGHT_COMM,->" << endl;
				result.push_back("<$RIGHT_COMM,->\n");
			}
			else
			{
				//cout << "<$MULT,->" << endl;
				result.push_back("<$MULT,->\n");
				i++;
			}
		}
		else if ('/' == str[i])
		{
			if ('*' == str[i + 1])
			{
				i++;
				strToken = "/*";
				//cout << strToken<<endl;
				strToken = "";
				//cout << "<$LEFT_COMM,->" << endl;
				result.push_back("<$LEFT_COMM,->\n");
			}
			else if ('/' == str[i + 1])
			{
				i++;
				strToken = "//";
				//cout << strToken<<endl;
				strToken = "";
				//cout << "<$LEFT_COMM,->" << endl;
				result.push_back("<$LINE_COMMENT,->\n");
			}
			else
			{
				//cout << str[i] << endl;
				//cout << "<$DIV,->" << endl;
				result.push_back("<$DIV,->\n");
				i++;
			}
		}
		else if ('>' == str[i])
		{
			if ('=' == str[i + 1])
			{
				i+=2;
				strToken = ">=";
				//cout << strToken << endl;
				//cout << "<$GREATER_OR_EQUAL,->" << endl;
				result.push_back("<$GREATER_OR_EQUAL,->\n");
				strToken = "";
			}
			else
			{
				//cout << str[i] << endl;
				//cout << "<$GREATER,->" << endl;
				result.push_back("<$GREATER,->\n");
				i++;
			}
		}
		else if ('<' == str[i])
		{
			if ('=' == str[i + 1])
			{
				i+=2;
				strToken = "<=";
				//cout << "<$LOWER_OR_EQUAL,->" << endl;
				//cout << strToken << endl;
				result.push_back("<$LOWER_OR_EQUAL,->\n");
				strToken = "";
			}
			else
			{
				//cout << str[i] << endl;
				//cout << "<$LOWER,->" << endl;
				result.push_back("<$LOWER,->\n");
				i++;
			}
		}
		else if ('!' == str[i])
		{
			if ('=' == str[i + 1])
			{
				i+=2;
				strToken = "!=";
				//cout << strToken<<endl;
				//cout << "<$UNEQUAL,->" << endl;
				result.push_back("<$UNEQUAL,->\n");
				strToken = "";
			}
		}
		else if ('(' == str[i])
		{
			//cout << str[i] << endl;
			//cout << "<$LPAR,->" << endl;
			result.push_back("<$LPAR,->\n");
			i++;
		}
		else if (')' == str[i])
		{
			//cout << str[i] << endl;
			//cout << "<$RPAR,->" << endl;
			result.push_back("<$RPAR,->\n");
			i++;
		}
		else if ('{' == str[i])
		{
			//cout << str[i] << endl;
			//cout << "<$LBRACE,->" << endl;
			result.push_back("<$LBRACE,->\n");
			i++;
		}
		else if ('}' == str[i])
		{
			result.push_back("<$RBRACE,->\n");
			i++;
		}
		else if ('[' == str[i])
		{
			result.push_back("<$LSQUARE_BRACKET,->\n");
			i++;
		}
		else if (']' == str[i])
		{
			result.push_back("<$RSQUARE_BRACKET,->\n");
			i++;	
		}
		else if ('\"' == str[i])
		{
			result.push_back("<$DOUBLE_QUOTE,->\n");
			i++;
		}
		else if ('\'' == str[i])
		{
			result.push_back("<$SINGLE_QUOTE,->\n");
			i++;
		}
		else if (';' == str[i])
		{
			result.push_back("<$BOUND,->\n");
			i++;
		}
		else if (',' == str[i])
		{
		//cout << str[i] << endl;
		//cout << "<$BOUND,->" << endl;
			result.push_back("<$COMMA,->\n");
			i++;
		}
		else if (' ' == str[i])
		{
			while (str[i]==' ')
			{
				i++;
			}
		}
		else
		{
			//out << "error" << endl;
			i++;
		}
	}
	return 0;
}

int main()
{
	string test;
	cout << "Please input the code(end with #):" << endl;
	while (true)
	{
		if (test[0] == '#')
			break;
		getline(cin, test);
		scanner(test);
	}
	int len = result.size();
	for (int i = 0; i < len; i++)
	{
		cout << result[i];
	}
	return 0;
}