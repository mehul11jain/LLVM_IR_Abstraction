#ifndef BRANCH_IR_STMT
#define BRANCH_IR_STMT
#include "IR_Stmt.h"
#include "llvm/IR/Value.h"
class Branch_IR_Stmt : public IR_Stmt{
    llvm::Value* opd1;
    llvm::Value* opd2;
    llvm::Value* opd3;
    bool flag;
    public :
        Branch_IR_Stmt(llvm::Value* res);
        Branch_IR_Stmt(llvm::Value* res1,llvm::Value* res2,llvm::Value* res3);
        ~Branch_IR_Stmt(){};
        Branch_IR_Stmt(){};
        llvm::Value* get_BBid();
        std::string get_IR_Stmt();
};
#endif 