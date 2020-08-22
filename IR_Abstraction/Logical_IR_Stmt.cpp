#include "Logical_IR_Stmt.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/IR/Constants.h"
Logical_IR_Stmt::Logical_IR_Stmt(llvm::Value *res, llvm::Value *op1,llvm::Value* op2,IR_Op opt) {
  opd1 = op1;
  opd2 = op2;
  this->opt = opt;
  result = res;
}
llvm::Value *Logical_IR_Stmt::get_opd1() { return opd1; }
llvm::Value *Logical_IR_Stmt::get_opd2() { return opd2; }
IR_Op Logical_IR_Stmt::get_operator() { return opt; }
llvm::Value *Logical_IR_Stmt::get_result() { return result; }
std::string Logical_IR_Stmt::get_IR_Stmt() {
	std::string op1,op2;	
	if(opd1->getName()==""){
		llvm::Constant* newop = llvm::dyn_cast<llvm::Constant>(llvm::dyn_cast<llvm::User>(opd1));
		op1 = newop->getUniqueInteger().toString(10,1);
		}
	else
		op1 = opd1->getName().str();
    if(opd2->getName()==""){
		llvm::Constant* newop = llvm::dyn_cast<llvm::Constant>(llvm::dyn_cast<llvm::User>(opd2));
		op2 = newop->getUniqueInteger().toString(10,1);
		}
	else
		op2 = opd1->getName().str();
	std::string res = result->getName().str();
	return res + " = " + op1 + operators_map[opt] + op2;
}