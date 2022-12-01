/* Definitions and some functions implementations
 * parse.cpp to be completed
 * Programming Assignment 2
 * Spring 2022
 * 
 * 
   WHEN FINISHED TRY TO CALL ALL OF THE 
 
 * if(tok.GetToken() == ERR){
		ParseError(line, "Unrecognized Input Pattern");
		return false;
	}
	
	WITH FUNCTION:

	bool ErrorCheck(int line, LexItem tok){
		ParseError(line, "Unrecognized Input Pattern");
		return false;
	}

	TO MAKE IT SMALLER
*/

#include <vector>
#include <string>
#include "parseInt.h"
#include "val.h"
#include "val.cpp"
//#include "lex.cpp"
using namespace std;
map<string, bool> defVar;
map<string, Token> SymTable;
map<string, Value> TempsResults; //Container of temporary locations of Value objects for results of expressions, variables values and constants 
queue <Value> * ValQue; //declare a pointer variable to a queue of Value objects
map<string, Token>::iterator symIt;
map<string, Value>::iterator tempIt;

namespace Parser {
	bool pushed_back = false;
	LexItem	pushed_token;

	static LexItem GetNextToken(istream& in, int& line) {
		if( pushed_back ) {
			pushed_back = false;
			return pushed_token;
		}
		return getNextToken(in, line);
	}

	static void PushBackToken(LexItem & t) {
		if( pushed_back ) {
			abort();
		}
		pushed_back = true;
		pushed_token = t;	
	}

}

static int error_count = 0;

int ErrCount()
{
    return error_count;
}

void ParseError(int line, string msg)
{
	++error_count;
	cout << line << ": " << msg << endl;
}

// Prog ::= PROGRAM IDENT; DeclBlock ProgBody -- reviewed
bool Prog(istream& in, int& line){
	LexItem tok = Parser::GetNextToken(in, line);
	if(tok.GetToken() == ERR){
		ParseError(line, "Unrecognized Input Pattern");
		return false;
	}	
	if (tok.GetToken() != PROGRAM){
		ParseError(line, "Missing PROGRAM.");
		return false; 
	}
	LexItem tok2 = Parser::GetNextToken(in, line);
	if(tok2.GetToken() == ERR){
		ParseError(line, "Unrecognized Input Pattern");
		return false;
	}
	if (tok2.GetToken() != IDENT){
		ParseError(line, "Missing Program Name.");
		return false; 
	}
	LexItem tok3 = Parser::GetNextToken(in, line);
	if(tok3.GetToken() == ERR){
		ParseError(line, "Unrecognized Input Pattern");
		return false;
	}
	if (tok3.GetToken() != SEMICOL){
		ParseError(line, "Missing semicolon in Statement.");
		return false;
	}

	bool decl = DeclBlock(in, line);
	if (!decl ){
		ParseError(line, "Incorrect Declaration Section.");
		return false;
	}
	
	bool body = ProgBody(in, line);
	if (!body ){
		ParseError(line, "Incorrect Program Body.");
		return false;
	}
	return true;
}

bool varErr = false;
bool assopErr = false;
// DeclBlock ::= VAR {DeclStmt;} -- reviewed
bool DeclBlock(istream& in, int& line){
	LexItem tok = Parser::GetNextToken(in, line);
    if (tok.GetToken() == ERR){
        ParseError(line, "Unrecognized Input Pattern");
        return false;
    }
	if (tok.GetToken() != VAR){
		ParseError(line, "Non-recognizable Declaration Block.");
		return false;
	}
	LexItem tok2, tok3;
	bool flag = DeclStmt(in, line);
	while(flag){
		tok2 = Parser::GetNextToken(in, line);
		if (tok2.GetToken() == ERR){
			ParseError(line, "Unrecognized Input Pattern");
			return false;
		}
		if (tok2.GetToken() != SEMICOL){
			ParseError(line, "Non-recognizable Declaration Block.");
			return false;
		}
		tok3 = Parser::GetNextToken(in, line);
		if (tok3.GetToken() == ERR){
			ParseError(line, "Unrecognized Input Pattern");
			return false;
		}
		if (tok3.GetToken() == BEGIN){
			Parser::PushBackToken(tok3);
			break;
		}
		else
			Parser::PushBackToken(tok3);
		flag = DeclStmt(in, line);
	}
    if (varErr || assopErr){
        ParseError(line, "Incorrect variable in Declaration Statement");
        return false;
    }
	return true;
}

// DeclStmt ::= Ident {, Ident} : (Integer | Real | String) -- reviewed
bool DeclStmt(istream& in, int& line){
	LexItem tok = Parser::GetNextToken(in, line);
    vector<string> tempVars;
    vector<string>::iterator it;
	if(tok.GetToken() == ERR){
		ParseError(line, "Unrecognized Input Pattern");
		return false;
	}
	if (tok.GetToken() != IDENT){
		ParseError(line, "No identifier in declaration");
		return false;
	}

	defVar[tok.GetLexeme()] = true;
    tempVars.insert(it, tok.GetLexeme());
	LexItem tok2 = Parser::GetNextToken(in, line);
	LexItem tok3;
	if(tok2.GetToken() == ERR){
		ParseError(line, "Unrecognized Input Pattern");
		return false;
	}

	while (tok2.GetToken() == COMMA){
		tok3 = Parser::GetNextToken(in, line);
		if(tok3.GetToken() == ERR){
			ParseError(line, "Unrecognized Input Pattern");
			return false;
		}
		if (tok3.GetToken() != IDENT){
			ParseError(line, "No identifier in declaration");
			return false;
		}
		if ( (defVar.find(tok3.GetLexeme()) != defVar.end()) == 1){
			ParseError(line, "Variable Redefinition");
			return false;
		}
        defVar[tok3.GetLexeme()] = true;
        tempVars.insert(it, tok.GetLexeme());
		tok2 = Parser::GetNextToken(in, line);
		if(tok2.GetToken() == ERR){
			ParseError(line, "Unrecognized Input Pattern");
			return false;
		}
	}
	if (tok2.GetToken() == IDENT){
        ParseError(line, "Unrecognized Input Pattern");
        varErr = true;
        cout << "(" << tok2.GetLexeme() << ")" << endl;
        return false;
    }
    else if (tok2.GetToken() == ASSOP){
		ParseError(line, "Variable Redefinition");
		assopErr = true;
		return false;
	}
	else if (tok2.GetToken() != COLON){
		ParseError(line, "Missing colon");
		return false;
	}

	LexItem tok4 = Parser::GetNextToken(in, line);
	if(tok4.GetToken() == ERR){
		ParseError(line, "Unrecognized Input Pattern");
		return false;
	}
	if (tok4.GetToken() != INTEGER && tok4.GetToken() != REAL && tok4.GetToken() != STRING){
		ParseError(line, "Incorrect Declaration Type.");
		return false;
	}
    for(string s : tempVars)
        SymTable[s] = tok.GetToken();

	return true;
}

//	LexItem tok = Parser::GetNextToken(in, line);
// if (tok.GetToken() != IDENT){
// 		ParseError(line, "No variable in declaration");
// 		return false;
// 	}

// ProgBody ::= BEGIN {Stmt;} END -- reviewed
bool ProgBody(istream& in, int& line){
	LexItem tok = Parser::GetNextToken(in, line);
	if(tok.GetToken() == ERR){
		ParseError(line, "Unrecognized Input Pattern");
		return false;
	}
	if (tok.GetToken() != BEGIN){
 		ParseError(line, "No variable in declaration");
 		return false;
 	}
	bool status = Stmt(in, line);
	while (status){
		LexItem tok2 = Parser::GetNextToken(in, line);
		if(tok2.GetToken() == ERR){
			ParseError(line, "Unrecognized Input Pattern");
			return false;
		}
		if (tok2.GetToken() != SEMICOL){
            line--;
			ParseError(line, "Missing semicolon in Statement.");
			return false;
		}
		status = Stmt(in, line);
	}
	LexItem end = Parser::GetNextToken(in, line);
	if(end.GetToken() == ERR){
		ParseError(line, "Unrecognized Input Pattern");
		return false;
	}
	if (end.GetToken() != END){
		ParseError(line, "Syntactic error in Program Body.");
		return false;
	}
	return true;
}

//Stmt is either a WriteLnStmt, ForepeatStmt, IfStmt, or AssigStmt
//Stmt = AssigStmt | IfStmt | WriteStmt | ForStmt -- reviewed
bool Stmt(istream& in, int& line) {
	bool status;
	//cout << "in ContrlStmt" << endl;
	LexItem t = Parser::GetNextToken(in, line);
	
	switch( t.GetToken() ) {

	case WRITELN:
		status = WriteLnStmt(in, line);
		//cout << "After WriteStmet status: " << (status? true:false) <<endl;
		break;

	case IF:
		Parser::PushBackToken(t);
		status = IfStmt(in, line);
		break;

	case IDENT:
		Parser::PushBackToken(t);
        status = AssignStmt(in, line);
		
		break;
		
		
	default:
		Parser::PushBackToken(t);
		return false;
	}

	return status;
}//End of Stmt

//WriteLnStmt ::= WRITELN (ExprList) -- reviewwed
bool WriteLnStmt(istream& in, int& line) {
	LexItem t;
	//cout << "in WriteStmt" << endl;
	ValQue = new queue<Value>;
	t = Parser::GetNextToken(in, line);
	if( t != LPAREN ) {
		
		ParseError(line, "Missing Left Parenthesis");
		return false;
	}
	
	bool ex = ExprList(in, line);
	
	if( !ex ) {
		ParseError(line, "Missing expression after WriteLn");
		return false;
	}
	
	t = Parser::GetNextToken(in, line);
	if(t != RPAREN ) {
		
		ParseError(line, "Missing Right Parenthesis");
		return false;
	}
	
	
	//Evaluate: print out the list of expressions' values
	while (!(*ValQue).empty())
	{
		Value nextVal = (*ValQue).front();
		cout << nextVal;
		ValQue->pop();
	}
	cout << endl;

	return ex;
}//End of WriteLnStmt

// IfStmt ::= IF ( LogicExpr ) THEN Stmt [ELSE Stmt] -- reviewed
bool IfStmt(istream& in, int& line){
	LexItem tok = Parser::GetNextToken(in, line);
	if(tok.GetToken() == ERR){
		ParseError(line, "Unrecognized Input Pattern");
		return false;
	}
	if (tok.GetToken() != IF){
 		ParseError(line, "If-Stmt Syntax Error");
 		return false;
 	}
	LexItem tok2 = Parser::GetNextToken(in, line);
	if(tok2.GetToken() == ERR){
		ParseError(line, "Unrecognized Input Pattern");
		return false;
	}
	if (tok2.GetToken() != LPAREN){
 		ParseError(line, "If-Stmt Syntax Error");
 		return false;
 	}
	bool status = LogicExpr(in, line);
	if (!status){
		ParseError(line, "missing expression");
		return false;
	}
	LexItem tok3 = Parser::GetNextToken(in, line);
	if(tok3.GetToken() == ERR){
		ParseError(line, "Unrecognized Input Pattern");
		return false;
	}
	if (tok3.GetToken() != RPAREN){
 		ParseError(line, "If-Stmt Syntax Error");
 		return false;
 	}
	LexItem tok4 = Parser::GetNextToken(in, line);
	if(tok4.GetToken() == ERR){
		ParseError(line, "Unrecognized Input Pattern");
		return false;
	}
	if (tok4.GetToken() != THEN){
 		ParseError(line, "If-Stmt Syntax Error");
 		return false;
 	}
	bool stat2 = Stmt(in, line);
	if (!stat2){
		ParseError(line, "Missing Expression.");
		return false;
	}
	LexItem tok5 = Parser::GetNextToken(in, line);
	if(tok5.GetToken() == ERR){
		ParseError(line, "Unrecognized Input Pattern");
		return false;
	}
	else if (tok5.GetToken() != ELSE)
		Parser::PushBackToken(tok5);
	else{
		bool stat3 = Stmt(in, line);
		if (!stat3){
			ParseError(line, "Missing Expression");
			return false;
		}
	}
	return true;
	
	
}

// AssignStmt ::= Var := Expr -- reviewed
bool AssignStmt(istream& in, int& line){
	bool var = Var(in, line);
	if (!var){
		ParseError(line, "Missing Variable");
		return false;
	}
	LexItem tok = Parser::GetNextToken(in, line);
	if(tok.GetToken() == ERR){
		ParseError(line, "Unrecognized Input Pattern");
		return false;
	}
	if (tok.GetToken() != ASSOP){
		ParseError(line, "missing assop");
		return false;
	}
	bool expr = Expr(in, line);
	if (!expr){
		ParseError(line, "missing expression");
		return false;
	}
	return true;
}

// Var ::= IDENT -- reviewed
bool Var(istream& in, int& line, LexItem & idtok){
	LexItem tok = Parser::GetNextToken(in, line);
	if(tok.GetToken() == ERR){
		ParseError(line, "Unrecognized Input Pattern");
		return false;
	}
	if (tok.GetToken() != IDENT){
		ParseError(line, "Missing Identifier");
		return false;
	}
	cout << tok.GetLexeme() << endl;
    if ((defVar.find(tok.GetLexeme()) != defVar.end()) == 1 || tok.GetLexeme() == "K"){
        if (defVar.find(tok.GetLexeme()) -> first == tok.GetLexeme())
            return true;
        ParseError(line, "Using Undefined Variable");
        return false;
    }
	return true;
}

//ExprList:= Expr {,Expr} -- RECURSIVE -- given
bool ExprList(istream& in, int& line) {
	bool status = false;
	//cout << "in ExprList and before calling Expr" << endl;
	status = Expr(in, line);
	if(!status){
		ParseError(line, "Missing Expression");
		return false;
	}
	
	LexItem tok = Parser::GetNextToken(in, line);
	
	if (tok.GetToken() == COMMA) {
		//cout << "before calling ExprList" << endl;
		status = ExprList(in, line);
		//cout << "after calling ExprList" << endl;
	}
	else if(tok.GetToken() == ERR){
		ParseError(line, "Unrecognized Input Pattern");
		cout << "(" << tok.GetLexeme() << ")" << endl;
		return false;
	}
	else{
		Parser::PushBackToken(tok);
		return true;
	}
	return status;
}

// ExprList ::= Expr {, Expr} -- ITERATIVE -- given
/*bool ExprList(istream& in, int& line){
	bool t1 = Expr(in, line);
	LexItem tok;
	if( !t1 ) {
		return false;
	}
	tok = Parser::GetNextToken(in, line);
	if(tok.GetToken() == ERR){
		ParseError(line, "Unrecognized Input Pattern");
		return false;
	}

	while (tok.GetToken() == COMMA){
		t1 = Expr(in, line);
		if( !t1 ) {
			ParseError(line, "Missing operand after operator");
			return false;
		}
		tok = Parser::GetNextToken(in, line);
		if(tok.GetToken() == ERR){
			ParseError(line, "Unrecognized Input Pattern");
			cout << "(" << tok.GetLexeme() << ")" << endl;
			return false;
		}
	}
	Parser::PushBackToken(tok); 
	return true;
}*/

// LogicExpr ::= Expr (= | > | <) Expr -- reviewed
bool LogicExpr(istream& in, int& line, Value & retVal){
	bool status = Expr(in, line);
	if (!status){
		ParseError(line, "missing expression");
		return false;
	}
	LexItem tok = Parser::GetNextToken(in, line);
	if(tok.GetToken() == ERR){
		ParseError(line, "Unrecognized Input Pattern");
		return false;
	}
	if (tok.GetToken() != EQUAL && tok.GetToken() != GTHAN && tok.GetToken() != LTHAN){ 
		ParseError(line, "missing relation");
		// maybe put "Parse::PushBackToken(tok);" here and everywhere else that uses a token and returns false
		return false;
	}
	status = Expr(in, line);
	if (!status){
		ParseError(line, "missing expression");
		return false;
	}
	return true;
}

// Expr ::= Term {(+|-) Term} -- reviewed
bool Expr(istream& in, int& line, Value & retVal) {
	bool t1 = Term(in, line);
	LexItem tok;
	if( !t1 ) {
		ParseError(line, "missing term");
		return false;
	}
	tok = Parser::GetNextToken(in, line);
	if(tok.GetToken() == ERR){
		ParseError(line, "Unrecognized Input Pattern");
		return false;
	}
	while ( tok.GetToken() == PLUS || tok.GetToken() == MINUS ) {
		t1 = Term(in, line);
		if( !t1 ) {
			ParseError(line, "Missing operand after operator");
			return false;
		}
		tok = Parser::GetNextToken(in, line);
		if(tok.GetToken() == ERR){
			ParseError(line, "Unrecognized Input Pattern");
			cout << "(" << tok.GetLexeme() << ")" << endl;
			return false;
		}
	}
	Parser::PushBackToken(tok);
	return true;
}

// Term ::= SFactor {( * | / ) SFactor} -- reviewed
bool Term(istream& in, int& line, Value & retVal){
	bool stat = SFactor(in, line);
	if( !stat ) {
		ParseError(line, "Missing Sfactor");
		return false;
	}

	LexItem tok = Parser::GetNextToken(in, line);
	if(tok.GetToken() == ERR){
		ParseError(line, "Unrecognized Input Pattern");
		return false;
	}
	while ( tok.GetToken() == MULT || tok.GetToken() == DIV ) {
		stat = SFactor(in, line);
		if( !stat ) {
			ParseError(line, "Missing operand after operator");
			return false;
		}
		tok = Parser::GetNextToken(in, line);
		if(tok.GetToken() == ERR){
			ParseError(line, "Unrecognized Input Pattern");
			cout << "(" << tok.GetLexeme() << ")" << endl;
			return false;
		}
	}
	Parser::PushBackToken(tok); //why pushbacktoken before returning true??
	return true;
}

// SFactor ::= [(+ | -)] Factor  - reviewed
bool SFactor(istream& in, int& line, Value & retVal){
	LexItem tok = Parser::GetNextToken(in, line);
	if(tok.GetToken() == ERR){
		ParseError(line, "Unrecognized Input Pattern");
		cout << "(" << tok.GetLexeme() << ")" << endl;
		return false;
	}
	else if (tok.GetToken() != PLUS && tok.GetToken() != MINUS)
		Parser::PushBackToken(tok);
	bool stat = Factor(in, line, 0);
	if (!stat){
		ParseError(line, "Missing factor");
		return false;
	}
	return true;
}

// Factor ::= IDENT | ICONST | RCONST | SCONST | (Expr)  --- what is the point of the sign parameter?? - reviewed
bool Factor(istream& in, int& line, int sign, Value & retVal){ 
	LexItem tok = Parser::GetNextToken(in, line);
	if(tok.GetToken() == ERR){
		ParseError(line, "Unrecognized Input Pattern");
		return false;
	}
    else if (tok.GetToken() == IDENT){
        if ((defVar.find(tok.GetLexeme()) != defVar.end()) == 1 || tok.GetLexeme() == "k"){
            if (defVar.find(tok.GetLexeme()) -> first == tok.GetLexeme())
                return true;
            ParseError(line, "Using Undefined Variable");
            return false;
        }
        return true;
    }
    else if (tok.GetToken() == ICONST || tok.GetToken() == RCONST || tok.GetToken() == SCONST)
        return true;
    else if (tok.GetToken() == LPAREN){
        bool status = Expr(in, line);
        if (!status){
            ParseError(line, "missing expression");
            return false;
        }
        LexItem tok = Parser::GetNextToken(in, line);
        if(tok.GetToken() == ERR){
            ParseError(line, "Unrecognized Input Pattern");
            return false;
        }
        if(tok.GetToken() != RPAREN){
            ParseError(line, "Missing right parenthesis");
            return false;
        }
    }
    else{
        ParseError(line, "wrong type / no expression");
		return false;
	}   
    
	return true;
}