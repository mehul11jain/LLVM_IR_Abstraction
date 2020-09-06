#include "Arith_IR_Stmt.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/IR/Constants.h"
Arith_IR_Stmt::Arith_IR_Stmt(llvm::Value *res, llvm::Value *op1,llvm::Value* op2,IR_Op opt) {
  opd1 = op1;
  opd2 = op2;
  this->opt = opt;
  result = res;
}
llvm::Value *Arith_IR_Stmt::get_opd1() { return opd1; }
llvm::Value *Arith_IR_Stmt::get_opd2() { return opd2; }
IR_Op Arith_IR_Stmt::get_operator() { return opt; }
llvm::Value *Arith_IR_Stmt::get_result() { return result; }
std::string Arith_IR_Stmt::get_IR_Stmt() {
	std::string op1,op2;	

	if(llvm::ConstantFP* newop = llvm::dyn_cast<llvm::ConstantFP>(opd1)){
		op1 = std::to_string(newop->getValueAPF().convertToFloat());
	}
	else if(llvm::ConstantInt* newop = llvm::dyn_cast<llvm::ConstantInt>(opd1)){
		op1 = newop->getValue().toString(10,1);
	}
	else
		op1 = opd1->getName().str();

    if(llvm::ConstantFP* newop = llvm::dyn_cast<llvm::ConstantFP>(opd2)){
		op2 = std::to_string(newop->getValueAPF().convertToFloat());
	}
	else if(llvm::ConstantInt* newop = llvm::dyn_cast<llvm::ConstantInt>(opd2)){
		op2 = newop->getValue().toString(10,1);
	}
	else
		op2 = opd2->getName().str();
	std::string res = result->getName().str();
	return res + " = " + op1 + operators_map[opt] + op2;
}