#include "Store_IR_Stmt.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/IR/Constants.h"
Store_IR_Stmt::Store_IR_Stmt(llvm::Value *res, llvm::Value *op1) {
  opd1 = op1;
  result = res;
}
llvm::Value *Store_IR_Stmt::get_opd1() { return opd1; }
llvm::Value *Store_IR_Stmt::get_result() { return result; }
std::string Store_IR_Stmt::get_IR_Stmt() {
	std::string op1;	
<<<<<<< HEAD
	if(opd1->getName()==""){
		llvm::ConstantFP* newop = llvm::dyn_cast<llvm::ConstantFP>(opd1);
		if(newop!=NULL)
			op1 = std::to_string(newop->getValueAPF().convertToFloat());
		else
			op1 = "-1";
		}
=======
	if(llvm::ConstantFP* newop = llvm::dyn_cast<llvm::ConstantFP>(opd1)){
		op1 = std::to_string(newop->getValueAPF().convertToFloat());
	}
	else if(llvm::ConstantInt* newop = llvm::dyn_cast<llvm::ConstantInt>(opd1)){
		op1 = newop->getValue().toString(10,1);
	}
>>>>>>> 42d547947c8efb428ac68e9c02afa7a5c13013b2
	else
		op1 = opd1->getName().str();
    
	std::string res = result->getName().str();
	return res + " = " + op1;
}