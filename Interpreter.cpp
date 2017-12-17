/*
   This code can be compiled and run ok.
    Goal: The goal of this part of the project is to
    implement a Tokenizer for the language Core.
    (1~11) Reserved words (11 reserved words):
        program, begin, end, int, if, then,
        else, while, loop, read, write
    (12~30) Special symbols (19 special symbols):
        ; , = ! [ ] && || ( ) + - * != == < > <= >=
    (31) Integers (unsigned) (max size of 8 digits).
        ex. 25;
    (32) Identifiers:
        ex. X,Y,z;
    (33) for end-of-life
        EOF
   usage (how to run):
     g++ -o test Tokenizer.cpp coreProgram.txt inputData.txt

   input file:
     coreProgram.txt inputData.txt

   output files:
     none

   compile (how to compile):
     g++ -o test Interpreter.cpp coreProgram.txt InputData.txt
     ./test

   coded by Su, Ming Yi, OSU_ID: su.672, email: su.672@osu.edu
   date: 2017.10.29
   LinkedList is learnt from website:
   https://github.com/alrightchiu/SecondRound/blob/master/content/Algorithms%20and%20Data%20Structures/BasicDataStructures/ExampleCode/LinkedList.cpp

*/
/*
    If I do it by Object Oriented method.
    Do not need to ParseTree class
    my tokenizer should have
    getToken: return (info about) current token.
    skipToken: skips current token.
    intVal: returns the value of the current (integer) token.
    idName: returns the name (string) of the current (id)token.

*/
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdlib.h>
using namespace std;

class Prog; class DS; class SS;
class DECL; class IDLIST; class Stmt;
class Assign; class IF; class Loop;
class Input; class Output; class Cond;
class Comp; class Exp; class Fac; class Op;
class ID;

struct id_table{
    string name;
    int value;
    bool declared;
    bool initialized;
};

id_table *idtable= new id_table [50];
int id_table_label =0;
const string token[30]= {
        "program", "begin", "end", "int",
        "if", "then", "else", "while", "loop",
        "read","write",
        ";", ",", "=", "!", "[", "]", "&&",
        "||", "(", ")", "+", "-", "*", "!=",
        "==", "<", ">", "<=", ">="
};
const char uppercase_letter[26]={
        'A','B','C','D','E',
        'F','G','H','I','J',
        'K','L','M','N','O',
        'P','Q','R','S','T',
        'U','V','W','X','Y','Z'
};
int int_stream[1000]={0};
int int_stream_label =0;
int int_use_label =0;
int int_print_label =0;
string id_stream[1000];
int id_stream_label =0;
int id_use_label = 0;
int id_print_label =0;
int idtable_use_label=0;
int *read_int = new int [1000];
int read_int_label =0;
int between_id_number =0;
int between_int_number =0;
int between_id_number_b =0;
int between_int_number_b =0;
class LinkedList;
// In order to set class LinkedList to friend of class ListNode
// need to declare class LinkedList first.
//class Prog, DS, SS, If;
class ListNode{
private:
    int data;
    ListNode *next;
public:
    ListNode():data(0), next(0){};
    ListNode(int a):data(a),next(0){};

    friend class LinkedList;
};


class LinkedList{
private:
    // first node of list
    ListNode *first;
    // PrintList : print all data in list
    // Push_back : add new node at the end of list
public:
    LinkedList():first(0){};
    void PrintList();
    void Push_back( int x);
    int getToken();
    void skipToken();
    int idnumber(int x, int y);
    int intnumber(int x, int y);
};

LinkedList mytokenizer;
void LinkedList::PrintList(){
    // if first node point at NIL, it means there is no data in list.
    if (first == 0) {
        cout <<"List is empty."<<endl;
        return;
    }
    // Use pointer *current to move in the list
    // Traversal
    ListNode *current = first;
    while (current != 0){
        cout << current->data<< " ";
        current = current->next;
    }
    cout <<endl;
}

void LinkedList::Push_back(int x){
    // allocate new memory
    ListNode *newNode = new ListNode(x);
    // if there is no node in list,
    // let newNode be first
    if (first == 0){
        first = newNode;
        return;
    }
    ListNode *current = first;
    // Traversal
    while (current->next != 0) {
        current = current->next;
    }
    // let newNode connect at the end of the list
    current->next = newNode;

}

int LinkedList::getToken(){
    // if first node point at NIL, it means there is no data in list.
    if (first == 0) {
        cout <<"List is empty."<<endl;
    }
    // Use pointer *current to move in the list
    // Traversal
    ListNode *current = first;
    int current_token = current->data;
    return current_token;
}

int LinkedList::idnumber(int x, int y){
    // if first node point at NIL, it means there is no data in list.
    if (first == 0) {
        cout <<"List is empty."<<endl;
    }
    int id_number =0;
    ListNode *current = first;
    // Traversal
    while (current->data != x) {
        current = current->next;
    }
    while(current->data!=y){
        current = current->next;
        if(current->data==32){
        id_number++;
        }
    }
    return id_number;
}

int LinkedList::intnumber(int x, int y){
    // if first node point at NIL, it means there is no data in list.
    if (first == 0) {
        cout <<"List is empty."<<endl;
    }
    int int_number =0;
    ListNode *current = first;
    // Traversal
    while (current->data != x) {
        current = current->next;
    }
    while(current->data!=y){
        current = current->next;
        if(current->data==31){
        int_number++;
        }
    }
    return int_number;
}

void LinkedList::skipToken(){
    ListNode *current = first;
    // Traversal
    first = current->next;
}

int intVal(int tokNo, int &int_use_label){
    if(tokNo==31){
        int current_int = int_stream[int_use_label];
        int_use_label++;
        return current_int;
    }
}
string idName( int &id_use_label){
        string current_string = id_stream[id_print_label];
        return current_string;
}

void token_check_int_id (string &x, LinkedList&mytokenizer,int &number){
    // Integers
    char number_char[] = {'0','1','2',
                        '3','4','5',
                        '6','7','8','9'};
    int key1 =0;
    int i, j;
    for(i = 0; i<x.size();i++){
        for(j=0;j<9;j++){
            if(x[i]==number_char[j]){
                key1++;
            }
        }
    }
    char *fff;
    fff= new char [x.size()];
    int value2[x.size()];
    for(i = 0; i < x.size(); i++) {
                fff[i]=x[i];
    }
    int value =atoi (fff);
    if((value >0||value<0)&&key1==(x.size())){

                mytokenizer.Push_back(31); number =1;

                int_stream[int_stream_label]=value;
                int_stream_label++;
    }
    if(x=="0"){
                mytokenizer.Push_back(31);number =1;
                int_stream[int_stream_label]=value;
                int_stream_label++;
    }
    //Identifiers
    int key=0,letter_value=0,key2=0;
    for (i=0;i<26;i++){
        if(fff[0]==uppercase_letter[i]){
        key2=1;
        }
        for (j=0; j<x.size();j++){
                if(fff[j]==uppercase_letter[i]){
                    key++;
                }
        }
    }
    for(j=0;j<x.size();j++){
    letter_value = fff[j]-'0';
        if(letter_value>=0&&letter_value<10){
                    key++;
        }
    }
    if (key==x.size()&&(key2==1)){
        mytokenizer.Push_back(32);number =1;
        id_stream[id_stream_label] = x;
        id_stream_label++;
    }
    if ((key!=x.size())&&(number==0)){
      //  cout <<x<<" is illegal."<<endl;
    }
}


int token_check(string &x, LinkedList&mytokenizer,int &number){
    int token_length[30]={0};
    number =0;
    for(int i =0;i<30;i++){
        token_length[i]= token[i].size();
    }
    int i=0,j=0;
            // number is the controller that my identifiers won't
            // bother my other staff
            for(i =0;i<30;i++){
                if(x==token[i]){
                    mytokenizer.Push_back(i+1);number =1;
                }
            }
    token_check_int_id (x,mytokenizer,number);
    //solve the problem that "ABC;" is illegal
    // it should be "ABC" and ";"
    string x_part1,x_part2;
    int k1=0,k2=0,part1=0,part2=0;
            int x_length= x.size();
            if(number==0){
                    if(x_length>1){
                        for(i = 1;i<x_length;i++){
                            x_part1 = x_part1.assign (x,0,i);
                            x_part2 = x_part2.assign (x,i,x_length-i);
                            int part1=0,part2=0,k1,k2;
                            for(j=0;j<30;j++){
                                if(x_part1==token[j]){
                                    part1=1;
                                    k1 = j+1;
                                }
                                if(x_part2==token[j]){
                                    part2=1;
                                    k2 = j+1;
                                }
                            }
                            if ((part1==1)&&(part2==1)){
                                    mytokenizer.Push_back(k1);
                                    mytokenizer.Push_back(k2);
                                    number =1;
                            }
                        }
                    }
            }
        if((number==0)&&(x_length>1)&&(part1+part2<2)){
            string x_part, x_rest, x_rest2;
            int key=0;
            for(i = 0;i<x_length;i++){
                for (j=0;j<30;j++){
                    x_part = x_part.assign (x, i,token_length[j]);
                    if(x_part==token[j] && key==0 ){
                        key=1;
                        if(i==0){
                        x_rest = x_rest.assign (x, token_length[j],x_length-token_length[j]);
                        mytokenizer.Push_back(j+1);
                        token_check(x_rest,mytokenizer,number);
                        }
                        if(i!=0){
                        x_rest = x_rest.assign (x, 0, i);
                        if(x_length!=i+token_length[j]){
                            x_rest2 = x_rest2.assign(x, i+token_length[j],x_length-i-token_length[j]);
                        }
                        token_check(x_rest,mytokenizer,number);
                        mytokenizer.Push_back(j+1);
                        if(x_length!=i+token_length[j]){
                            token_check(x_rest2,mytokenizer,number);
                        }

                        }
                    }
                }
            }
        }
    return(number);
}
/////////////////////////////////////////////////////////////
// Parser, Printer, Executer

class ID{

public:
    void ParseID(){
        int tokNo;
        tokNo = mytokenizer.getToken();
        mytokenizer.skipToken();
    };
    void PrintID(){
        cout <<id_stream[id_print_label];
        id_print_label++;
    };
    void ExecID(){
        // for declaration part
        string idname = id_stream[id_use_label];
        int i; int key=0;
        for(i=0;i<=id_table_label;i++){
            if(idname ==idtable[i].name){
                key++;
            }
        }
        if(key==0){
            idtable[id_table_label].name = idname;
            idtable[id_table_label].declared = true;
            id_table_label++;
        }
        id_use_label++;
    };
};
class IDLIST{
private:
    ID *id; IDLIST *idlist;int altNo;
public:
    IDLIST(){id=0;idlist=0;}
    void ParseIDLIST(){
        int tokNo;
        id = new ID();
        id->ParseID();
        tokNo = mytokenizer.getToken();
        if( tokNo== 13){
            altNo = 2;
            mytokenizer.skipToken();
            idlist = new IDLIST();
            idlist->ParseIDLIST();
        }
    };
    void PrintIDLIST(){
        id->PrintID();
        if(altNo==2){
            cout<<", ";
            idlist->PrintIDLIST();
        }
    };
    void ExecIDLIST(){
        id->ExecID();
        if(altNo==2){ idlist->ExecIDLIST();}
    }
};

class DECL{
private:
    IDLIST *idlist;
public:
    DECL(){idlist=0;}
    void ParseDECL(){
        mytokenizer.skipToken();
        idlist = new IDLIST();

        idlist->ParseIDLIST();

        mytokenizer.skipToken();
    };
    void PrintDECL(){
        cout <<"int ";idlist->PrintIDLIST();
        cout <<";"<<endl;
    }
    void ExecDECL(){
        idlist->ExecIDLIST();
    };

};

class DS{
private:
    DECL *decl; DS *ds; int altNo;
public:
    DS(){ decl=0;}
    void ParseDS(){
        decl = new DECL(); decl->ParseDECL();
        int tokNo;
        tokNo = mytokenizer.getToken();
        if(tokNo==4){
            altNo=2;
            ds = new DS(); ds->ParseDS();
        }
    };
    void PrintDS(){
        decl->PrintDECL();
        if(altNo==2){ ds->PrintDS();}
    };
    void ExecDS(){
        decl->ExecDECL();
        if(altNo==2){ ds->ExecDS();}
    };
};
//////////////////////////////////////////////////////////

class SS{
private:
    Stmt *stmt; SS *ss; int altNo;
public:
    SS(){ stmt=0;ss=0;}
    void ParseSS();
    void PrintSS();
    void ExecSS();
};


////////////////////////////////////////////////

class Op{
private:
    int a; ID *id; Exp*exp; int altNo;
public:
    Op(){a=0;id=0;exp=0;}
    void parseOp(){
        int tokNo;
        tokNo = mytokenizer.getToken();
        if (tokNo==31){
            altNo=1;mytokenizer.skipToken();
        }
        if (tokNo==32){
            altNo=2; id =new ID();
            id->ParseID();
        }
        tokNo = mytokenizer.getToken();
    };
    void printOp(){
        if(altNo==1){
            cout<<int_stream[int_print_label];
            int_print_label++;
        }
        if(altNo==2){ id->PrintID();}
    };
    int execOp(){
        int x;
        if(altNo==1){
            x = int_stream[int_use_label];
            int_use_label++;
        }
        if(altNo==2){
            string idname = id_stream[id_use_label];
            int i;
            for(i=0; i<30;i++){
                if(idname==idtable[i].name){
                    x = idtable[i].value;
                }
            }
            id_use_label++;
        }
        return x;
    };
};

class Fac{
private:
    Op *op; Fac *fac; int altNo;
public:
    Fac(){op=0;fac=0;}
    void parseFac(){
        op = new Op(); op->parseOp();
        int tokNo;
        tokNo = mytokenizer.getToken();
        if(tokNo==24){
            altNo=2;
            mytokenizer.skipToken();
            fac = new Fac(); fac->parseFac();
        }
    }
    void printFac(){
        op->printOp();
        if(altNo==2){ fac->printFac();}
    }
    int execFac(){
        int x = op->execOp();
        if(altNo==2){ x= x*fac->execFac();}
        return x;
    }
};


class Comp{
private:
    Op *op1; Op *op2; int altNo;
public:
    Comp(){op1=0;op2=0;}
    void parseComp(){
        op1 = new Op();
        op1->parseOp();
        int tokNo;
        tokNo = mytokenizer.getToken();
        // this token should be one of
        // !=, ==, <, >, <=, >=
        if( tokNo ==25){ altNo = 1;} // !=
        if( tokNo ==26){ altNo = 2;} // ==
        if( tokNo ==27){ altNo = 3;} // <
        if( tokNo ==28){ altNo = 4;} // >
        if( tokNo ==29){ altNo = 5;} // <=
        if( tokNo ==30){ altNo = 6;} // >=
        mytokenizer.skipToken();
        op2 = new Op();
        op2->parseOp();
    };
    void printComp(){
        op1->printOp();
        if(altNo==1){ cout<<"!=";}
        if(altNo==2){ cout<<"==";}
        if(altNo==3){ cout<<"<";}
        if(altNo==4){ cout<<">";}
        if(altNo==5){ cout<<"<=";}
        if(altNo==6){ cout<<">=";}
        op2->printOp();
    };
    bool execComp(){
        bool x;
        int a = op1->execOp();
        int b = op2->execOp();
        if(altNo==1){
            if(a!=b){ x = true;}
        }
        if(altNo==2){
            if(a==b){ x = true;}
        }
        if(altNo==3){
            if(a<b){ x = true;}
        }
        if(altNo==4){
            if(a>b){ x = true;}
        }
        if(altNo==5){
            if(a<=b){ x = true;}
        }
        if(altNo==6){
            if(a>=b){ x = true;}
        }
        return x;
    };

};

class Cond{
private:
    int altNo; Comp *comp;Cond *cond1; Cond *cond2;
public:
    Cond(){
    };
    void parseCond(){
        int tokNo;
        tokNo = mytokenizer.getToken();

        // case1: <comp> ex. X > 0
        if(tokNo==31||tokNo==32){
            altNo=1; comp = new Comp();
            comp->parseComp();
        }
        // case2: !<cond>
        if(tokNo==15){
            mytokenizer.skipToken(); // skip !
            altNo=2; cond1 = new Cond();
            cond1->parseCond();
        }
        // case3: <cond> && <cond>
        // case4: <cond> || <cond>
        /*
        if(tokNo==18){
            mytokenizer.skipToken(); // skip &&
            altNo=3; con
        }
        */
    };
    void printCond(){
        if(altNo==1){ comp->printComp();}
        if(altNo==2){
            cout<<"!";
            comp->printComp();
        }
    };
    bool EvalCond(){
        bool x = comp->execComp();
        //cout<<"after Cond"<<endl;
        //cout<<"id_use_label: "<<id_use_label<<endl;
        return x;
    };
};

class Exp{
private:
    int altNo; Fac *fac; Exp *exp;
public:
    Exp(){ fac=0; exp=0;};
    void ParseExp(){
        fac = new Fac(); fac->parseFac();
        int tokNo;
        tokNo = mytokenizer.getToken();
        if(tokNo == 22){
            mytokenizer.skipToken(); // skip +
            altNo =2; exp = new Exp();
            exp->ParseExp();
        }
        if(tokNo == 23){
            mytokenizer.skipToken(); // skip -
            altNo =3; exp = new Exp();
            exp->ParseExp();
        }
    };
    void PrinExp(){
        fac->printFac();
        if(altNo ==2){ cout<<"+";exp->PrinExp();}
        if(altNo ==3){ cout<<"-";exp->PrinExp();}
    };
    int ExecExp(){
        int x;
        x = fac->execFac();
        if(altNo ==2){ x = x + exp->ExecExp();}
        if(altNo ==3){ x = x - exp->ExecExp();}
        return x;
    };
};

class Assign{
private:
    ID *id; Exp*exp;
public:
    Assign(){ id =0; exp=0;}
    void parseAssign(){
        int tokNo;
        id = new ID(), id->ParseID();
        mytokenizer.skipToken(); // for token "="
        exp = new Exp(); exp->ParseExp();
        mytokenizer.skipToken(); // skip ;
        tokNo = mytokenizer.getToken();
    }
    void printAssign(){
        id->PrintID();cout<<"=";
        exp->PrinExp();cout<<";"<<'\n'<<"  ";
    }
    void execAssign(){
        //id->ExecID();
        //exp->ExecExp();
        string idname = id_stream[id_use_label];
        id_use_label++;
        int x = exp->ExecExp();
        int i;
        for(i=0;i<30;i++){
            if(idname==idtable[i].name){
                idtable[i].value=x;
            }
        }
    };
};
class IF{
private:
    Cond *c; SS*ss1; SS*ss2; int altNo;
public:
    IF(){ c=0; ss1=0; ss2=0;}
    // IF has two case
    // 1. if <cond> then <ss> end;
    // 2. if <cond> then <ss> else <ss> end;
    void parseIF(){
        int tokNo;
        between_id_number = mytokenizer.idnumber(6,7);
        between_id_number_b = mytokenizer.idnumber(7,3);
        between_int_number = mytokenizer.intnumber(6,7);
        between_int_number_b = mytokenizer.intnumber(7,3);
        mytokenizer.skipToken(); // skip if
        mytokenizer.skipToken(); // skip (
        tokNo = mytokenizer.getToken();
        c = new Cond(); c->parseCond();
        mytokenizer.skipToken(); // skip )
        mytokenizer.skipToken(); // skip then
        tokNo=mytokenizer.getToken();
        ss1 = new SS(); ss1->ParseSS();
        tokNo = mytokenizer.getToken();
        if(tokNo==3){
            altNo=1;
            mytokenizer.skipToken();
            mytokenizer.skipToken();return;
        }
        if(tokNo==7){
            altNo=2;
            mytokenizer.skipToken(); // skip 7
            ss2 = new SS(); ss2->ParseSS();
            mytokenizer.skipToken();
            mytokenizer.skipToken();return;
        }
    }
    void printIF(){
        cout <<"if  ("; c->printCond();cout<<") then "<<endl;
        cout<<"     ";
        ss1->PrintSS();
        if(ss2==0){
            cout <<" end;"<<endl;
        }
        if(ss2!=0){
            cout<<"  else "<<endl;
            cout<<"     ";
            ss2->PrintSS();
            cout<<" end;"<<endl;
        }
    }
    void execIF(){
        cout <<" ";
        bool b = c->EvalCond();

        if(b){
            ss1->ExecSS();
            id_use_label = id_use_label+between_id_number_b;
            int_use_label = int_use_label+between_int_number_b;
            return;
        }
        else{
            id_use_label= id_use_label+between_id_number;
            int_use_label = int_use_label+between_int_number;
            // I added this 3 by human hand
            if(altNo==2){
                ss2->ExecSS();return;
            }
        }

    }
};

class Loop{
private:
    Cond *c; SS *ss;
public:
    Loop(){ c=0; ss=0;}
    void parseLoop(){
        int tokNo;
        tokNo = mytokenizer.getToken();
        mytokenizer.skipToken(); // skip while
        mytokenizer.skipToken(); // skip (
        c = new Cond(); c->parseCond();
        mytokenizer.skipToken(); // skip )
        tokNo = mytokenizer.getToken();
        mytokenizer.skipToken(); // skip loop
        ss = new SS(); ss->ParseSS();
        mytokenizer.skipToken();
        mytokenizer.skipToken();

    };
    void printLoop(){
        cout<<"while (";c->printCond();
        cout<<")"<<'\n'<<"   ";
        cout<<"loop "<<'\n'<<"    ";ss->PrintSS();
        cout<<"  end;"<<'\n'<<"  ";
    };
    void execLoop(){
        int origin_id_label ;int origin_int_label;
        origin_id_label = id_use_label;
        origin_int_label = int_use_label;
        //bool x = c->EvalCond();
        int after_id_label; int after_int_label;
        while(c->EvalCond()){
                ss->ExecSS();
                after_id_label = id_use_label;
                after_int_label = int_use_label;
                id_use_label = origin_id_label;
                int_use_label = origin_int_label;
        }
        id_use_label = after_id_label;
        int_use_label = after_int_label;
    };
};

class Input{
private:
    IDLIST *idlist;
public:
    Input(){ idlist = 0;};
    void parseInput(){
        mytokenizer.skipToken();
        // skip token: read
        // Now we are at token 32(id)
        int tokNo;
        tokNo = mytokenizer.getToken();
        idlist = new IDLIST();
        idlist->ParseIDLIST();
        mytokenizer.skipToken();
        tokNo = mytokenizer.getToken();
    };
    void printInput(){
        cout<<"read ";idlist->PrintIDLIST();
        cout<<";"<<'\n'<<"  ";
    };
    void execInput(){
        //idlist->ExecIDLIST();
        string idname =id_stream[id_use_label];
        int i; int label;
        for(i=0;i<id_table_label;i++){
            if(idname==idtable[i].name){
                idtable[i].value = read_int[read_int_label];
                read_int_label++;
            }
        }
        id_use_label++;
    }
};

class Output{
private:
    IDLIST *idlist;
public:
    Output(){
        idlist=0;
    }
    void parseOutput(){
        int tokNo;
        tokNo = mytokenizer.getToken();
        mytokenizer.skipToken();// skip token write
        idlist = new IDLIST();
        idlist->ParseIDLIST();
        tokNo = mytokenizer.getToken();
        mytokenizer.skipToken(); // skip token ;
        tokNo = mytokenizer.getToken();
    }
    void printOutput(){
        cout<<"write ";
        idlist->PrintIDLIST();
        cout<<";"<<'\n'<<"  ";
    }
    void execOutput(){
        string idname = id_stream[id_use_label];
        int i;
        for(i=0;i<30;i++){
            if(idname==idtable[i].name){
                cout<<idname<<" = "<<idtable[i].value<<endl;
            }
        }
        id_use_label++;
    }
};

class Stmt{
private:
int altNo; Assign*s1; IF *s2; Loop *s3; Input *s4; Output *s5;
public:
    Stmt(){altNo=0, s1=0,s2=0, s3=0, s4=0,s5=0;}
    void ParseStmt(){
        int tokNo;
        tokNo = mytokenizer.getToken();
        if(tokNo== 32){ altNo=1; s1 = new Assign(); s1->parseAssign();}
        if(tokNo== 5){ altNo=2; s2 = new IF(); s2->parseIF();}
        if(tokNo== 8){ altNo=3, s3 = new Loop(); s3->parseLoop();}
        if(tokNo== 10){ altNo=4, s4 = new Input(); s4->parseInput();}
        if(tokNo== 11){ altNo=5; s5 = new Output(); s5-> parseOutput();}
    };
    void PrintStmt(){
        if(altNo==1){; s1->printAssign();return;}
        if(altNo==2){; s2->printIF();return;}
        if(altNo==3){; s3->printLoop();return;}
        if(altNo==4){; s4->printInput();return;}
        if(altNo==5){; s5->printOutput();return;} };
    void ExecStmt(){
        if(altNo==1){; s1->execAssign();return;}
        if(altNo==2){; s2->execIF();return;}
        if(altNo==3){; s3->execLoop();return;}
        if(altNo==4){; s4->execInput();return;}
        if(altNo==5){; s5->execOutput();return;}
    };
};
//////////////////////////////////////////////////////////

void SS::ParseSS(){
       int tokNo;
       stmt = new Stmt(); stmt->ParseStmt();
       tokNo = mytokenizer.getToken();
       if(tokNo==7){
            //mytokenizer.skipToken();
       }
       if(tokNo==32||tokNo==5||tokNo==8||
          tokNo==10||tokNo==11){
            altNo=2;ss = new SS(); ss->ParseSS();
       }
};
void SS::PrintSS(){
        stmt->PrintStmt();
        if(altNo==2){ ss->PrintSS();}
};
void SS::ExecSS(){
        stmt->ExecStmt();
        if(altNo==2){ss->ExecSS();}
};

///////////////////////////////////////////////////////////

class Prog{
private:
    DS *ds; SS *ss;
public:
    Prog(){ ds =0, ss=0;}
    void ParseProg(){
        int tokNo;
        tokNo = mytokenizer.getToken();
        if(tokNo!=1){
            cout<<"error: this token should be program."<<endl;
        }
        mytokenizer.skipToken();
        ds = new DS(); ds->ParseDS();
        tokNo = mytokenizer.getToken();
        if(tokNo!=2){
            cout<<"error: this token should be begin."<<endl;
        }
        mytokenizer.skipToken();
        ss = new SS(); ss->ParseSS();
        tokNo = mytokenizer.getToken();
        if(tokNo!=3){
            cout<<"error: this token should be end."<<endl;
        }
        mytokenizer.skipToken();mytokenizer.skipToken();
    }
    void PrintProg(){
        cout<<"program"<<'\n'<<" ";ds->PrintDS();
        cout<<" begin"<<'\n'<<"  ";ss->PrintSS();
        cout<<"end"<<endl;
    }
    void ExecProg(){
       ds->ExecDS();
       ss->ExecSS();
    }
};

int main(int argc, char* argv[]){
    // int argc, char* argv[]
    // argc = the number of the command line = 3
    // argv[0] = ./test
    // argv[1] = coreProgram.txt
    // argv[2] = inputData.txt
    ifstream file;
    // method 1
    //file.open( "coreProgram.txt");
    // method 2
    char* filename = argv[1];
    file.open( filename );
    // method 3
    //string filename;
    //cin>> filename;
    //file.open(filename.c_str());

    string x;
    while (file >>x){
            // Reserved words
            int number =0;
            number = token_check(x, mytokenizer, number);
    }
    file.close();
    // read inputData.txt file
    ifstream file2;
    int i=0;

    // method 1
    //file2.open("inputData.txt");
    // method 2
    char *filename2 = argv[2];
    file2.open( filename2 );
    // method3
    //string filename2;
    //cin>> filename2;
    //file.open(filename2.c_str());


    while (file2>> read_int[i]){
        i++;
    }
    // EOF (for end-of-file)
    mytokenizer.Push_back(33);
    // print out all the token
    cout <<"Output:"<<endl;
    mytokenizer.PrintList();
    Prog program;
    program.ParseProg();
    for(i=0;i<id_stream_label;i++){
        cout<<" ";
    }
    cout<<endl;
    cout<<"Pretty print version of the "
        <<"Core Program "<<endl;
    program.PrintProg();
    cout<<'\n'<<"set of output"<<endl;
    program.ExecProg();

    return 0;
}
