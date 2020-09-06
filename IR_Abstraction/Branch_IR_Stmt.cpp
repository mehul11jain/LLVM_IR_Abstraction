#include "Branch_IR_Stmt.h"
#include "IR_Stmt.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/IR/Constants.h"
Branch_IR_Stmt::Branch_IR_Stmt(llvm::Value *opd1) {
  this->opd1 = opd1;
  this->flag=0;
}
Branch_IR_Stmt::Branch_IR_Stmt(llvm::Value *op1,llvm::Value *op2,llvm::Value *op3) {
  this->opd1=op1;
  this->opd2=op2;
  this->opd3=op3;
  this->flag=1;
}
llvm::Value *Branch_IR_Stmt::get_BBid() { return opd1; }
std::string Branch_IR_Stmt::get_IR_Stmt() {
    std::string op1,op2,op3;
	if(!opd1)
		return "goto ;";
	if(llvm::ConstantFP* newop = llvm::dyn_cast<llvm::ConstantFP>(opd1)){
		op1 = std::to_string(newop->getValueAPF().convertToFloat());
	}
	else if(llvm::ConstantInt* newop = llvm::dyn_cast<llvm::ConstantInt>(opd1)){
		op1 = newop->getValue().toString(10,1);
	}
	else if(opd1)
    op1 = opd1->getName().str();
  if(flag)
        {    
    if(llvm::ConstantInt* newop = llvm::dyn_cast<llvm::ConstantInt>(opd2))
		op2+= newop->getValue().toString(10,1)+" ";
    else if(opd2)
      op2+= opd2->getName().str()+" ";
    if(llvm::ConstantInt* newop = llvm::dyn_cast<llvm::ConstantInt>(opd3))
    op3+= newop->getValue().toString(10,1)+" ";
    else if(opd3)
       op3+= opd3->getName().str()+" ";
     return "If("+ op1 +") goto " + op2 +"\ngoto " + op3; 
      }
 return "goto " + op1;
}