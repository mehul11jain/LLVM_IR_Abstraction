#ifndef LABEL_IR_STMT
#define LABEL_IR_STMT
#include "IR_Stmt.h"
#include "llvm/IR/Value.h"
class Label_IR_Stmt : public IR_Stmt{
    std::string id;
    public :
        Label_IR_Stmt(std::string a);
        ~Label_IR_Stmt(){};
        Label_IR_Stmt(){};
        std::string get_id();
        std::string get_IR_Stmt();
};
#endif 