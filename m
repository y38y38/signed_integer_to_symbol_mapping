verilator --cc --exe  --trace-fst --trace-params --trace-structs --trace-underscore \
    signed_integer_to_symbol_mapping.v -exe test_signed_integer_to_symbol_mapping.cpp
make -C obj_dir -f Vsigned_integer_to_symbol_mapping.mk

