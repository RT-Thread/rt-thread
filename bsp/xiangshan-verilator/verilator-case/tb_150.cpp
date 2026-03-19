#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <memory>

#include "verilated.h"
#include "verilated_cov.h"
#include "Vdut_150.h"

static inline void tick(Vdut_150 *dut, VerilatedContext *ctx) {
    dut->clk = 0;
    dut->eval();
    ctx->timeInc(1);
    dut->clk = 1;
    dut->eval();
    ctx->timeInc(1);
}

// g[3:1] packed into low 3 bits of dut->g (bit0=g[1], bit1=g[2], bit2=g[3])
static inline uint8_t g_bus(Vdut_150 *dut) {
    return static_cast<uint8_t>(dut->g & 0x07u);
}

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);
    auto ctx = std::make_unique<VerilatedContext>();
    ctx->traceEverOn(false);

    auto dut = std::make_unique<Vdut_150>(ctx.get());

    enum { A = 0, B = 1, C = 2, D = 3 };
    uint8_t state = A;

    auto apply_reset = [&]() {
        dut->resetn = 0;
        dut->r = 0;
        tick(dut.get(), ctx.get());
        dut->resetn = 1;
        state = A;
    };

    auto step = [&](uint8_t r_val, const char *ctx_str) {
        uint8_t r = r_val & 0x07u;  // r[3:1] in bits [2:0]
        dut->r = r;

        // Model next_state with r[1:3] mapped to bits 0..2.
        bool r1 = (r & 0x1u) != 0;
        bool r2 = (r & 0x2u) != 0;
        bool r3 = (r & 0x4u) != 0;

        uint8_t next = state;
        switch (state) {
            case A:
                if (r1)                        next = B;
                else if (!r1 && r2)            next = C;
                else if (!r1 && !r2 && r3)     next = D;
                else                           next = A;
                break;
            case B:
                next = r1 ? B : A;
                break;
            case C:
                next = r2 ? C : A;
                break;
            case D:
                next = r3 ? D : A;
                break;
        }

        tick(dut.get(), ctx.get());
        state = next;

        // Expected g bus: bit0 for B, bit1 for C, bit2 for D.
        uint8_t g_exp = 0;
        if (state == B) g_exp = 0x1u;
        else if (state == C) g_exp = 0x2u;
        else if (state == D) g_exp = 0x4u;

        uint8_t g_act = g_bus(dut.get());
        if (g_act != g_exp) {
            std::cerr << "[TB] dut_150 failed (" << ctx_str << "): "
                      << "state=" << int(state)
                      << " r=0x" << std::hex << int(r)
                      << " expected g=0x" << int(g_exp)
                      << " got g=0x" << int(g_act) << std::dec << std::endl;
            std::exit(EXIT_FAILURE);
        }
    };

    // Scenario 1: exercise all branches in state A (r1, r2, r3, none).
    apply_reset();                  // A
    step(0x00u, "A->A_none");       // else
    step(0x01u, "A->B_r1");         // if(r1)
    // Now in B; release back to A
    step(0x00u, "B->A_release_r1");

    apply_reset();                  // A
    step(0x02u, "A->C_r2");         // else if(~r1 & r2)
    step(0x00u, "C->A_release_r2");

    apply_reset();                  // A
    step(0x04u, "A->D_r3");         // else if(~r1 & ~r2 & r3)
    step(0x00u, "D->A_release_r3");

    // Scenario 2: exercise B state's if/else.
    apply_reset();                  // A
    step(0x01u, "A->B_for_B");      // into B
    step(0x01u, "B->B_hold_r1");    // if(r1) branch
    step(0x00u, "B->A_else");       // else branch

    // Scenario 3: C state's branches.
    apply_reset();                  // A
    step(0x02u, "A->C_for_C");
    step(0x02u, "C->C_hold_r2");    // if(r2)
    step(0x00u, "C->A_else_C");     // else

    // Scenario 4: D state's branches.
    apply_reset();                  // A
    step(0x04u, "A->D_for_D");
    step(0x04u, "D->D_hold_r3");    // if(r3)
    step(0x00u, "D->A_else_D");     // else

    std::cout << "[TB] dut_150 passed: fixed-priority arbiter full coverage" << std::endl;

#if VM_COVERAGE
    const char *covPath = std::getenv("VERILATOR_COV_FILE");
    if (covPath == nullptr || covPath[0] == '\0') {
        covPath = "coverage.dat";
    }
    VerilatedCov::write(covPath);
#endif
    return EXIT_SUCCESS;
}
