#ifndef IR_STMT
#define IR_STMT
#include "llvm/IR/Value.h"
#include <bits/stdc++.h>
typedef enum {
  add_inst,
  sub_inst,
  mult_inst,
  div_inst,
  and_inst,
  or_inst,
  not_inst,
  no_op_inst,
  icmp_eq_inst,  ///< equal
  icmp_ne_inst,   ///< not equal
  icmp_gt_inst, ///< signed greater than
  icmp_ge_inst, ///< signed greater or equal
  icmp_lt_inst, ///< signed less than
  icmp_le_inst, ///< signed less or equal

} IR_Op;
class IR_Stmt {
  std::string IR_Stmt_string;
  std::unordered_map<llvm::Value *, std::set<llvm::Value *>> def_use;
protected :
  std::unordered_map<IR_Op,std::string> operators_map;

public:
  IR_Stmt(){
    operators_map[add_inst] = " + ";
    operators_map[sub_inst] = " - ";
    operators_map[mult_inst] = " * ";
    operators_map[div_inst] = " / ";
    operators_map[and_inst] = " & ";
    operators_map[or_inst] = " | ";
    operators_map[not_inst] = " ! ";
    operators_map[no_op_inst] = " ";
    operators_map[icmp_eq_inst] = " == ";
    operators_map[icmp_ne_inst] = " != ";
    operators_map[icmp_gt_inst] = " > ";
    operators_map[icmp_ge_inst] = " >= ";
    operators_map[icmp_lt_inst] = " < ";
    operators_map[icmp_le_inst] = " <= ";
  };
  ~IR_Stmt(){};
  virtual llvm::Value *get_opd1();
  virtual llvm::Value *get_opd2();
  virtual llvm::Value *get_result();
  virtual std::string get_IR_Stmt() = 0;
  void populate_users();  
};
#endif
