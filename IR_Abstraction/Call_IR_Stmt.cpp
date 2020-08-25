#include "Call_IR_Stmt.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/IR/Constants.h"
Call_IR_Stmt::Call_IR_Stmt(std::list<llvm::Value*> arg2,llvm::Function* f,llvm::Value* res) {
  arglist = arg2;    
  called_function = f;
  result = res;
}
llvm::Value *Call_IR_Stmt::get_result() { return result; }
std::string Call_IR_Stmt::get_IR_Stmt() {
	std::string op1="Call ";
	op1+=called_function->getName().str();	
	op1+='(';
    for( auto i : arglist)
    {
	if(i->getName()==""){
		llvm::ConstantFP* newop = llvm::dyn_cast<llvm::ConstantFP>(i);
		if(newop!=NULL)
			op1 += std::to_string(newop->getValueAPF().convertToFloat());
		else
			op1 += "-1";
	}
	else
		op1 += i->getName().str();
        op1+=",";
    }
	op1+=')';
	std::string res = result->getName().str();
	if(res=="")
		return  op1 ;
	else
		return res + " = " + op1;
}