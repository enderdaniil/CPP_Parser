#include <stdlib.h>
#include <iomanip>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <string>

#define _CRT_SECURE_NO_WARNINGS;

using namespace std;

class FloatStack
{
protected:
    float* Values;
    int Size;
    int Top;

public:
    FloatStack() : Size(10)
    {
        Top = -1;
        Values = new float[Size];
    }

    FloatStack(int s) : Size(s)
    {
        Top = -1;
        Values = new float[Size];
    }

    void Push(float number)
    {
        Top++;
        Values[Top] = number;
    }

    float Pop()
    {
        return Values[Top];
        Top--;
    }
};

class Token {

public:

    virtual float GetNumber() = 0;

    virtual char GetOperator() = 0;

};

class Operator : public Token {

private:

    char oper;

public:

    Operator(char);

    char GetOperator() override;

    float GetNumber() override;

};

Operator::Operator(char c)
{
    oper = c;
}

char Operator::GetOperator()
{
    return oper;
}

float Operator::GetNumber()
{
    return NULL;
}



class Number : public Token {
private:
    float fnum;

public:

    Number(float);

    float GetNumber() override;

    char GetOperator() override;

};

Number::Number(float value)
{
    fnum = value;
}

float Number::GetNumber()
{
    return fnum;
}

char Number::GetOperator()
{
    return NULL;
}

class TokenStack
{
protected:
    Token **Values;
    int Size;
    int Top;

    bool Find(char c, string s)
    {
        bool result = false;
        for (int i = 0; i < s.length(); i++)
        {
            if (c == s[i])
            {
                result = true;
            }
        }
        return result;
    }

    float mstold(string s)
    {
        float value;
        string digits = "0123456789";
        string StringValue;
        int dot;
        for (int i = 0; i < s.length(); i++)
        {
            char c = s[i];
            if (Find(c, digits))
            {
                StringValue.push_back(c);
            }
            else
            {
                dot = i;
            }
        }

        char* numbersCh = new char[StringValue.length() + 1];
        strncpy(numbersCh, StringValue.c_str(), StringValue.length());

        value = atof(numbersCh);
        value /= pow(10, dot);
        return value;
    }

    int FindAmountOfFloats()
    {
        int AmountOfFloats = 0;
        for (int i = 0; i < Top; i++)
        {
            if (Values[i]->GetOperator != NULL)
            {
                AmountOfFloats++;
            }
        }
        return ++AmountOfFloats;
        
    }

public:
    TokenStack() : Size(70)
    {
        Top = -1;
        Values = new Token*[Size];
    }

    TokenStack(int s) : Size(s)
    {
        Top = -1;
        Values = new Token*[Size];
    }

    void Push(Token* number)
    {
        Top++;
        Values[Top] = number;
    }

    Token* Pop()
    {
        return Values[Top];
        Top--;
    }

    float GetResultOfTheOperation()
    {
        int AmountOfFloats = FindAmountOfFloats();
        float *NumberArray = new float[AmountOfFloats];

        int i = 0;
        int j = 0;
        string CurrentFloat;
        while (i < Top)
        {
            if (Values[i]->GetNumber != NULL)
            {
                CurrentFloat.append(Values[i]->GetNumber);
            }
            else
            {
                NumberArray[i] = mstold(CurrentFloat);
                CurrentFloat = "";
            }

            i++;
        }
    }

};

int main()
{
    setlocale(LC_ALL, "Russian");

    Number a(5);
    cout << a.GetOperator();

    return 0;
}
