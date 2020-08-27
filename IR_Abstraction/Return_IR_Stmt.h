#ifndef RETURN_IR_STMT
#define RETURN_IR_STMT
#include "IR_Stmt.h"
#include "llvm/IR/Value.h"
class Return_IR_Stmt : public IR_Stmt{
    llvm::Value* opd1;
    public :
        Return_IR_Stmt(llvm::Value* opd);
        ~Return_IR_Stmt(){};
        Return_IR_Stmt(){};
        llvm::Value *get_opd1();
        std::string get_IR_Stmt();

};
#endif 