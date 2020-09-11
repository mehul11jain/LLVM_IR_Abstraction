#include "../IR_Abstraction/Arith_IR_Stmt.h"
#include "../IR_Abstraction/Branch_IR_Stmt.h"
#include "../IR_Abstraction/Call_IR_Stmt.h"
#include "../IR_Abstraction/IR_Stmt.h"
#include "../IR_Abstraction/Label_IR_Stmt.h"
#include "../IR_Abstraction/Load_IR_Stmt.h"
#include "../IR_Abstraction/Logical_IR_Stmt.h"
#include "../IR_Abstraction/Return_IR_Stmt.h"
#include "../IR_Abstraction/Store_IR_Stmt.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/User.h"
#include "llvm/IR/Value.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

using namespace llvm;

std::unordered_map<CmpInst::Predicate, IR_Op> PredMap;

namespace {
struct IRConstructPass : public ModulePass {
  static char ID;
  IRConstructPass() : ModulePass(ID) {}
  bool runOnModule(Module &M) override {
      PredMap.insert({CmpInst::ICMP_EQ,icmp_eq_inst});
      PredMap.insert({CmpInst::ICMP_NE,icmp_ne_inst});
      PredMap.insert({CmpInst::ICMP_SGT,icmp_gt_inst});
      PredMap.insert({CmpInst::ICMP_SGE,icmp_ge_inst});
      PredMap.insert({CmpInst::ICMP_SLT,icmp_lt_inst});
      PredMap.insert({CmpInst::ICMP_SLE,icmp_le_inst});
    Module::FunctionListType &flt = M.getFunctionList();
    for (auto itr = flt.begin(); itr != flt.end(); itr++) {
      std::list<IR_Stmt *> New_IR_list;
      errs() << itr->getName() << "\n";
      Function &f = (*itr);
      for (BasicBlock &BB : f) {
        Label_IR_Stmt *s = new Label_IR_Stmt(BB.getName().str());
        New_IR_list.push_back(s);
        // errs() << BB.getName() << "\n"; //Label BB block
        for (Instruction &I : BB) {
          // errs() << I << "\n";
          if (isa<StoreInst>(I)) {
            Store_IR_Stmt *n =
                new Store_IR_Stmt(I.getOperand(1), I.getOperand(0));
            n->populate_users();
            // llvm::errs()<<"After PopulateUsers in InstructionPass \n";
            New_IR_list.push_back(n);
          } else if (isa<LoadInst>(I)) {
            auto lhs = dyn_cast<Value>(&I);
            Load_IR_Stmt *n = new Load_IR_Stmt(lhs, I.getOperand(0));
            n->populate_users();
            New_IR_list.push_back(n);
          } else if (isa<BinaryOperator>(I)) {
            auto lhs = dyn_cast<Value>(&I);
            auto op1 = dyn_cast<BinaryOperator>(&I)->getOperand(0);
            auto op2 = dyn_cast<BinaryOperator>(&I)->getOperand(1);
            IR_Op opt;
            if (dyn_cast<BinaryOperator>(&I)->getOpcode() == Instruction::Add) {
              opt = add_inst;
              Arith_IR_Stmt *n = new Arith_IR_Stmt(lhs, op1, op2, opt);
              New_IR_list.push_back(n);
            } else if (dyn_cast<BinaryOperator>(&I)->getOpcode() ==
                       Instruction::Sub) {
              opt = sub_inst;
              Arith_IR_Stmt *n = new Arith_IR_Stmt(lhs, op1, op2, opt);
              New_IR_list.push_back(n);
            } else if (dyn_cast<BinaryOperator>(&I)->getOpcode() ==
                       Instruction::Mul) {
              opt = mult_inst;
              Arith_IR_Stmt *n = new Arith_IR_Stmt(lhs, op1, op2, opt);
              New_IR_list.push_back(n);
            } else if (dyn_cast<BinaryOperator>(&I)->getOpcode() ==
                       Instruction::UDiv) {
              opt = div_inst;
              Arith_IR_Stmt *n = new Arith_IR_Stmt(lhs, op1, op2, opt);
              New_IR_list.push_back(n);
            } else if (dyn_cast<BinaryOperator>(&I)->getOpcode() ==
                       Instruction::And) {
              opt = and_inst;
              Logical_IR_Stmt *n = new Logical_IR_Stmt(lhs, op1, op2, opt);
              New_IR_list.push_back(n);
            }
          } else if (dyn_cast<ReturnInst>(&I)) {
            Return_IR_Stmt *s;
            if (I.getNumOperands() != 0)
              s = new Return_IR_Stmt(I.getOperand(0));
            else
              s = new Return_IR_Stmt();
            New_IR_list.push_back(s);
          } else if ( CallInst *fnn = dyn_cast<CallInst>(&I)) {
            std::list<llvm::Argument*> arg2;
            Call_IR_Stmt *s = new Call_IR_Stmt(fnn, dyn_cast<Value>(&I));
            New_IR_list.push_back(s);
          } else if (const BranchInst *br = dyn_cast<BranchInst>(&I)) {
            // errs() << "Before \n";
            Branch_IR_Stmt *s;
            if (I.getNumOperands() == 3)
              s = new Branch_IR_Stmt(I.getOperand(0), I.getOperand(1),
                                     I.getOperand(2));
            else if (I.getNumOperands() == 1)
              s = new Branch_IR_Stmt(I.getOperand(0));
            else
              s = new Branch_IR_Stmt();
            New_IR_list.push_back(s);
          } else if (const CmpInst *br = dyn_cast<CmpInst>(&I)) {
            if (dyn_cast<ICmpInst>(br)) {
              const ICmpInst *ic = dyn_cast<ICmpInst>(br);
              IR_Op opt= PredMap[ic->getPredicate()];
              Value* lhs= dyn_cast<Value>(&I);
              Logical_IR_Stmt *s = new Logical_IR_Stmt(lhs,ic->getOperand(0),ic->getOperand(1),opt);
              New_IR_list.push_back(s);
            }
          }
        }
      }
      for (auto x : New_IR_list) {
        // errs()<<"Before getting IR\n";
        errs() << x->get_IR_Stmt() << "\n";
      }
    }
    return false;
  }
};
} // namespace


char IRConstructPass::ID = 0;
static RegisterPass<IRConstructPass>
    X("AbstractIR", "Creates an abstraction for LLVM IR", false, false);

static RegisterStandardPasses Y(PassManagerBuilder::EP_EarlyAsPossible,
                                [](const PassManagerBuilder &Builder,
                                   legacy::PassManagerBase &PM) {
                                  PM.add(new IRConstructPass());
                                });
