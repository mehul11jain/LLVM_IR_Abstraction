#ifndef STORE_IR
#define STORE_IR
#include "IR_Stmt.h"
class Store_IR_Stmt : public IR_Stmt {
  llvm::Value *result;
  llvm::Value *opd1;  

public:
  Store_IR_Stmt(llvm::Value *res, llvm::Value *op1);
  ~Store_IR_Stmt(){};
  llvm::Value *get_opd1();
  llvm::Value *get_result();
  std::string get_IR_Stmt();
};
#endif // !1