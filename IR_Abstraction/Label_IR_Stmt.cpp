#include "Label_IR_Stmt.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/IR/Constants.h"
Label_IR_Stmt::Label_IR_Stmt(std::string a) {
  id=a;
}
std::string Label_IR_Stmt::get_id() { return id;}
std::string Label_IR_Stmt::get_IR_Stmt(){
	std::string op1;	
    op1+=id;
	return  "Label " + op1;
}