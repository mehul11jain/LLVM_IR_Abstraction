#ifndef CALL_IR_STMT
#define CALL_IR_STMT
#include "IR_Stmt.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Argument.h"
class Call_IR_Stmt : public IR_Stmt{
    llvm::Value* result;    
    llvm::CallInst* current_call_instruction;
    public :
        Call_IR_Stmt(llvm::CallInst* f,llvm::Value* res );
        ~Call_IR_Stmt(){};
        llvm::Value *get_result();
        std::string get_IR_Stmt();
};
#endif 