#include "Pointer_Arith_IR.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/IR/Constants.h"
PTR_IR_Stmt::PTR_IR_Stmt(llvm::Value* *res, llvm::Value* *op1,llvm::Value* *op2,IR_Op opt) {
  opd1 = op1;
  opd2 = op2;
  this->opt = opt;
  result = res;
}
llvm::Value *PTR_IR_Stmt::get_opd1() { return *opd1; }
llvm::Value *PTR_IR_Stmt::get_opd2() { return *opd2; }
IR_Op PTR_IR_Stmt::get_operator() { return opt; }
llvm::Value *PTR_IR_Stmt::get_result() { return *result; }
std::string PTR_IR_Stmt::get_IR_Stmt() {
	std::string op1,op2;		
	if(llvm::ConstantInt* newop = llvm::dyn_cast<llvm::ConstantInt>(*opd2))
	{
		op2= newop->getValue().toString(10,1);
	}
	else if(llvm::ConstantFP* newop = llvm::dyn_cast<llvm::ConstantFP>(*opd2))
	{
		op2 = std::to_string(newop->getValueAPF().convertToFloat());
	}
	
	if(llvm::ConstantInt* newop = llvm::dyn_cast<llvm::ConstantInt>(*opd1))
	{
		op1= newop->getValue().toString(10,1);
	}
	else if(llvm::ConstantFP* newop = llvm::dyn_cast<llvm::ConstantFP>(*opd1))
	{
		op1 = std::to_string(newop->getValueAPF().convertToFloat());
	}
	std::string res = result->getName().str();
	return res + " = " + op1 + operators_map[opt] + op2;
}