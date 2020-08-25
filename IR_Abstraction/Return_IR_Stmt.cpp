#include "Return_IR_Stmt.h"
#include "IR_Stmt.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/IR/Constants.h"
Return_IR_Stmt::Return_IR_Stmt(llvm::Value *opd1) {
  this->opd1 = opd1;
}
llvm::Value *Return_IR_Stmt::get_opd1() { return opd1; }
std::string Return_IR_Stmt::get_IR_Stmt() {
    std::string op1;	
	if(opd1->getName()==""){
		llvm::ConstantFP* newop = llvm::dyn_cast<llvm::ConstantFP>(opd1);
		if(newop!=NULL)
			op1 = std::to_string(newop->getValueAPF().convertToFloat());
		else
			op1 = "-1";
		}
	else
		op1 = opd1->getName().str();
	return "return " + op1;
}