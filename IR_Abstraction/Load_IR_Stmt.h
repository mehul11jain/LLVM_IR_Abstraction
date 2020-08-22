#ifndef LOAD_IR_STMT
#define LOAD_IR_STMT
#include "IR_Stmt.h"
class Load_IR_Stmt : public IR_Stmt {
    llvm::Value *opd1;
    llvm::Value *result;

public:
    Load_IR_Stmt(llvm::Value *res, llvm::Value *op1);
    ~Load_IR_Stmt(){};
    llvm::Value* get_opd1();
    llvm::Value* get_result();
    std::string get_IR_Stmt();
    
};
#endif
