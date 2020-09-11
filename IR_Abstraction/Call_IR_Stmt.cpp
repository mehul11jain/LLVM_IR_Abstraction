#include "Call_IR_Stmt.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Instructions.h"


Call_IR_Stmt::Call_IR_Stmt(llvm::CallInst* f,llvm::Value* res) {
  current_call_instruction = f;
  result = res;
}
llvm::Value *Call_IR_Stmt::get_result() { return result; }
std::string Call_IR_Stmt::get_IR_Stmt() {
	std::string op1="Call ";
	op1+=  current_call_instruction->getCalledFunction()->getName().str();	
	op1+='(';
	int i=0;
	while(i<current_call_instruction->getNumArgOperands())
	{
		std::string test=current_call_instruction->getArgOperand(i)->getName().str();
		auto opd1=current_call_instruction->getArgOperand(i);
		if(llvm::ConstantFP* newop = llvm::dyn_cast<llvm::ConstantFP>(llvm::dyn_cast<llvm::Value>(opd1))){
			op1+= std::to_string(newop->getValueAPF().convertToFloat());
		}
		else if(llvm::ConstantInt* newop = llvm::dyn_cast<llvm::ConstantInt>(llvm::dyn_cast<llvm::Value>(opd1))){
			op1+= newop->getValue().toString(10,1);
		}	
		else
		{
			op1+=test;
		}	
		i++;
		if(i!=current_call_instruction->getNumArgOperands())
			op1+=", " ;
		
	}
	op1+=')';
	std::string res = result->getName().str();
	if(res=="")
		return  op1 ;
	else
		return res + " = " + op1;
}