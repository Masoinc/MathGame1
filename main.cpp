#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <time.h>

#include "linkNode.h"
using namespace std;

unsigned long int stage[12];

struct sNode
{
    int P1_LH,P1_RH;
    int P2_LH,P2_RH;
    int sindex;
    string scheme;
};

vector<sNode> TestReadin;

void SetNextStage(int index, int hands, int round)
{
    if(round==0)
    {
        for(int i=0;i< 12;i++)
            stage[i]=1;

        return;
    }

    for(int i=index; i<12; i++)
    {
        stage[i]+=pow(hands,round);

    }

    return;

}

sNode StructCpy(const sNode Input)
{
    return Input;
}

int checkbreak(sNode checked)
{
    if(checked.P1_LH==NULL)
        return 1;
    else if (checked.P1_RH==NULL)
        return 1;
    else if (checked.P2_LH==NULL)
        return 2;
    else if (checked.P2_RH==NULL)
        return 2;
    else
        return 0;

}

void vCalc_initialization(vector<sNode> *_Dst, sNode _sValue)
{
    const int MaxCase=4;

    for(int counter=NULL; counter<MaxCase;counter++)
        _Dst->push_back(_sValue);

    return;
}

void vCalc_vectorCpy(vector<sNode> _Source, vector<sNode> *_Dst)
{

    for(int index=NULL; index<_Source.size(); index++)
        _Dst->push_back(_Source[index]);

    return;
}

int vCalc_HandValueAdd(const int _HandA, const int _HandB)
{
    const int lead=10;

    if(_HandA + _HandB == lead)
        return NULL;

    else
        return _HandA+_HandB;

}

void CalcNextRound(const sNode Input,int  round)
{
    const int caseSkip=-1;
    const int p1Turn=0;
    const int p2Turn=1;
    const int tklead=2;
    const int MaxSize=4;

    string Ll="Ll,";
    string Lr="Lr,";
    string Rl="Rl,";
    string Rr="Rr,";

    string lL="lR,";
    string lR="lR,";
    string rL="rL,";
    string rR="rR,";

    vector<sNode> CalcResult;

    sNode Pushin=StructCpy(Input);
    sNode Skip={caseSkip,caseSkip,caseSkip,caseSkip};

    vCalc_initialization(&CalcResult,Input);

    if(checkbreak(Input)==tklead || Input.P1_LH == caseSkip)
    {
        for(int i=0;i<4;i++)
            TestReadin.push_back(Skip);

        return;
    }

    if(round == p1Turn) {

        CalcResult[0].P1_LH = vCalc_HandValueAdd(CalcResult[0].P1_LH, CalcResult[0].P2_LH);
        CalcResult[1].P1_LH = vCalc_HandValueAdd(CalcResult[1].P1_LH, CalcResult[1].P2_RH);
        CalcResult[2].P1_RH = vCalc_HandValueAdd(CalcResult[2].P1_RH, CalcResult[2].P2_LH);
        CalcResult[3].P1_RH = vCalc_HandValueAdd(CalcResult[3].P1_RH, CalcResult[3].P2_RH);

        CalcResult[0].scheme+=Ll;
        CalcResult[1].scheme+=Lr;
        CalcResult[2].scheme+=Rl;
        CalcResult[3].scheme+=Rr;
    }
    else {

        CalcResult[0].P2_LH=vCalc_HandValueAdd(CalcResult[0].P1_LH,CalcResult[0].P2_LH);
        CalcResult[1].P2_LH=vCalc_HandValueAdd(CalcResult[1].P1_RH,CalcResult[1].P2_LH);
        CalcResult[2].P2_RH=vCalc_HandValueAdd(CalcResult[2].P1_LH,CalcResult[2].P2_RH);
        CalcResult[3].P2_RH=vCalc_HandValueAdd(CalcResult[3].P1_RH,CalcResult[3].P2_RH);

        CalcResult[0].scheme+=lL;
        CalcResult[1].scheme+=lR;
        CalcResult[2].scheme+=rL;
        CalcResult[3].scheme+=rR;
    }

    CalcResult[0].sindex++;
    CalcResult[1].sindex++;
    CalcResult[2].sindex++;
    CalcResult[3].sindex++;

    vCalc_vectorCpy(CalcResult,&TestReadin);
    return;

}

void SchemeProcess(LinkList *_Scheme, Info _Insert)
{
    int index=_Scheme->Length();
    _Scheme->Insert(_Insert,index);
}

int checkSolo(int P1Hand,int P2Hand)
{
    const int Max_NonWin=64;
    int turn=0;

    for(int i=0;i<Max_NonWin; i++)
    {
        if(turn==0) {

            P1Hand+=P2Hand;
            turn=1;
        }
        else {

            P2Hand+=P1Hand;
            turn=0;
        }

        if(P1Hand==10)
            return 1;

        else if (P2Hand==10)
            return 0;

    }
    return -1;
}

void checkChange(void)
{

}
int main(void)
{
    LinkList Scheme;
    Info val1,val2,val3;

    sNode a,b;
    a={1,1,1,1};
    a.sindex=0;

    TestReadin.push_back(a);

    unsigned int nodes=0;
    const int hands=4;

    clock_t start = clock();

    for(int round=0;round<12;round++)
        SetNextStage(round,hands,round);

    int i,rT,r=0;

    for(i=0,rT=0; checkbreak(TestReadin[i])!=1 ; i++)
    {

        CalcNextRound(TestReadin[i],r);

        if(i+1 == stage[rT])
        {
            if(r == 1)
                r=0;
            else
                r=1;

            rT++;
        }
    }

    cout << r << endl;

    cout << i << endl;

    val1.scheme="test1";
    val2.scheme="test2";
    val3.scheme="test3";

    //当前游戏信息

    cout << TestReadin[i].P1_LH << TestReadin[i].P1_RH << endl;
    cout << TestReadin[i].P2_LH << TestReadin[i].P2_RH << endl;

    //领先路径
    cout << TestReadin[i].scheme << endl;

    clock_t ends = clock();


    cout << "链表插入测试" << endl;

    cout << Scheme.Length() << endl;
    SchemeProcess(&Scheme, val1);
    SchemeProcess(&Scheme, val2);
    SchemeProcess(&Scheme, val3);

    cout << Scheme.getval() << endl;

    Scheme.Reverse();
    cout << Scheme.getval() << endl;

    Scheme.Remove(val3);
    cout << Scheme.getval() << endl;


    cout << checkSolo(2,1) << endl;

    cout <<"Running Time : "<<(double)(ends - start)/ CLOCKS_PER_SEC << endl;
    cout << "testsuccess" << endl;


    return 0;
}

