#ifndef CALL_IR_STMT
#define CALL_IR_STMT
#include "IR_Stmt.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/Function.h"
class Call_IR_Stmt : public IR_Stmt{
    llvm::Value* result;    
    llvm::Function* called_function;
    std::list<llvm::Value*> arglist;
    public :
        Call_IR_Stmt(std::list<llvm::Value*> arg2 ,llvm::Function* f,llvm::Value* res );
        ~Call_IR_Stmt(){};
        llvm::Value *get_result();
        std::string get_IR_Stmt();
};
#endif 