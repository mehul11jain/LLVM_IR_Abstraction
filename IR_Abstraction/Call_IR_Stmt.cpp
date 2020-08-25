#include "Call_IR_Stmt.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/IR/Constants.h"
Call_IR_Stmt::Call_IR_Stmt(std::list<llvm::Value> *arg2, llvm::Value* res) {
  arglist = arg2;
  result=res;
}
llvm::Value *Store_IR_Stmt::get_result() { return result; }
std::string Store_IR_Stmt::get_IR_Stmt() {
	std::string op1="Call ";	
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
		op1 += opd1->getName().str();
        op1+=",";
    }
	std::string res = result->getName().str();
	return op1 + " = " ;
}