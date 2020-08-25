#include "../IR_Abstraction/IR_Stmt.h"
#include "../IR_Abstraction/Store_IR_Stmt.h"
#include "../IR_Abstraction/Load_IR_Stmt.h"
#include "../IR_Abstraction/Arith_IR_Stmt.h"
#include "../IR_Abstraction/Logical_IR_Stmt.h"
#include "../IR_Abstraction/Return_IR_Stmt.h"
#include "../IR_Abstraction/Call_IR_Stmt.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/User.h"
#include "llvm/IR/Value.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

using namespace llvm;
namespace {
struct InstructionPass : public FunctionPass {
  static char ID;
  InstructionPass() : FunctionPass(ID) {}
  bool runOnFunction(Function &F) override {
    std::list<IR_Stmt *> New_IR_list;
    for (BasicBlock &BB : F) {
      for (Instruction &I : BB) {
        if (isa<StoreInst>(I)) {
          Store_IR_Stmt *n = new Store_IR_Stmt(I.getOperand(1), I.getOperand(0));
          n->populate_users();
		  //llvm::errs()<<"After PopulateUsers in InstructionPass \n";
          New_IR_list.push_back(n);
        }
		else if(isa<LoadInst>(I)){
			auto lhs = dyn_cast<Value>(&I);
			Load_IR_Stmt *n = new Load_IR_Stmt(lhs,I.getOperand(0));
			n->populate_users();
			New_IR_list.push_back(n);
		}
		else if(isa<BinaryOperator>(I)){
			auto lhs = dyn_cast<Value>(&I);
			auto  op1 = dyn_cast<BinaryOperator>(&I)->getOperand(0);
			auto op2 = dyn_cast<BinaryOperator>(&I)->getOperand(1);
			IR_Op opt;
			if(dyn_cast<BinaryOperator>(&I)->getOpcode() == Instruction::Add){
				opt = add_inst;
				Arith_IR_Stmt *n = new Arith_IR_Stmt(lhs,op1,op2,opt);
				New_IR_list.push_back(n);
			}
			else if(dyn_cast<BinaryOperator>(&I)->getOpcode() == Instruction::Sub){
				opt = sub_inst;
				Arith_IR_Stmt *n = new Arith_IR_Stmt(lhs,op1,op2,opt);
				New_IR_list.push_back(n);
			}
			else if(dyn_cast<BinaryOperator>(&I)->getOpcode() == Instruction::Mul){
				opt = mult_inst;
				Arith_IR_Stmt *n = new Arith_IR_Stmt(lhs,op1,op2,opt);
				New_IR_list.push_back(n);
			}
			else if(dyn_cast<BinaryOperator>(&I)->getOpcode() == Instruction::UDiv){
				opt = div_inst;
				Arith_IR_Stmt *n = new Arith_IR_Stmt(lhs,op1,op2,opt);
				New_IR_list.push_back(n);
			}
			else if(dyn_cast<BinaryOperator>(&I)->getOpcode() == Instruction::And){
				opt = and_inst;
				Logical_IR_Stmt *n = new Logical_IR_Stmt(lhs,op1,op2,opt);
				New_IR_list.push_back(n);
			}			
		}
		else if(dyn_cast<ReturnInst>(&I))
		{
			Return_IR_Stmt *s = new Return_IR_Stmt(I.getOperand(0));
			New_IR_list.push_back(s);
		}
		else 
      	{
			  	const CallInst *fnn = dyn_cast<CallInst>(&I);
			  	std::list<llvm::Value*> arg2;
			  	Function* fn = fnn->getCalledFunction();
                StringRef fn_name = fn->getName();
                for(auto arg = fn->arg_begin(); arg != fn->arg_end(); ++arg) 
                    arg2.push_back(*arg);
				Call_IR_Stmt *s= new Call_IR_Stmt(arg2, dyn_cast<Value>(&I));
				New_IR_list.push_back(s);
		}
    }
    for (auto x : New_IR_list) {
	 	//errs()<<"Before getting IR\n";
      errs() << x->get_IR_Stmt() << "\n";

    }
    return false;
  }
  }
};
} // namespace

char InstructionPass::ID = 0;
static RegisterPass<InstructionPass>
    X("instruction", "Iterates over each instruction", false, false);

static RegisterStandardPasses Y(PassManagerBuilder::EP_EarlyAsPossible,
                                [](const PassManagerBuilder &Builder,
                                   legacy::PassManagerBase &PM) {
                                  PM.add(new InstructionPass());
                                });
