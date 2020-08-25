#ifndef ARITH_IR_STMT
#define ARITH_IR_STMT
#include "IR_Stmt.h"
#include "llvm/IR/Value.h"
class Arith_IR_Stmt : public IR_Stmt{
    llvm::Value* opd1;
    llvm::Value* opd2;
    llvm::Value* result;
    IR_Op opt;

    public :
        Arith_IR_Stmt(llvm::Value* res,llvm::Value* op1,llvm::Value* op2,IR_Op opt);
        ~Arith_IR_Stmt(){};
        llvm::Value *get_opd1();
        llvm::Value *get_opd2();
        IR_Op get_operator();
        llvm::Value *get_result();
        std::string get_IR_Stmt();
};
#endif 