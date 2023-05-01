#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<iostream>
#include<string>
#include<vector>
#include<QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("lexical analyzer");
}

MainWindow::~MainWindow()
{
    delete ui;
}


using namespace std;
vector<string> id_table;
vector<string> result;
QString out;

bool IsLetter(char ch)
{
    if ((ch >= 'a'&&ch <= 'z')|| (ch >= 'A'&&ch <= 'Z'))
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
                //cout << strToken << endl;
                //cout << "<$int,->" << endl;
                result.push_back("<$int,->\n");
                out.append("<$int,->\n");
            }
            else if ("void" == strToken)
            {
                //cout << strToken << endl;
                //cout << "<$void,->" << endl;
                result.push_back("<$void,->\n");
                out.append("<$void,->\n");
            }
            else if ("if" == strToken)
            {
                //cout << strToken << endl;
                //cout << "<$if,->" << endl;
                result.push_back("<$if,->\n");
                out.append("<$if,->\n");
            }
            else if ("else" == strToken)
            {
                //cout << strToken << endl;
                //cout << "<$else,->" << endl;
                result.push_back("<$else,->\n");
                out.append("<$else,->\n");
            }
            else if ("while" == strToken)
            {
                //cout << strToken << endl;
                //cout << "<$while,->" << endl;
                result.push_back("<$while,->\n");
                out.append("<$while,->\n");
            }
            else if ("return" == strToken)
            {
                //cout << strToken << endl;
                //cout << "<$return,->" << endl;
                result.push_back("<$return,->\n");
                out.append("<$return,->\n");
            }
            else if ("char" == strToken)
            {
                result.push_back("<$char,->\n");
                out.append("<$char,->\n");
            }
            else if ("const" == strToken)
            {
                result.push_back("<$const,->\n");
                out.append("<$const,->\n");
            }
            else if ("unsigned" == strToken)
            {
                result.push_back("<$unsigned,->\n");
                out.append("<$unsigned,->\n");
            }
            else if ("bool" == strToken)
            {
                result.push_back("<$bool,->\n");
                out.append("<$bool,->\n");
            }
            else if ("true" == strToken)
            {
                result.push_back("<$true,->\n");
                out.append("<$true,->\n");
            }
            else if ("false" == strToken)
            {
                result.push_back("<$false,->\n");
                out.append("<$false,->\n");
            }
else
            {
                int index=0;
                //cout << strToken << endl;
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
                //cout << "<$ID," << index << ">" << endl;
                result.push_back("<$ID,"+to_string(index)+">\n");
                out.append("<$ID,"+QString::number(index,10)+">\n");
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
            out.append("<$VALUE,"+QString::fromStdString(strToken)+">\n");
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
                out.append("<$EQUAL,->\n");
            }
            else
            {
                //cout << str[i] << endl;
                //cout << "<$ASSIGN,->" << endl;
                result.push_back("<$ASSIGN,->\n");
                out.append("<$ASSIGN,->\n");
                i++;
            }
        }
        else if ('+' == str[i])
        {
            //cout << str[i] << endl;
            //cout << "<$PLUS,->" << endl;
            result.push_back("<$PLUS,->\n");
            out.append("<$PLUS,->\n");
            i++;
        }
        else if ('-' == str[i])
        {
            //cout << str[i] << endl;
            //cout << "<$MINUS,->" << endl;
            result.push_back("<$MINUS,->\n");
            out.append("<$MINUS,->\n");
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
                out.append("<$RIGHT_COMM,->\n");
            }
            else
            {
                //cout << "<$MULT,->" << endl;
                result.push_back("<$MULT,->\n");
                out.append("<$MULT,->\n");
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
                out.append("<$LEFT_COMM,->\n");
            }
            else if ('/' == str[i + 1])
            {
                i++;
                strToken = "//";
                //cout << strToken<<endl;
                strToken = "";
                //cout << "<$LEFT_COMM,->" << endl;
                result.push_back("<$LINE_COMMENT,->\n");
                out.append("<$LINE_COMMENT,->\n");
            }
            else
            {
                //cout << str[i] << endl;
                //cout << "<$DIV,->" << endl;
                result.push_back("<$DIV,->\n");
                out.append("<$LINE_COMMENT,->\n");
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
                out.append("<$GREATER_OR_EQUAL,->\n");
                strToken = "";
            }
            else
            {
                //cout << str[i] << endl;
                //cout << "<$GREATER,->" << endl;
                result.push_back("<$GREATER,->\n");
                out.append("<$GREATER,->\n");
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
                out.append("<$LOWER_OR_EQUAL,->\n");
                strToken = "";
            }
            else
            {
                //cout << str[i] << endl;
                //cout << "<$LOWER,->" << endl;
                result.push_back("<$LOWER,->\n");
                out.append("<$LOWER,->\n");
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
                out.append("<$UNEQUAL,->\n");
                strToken = "";
            }
        }
        else if ('(' == str[i])
        {
            //cout << str[i] << endl;
            //cout << "<$LPAR,->" << endl;
            result.push_back("<$LPAR,->\n");
            out.append("<$LPAR,->\n");
            i++;
        }
        else if (')' == str[i])
        {
            //cout << str[i] << endl;
            //cout << "<$RPAR,->" << endl;
            result.push_back("<$RPAR,->\n");
            out.append("<$RPAR,->\n");
            i++;
        }
        else if ('{' == str[i])
        {
            //cout << str[i] << endl;
            //cout << "<$LBRACE,->" << endl;
            result.push_back("<$LBRACE,->\n");
            out.append("<$LBRACE,->\n");
            i++;
        }
        else if ('}' == str[i])
        {
            //cout << str[i] << endl;
            //cout << "<$RBRACE,->" << endl;
            result.push_back("<$RBRACE,->\n");
            out.append("<$RBRACE,->\n");
            i++;
        }
        else if ('[' == str[i])
        {
            result.push_back("<$LSQUARE_BRACKET,->\n");
            out.append("<$LSQUARE_BRACKET,->\n");
            i++;
        }
        else if (']' == str[i])
        {
            result.push_back("<$RSQUARE_BRACKET,->\n");
            out.append("<$RSQUARE_BRACKET,->\n");
            i++;
        }
        else if ('\"' == str[i])
        {
            result.push_back("<$DOUBLE_QUOTE,->\n");
            out.append("<$DOUBLE_QUOTE,->\n");
            i++;
        }
        else if ('\'' == str[i])
        {
            result.push_back("<$SINGLE_QUOTE,->\n");
            out.append("<$SINGLE_QUOTE,->\n");
            i++;
        }
        else if (';' == str[i])
        {
            //cout << str[i] << endl;
            //cout << "<$BOUND,->" << endl;
            result.push_back("<$BOUND,->\n");
            out.append("<$BOUND,->\n");
            i++;
        }
        else if (',' == str[i])
        {
        //cout << str[i] << endl;
        //cout << "<$BOUND,->" << endl;
            result.push_back("<$COMMA,->\n");
            out.append("<$COMMA,->\n");
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
            i++;
        }
    }
    return 0;
}


void MainWindow::on_pushButton_3_clicked()
{
    QString input=ui->plainTextEdit->toPlainText();
    qDebug()<<input;
    string s_input=input.toStdString();
    scanner(s_input);
    string s_output;
    ui->textBrowser->setText(out);
}
