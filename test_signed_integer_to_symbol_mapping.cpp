
#include <iostream>
#include <verilated.h>
#include "Vsigned_integer_to_symbol_mapping.h"
#include <verilated_fst_c.h> 

static int32_t GetAbs(int32_t val)
{
    if (val < 0) {
        //printf("m\n");
        return val * -1;
    } else {
        //printf("p\n");
        return val;
    }
}


static int32_t Signedintegertosymbolmapping(int32_t val)
{
    uint32_t sn;
    if (val >=0 ) {
        sn = GetAbs(val) << 1;

    } else {
        sn = (GetAbs(val) << 1) - 1;
    }
    return sn;
}

int time_counter = 0;

int main(int argc, char** argv) {

	Verilated::commandArgs(argc, argv);
	FILE *in = fopen(argv[1], "r");
	if (in==NULL) {
		printf("err\n");
	}
	// Instantiate DUT
	Vsigned_integer_to_symbol_mapping *dut = new Vsigned_integer_to_symbol_mapping();
	// Trace DUMP ON
	Verilated::traceEverOn(true);
	VerilatedFstC* tfp = new VerilatedFstC;

	dut->trace(tfp, 100);  // Trace 100 levels of hierarchy
	tfp->open("simx.fst");

	// Format
	dut->reset_n = 0;
	dut->clk = 0;

	// Reset Time
	while (time_counter < 10) {
		dut->eval();
		tfp->dump(time_counter);  // 波形ダンプ用の記述を追加
		time_counter++;
	}
	// Release reset
	dut->reset_n = 1;

	int state = 0;

	int k,val,codeword_length,sum;
	while (time_counter < 100 && !Verilated::gotFinish()) {
		dut->clk = !dut->clk; // Toggle clock
		if (dut->clk) {
			fscanf(in, "%d %d",&val, &sum);
//			printf("%d %d\n", val, sum);
//			if (state == 0) {
				dut->input_data = val;
//				state = 1;
//			}
		}

		// Evaluate DUT
		dut->eval();
		if (dut->clk) {
//			uint32_t sum;
//			int32_t codword_length;
//			sum = Signedintegertosymbolmapping(dut->input_data);
			if (dut->sum != sum) {
				printf("input_data=%d sum=%d sum=%d\n", 
				dut->input_data, dut->sum, sum);

			}
		}
		tfp->dump(time_counter);  // 波形ダンプ用の記述を追加
		time_counter++;
//		break;
	}

	dut->final();
	tfp->close(); 
}