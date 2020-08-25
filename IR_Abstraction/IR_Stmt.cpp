#include "IR_Stmt.h"
#include "llvm/ADT/Twine.h"
#include "llvm/IR/User.h"
#include "llvm/Support/raw_ostream.h"

llvm::Value *IR_Stmt::get_result() { return nullptr; }
llvm::Value *IR_Stmt::get_opd1() { return nullptr; }
llvm::Value *IR_Stmt::get_opd2() { return nullptr; }
void IR_Stmt::populate_users() {
  llvm::Value *res = get_result();
  llvm::Value *def = res;
 // llvm::errs()<<"Before Iteration\n";
  for (auto x : res->users()) {
    llvm::Value *use = llvm::dyn_cast<llvm::Value>(x);
    def_use[res].insert(use);
  }
}