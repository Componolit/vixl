// Copyright 2016, ARM Limited
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//   * Redistributions of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//   * Redistributions in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//   * Neither the name of ARM Limited nor the names of its contributors may be
//     used to endorse or promote products derived from this software without
//     specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// -----------------------------------------------------------------------------
// This file is auto generated from the
// test/a32/config/template-simulator-a32.cc.in template file using
// tools/generate_tests.py.
//
// PLEASE DO NOT EDIT.
// -----------------------------------------------------------------------------

#include "test-runner.h"

#include "test-utils.h"
#include "test-utils-a32.h"

#include "a32/assembler-a32.h"
#include "a32/macro-assembler-a32.h"
#include "a32/disasm-a32.h"

#define __ masm.
#define BUF_SIZE (4096)

#ifdef VIXL_INCLUDE_SIMULATOR
// Run tests with the simulator.

#define SETUP() MacroAssembler masm(BUF_SIZE)

#define START() masm.GetBuffer().Reset()

#define END() \
  __ Hlt(0);  \
  __ FinalizeCode();

// TODO: Run the tests in the simulator.
#define RUN()

#define TEARDOWN()

#else  // ifdef VIXL_INCLUDE_SIMULATOR.

#define SETUP() MacroAssembler masm(BUF_SIZE);

#define START()             \
  masm.GetBuffer().Reset(); \
  __ Push(r4);              \
  __ Push(r5);              \
  __ Push(r6);              \
  __ Push(r7);              \
  __ Push(r8);              \
  __ Push(r9);              \
  __ Push(r10);             \
  __ Push(r11);             \
  __ Push(r12);             \
  __ Push(lr)

#define END()  \
  __ Pop(lr);  \
  __ Pop(r12); \
  __ Pop(r11); \
  __ Pop(r10); \
  __ Pop(r9);  \
  __ Pop(r8);  \
  __ Pop(r7);  \
  __ Pop(r6);  \
  __ Pop(r5);  \
  __ Pop(r4);  \
  __ Bx(lr);   \
  __ FinalizeCode();

// Copy the generated code into a memory area garanteed to be executable before
// executing it.
#define RUN()                                                  \
  {                                                            \
    ExecutableMemory code(masm.GetBuffer().GetCursorOffset()); \
    code.Write(masm.GetBuffer().GetOffsetAddress<byte*>(0),    \
               masm.GetBuffer().GetCursorOffset());            \
    int pcs_offset = masm.IsT32() ? 1 : 0;                     \
    code.Execute(pcs_offset);                                  \
  }

#define TEARDOWN()

#endif  // ifdef VIXL_INCLUDE_SIMULATOR

namespace vixl {
namespace aarch32 {

// List of instruction encodings:
#define FOREACH_INSTRUCTION(M) \
  M(Adc)                       \
  M(Adcs)                      \
  M(Add)                       \
  M(Adds)                      \
  M(And)                       \
  M(Ands)                      \
  M(Bic)                       \
  M(Bics)                      \
  M(Eor)                       \
  M(Eors)                      \
  M(Orn)                       \
  M(Orns)                      \
  M(Orr)                       \
  M(Orrs)                      \
  M(Rsb)                       \
  M(Rsbs)                      \
  M(Sbc)                       \
  M(Sbcs)                      \
  M(Sub)                       \
  M(Subs)

// Values to be passed to the assembler to produce the instruction under test.
struct Operands {
  Condition cond;
  Register rd;
  Register rn;
  Register rm;
  ShiftType shift;
  uint32_t amount;
};

// Input data to feed to the instruction.
struct Inputs {
  uint32_t apsr;
  uint32_t rd;
  uint32_t rn;
  uint32_t rm;
};

// This structure contains all input data needed to test one specific encoding.
// It used to generate a loop over an instruction.
struct TestLoopData {
  // The `operands` fields represents the values to pass to the assembler to
  // produce the instruction.
  Operands operands;
  // Description of the operands, used for error reporting.
  const char* operands_description;
  // Unique identifier, used for generating traces.
  const char* identifier;
  // Array of values to be fed to the instruction.
  size_t input_size;
  const Inputs* inputs;
};

static const Inputs kCondition[] = {
    {NFlag, 0xabababab, 0xabababab, 0xabababab},
    {ZFlag, 0xabababab, 0xabababab, 0xabababab},
    {CFlag, 0xabababab, 0xabababab, 0xabababab},
    {VFlag, 0xabababab, 0xabababab, 0xabababab},
    {NZFlag, 0xabababab, 0xabababab, 0xabababab},
    {NCFlag, 0xabababab, 0xabababab, 0xabababab},
    {NVFlag, 0xabababab, 0xabababab, 0xabababab},
    {ZCFlag, 0xabababab, 0xabababab, 0xabababab},
    {ZVFlag, 0xabababab, 0xabababab, 0xabababab},
    {CVFlag, 0xabababab, 0xabababab, 0xabababab},
    {NZCFlag, 0xabababab, 0xabababab, 0xabababab},
    {NZVFlag, 0xabababab, 0xabababab, 0xabababab},
    {NCVFlag, 0xabababab, 0xabababab, 0xabababab},
    {ZCVFlag, 0xabababab, 0xabababab, 0xabababab},
    {NZCVFlag, 0xabababab, 0xabababab, 0xabababab}};

static const Inputs kRdIsRn[] = {{NoFlag, 0xffffff83, 0xffffff83, 0xffff8002},
                                 {NoFlag, 0x0000007e, 0x0000007e, 0x7fffffff},
                                 {NoFlag, 0x0000007d, 0x0000007d, 0xffffffe0},
                                 {NoFlag, 0x7fffffff, 0x7fffffff, 0x00000002},
                                 {NoFlag, 0xffff8002, 0xffff8002, 0xfffffffd},
                                 {NoFlag, 0xffffffe0, 0xffffffe0, 0x00007fff},
                                 {NoFlag, 0xffff8000, 0xffff8000, 0xffffff83},
                                 {NoFlag, 0xffff8002, 0xffff8002, 0x80000001},
                                 {NoFlag, 0x00007ffd, 0x00007ffd, 0xffff8003},
                                 {NoFlag, 0x00007fff, 0x00007fff, 0xffffffff},
                                 {NoFlag, 0x00000000, 0x00000000, 0xffffff80},
                                 {NoFlag, 0xffff8001, 0xffff8001, 0x33333333},
                                 {NoFlag, 0xffffff80, 0xffffff80, 0x0000007e},
                                 {NoFlag, 0x0000007e, 0x0000007e, 0x7ffffffd},
                                 {NoFlag, 0xffffff80, 0xffffff80, 0xfffffffd},
                                 {NoFlag, 0x00000020, 0x00000020, 0xffff8002},
                                 {NoFlag, 0xffffff80, 0xffffff80, 0xfffffffe},
                                 {NoFlag, 0x00000002, 0x00000002, 0x00000000},
                                 {NoFlag, 0x0000007e, 0x0000007e, 0x00000001},
                                 {NoFlag, 0x00000002, 0x00000002, 0x0000007f},
                                 {NoFlag, 0x80000000, 0x80000000, 0x80000000},
                                 {NoFlag, 0x7fffffff, 0x7fffffff, 0xffffff80},
                                 {NoFlag, 0x00000001, 0x00000001, 0xfffffffe},
                                 {NoFlag, 0x33333333, 0x33333333, 0x0000007d},
                                 {NoFlag, 0x00000001, 0x00000001, 0x7ffffffe},
                                 {NoFlag, 0x00007ffe, 0x00007ffe, 0x7fffffff},
                                 {NoFlag, 0x80000000, 0x80000000, 0xffffff83},
                                 {NoFlag, 0x00000000, 0x00000000, 0x7ffffffe},
                                 {NoFlag, 0x00000000, 0x00000000, 0x0000007f},
                                 {NoFlag, 0x7fffffff, 0x7fffffff, 0xcccccccc},
                                 {NoFlag, 0xffffff82, 0xffffff82, 0x00000002},
                                 {NoFlag, 0x7ffffffd, 0x7ffffffd, 0xaaaaaaaa},
                                 {NoFlag, 0xcccccccc, 0xcccccccc, 0xffff8001},
                                 {NoFlag, 0xfffffffe, 0xfffffffe, 0xffff8001},
                                 {NoFlag, 0x7fffffff, 0x7fffffff, 0x00000020},
                                 {NoFlag, 0xffffffe0, 0xffffffe0, 0x00007ffe},
                                 {NoFlag, 0x80000001, 0x80000001, 0xffff8000},
                                 {NoFlag, 0xffffff82, 0xffffff82, 0x0000007d},
                                 {NoFlag, 0x0000007e, 0x0000007e, 0x7ffffffe},
                                 {NoFlag, 0x00007ffd, 0x00007ffd, 0xffffff80},
                                 {NoFlag, 0x0000007d, 0x0000007d, 0x0000007e},
                                 {NoFlag, 0xffff8002, 0xffff8002, 0x7fffffff},
                                 {NoFlag, 0xffffffe0, 0xffffffe0, 0x0000007f},
                                 {NoFlag, 0x00007ffe, 0x00007ffe, 0xffffff81},
                                 {NoFlag, 0x80000000, 0x80000000, 0x0000007e},
                                 {NoFlag, 0xffffffff, 0xffffffff, 0xaaaaaaaa},
                                 {NoFlag, 0xfffffffe, 0xfffffffe, 0x00000020},
                                 {NoFlag, 0xffffff82, 0xffffff82, 0xffff8003},
                                 {NoFlag, 0x7ffffffd, 0x7ffffffd, 0xffff8002},
                                 {NoFlag, 0x7ffffffe, 0x7ffffffe, 0x00000000},
                                 {NoFlag, 0xfffffffd, 0xfffffffd, 0xffffffe0},
                                 {NoFlag, 0xffff8000, 0xffff8000, 0xffff8002},
                                 {NoFlag, 0xffffff82, 0xffffff82, 0x7ffffffd},
                                 {NoFlag, 0xcccccccc, 0xcccccccc, 0x80000000},
                                 {NoFlag, 0x80000001, 0x80000001, 0x33333333},
                                 {NoFlag, 0x00000001, 0x00000001, 0x00000002},
                                 {NoFlag, 0x55555555, 0x55555555, 0x0000007f},
                                 {NoFlag, 0xffffffff, 0xffffffff, 0xfffffffd},
                                 {NoFlag, 0xffffff80, 0xffffff80, 0x80000000},
                                 {NoFlag, 0x00000000, 0x00000000, 0x00000020},
                                 {NoFlag, 0xfffffffe, 0xfffffffe, 0xffff8003},
                                 {NoFlag, 0xffff8001, 0xffff8001, 0xffff8000},
                                 {NoFlag, 0x55555555, 0x55555555, 0x55555555},
                                 {NoFlag, 0x00007fff, 0x00007fff, 0xffff8000},
                                 {NoFlag, 0x7fffffff, 0x7fffffff, 0xffffffe0},
                                 {NoFlag, 0x00000001, 0x00000001, 0x55555555},
                                 {NoFlag, 0x33333333, 0x33333333, 0x7ffffffe},
                                 {NoFlag, 0x80000000, 0x80000000, 0xffffffe0},
                                 {NoFlag, 0xffffff83, 0xffffff83, 0x0000007d},
                                 {NoFlag, 0xffff8003, 0xffff8003, 0x00000002},
                                 {NoFlag, 0x7ffffffe, 0x7ffffffe, 0xffffff81},
                                 {NoFlag, 0xfffffffe, 0xfffffffe, 0xffffff80},
                                 {NoFlag, 0x00007ffe, 0x00007ffe, 0xffff8002},
                                 {NoFlag, 0x80000001, 0x80000001, 0xfffffffe},
                                 {NoFlag, 0x7ffffffd, 0x7ffffffd, 0xfffffffd},
                                 {NoFlag, 0x7ffffffd, 0x7ffffffd, 0xfffffffe},
                                 {NoFlag, 0x7ffffffe, 0x7ffffffe, 0xffffff83},
                                 {NoFlag, 0xfffffffd, 0xfffffffd, 0x00007ffe},
                                 {NoFlag, 0x7fffffff, 0x7fffffff, 0x80000000},
                                 {NoFlag, 0xffffff82, 0xffffff82, 0x7fffffff},
                                 {NoFlag, 0xffffffe0, 0xffffffe0, 0xffffff83},
                                 {NoFlag, 0xffff8000, 0xffff8000, 0xffff8000},
                                 {NoFlag, 0x00000001, 0x00000001, 0x7fffffff},
                                 {NoFlag, 0xfffffffe, 0xfffffffe, 0xffffffff},
                                 {NoFlag, 0xffffff82, 0xffffff82, 0xffffffff},
                                 {NoFlag, 0xffffffff, 0xffffffff, 0xfffffffe},
                                 {NoFlag, 0xaaaaaaaa, 0xaaaaaaaa, 0x0000007d},
                                 {NoFlag, 0xffff8001, 0xffff8001, 0xfffffffe},
                                 {NoFlag, 0x00007ffe, 0x00007ffe, 0x0000007d},
                                 {NoFlag, 0xffffff82, 0xffffff82, 0xfffffffe},
                                 {NoFlag, 0x00000000, 0x00000000, 0x00007ffd},
                                 {NoFlag, 0xaaaaaaaa, 0xaaaaaaaa, 0xffff8002},
                                 {NoFlag, 0x0000007f, 0x0000007f, 0xffffff82},
                                 {NoFlag, 0x00007fff, 0x00007fff, 0x33333333},
                                 {NoFlag, 0xfffffffd, 0xfffffffd, 0x80000000},
                                 {NoFlag, 0x00000000, 0x00000000, 0xfffffffd},
                                 {NoFlag, 0x0000007d, 0x0000007d, 0x0000007f},
                                 {NoFlag, 0xfffffffd, 0xfffffffd, 0x0000007e},
                                 {NoFlag, 0xffffffe0, 0xffffffe0, 0x55555555},
                                 {NoFlag, 0xffffffff, 0xffffffff, 0x80000000},
                                 {NoFlag, 0xffffffe0, 0xffffffe0, 0x0000007e},
                                 {NoFlag, 0xffffff81, 0xffffff81, 0x00007ffd},
                                 {NoFlag, 0x00000020, 0x00000020, 0xffff8001},
                                 {NoFlag, 0x00007fff, 0x00007fff, 0xffffff83},
                                 {NoFlag, 0x33333333, 0x33333333, 0x00000000},
                                 {NoFlag, 0xffff8000, 0xffff8000, 0xffffff82},
                                 {NoFlag, 0xffff8001, 0xffff8001, 0x0000007e},
                                 {NoFlag, 0xffffff80, 0xffffff80, 0x00000001},
                                 {NoFlag, 0x80000000, 0x80000000, 0xcccccccc},
                                 {NoFlag, 0x00000002, 0x00000002, 0x00007ffd},
                                 {NoFlag, 0x7ffffffe, 0x7ffffffe, 0x80000001},
                                 {NoFlag, 0x00000020, 0x00000020, 0x00007ffe},
                                 {NoFlag, 0xffff8000, 0xffff8000, 0xfffffffd},
                                 {NoFlag, 0x7fffffff, 0x7fffffff, 0xffff8001},
                                 {NoFlag, 0x00000000, 0x00000000, 0xffffff83},
                                 {NoFlag, 0x0000007f, 0x0000007f, 0x00000020},
                                 {NoFlag, 0x80000001, 0x80000001, 0xffff8003},
                                 {NoFlag, 0xffff8001, 0xffff8001, 0x0000007f},
                                 {NoFlag, 0x0000007f, 0x0000007f, 0x80000001},
                                 {NoFlag, 0x00000002, 0x00000002, 0x7ffffffe},
                                 {NoFlag, 0xffffff82, 0xffffff82, 0xffffff83},
                                 {NoFlag, 0x00007ffd, 0x00007ffd, 0x7fffffff},
                                 {NoFlag, 0x7ffffffe, 0x7ffffffe, 0xfffffffe},
                                 {NoFlag, 0xffffff82, 0xffffff82, 0xffff8000},
                                 {NoFlag, 0xfffffffe, 0xfffffffe, 0xffff8000},
                                 {NoFlag, 0xffff8002, 0xffff8002, 0xffffff81},
                                 {NoFlag, 0x33333333, 0x33333333, 0x7fffffff},
                                 {NoFlag, 0x80000001, 0x80000001, 0x00007fff},
                                 {NoFlag, 0xffff8002, 0xffff8002, 0xcccccccc},
                                 {NoFlag, 0xffffffff, 0xffffffff, 0x00000002},
                                 {NoFlag, 0x33333333, 0x33333333, 0xffffff81},
                                 {NoFlag, 0xfffffffd, 0xfffffffd, 0xffffff80},
                                 {NoFlag, 0x55555555, 0x55555555, 0xaaaaaaaa},
                                 {NoFlag, 0x33333333, 0x33333333, 0xffffff82},
                                 {NoFlag, 0xffffff80, 0xffffff80, 0xaaaaaaaa},
                                 {NoFlag, 0x0000007e, 0x0000007e, 0x00000020},
                                 {NoFlag, 0xffffff83, 0xffffff83, 0x00007ffd},
                                 {NoFlag, 0xffffff82, 0xffffff82, 0xaaaaaaaa},
                                 {NoFlag, 0xffff8003, 0xffff8003, 0xffffffff},
                                 {NoFlag, 0xaaaaaaaa, 0xaaaaaaaa, 0xfffffffe},
                                 {NoFlag, 0xaaaaaaaa, 0xaaaaaaaa, 0x00000000},
                                 {NoFlag, 0xaaaaaaaa, 0xaaaaaaaa, 0x0000007f},
                                 {NoFlag, 0x0000007f, 0x0000007f, 0x0000007d},
                                 {NoFlag, 0xfffffffd, 0xfffffffd, 0x55555555},
                                 {NoFlag, 0xffffffff, 0xffffffff, 0x00000020},
                                 {NoFlag, 0x00007ffe, 0x00007ffe, 0xffffff83},
                                 {NoFlag, 0x7fffffff, 0x7fffffff, 0x55555555},
                                 {NoFlag, 0x55555555, 0x55555555, 0xcccccccc},
                                 {NoFlag, 0xffffffe0, 0xffffffe0, 0xffff8003},
                                 {NoFlag, 0x7ffffffe, 0x7ffffffe, 0x00007ffe},
                                 {NoFlag, 0x00007ffd, 0x00007ffd, 0xffff8002},
                                 {NoFlag, 0x00007ffd, 0x00007ffd, 0x00000001},
                                 {NoFlag, 0x00000000, 0x00000000, 0x00007ffe},
                                 {NoFlag, 0xffffff80, 0xffffff80, 0x00000020},
                                 {NoFlag, 0xffff8000, 0xffff8000, 0x0000007d},
                                 {NoFlag, 0xffff8003, 0xffff8003, 0x00000000},
                                 {NoFlag, 0x0000007e, 0x0000007e, 0x80000000},
                                 {NoFlag, 0xfffffffd, 0xfffffffd, 0x00000000},
                                 {NoFlag, 0xffffff80, 0xffffff80, 0xffffffff},
                                 {NoFlag, 0xcccccccc, 0xcccccccc, 0x0000007f},
                                 {NoFlag, 0x7ffffffd, 0x7ffffffd, 0x00000000},
                                 {NoFlag, 0x00007fff, 0x00007fff, 0x00000000},
                                 {NoFlag, 0x0000007f, 0x0000007f, 0x00000001},
                                 {NoFlag, 0xffffffff, 0xffffffff, 0xffffff82},
                                 {NoFlag, 0x00007ffe, 0x00007ffe, 0x00007ffd},
                                 {NoFlag, 0xaaaaaaaa, 0xaaaaaaaa, 0x33333333},
                                 {NoFlag, 0xffffff82, 0xffffff82, 0x55555555},
                                 {NoFlag, 0xffff8003, 0xffff8003, 0x0000007e},
                                 {NoFlag, 0xffffff83, 0xffffff83, 0x00000002},
                                 {NoFlag, 0xffffff82, 0xffffff82, 0x33333333},
                                 {NoFlag, 0x55555555, 0x55555555, 0xffffffff},
                                 {NoFlag, 0xaaaaaaaa, 0xaaaaaaaa, 0x80000001},
                                 {NoFlag, 0xffffff83, 0xffffff83, 0xffffffe0},
                                 {NoFlag, 0x00000001, 0x00000001, 0xffffffe0},
                                 {NoFlag, 0x33333333, 0x33333333, 0x33333333},
                                 {NoFlag, 0x55555555, 0x55555555, 0x00000001},
                                 {NoFlag, 0xffffff83, 0xffffff83, 0x00007fff},
                                 {NoFlag, 0x00000002, 0x00000002, 0xfffffffd},
                                 {NoFlag, 0xffffffe0, 0xffffffe0, 0xffff8002},
                                 {NoFlag, 0x80000000, 0x80000000, 0x00007ffd},
                                 {NoFlag, 0xffffff83, 0xffffff83, 0xfffffffe},
                                 {NoFlag, 0x80000001, 0x80000001, 0xffffffff},
                                 {NoFlag, 0xffff8003, 0xffff8003, 0x00000020},
                                 {NoFlag, 0xffffff82, 0xffffff82, 0xcccccccc},
                                 {NoFlag, 0x00000020, 0x00000020, 0x7fffffff},
                                 {NoFlag, 0xffffff80, 0xffffff80, 0x55555555},
                                 {NoFlag, 0x00000001, 0x00000001, 0x00000020},
                                 {NoFlag, 0xffff8001, 0xffff8001, 0x00007fff},
                                 {NoFlag, 0x00000020, 0x00000020, 0xaaaaaaaa},
                                 {NoFlag, 0x55555555, 0x55555555, 0x7fffffff},
                                 {NoFlag, 0xfffffffe, 0xfffffffe, 0x7fffffff},
                                 {NoFlag, 0x00007fff, 0x00007fff, 0x55555555},
                                 {NoFlag, 0x55555555, 0x55555555, 0x0000007d},
                                 {NoFlag, 0xcccccccc, 0xcccccccc, 0x7ffffffe},
                                 {NoFlag, 0xffff8002, 0xffff8002, 0x00007ffe},
                                 {NoFlag, 0xfffffffe, 0xfffffffe, 0xffffff81},
                                 {NoFlag, 0xffffff81, 0xffffff81, 0x0000007d},
                                 {NoFlag, 0x00000020, 0x00000020, 0x0000007e},
                                 {NoFlag, 0xffffffff, 0xffffffff, 0x00007ffe},
                                 {NoFlag, 0xffff8002, 0xffff8002, 0x0000007e}};

static const Inputs kRdIsRm[] = {{NoFlag, 0x55555555, 0x7ffffffe, 0x55555555},
                                 {NoFlag, 0xfffffffe, 0x00000001, 0xfffffffe},
                                 {NoFlag, 0xffffff82, 0xffffff82, 0xffffff82},
                                 {NoFlag, 0xffff8000, 0xffff8003, 0xffff8000},
                                 {NoFlag, 0x00000001, 0x00000000, 0x00000001},
                                 {NoFlag, 0xffffff81, 0x00007fff, 0xffffff81},
                                 {NoFlag, 0x0000007d, 0xffff8002, 0x0000007d},
                                 {NoFlag, 0x80000000, 0xffff8000, 0x80000000},
                                 {NoFlag, 0xffffff80, 0x00000020, 0xffffff80},
                                 {NoFlag, 0x55555555, 0xffffff81, 0x55555555},
                                 {NoFlag, 0x00007ffd, 0xffffff82, 0x00007ffd},
                                 {NoFlag, 0x55555555, 0x00007fff, 0x55555555},
                                 {NoFlag, 0x7ffffffd, 0xffff8000, 0x7ffffffd},
                                 {NoFlag, 0xffffffff, 0xffffff83, 0xffffffff},
                                 {NoFlag, 0x00000000, 0xffffffff, 0x00000000},
                                 {NoFlag, 0xffff8002, 0x33333333, 0xffff8002},
                                 {NoFlag, 0x00007ffd, 0xaaaaaaaa, 0x00007ffd},
                                 {NoFlag, 0x55555555, 0xffff8000, 0x55555555},
                                 {NoFlag, 0x80000001, 0xffffffff, 0x80000001},
                                 {NoFlag, 0x0000007d, 0xffffff83, 0x0000007d},
                                 {NoFlag, 0x0000007e, 0xffffff82, 0x0000007e},
                                 {NoFlag, 0xcccccccc, 0x0000007d, 0xcccccccc},
                                 {NoFlag, 0xffff8002, 0xffffffff, 0xffff8002},
                                 {NoFlag, 0xffffff81, 0x0000007f, 0xffffff81},
                                 {NoFlag, 0xffff8000, 0xffffff83, 0xffff8000},
                                 {NoFlag, 0xffffffff, 0xffffffe0, 0xffffffff},
                                 {NoFlag, 0xfffffffd, 0x80000001, 0xfffffffd},
                                 {NoFlag, 0x55555555, 0x80000000, 0x55555555},
                                 {NoFlag, 0xffff8000, 0x0000007d, 0xffff8000},
                                 {NoFlag, 0xaaaaaaaa, 0xffff8003, 0xaaaaaaaa},
                                 {NoFlag, 0x00000001, 0x00007ffd, 0x00000001},
                                 {NoFlag, 0x0000007e, 0x7ffffffe, 0x0000007e},
                                 {NoFlag, 0x00000020, 0x00007ffd, 0x00000020},
                                 {NoFlag, 0xffffff81, 0x7ffffffd, 0xffffff81},
                                 {NoFlag, 0xffffff83, 0x0000007f, 0xffffff83},
                                 {NoFlag, 0x00000001, 0x0000007e, 0x00000001},
                                 {NoFlag, 0xffffff82, 0xfffffffd, 0xffffff82},
                                 {NoFlag, 0xffff8003, 0x7ffffffe, 0xffff8003},
                                 {NoFlag, 0x00000002, 0x00000002, 0x00000002},
                                 {NoFlag, 0xffffff83, 0xffff8001, 0xffffff83},
                                 {NoFlag, 0xffff8002, 0xfffffffe, 0xffff8002},
                                 {NoFlag, 0xffffff80, 0xffffff81, 0xffffff80},
                                 {NoFlag, 0x7fffffff, 0xffffff81, 0x7fffffff},
                                 {NoFlag, 0x00000020, 0xffffff81, 0x00000020},
                                 {NoFlag, 0x0000007f, 0xffffffff, 0x0000007f},
                                 {NoFlag, 0x0000007d, 0xcccccccc, 0x0000007d},
                                 {NoFlag, 0x00007fff, 0x55555555, 0x00007fff},
                                 {NoFlag, 0xffff8003, 0x00007ffd, 0xffff8003},
                                 {NoFlag, 0x80000001, 0x80000001, 0x80000001},
                                 {NoFlag, 0xffffffff, 0xfffffffd, 0xffffffff},
                                 {NoFlag, 0xffff8000, 0xfffffffe, 0xffff8000},
                                 {NoFlag, 0xcccccccc, 0x0000007f, 0xcccccccc},
                                 {NoFlag, 0x00000001, 0x00000002, 0x00000001},
                                 {NoFlag, 0xffffff82, 0xffffff81, 0xffffff82},
                                 {NoFlag, 0xfffffffd, 0x00007ffd, 0xfffffffd},
                                 {NoFlag, 0x80000001, 0x33333333, 0x80000001},
                                 {NoFlag, 0xffffff82, 0xffff8002, 0xffffff82},
                                 {NoFlag, 0xffff8003, 0xfffffffd, 0xffff8003},
                                 {NoFlag, 0xffffff81, 0x00000020, 0xffffff81},
                                 {NoFlag, 0xffff8001, 0xffff8003, 0xffff8001},
                                 {NoFlag, 0x00000001, 0x80000001, 0x00000001},
                                 {NoFlag, 0xfffffffd, 0x00000002, 0xfffffffd},
                                 {NoFlag, 0xffff8003, 0x7ffffffd, 0xffff8003},
                                 {NoFlag, 0x0000007e, 0xaaaaaaaa, 0x0000007e},
                                 {NoFlag, 0x7ffffffe, 0x7fffffff, 0x7ffffffe},
                                 {NoFlag, 0x00007ffd, 0x00007ffe, 0x00007ffd},
                                 {NoFlag, 0x00007fff, 0x80000001, 0x00007fff},
                                 {NoFlag, 0x00007fff, 0xfffffffe, 0x00007fff},
                                 {NoFlag, 0x00000001, 0xffffff80, 0x00000001},
                                 {NoFlag, 0x55555555, 0xcccccccc, 0x55555555},
                                 {NoFlag, 0x7ffffffd, 0xffffffe0, 0x7ffffffd},
                                 {NoFlag, 0xffffff81, 0xfffffffe, 0xffffff81},
                                 {NoFlag, 0xffffff82, 0x00007ffe, 0xffffff82},
                                 {NoFlag, 0xffffff82, 0x80000001, 0xffffff82},
                                 {NoFlag, 0x0000007f, 0xffff8001, 0x0000007f},
                                 {NoFlag, 0x7ffffffd, 0xffffff83, 0x7ffffffd},
                                 {NoFlag, 0xffffff82, 0xcccccccc, 0xffffff82},
                                 {NoFlag, 0x00000020, 0xffffff83, 0x00000020},
                                 {NoFlag, 0x00007ffe, 0x80000000, 0x00007ffe},
                                 {NoFlag, 0x0000007f, 0xffff8000, 0x0000007f},
                                 {NoFlag, 0xffffff82, 0x33333333, 0xffffff82},
                                 {NoFlag, 0x7ffffffd, 0x7ffffffd, 0x7ffffffd},
                                 {NoFlag, 0xffffff80, 0xffff8001, 0xffffff80},
                                 {NoFlag, 0x00000002, 0xaaaaaaaa, 0x00000002},
                                 {NoFlag, 0xffffffff, 0x7fffffff, 0xffffffff},
                                 {NoFlag, 0xfffffffd, 0xfffffffe, 0xfffffffd},
                                 {NoFlag, 0x00000020, 0x00000001, 0x00000020},
                                 {NoFlag, 0x55555555, 0x00000001, 0x55555555},
                                 {NoFlag, 0x55555555, 0xffffff80, 0x55555555},
                                 {NoFlag, 0xffffffff, 0x00007fff, 0xffffffff},
                                 {NoFlag, 0x00000020, 0xaaaaaaaa, 0x00000020},
                                 {NoFlag, 0x00000002, 0x00007ffe, 0x00000002},
                                 {NoFlag, 0x00000001, 0xcccccccc, 0x00000001},
                                 {NoFlag, 0xffff8001, 0x00000000, 0xffff8001},
                                 {NoFlag, 0x00000001, 0xffff8000, 0x00000001},
                                 {NoFlag, 0xffffffe0, 0x00007fff, 0xffffffe0},
                                 {NoFlag, 0xfffffffe, 0x00007fff, 0xfffffffe},
                                 {NoFlag, 0xffffff83, 0x00000001, 0xffffff83},
                                 {NoFlag, 0x00007fff, 0xffff8002, 0x00007fff},
                                 {NoFlag, 0x7ffffffd, 0x7ffffffe, 0x7ffffffd},
                                 {NoFlag, 0x80000001, 0xaaaaaaaa, 0x80000001},
                                 {NoFlag, 0x80000001, 0xcccccccc, 0x80000001},
                                 {NoFlag, 0x00007ffe, 0xffffffe0, 0x00007ffe},
                                 {NoFlag, 0x00007ffe, 0xfffffffd, 0x00007ffe},
                                 {NoFlag, 0x55555555, 0xaaaaaaaa, 0x55555555},
                                 {NoFlag, 0xffffffe0, 0x00000001, 0xffffffe0},
                                 {NoFlag, 0x0000007e, 0x00007fff, 0x0000007e},
                                 {NoFlag, 0xfffffffe, 0xfffffffd, 0xfffffffe},
                                 {NoFlag, 0x33333333, 0x0000007d, 0x33333333},
                                 {NoFlag, 0xffffff81, 0x7fffffff, 0xffffff81},
                                 {NoFlag, 0x0000007e, 0x0000007d, 0x0000007e},
                                 {NoFlag, 0x00000001, 0xffffff81, 0x00000001},
                                 {NoFlag, 0x80000000, 0x00000002, 0x80000000},
                                 {NoFlag, 0x0000007d, 0xffff8003, 0x0000007d},
                                 {NoFlag, 0x7ffffffe, 0x00007ffd, 0x7ffffffe},
                                 {NoFlag, 0x7ffffffe, 0xaaaaaaaa, 0x7ffffffe},
                                 {NoFlag, 0x00000000, 0xffff8000, 0x00000000},
                                 {NoFlag, 0x33333333, 0x00000002, 0x33333333},
                                 {NoFlag, 0xffffff81, 0xffffff83, 0xffffff81},
                                 {NoFlag, 0x7ffffffe, 0x00007ffe, 0x7ffffffe},
                                 {NoFlag, 0x80000000, 0x0000007d, 0x80000000},
                                 {NoFlag, 0x00000020, 0x00000002, 0x00000020},
                                 {NoFlag, 0x33333333, 0x80000001, 0x33333333},
                                 {NoFlag, 0xffffff83, 0x00007ffd, 0xffffff83},
                                 {NoFlag, 0x00007ffd, 0xffffff83, 0x00007ffd},
                                 {NoFlag, 0xffff8001, 0x80000000, 0xffff8001},
                                 {NoFlag, 0x00000000, 0x80000000, 0x00000000},
                                 {NoFlag, 0xffffffe0, 0xffffffff, 0xffffffe0},
                                 {NoFlag, 0x80000000, 0xffffff83, 0x80000000},
                                 {NoFlag, 0x00000020, 0xffffff80, 0x00000020},
                                 {NoFlag, 0x7ffffffd, 0xffff8001, 0x7ffffffd},
                                 {NoFlag, 0x80000001, 0xffff8003, 0x80000001},
                                 {NoFlag, 0x00007ffe, 0x7fffffff, 0x00007ffe},
                                 {NoFlag, 0x7fffffff, 0x00000002, 0x7fffffff},
                                 {NoFlag, 0xffffff83, 0xffff8003, 0xffffff83},
                                 {NoFlag, 0xaaaaaaaa, 0xcccccccc, 0xaaaaaaaa},
                                 {NoFlag, 0x0000007f, 0xffffff80, 0x0000007f},
                                 {NoFlag, 0x80000001, 0x00007ffd, 0x80000001},
                                 {NoFlag, 0xffff8000, 0x80000001, 0xffff8000},
                                 {NoFlag, 0x00007fff, 0x00007ffd, 0x00007fff},
                                 {NoFlag, 0x0000007e, 0x0000007f, 0x0000007e},
                                 {NoFlag, 0x00000002, 0x0000007d, 0x00000002},
                                 {NoFlag, 0x80000001, 0x7fffffff, 0x80000001},
                                 {NoFlag, 0x0000007e, 0xffffff81, 0x0000007e},
                                 {NoFlag, 0x7ffffffe, 0xffff8001, 0x7ffffffe},
                                 {NoFlag, 0x7fffffff, 0x80000001, 0x7fffffff},
                                 {NoFlag, 0x7ffffffd, 0x0000007f, 0x7ffffffd},
                                 {NoFlag, 0xffffff81, 0xffffff81, 0xffffff81},
                                 {NoFlag, 0x00000001, 0xfffffffd, 0x00000001},
                                 {NoFlag, 0x00000001, 0xffffffff, 0x00000001},
                                 {NoFlag, 0x7ffffffd, 0x55555555, 0x7ffffffd},
                                 {NoFlag, 0x55555555, 0x0000007f, 0x55555555},
                                 {NoFlag, 0x55555555, 0xffff8003, 0x55555555},
                                 {NoFlag, 0xaaaaaaaa, 0x00007ffd, 0xaaaaaaaa},
                                 {NoFlag, 0x0000007e, 0x33333333, 0x0000007e},
                                 {NoFlag, 0xfffffffe, 0x80000001, 0xfffffffe},
                                 {NoFlag, 0xfffffffe, 0xffff8000, 0xfffffffe},
                                 {NoFlag, 0xffffffe0, 0xffffff81, 0xffffffe0},
                                 {NoFlag, 0x7fffffff, 0x0000007f, 0x7fffffff},
                                 {NoFlag, 0xffff8003, 0x0000007f, 0xffff8003},
                                 {NoFlag, 0xffffff82, 0x00007ffd, 0xffffff82},
                                 {NoFlag, 0x33333333, 0xffffffff, 0x33333333},
                                 {NoFlag, 0xffffffe0, 0xcccccccc, 0xffffffe0},
                                 {NoFlag, 0xffffff83, 0x7ffffffd, 0xffffff83},
                                 {NoFlag, 0x0000007e, 0xcccccccc, 0x0000007e},
                                 {NoFlag, 0x00000002, 0xfffffffd, 0x00000002},
                                 {NoFlag, 0x00007fff, 0xcccccccc, 0x00007fff},
                                 {NoFlag, 0x7fffffff, 0x00007fff, 0x7fffffff},
                                 {NoFlag, 0xffffffe0, 0x33333333, 0xffffffe0},
                                 {NoFlag, 0x0000007f, 0x0000007d, 0x0000007f},
                                 {NoFlag, 0x0000007f, 0xffffffe0, 0x0000007f},
                                 {NoFlag, 0x00007fff, 0xffff8000, 0x00007fff},
                                 {NoFlag, 0x7fffffff, 0xffffffff, 0x7fffffff},
                                 {NoFlag, 0xffff8000, 0x7ffffffd, 0xffff8000},
                                 {NoFlag, 0xcccccccc, 0x0000007e, 0xcccccccc},
                                 {NoFlag, 0x33333333, 0xffff8003, 0x33333333},
                                 {NoFlag, 0x55555555, 0x00000002, 0x55555555},
                                 {NoFlag, 0x00000001, 0x00000001, 0x00000001},
                                 {NoFlag, 0xaaaaaaaa, 0x33333333, 0xaaaaaaaa},
                                 {NoFlag, 0x7ffffffd, 0x00000001, 0x7ffffffd},
                                 {NoFlag, 0xffffff82, 0xffff8000, 0xffffff82},
                                 {NoFlag, 0x0000007d, 0x55555555, 0x0000007d},
                                 {NoFlag, 0xffff8000, 0x7ffffffe, 0xffff8000},
                                 {NoFlag, 0x7fffffff, 0xffffffe0, 0x7fffffff},
                                 {NoFlag, 0x7fffffff, 0xffff8003, 0x7fffffff},
                                 {NoFlag, 0xffffff82, 0xaaaaaaaa, 0xffffff82},
                                 {NoFlag, 0xfffffffd, 0xffffff80, 0xfffffffd},
                                 {NoFlag, 0x7ffffffd, 0x80000001, 0x7ffffffd},
                                 {NoFlag, 0x00000000, 0x00007ffd, 0x00000000},
                                 {NoFlag, 0xffffffff, 0xffffff80, 0xffffffff},
                                 {NoFlag, 0xffffff80, 0xcccccccc, 0xffffff80},
                                 {NoFlag, 0x00007ffe, 0x55555555, 0x00007ffe},
                                 {NoFlag, 0xffff8000, 0xffff8000, 0xffff8000},
                                 {NoFlag, 0xffffffff, 0xffff8000, 0xffffffff},
                                 {NoFlag, 0x80000001, 0x0000007d, 0x80000001},
                                 {NoFlag, 0xffffffe0, 0xffff8002, 0xffffffe0},
                                 {NoFlag, 0xfffffffe, 0xffffffe0, 0xfffffffe},
                                 {NoFlag, 0x80000000, 0xffff8003, 0x80000000},
                                 {NoFlag, 0x80000001, 0xffffff81, 0x80000001},
                                 {NoFlag, 0xffffffe0, 0x00007ffe, 0xffffffe0}};

static const Inputs kRdIsNotRnIsNotRm[] = {
    {NoFlag, 0x0000007e, 0x0000007e, 0x0000007d},
    {NoFlag, 0x55555555, 0x00000002, 0xffff8002},
    {NoFlag, 0xffffffe0, 0x80000001, 0x00000000},
    {NoFlag, 0x55555555, 0xffffff83, 0x00000002},
    {NoFlag, 0xffffffe0, 0xffffffe0, 0x00000002},
    {NoFlag, 0x00000000, 0x80000001, 0xffffff82},
    {NoFlag, 0x80000001, 0x00007fff, 0x0000007f},
    {NoFlag, 0xffffff80, 0x0000007d, 0x7ffffffe},
    {NoFlag, 0xaaaaaaaa, 0x00000020, 0xffff8002},
    {NoFlag, 0x33333333, 0x55555555, 0x00000001},
    {NoFlag, 0x7ffffffe, 0x33333333, 0x00000000},
    {NoFlag, 0x80000000, 0x7ffffffd, 0x55555555},
    {NoFlag, 0xcccccccc, 0xffff8001, 0x7ffffffe},
    {NoFlag, 0x00000020, 0xffffff83, 0xffff8003},
    {NoFlag, 0x00007fff, 0xffffffe0, 0xffffff81},
    {NoFlag, 0xffff8000, 0xffff8001, 0x0000007e},
    {NoFlag, 0x33333333, 0x0000007e, 0x00000020},
    {NoFlag, 0x0000007f, 0xfffffffd, 0xaaaaaaaa},
    {NoFlag, 0xffffff83, 0xffffff82, 0x7ffffffd},
    {NoFlag, 0x0000007e, 0xcccccccc, 0x7fffffff},
    {NoFlag, 0xffff8001, 0x80000001, 0xffffffff},
    {NoFlag, 0xffffff81, 0x00000020, 0x7ffffffe},
    {NoFlag, 0xffffff83, 0xffffff81, 0xffffffe0},
    {NoFlag, 0xffffffe0, 0xffffff81, 0xfffffffd},
    {NoFlag, 0x80000001, 0xffffffff, 0xffffffff},
    {NoFlag, 0x7ffffffe, 0xffff8000, 0xcccccccc},
    {NoFlag, 0xffffff80, 0x00007ffe, 0xffffff82},
    {NoFlag, 0x0000007e, 0x0000007d, 0xffff8003},
    {NoFlag, 0xffff8002, 0xffffff81, 0x0000007e},
    {NoFlag, 0x00007fff, 0x7ffffffd, 0xfffffffe},
    {NoFlag, 0x00007ffe, 0x80000001, 0xffffff81},
    {NoFlag, 0xffffff81, 0x00007ffd, 0xfffffffd},
    {NoFlag, 0x00000020, 0x7fffffff, 0xffff8003},
    {NoFlag, 0x0000007e, 0x0000007d, 0x33333333},
    {NoFlag, 0xcccccccc, 0xffff8000, 0x00007ffe},
    {NoFlag, 0x00007fff, 0xffff8000, 0x00000020},
    {NoFlag, 0x00007ffd, 0x00007fff, 0xffffffe0},
    {NoFlag, 0x7ffffffd, 0x00000000, 0x00007ffe},
    {NoFlag, 0xffffff82, 0x33333333, 0x00000001},
    {NoFlag, 0x7ffffffe, 0xffffff80, 0x00000020},
    {NoFlag, 0x00007fff, 0xffffff83, 0x00007ffd},
    {NoFlag, 0xffff8001, 0xffffffff, 0x80000001},
    {NoFlag, 0x00000002, 0xffffff81, 0xcccccccc},
    {NoFlag, 0x55555555, 0x0000007f, 0xffff8001},
    {NoFlag, 0x80000000, 0x00000020, 0x80000000},
    {NoFlag, 0xffffff83, 0x00007fff, 0xffffff80},
    {NoFlag, 0x33333333, 0x7ffffffe, 0x7ffffffd},
    {NoFlag, 0xffffff80, 0xffffffff, 0x00000001},
    {NoFlag, 0x00007ffd, 0x7ffffffd, 0xffffff83},
    {NoFlag, 0x33333333, 0xffff8001, 0xffffffe0},
    {NoFlag, 0xffff8001, 0xffffff80, 0x00007ffd},
    {NoFlag, 0xffffffe0, 0x00007fff, 0x00007ffe},
    {NoFlag, 0x0000007d, 0x00000000, 0xffff8000},
    {NoFlag, 0x7ffffffe, 0xaaaaaaaa, 0x7ffffffe},
    {NoFlag, 0x0000007e, 0x00007ffd, 0xffffffe0},
    {NoFlag, 0xfffffffd, 0xffffffe0, 0xffffff83},
    {NoFlag, 0x00000001, 0xffffffe0, 0x7ffffffd},
    {NoFlag, 0xfffffffd, 0xffff8002, 0x80000000},
    {NoFlag, 0x00000020, 0xffffffff, 0x80000000},
    {NoFlag, 0x00000001, 0x80000001, 0xffff8003},
    {NoFlag, 0xffff8003, 0xaaaaaaaa, 0xffffff81},
    {NoFlag, 0x0000007f, 0xfffffffd, 0xffffffe0},
    {NoFlag, 0x00007ffe, 0xffffff80, 0x00007ffe},
    {NoFlag, 0xffff8002, 0xffff8003, 0xffffffff},
    {NoFlag, 0x7ffffffe, 0xffffff82, 0xffff8000},
    {NoFlag, 0xffff8000, 0x00000002, 0x80000000},
    {NoFlag, 0xffffff80, 0xffffff82, 0xffffff81},
    {NoFlag, 0x00000000, 0xcccccccc, 0x00007ffd},
    {NoFlag, 0x55555555, 0x00007ffe, 0x7fffffff},
    {NoFlag, 0x00000002, 0xffffff81, 0xaaaaaaaa},
    {NoFlag, 0x00007ffd, 0x0000007e, 0x00000002},
    {NoFlag, 0xffffff83, 0x0000007e, 0xffffff80},
    {NoFlag, 0xcccccccc, 0x00007ffe, 0xaaaaaaaa},
    {NoFlag, 0x7ffffffe, 0x55555555, 0xffff8003},
    {NoFlag, 0xfffffffd, 0x00000001, 0xffffff80},
    {NoFlag, 0x00007ffd, 0x55555555, 0x80000001},
    {NoFlag, 0x0000007f, 0x00000000, 0x0000007e},
    {NoFlag, 0x7fffffff, 0xaaaaaaaa, 0x00000000},
    {NoFlag, 0x7ffffffd, 0xffffff81, 0xcccccccc},
    {NoFlag, 0xffffffe0, 0xcccccccc, 0xfffffffd},
    {NoFlag, 0x00000002, 0xffff8000, 0x7ffffffd},
    {NoFlag, 0xffffffe0, 0xffff8000, 0x80000001},
    {NoFlag, 0x7ffffffd, 0xffff8003, 0xffff8001},
    {NoFlag, 0x33333333, 0x00007ffd, 0x80000000},
    {NoFlag, 0x7ffffffd, 0x00007fff, 0xcccccccc},
    {NoFlag, 0xffffffff, 0xffffff80, 0x00007ffe},
    {NoFlag, 0xffffff83, 0x7ffffffd, 0xaaaaaaaa},
    {NoFlag, 0xfffffffd, 0xffff8003, 0x0000007f},
    {NoFlag, 0xfffffffe, 0xfffffffe, 0xfffffffd},
    {NoFlag, 0x00007fff, 0xfffffffe, 0x55555555},
    {NoFlag, 0x7ffffffd, 0xfffffffe, 0xfffffffe},
    {NoFlag, 0xfffffffe, 0xffffffff, 0x00007fff},
    {NoFlag, 0x7ffffffd, 0x0000007e, 0x00007ffd},
    {NoFlag, 0x7ffffffd, 0xffffffe0, 0x00000002},
    {NoFlag, 0xffffffff, 0x00007ffd, 0xffffff81},
    {NoFlag, 0xffff8001, 0x00000020, 0xfffffffd},
    {NoFlag, 0x00007fff, 0x0000007d, 0xffffff83},
    {NoFlag, 0x00000002, 0x55555555, 0x7ffffffe},
    {NoFlag, 0x00007fff, 0x00007ffe, 0x00000002},
    {NoFlag, 0x80000001, 0x7fffffff, 0x00007ffd},
    {NoFlag, 0x0000007f, 0xffffffff, 0x00000001},
    {NoFlag, 0xffff8001, 0x33333333, 0xffffff83},
    {NoFlag, 0x00007fff, 0xcccccccc, 0x33333333},
    {NoFlag, 0x33333333, 0xffffff80, 0x00000001},
    {NoFlag, 0x00007fff, 0xcccccccc, 0x00007ffd},
    {NoFlag, 0xffff8002, 0xfffffffd, 0x7ffffffe},
    {NoFlag, 0x00007ffe, 0x7ffffffe, 0xffffff83},
    {NoFlag, 0xffffffe0, 0x0000007f, 0xffff8001},
    {NoFlag, 0x80000000, 0x00007fff, 0xffffff80},
    {NoFlag, 0x7fffffff, 0x00007fff, 0x7ffffffe},
    {NoFlag, 0xffff8002, 0x55555555, 0xffff8001},
    {NoFlag, 0xffffff80, 0x00000000, 0xffffff80},
    {NoFlag, 0x00007ffd, 0x00007fff, 0x00000002},
    {NoFlag, 0x00000000, 0x55555555, 0xffff8003},
    {NoFlag, 0x0000007f, 0xffff8003, 0x00000020},
    {NoFlag, 0x00000000, 0xffff8002, 0x7fffffff},
    {NoFlag, 0x00007fff, 0x55555555, 0x00000000},
    {NoFlag, 0x7fffffff, 0x00007ffe, 0xffffff81},
    {NoFlag, 0x0000007e, 0x80000001, 0x00007ffe},
    {NoFlag, 0x7ffffffd, 0xaaaaaaaa, 0x00000020},
    {NoFlag, 0xfffffffd, 0xfffffffe, 0x00000002},
    {NoFlag, 0xffffff80, 0xffff8000, 0xffff8002},
    {NoFlag, 0x0000007d, 0x00007fff, 0xaaaaaaaa},
    {NoFlag, 0xfffffffd, 0xffffff80, 0x00007ffd},
    {NoFlag, 0xffffff82, 0x80000000, 0xffffff80},
    {NoFlag, 0xffffffe0, 0x55555555, 0xfffffffd},
    {NoFlag, 0xffffffff, 0xffffffff, 0x00007ffd},
    {NoFlag, 0x0000007e, 0xfffffffe, 0xffffff80},
    {NoFlag, 0xffff8000, 0xffffff82, 0xffff8002},
    {NoFlag, 0xaaaaaaaa, 0x7ffffffe, 0xffff8000},
    {NoFlag, 0x55555555, 0xffff8003, 0xffffff80},
    {NoFlag, 0x7ffffffe, 0x00000020, 0xffffffe0},
    {NoFlag, 0x00000001, 0xffff8001, 0xffffffe0},
    {NoFlag, 0xcccccccc, 0xffff8000, 0xffff8002},
    {NoFlag, 0x80000000, 0x00000002, 0x7ffffffe},
    {NoFlag, 0x00000002, 0x0000007f, 0xffffff81},
    {NoFlag, 0xffffffff, 0x00000001, 0x7fffffff},
    {NoFlag, 0xffffff83, 0x00000000, 0x33333333},
    {NoFlag, 0xffff8000, 0xffffff83, 0xcccccccc},
    {NoFlag, 0x80000000, 0x00000020, 0x00007ffd},
    {NoFlag, 0xffffff81, 0xcccccccc, 0x00000000},
    {NoFlag, 0xffffffff, 0xffff8000, 0x00007fff},
    {NoFlag, 0xffff8003, 0xcccccccc, 0x00007ffe},
    {NoFlag, 0xffffffff, 0xfffffffd, 0x7ffffffe},
    {NoFlag, 0xffff8003, 0xaaaaaaaa, 0x55555555},
    {NoFlag, 0x00000000, 0xaaaaaaaa, 0xffffff81},
    {NoFlag, 0x0000007f, 0xfffffffe, 0xffff8000},
    {NoFlag, 0x00000001, 0xffffffe0, 0xfffffffd},
    {NoFlag, 0x33333333, 0x33333333, 0xfffffffd},
    {NoFlag, 0xffffff82, 0xffff8002, 0x80000001},
    {NoFlag, 0x55555555, 0xffffff83, 0xffffff83},
    {NoFlag, 0xffffff83, 0xffff8002, 0x00000020},
    {NoFlag, 0x0000007d, 0x7fffffff, 0x0000007f},
    {NoFlag, 0x00000000, 0xcccccccc, 0xffff8000},
    {NoFlag, 0x00000002, 0x7ffffffe, 0x00007fff},
    {NoFlag, 0xffffff82, 0x7ffffffd, 0x7ffffffd},
    {NoFlag, 0xaaaaaaaa, 0xfffffffd, 0xffff8002},
    {NoFlag, 0xfffffffd, 0x00000002, 0x7fffffff},
    {NoFlag, 0xfffffffe, 0xfffffffe, 0x00000020},
    {NoFlag, 0x80000001, 0x0000007e, 0x00007ffe},
    {NoFlag, 0x00007ffd, 0x00007ffd, 0xfffffffd},
    {NoFlag, 0xffff8000, 0x0000007f, 0x00000002},
    {NoFlag, 0x7ffffffd, 0x80000000, 0x7ffffffd},
    {NoFlag, 0x0000007d, 0x00007fff, 0x80000001},
    {NoFlag, 0xffffffff, 0x80000000, 0xaaaaaaaa},
    {NoFlag, 0x00000000, 0xaaaaaaaa, 0xffff8001},
    {NoFlag, 0xaaaaaaaa, 0xffffffe0, 0xffff8003},
    {NoFlag, 0xffffff82, 0xffffffff, 0x00007ffd},
    {NoFlag, 0x00000001, 0xffffff81, 0x00000001},
    {NoFlag, 0x7fffffff, 0xaaaaaaaa, 0x80000001},
    {NoFlag, 0x7fffffff, 0xffff8000, 0xffff8000},
    {NoFlag, 0xaaaaaaaa, 0x00007ffd, 0xaaaaaaaa},
    {NoFlag, 0x0000007f, 0x7ffffffe, 0x80000000},
    {NoFlag, 0x00007ffd, 0x00007ffe, 0xffffff81},
    {NoFlag, 0x0000007d, 0x0000007d, 0xffff8002},
    {NoFlag, 0x80000001, 0x00000002, 0xffffff81},
    {NoFlag, 0xffff8000, 0xfffffffd, 0x7ffffffd},
    {NoFlag, 0xfffffffe, 0x00000020, 0xffffff80},
    {NoFlag, 0x00000020, 0x7fffffff, 0xffffffe0},
    {NoFlag, 0xffff8002, 0xffff8002, 0x0000007f},
    {NoFlag, 0xffff8003, 0x7fffffff, 0xffff8002},
    {NoFlag, 0x00000020, 0xfffffffd, 0x00000020},
    {NoFlag, 0x7ffffffd, 0xffffffe0, 0x0000007e},
    {NoFlag, 0x00000020, 0x00000020, 0x7ffffffe},
    {NoFlag, 0xfffffffe, 0x0000007f, 0xffff8000},
    {NoFlag, 0x80000001, 0x80000001, 0x0000007d},
    {NoFlag, 0x55555555, 0x0000007f, 0x00007ffd},
    {NoFlag, 0x55555555, 0xffffffe0, 0xffffff82},
    {NoFlag, 0xffff8001, 0x0000007e, 0xffff8002},
    {NoFlag, 0xffffffe0, 0x55555555, 0x0000007f},
    {NoFlag, 0xffff8000, 0x7fffffff, 0x7ffffffe},
    {NoFlag, 0xffffffff, 0xfffffffe, 0xffffff80},
    {NoFlag, 0xffff8001, 0xffff8002, 0x33333333},
    {NoFlag, 0x7ffffffd, 0xfffffffd, 0xaaaaaaaa},
    {NoFlag, 0xaaaaaaaa, 0xfffffffd, 0x00000020},
    {NoFlag, 0x0000007f, 0x00007ffe, 0x55555555},
    {NoFlag, 0x00000020, 0x00000020, 0x00000002},
    {NoFlag, 0x80000001, 0xffff8002, 0xfffffffe},
    {NoFlag, 0x7fffffff, 0x80000001, 0xffff8002},
    {NoFlag, 0x00000020, 0x0000007e, 0x33333333}};

static const Inputs kShiftTypes[] = {
    {NoFlag, 0xabababab, 0xabababab, 0x00000000},
    {NoFlag, 0xabababab, 0xabababab, 0x00000001},
    {NoFlag, 0xabababab, 0xabababab, 0x00000002},
    {NoFlag, 0xabababab, 0xabababab, 0x00000020},
    {NoFlag, 0xabababab, 0xabababab, 0x0000007d},
    {NoFlag, 0xabababab, 0xabababab, 0x0000007e},
    {NoFlag, 0xabababab, 0xabababab, 0x0000007f},
    {NoFlag, 0xabababab, 0xabababab, 0x00007ffd},
    {NoFlag, 0xabababab, 0xabababab, 0x00007ffe},
    {NoFlag, 0xabababab, 0xabababab, 0x00007fff},
    {NoFlag, 0xabababab, 0xabababab, 0x33333333},
    {NoFlag, 0xabababab, 0xabababab, 0x55555555},
    {NoFlag, 0xabababab, 0xabababab, 0x7ffffffd},
    {NoFlag, 0xabababab, 0xabababab, 0x7ffffffe},
    {NoFlag, 0xabababab, 0xabababab, 0x7fffffff},
    {NoFlag, 0xabababab, 0xabababab, 0x80000000},
    {NoFlag, 0xabababab, 0xabababab, 0x80000001},
    {NoFlag, 0xabababab, 0xabababab, 0xaaaaaaaa},
    {NoFlag, 0xabababab, 0xabababab, 0xcccccccc},
    {NoFlag, 0xabababab, 0xabababab, 0xffff8000},
    {NoFlag, 0xabababab, 0xabababab, 0xffff8001},
    {NoFlag, 0xabababab, 0xabababab, 0xffff8002},
    {NoFlag, 0xabababab, 0xabababab, 0xffff8003},
    {NoFlag, 0xabababab, 0xabababab, 0xffffff80},
    {NoFlag, 0xabababab, 0xabababab, 0xffffff81},
    {NoFlag, 0xabababab, 0xabababab, 0xffffff82},
    {NoFlag, 0xabababab, 0xabababab, 0xffffff83},
    {NoFlag, 0xabababab, 0xabababab, 0xffffffe0},
    {NoFlag, 0xabababab, 0xabababab, 0xfffffffd},
    {NoFlag, 0xabababab, 0xabababab, 0xfffffffe},
    {NoFlag, 0xabababab, 0xabababab, 0xffffffff}};

// A loop will be generated for each element of this array.
static const TestLoopData kTests[] = {{{eq, r0, r0, r0, LSR, 1},
                                       "eq r0 r0 r0 LSR 1",
                                       "Condition_eq_r0_r0_r0_LSR_1",
                                       ARRAY_SIZE(kCondition),
                                       kCondition},
                                      {{ne, r0, r0, r0, LSR, 1},
                                       "ne r0 r0 r0 LSR 1",
                                       "Condition_ne_r0_r0_r0_LSR_1",
                                       ARRAY_SIZE(kCondition),
                                       kCondition},
                                      {{cs, r0, r0, r0, LSR, 1},
                                       "cs r0 r0 r0 LSR 1",
                                       "Condition_cs_r0_r0_r0_LSR_1",
                                       ARRAY_SIZE(kCondition),
                                       kCondition},
                                      {{cc, r0, r0, r0, LSR, 1},
                                       "cc r0 r0 r0 LSR 1",
                                       "Condition_cc_r0_r0_r0_LSR_1",
                                       ARRAY_SIZE(kCondition),
                                       kCondition},
                                      {{mi, r0, r0, r0, LSR, 1},
                                       "mi r0 r0 r0 LSR 1",
                                       "Condition_mi_r0_r0_r0_LSR_1",
                                       ARRAY_SIZE(kCondition),
                                       kCondition},
                                      {{pl, r0, r0, r0, LSR, 1},
                                       "pl r0 r0 r0 LSR 1",
                                       "Condition_pl_r0_r0_r0_LSR_1",
                                       ARRAY_SIZE(kCondition),
                                       kCondition},
                                      {{vs, r0, r0, r0, LSR, 1},
                                       "vs r0 r0 r0 LSR 1",
                                       "Condition_vs_r0_r0_r0_LSR_1",
                                       ARRAY_SIZE(kCondition),
                                       kCondition},
                                      {{vc, r0, r0, r0, LSR, 1},
                                       "vc r0 r0 r0 LSR 1",
                                       "Condition_vc_r0_r0_r0_LSR_1",
                                       ARRAY_SIZE(kCondition),
                                       kCondition},
                                      {{hi, r0, r0, r0, LSR, 1},
                                       "hi r0 r0 r0 LSR 1",
                                       "Condition_hi_r0_r0_r0_LSR_1",
                                       ARRAY_SIZE(kCondition),
                                       kCondition},
                                      {{ls, r0, r0, r0, LSR, 1},
                                       "ls r0 r0 r0 LSR 1",
                                       "Condition_ls_r0_r0_r0_LSR_1",
                                       ARRAY_SIZE(kCondition),
                                       kCondition},
                                      {{ge, r0, r0, r0, LSR, 1},
                                       "ge r0 r0 r0 LSR 1",
                                       "Condition_ge_r0_r0_r0_LSR_1",
                                       ARRAY_SIZE(kCondition),
                                       kCondition},
                                      {{lt, r0, r0, r0, LSR, 1},
                                       "lt r0 r0 r0 LSR 1",
                                       "Condition_lt_r0_r0_r0_LSR_1",
                                       ARRAY_SIZE(kCondition),
                                       kCondition},
                                      {{gt, r0, r0, r0, LSR, 1},
                                       "gt r0 r0 r0 LSR 1",
                                       "Condition_gt_r0_r0_r0_LSR_1",
                                       ARRAY_SIZE(kCondition),
                                       kCondition},
                                      {{le, r0, r0, r0, LSR, 1},
                                       "le r0 r0 r0 LSR 1",
                                       "Condition_le_r0_r0_r0_LSR_1",
                                       ARRAY_SIZE(kCondition),
                                       kCondition},
                                      {{al, r0, r0, r0, LSR, 1},
                                       "al r0 r0 r0 LSR 1",
                                       "Condition_al_r0_r0_r0_LSR_1",
                                       ARRAY_SIZE(kCondition),
                                       kCondition},
                                      {{al, r3, r3, r4, LSR, 1},
                                       "al r3 r3 r4 LSR 1",
                                       "RdIsRn_al_r3_r3_r4_LSR_1",
                                       ARRAY_SIZE(kRdIsRn),
                                       kRdIsRn},
                                      {{al, r2, r2, r12, LSR, 1},
                                       "al r2 r2 r12 LSR 1",
                                       "RdIsRn_al_r2_r2_r12_LSR_1",
                                       ARRAY_SIZE(kRdIsRn),
                                       kRdIsRn},
                                      {{al, r8, r8, r5, LSR, 1},
                                       "al r8 r8 r5 LSR 1",
                                       "RdIsRn_al_r8_r8_r5_LSR_1",
                                       ARRAY_SIZE(kRdIsRn),
                                       kRdIsRn},
                                      {{al, r14, r14, r0, LSR, 1},
                                       "al r14 r14 r0 LSR 1",
                                       "RdIsRn_al_r14_r14_r0_LSR_1",
                                       ARRAY_SIZE(kRdIsRn),
                                       kRdIsRn},
                                      {{al, r11, r11, r10, LSR, 1},
                                       "al r11 r11 r10 LSR 1",
                                       "RdIsRn_al_r11_r11_r10_LSR_1",
                                       ARRAY_SIZE(kRdIsRn),
                                       kRdIsRn},
                                      {{al, r12, r12, r10, LSR, 1},
                                       "al r12 r12 r10 LSR 1",
                                       "RdIsRn_al_r12_r12_r10_LSR_1",
                                       ARRAY_SIZE(kRdIsRn),
                                       kRdIsRn},
                                      {{al, r4, r4, r8, LSR, 1},
                                       "al r4 r4 r8 LSR 1",
                                       "RdIsRn_al_r4_r4_r8_LSR_1",
                                       ARRAY_SIZE(kRdIsRn),
                                       kRdIsRn},
                                      {{al, r5, r5, r14, LSR, 1},
                                       "al r5 r5 r14 LSR 1",
                                       "RdIsRn_al_r5_r5_r14_LSR_1",
                                       ARRAY_SIZE(kRdIsRn),
                                       kRdIsRn},
                                      {{al, r0, r0, r6, LSR, 1},
                                       "al r0 r0 r6 LSR 1",
                                       "RdIsRn_al_r0_r0_r6_LSR_1",
                                       ARRAY_SIZE(kRdIsRn),
                                       kRdIsRn},
                                      {{al, r12, r12, r1, LSR, 1},
                                       "al r12 r12 r1 LSR 1",
                                       "RdIsRn_al_r12_r12_r1_LSR_1",
                                       ARRAY_SIZE(kRdIsRn),
                                       kRdIsRn},
                                      {{al, r6, r11, r6, LSR, 1},
                                       "al r6 r11 r6 LSR 1",
                                       "RdIsRm_al_r6_r11_r6_LSR_1",
                                       ARRAY_SIZE(kRdIsRm),
                                       kRdIsRm},
                                      {{al, r11, r9, r11, LSR, 1},
                                       "al r11 r9 r11 LSR 1",
                                       "RdIsRm_al_r11_r9_r11_LSR_1",
                                       ARRAY_SIZE(kRdIsRm),
                                       kRdIsRm},
                                      {{al, r0, r8, r0, LSR, 1},
                                       "al r0 r8 r0 LSR 1",
                                       "RdIsRm_al_r0_r8_r0_LSR_1",
                                       ARRAY_SIZE(kRdIsRm),
                                       kRdIsRm},
                                      {{al, r2, r11, r2, LSR, 1},
                                       "al r2 r11 r2 LSR 1",
                                       "RdIsRm_al_r2_r11_r2_LSR_1",
                                       ARRAY_SIZE(kRdIsRm),
                                       kRdIsRm},
                                      {{al, r9, r4, r9, LSR, 1},
                                       "al r9 r4 r9 LSR 1",
                                       "RdIsRm_al_r9_r4_r9_LSR_1",
                                       ARRAY_SIZE(kRdIsRm),
                                       kRdIsRm},
                                      {{al, r14, r10, r14, LSR, 1},
                                       "al r14 r10 r14 LSR 1",
                                       "RdIsRm_al_r14_r10_r14_LSR_1",
                                       ARRAY_SIZE(kRdIsRm),
                                       kRdIsRm},
                                      {{al, r7, r0, r7, LSR, 1},
                                       "al r7 r0 r7 LSR 1",
                                       "RdIsRm_al_r7_r0_r7_LSR_1",
                                       ARRAY_SIZE(kRdIsRm),
                                       kRdIsRm},
                                      {{al, r4, r9, r4, LSR, 1},
                                       "al r4 r9 r4 LSR 1",
                                       "RdIsRm_al_r4_r9_r4_LSR_1",
                                       ARRAY_SIZE(kRdIsRm),
                                       kRdIsRm},
                                      {{al, r6, r10, r6, LSR, 1},
                                       "al r6 r10 r6 LSR 1",
                                       "RdIsRm_al_r6_r10_r6_LSR_1",
                                       ARRAY_SIZE(kRdIsRm),
                                       kRdIsRm},
                                      {{al, r7, r6, r7, LSR, 1},
                                       "al r7 r6 r7 LSR 1",
                                       "RdIsRm_al_r7_r6_r7_LSR_1",
                                       ARRAY_SIZE(kRdIsRm),
                                       kRdIsRm},
                                      {{al, r3, r9, r10, LSR, 1},
                                       "al r3 r9 r10 LSR 1",
                                       "RdIsNotRnIsNotRm_al_r3_r9_r10_LSR_1",
                                       ARRAY_SIZE(kRdIsNotRnIsNotRm),
                                       kRdIsNotRnIsNotRm},
                                      {{al, r7, r12, r5, LSR, 1},
                                       "al r7 r12 r5 LSR 1",
                                       "RdIsNotRnIsNotRm_al_r7_r12_r5_LSR_1",
                                       ARRAY_SIZE(kRdIsNotRnIsNotRm),
                                       kRdIsNotRnIsNotRm},
                                      {{al, r8, r5, r6, LSR, 1},
                                       "al r8 r5 r6 LSR 1",
                                       "RdIsNotRnIsNotRm_al_r8_r5_r6_LSR_1",
                                       ARRAY_SIZE(kRdIsNotRnIsNotRm),
                                       kRdIsNotRnIsNotRm},
                                      {{al, r0, r6, r0, LSR, 1},
                                       "al r0 r6 r0 LSR 1",
                                       "RdIsNotRnIsNotRm_al_r0_r6_r0_LSR_1",
                                       ARRAY_SIZE(kRdIsNotRnIsNotRm),
                                       kRdIsNotRnIsNotRm},
                                      {{al, r11, r7, r8, LSR, 1},
                                       "al r11 r7 r8 LSR 1",
                                       "RdIsNotRnIsNotRm_al_r11_r7_r8_LSR_1",
                                       ARRAY_SIZE(kRdIsNotRnIsNotRm),
                                       kRdIsNotRnIsNotRm},
                                      {{al, r12, r2, r3, LSR, 1},
                                       "al r12 r2 r3 LSR 1",
                                       "RdIsNotRnIsNotRm_al_r12_r2_r3_LSR_1",
                                       ARRAY_SIZE(kRdIsNotRnIsNotRm),
                                       kRdIsNotRnIsNotRm},
                                      {{al, r7, r4, r10, LSR, 1},
                                       "al r7 r4 r10 LSR 1",
                                       "RdIsNotRnIsNotRm_al_r7_r4_r10_LSR_1",
                                       ARRAY_SIZE(kRdIsNotRnIsNotRm),
                                       kRdIsNotRnIsNotRm},
                                      {{al, r9, r6, r1, LSR, 1},
                                       "al r9 r6 r1 LSR 1",
                                       "RdIsNotRnIsNotRm_al_r9_r6_r1_LSR_1",
                                       ARRAY_SIZE(kRdIsNotRnIsNotRm),
                                       kRdIsNotRnIsNotRm},
                                      {{al, r10, r14, r3, LSR, 1},
                                       "al r10 r14 r3 LSR 1",
                                       "RdIsNotRnIsNotRm_al_r10_r14_r3_LSR_1",
                                       ARRAY_SIZE(kRdIsNotRnIsNotRm),
                                       kRdIsNotRnIsNotRm},
                                      {{al, r14, r3, r6, LSR, 1},
                                       "al r14 r3 r6 LSR 1",
                                       "RdIsNotRnIsNotRm_al_r14_r3_r6_LSR_1",
                                       ARRAY_SIZE(kRdIsNotRnIsNotRm),
                                       kRdIsNotRnIsNotRm},
                                      {{al, r0, r1, r2, LSR, 1},
                                       "al r0 r1 r2 LSR 1",
                                       "ShiftTypes_al_r0_r1_r2_LSR_1",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, LSR, 2},
                                       "al r0 r1 r2 LSR 2",
                                       "ShiftTypes_al_r0_r1_r2_LSR_2",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, LSR, 3},
                                       "al r0 r1 r2 LSR 3",
                                       "ShiftTypes_al_r0_r1_r2_LSR_3",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, LSR, 4},
                                       "al r0 r1 r2 LSR 4",
                                       "ShiftTypes_al_r0_r1_r2_LSR_4",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, LSR, 5},
                                       "al r0 r1 r2 LSR 5",
                                       "ShiftTypes_al_r0_r1_r2_LSR_5",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, LSR, 6},
                                       "al r0 r1 r2 LSR 6",
                                       "ShiftTypes_al_r0_r1_r2_LSR_6",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, LSR, 7},
                                       "al r0 r1 r2 LSR 7",
                                       "ShiftTypes_al_r0_r1_r2_LSR_7",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, LSR, 8},
                                       "al r0 r1 r2 LSR 8",
                                       "ShiftTypes_al_r0_r1_r2_LSR_8",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, LSR, 9},
                                       "al r0 r1 r2 LSR 9",
                                       "ShiftTypes_al_r0_r1_r2_LSR_9",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, LSR, 10},
                                       "al r0 r1 r2 LSR 10",
                                       "ShiftTypes_al_r0_r1_r2_LSR_10",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, LSR, 11},
                                       "al r0 r1 r2 LSR 11",
                                       "ShiftTypes_al_r0_r1_r2_LSR_11",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, LSR, 12},
                                       "al r0 r1 r2 LSR 12",
                                       "ShiftTypes_al_r0_r1_r2_LSR_12",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, LSR, 13},
                                       "al r0 r1 r2 LSR 13",
                                       "ShiftTypes_al_r0_r1_r2_LSR_13",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, LSR, 14},
                                       "al r0 r1 r2 LSR 14",
                                       "ShiftTypes_al_r0_r1_r2_LSR_14",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, LSR, 15},
                                       "al r0 r1 r2 LSR 15",
                                       "ShiftTypes_al_r0_r1_r2_LSR_15",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, LSR, 16},
                                       "al r0 r1 r2 LSR 16",
                                       "ShiftTypes_al_r0_r1_r2_LSR_16",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, LSR, 17},
                                       "al r0 r1 r2 LSR 17",
                                       "ShiftTypes_al_r0_r1_r2_LSR_17",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, LSR, 18},
                                       "al r0 r1 r2 LSR 18",
                                       "ShiftTypes_al_r0_r1_r2_LSR_18",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, LSR, 19},
                                       "al r0 r1 r2 LSR 19",
                                       "ShiftTypes_al_r0_r1_r2_LSR_19",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, LSR, 20},
                                       "al r0 r1 r2 LSR 20",
                                       "ShiftTypes_al_r0_r1_r2_LSR_20",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, LSR, 21},
                                       "al r0 r1 r2 LSR 21",
                                       "ShiftTypes_al_r0_r1_r2_LSR_21",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, LSR, 22},
                                       "al r0 r1 r2 LSR 22",
                                       "ShiftTypes_al_r0_r1_r2_LSR_22",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, LSR, 23},
                                       "al r0 r1 r2 LSR 23",
                                       "ShiftTypes_al_r0_r1_r2_LSR_23",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, LSR, 24},
                                       "al r0 r1 r2 LSR 24",
                                       "ShiftTypes_al_r0_r1_r2_LSR_24",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, LSR, 25},
                                       "al r0 r1 r2 LSR 25",
                                       "ShiftTypes_al_r0_r1_r2_LSR_25",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, LSR, 26},
                                       "al r0 r1 r2 LSR 26",
                                       "ShiftTypes_al_r0_r1_r2_LSR_26",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, LSR, 27},
                                       "al r0 r1 r2 LSR 27",
                                       "ShiftTypes_al_r0_r1_r2_LSR_27",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, LSR, 28},
                                       "al r0 r1 r2 LSR 28",
                                       "ShiftTypes_al_r0_r1_r2_LSR_28",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, LSR, 29},
                                       "al r0 r1 r2 LSR 29",
                                       "ShiftTypes_al_r0_r1_r2_LSR_29",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, LSR, 30},
                                       "al r0 r1 r2 LSR 30",
                                       "ShiftTypes_al_r0_r1_r2_LSR_30",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, LSR, 31},
                                       "al r0 r1 r2 LSR 31",
                                       "ShiftTypes_al_r0_r1_r2_LSR_31",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, LSR, 32},
                                       "al r0 r1 r2 LSR 32",
                                       "ShiftTypes_al_r0_r1_r2_LSR_32",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, ASR, 1},
                                       "al r0 r1 r2 ASR 1",
                                       "ShiftTypes_al_r0_r1_r2_ASR_1",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, ASR, 2},
                                       "al r0 r1 r2 ASR 2",
                                       "ShiftTypes_al_r0_r1_r2_ASR_2",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, ASR, 3},
                                       "al r0 r1 r2 ASR 3",
                                       "ShiftTypes_al_r0_r1_r2_ASR_3",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, ASR, 4},
                                       "al r0 r1 r2 ASR 4",
                                       "ShiftTypes_al_r0_r1_r2_ASR_4",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, ASR, 5},
                                       "al r0 r1 r2 ASR 5",
                                       "ShiftTypes_al_r0_r1_r2_ASR_5",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, ASR, 6},
                                       "al r0 r1 r2 ASR 6",
                                       "ShiftTypes_al_r0_r1_r2_ASR_6",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, ASR, 7},
                                       "al r0 r1 r2 ASR 7",
                                       "ShiftTypes_al_r0_r1_r2_ASR_7",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, ASR, 8},
                                       "al r0 r1 r2 ASR 8",
                                       "ShiftTypes_al_r0_r1_r2_ASR_8",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, ASR, 9},
                                       "al r0 r1 r2 ASR 9",
                                       "ShiftTypes_al_r0_r1_r2_ASR_9",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, ASR, 10},
                                       "al r0 r1 r2 ASR 10",
                                       "ShiftTypes_al_r0_r1_r2_ASR_10",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, ASR, 11},
                                       "al r0 r1 r2 ASR 11",
                                       "ShiftTypes_al_r0_r1_r2_ASR_11",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, ASR, 12},
                                       "al r0 r1 r2 ASR 12",
                                       "ShiftTypes_al_r0_r1_r2_ASR_12",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, ASR, 13},
                                       "al r0 r1 r2 ASR 13",
                                       "ShiftTypes_al_r0_r1_r2_ASR_13",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, ASR, 14},
                                       "al r0 r1 r2 ASR 14",
                                       "ShiftTypes_al_r0_r1_r2_ASR_14",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, ASR, 15},
                                       "al r0 r1 r2 ASR 15",
                                       "ShiftTypes_al_r0_r1_r2_ASR_15",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, ASR, 16},
                                       "al r0 r1 r2 ASR 16",
                                       "ShiftTypes_al_r0_r1_r2_ASR_16",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, ASR, 17},
                                       "al r0 r1 r2 ASR 17",
                                       "ShiftTypes_al_r0_r1_r2_ASR_17",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, ASR, 18},
                                       "al r0 r1 r2 ASR 18",
                                       "ShiftTypes_al_r0_r1_r2_ASR_18",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, ASR, 19},
                                       "al r0 r1 r2 ASR 19",
                                       "ShiftTypes_al_r0_r1_r2_ASR_19",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, ASR, 20},
                                       "al r0 r1 r2 ASR 20",
                                       "ShiftTypes_al_r0_r1_r2_ASR_20",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, ASR, 21},
                                       "al r0 r1 r2 ASR 21",
                                       "ShiftTypes_al_r0_r1_r2_ASR_21",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, ASR, 22},
                                       "al r0 r1 r2 ASR 22",
                                       "ShiftTypes_al_r0_r1_r2_ASR_22",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, ASR, 23},
                                       "al r0 r1 r2 ASR 23",
                                       "ShiftTypes_al_r0_r1_r2_ASR_23",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, ASR, 24},
                                       "al r0 r1 r2 ASR 24",
                                       "ShiftTypes_al_r0_r1_r2_ASR_24",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, ASR, 25},
                                       "al r0 r1 r2 ASR 25",
                                       "ShiftTypes_al_r0_r1_r2_ASR_25",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, ASR, 26},
                                       "al r0 r1 r2 ASR 26",
                                       "ShiftTypes_al_r0_r1_r2_ASR_26",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, ASR, 27},
                                       "al r0 r1 r2 ASR 27",
                                       "ShiftTypes_al_r0_r1_r2_ASR_27",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, ASR, 28},
                                       "al r0 r1 r2 ASR 28",
                                       "ShiftTypes_al_r0_r1_r2_ASR_28",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, ASR, 29},
                                       "al r0 r1 r2 ASR 29",
                                       "ShiftTypes_al_r0_r1_r2_ASR_29",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, ASR, 30},
                                       "al r0 r1 r2 ASR 30",
                                       "ShiftTypes_al_r0_r1_r2_ASR_30",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, ASR, 31},
                                       "al r0 r1 r2 ASR 31",
                                       "ShiftTypes_al_r0_r1_r2_ASR_31",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes},
                                      {{al, r0, r1, r2, ASR, 32},
                                       "al r0 r1 r2 ASR 32",
                                       "ShiftTypes_al_r0_r1_r2_ASR_32",
                                       ARRAY_SIZE(kShiftTypes),
                                       kShiftTypes}};

// We record all inputs to the instructions as outputs. This way, we also check
// that what shouldn't change didn't change.
struct TestResult {
  size_t output_size;
  const Inputs* outputs;
};

// These headers each contain an array of `TestResult` with the reference output
// values. The reference arrays are names `kReference{mnemonic}`.
#include "a32/traces/simulator-cond-rd-rn-operand-rm-shift-amount-1to32-t32-adc.h"
#include "a32/traces/simulator-cond-rd-rn-operand-rm-shift-amount-1to32-t32-adcs.h"
#include "a32/traces/simulator-cond-rd-rn-operand-rm-shift-amount-1to32-t32-add.h"
#include "a32/traces/simulator-cond-rd-rn-operand-rm-shift-amount-1to32-t32-adds.h"
#include "a32/traces/simulator-cond-rd-rn-operand-rm-shift-amount-1to32-t32-and.h"
#include "a32/traces/simulator-cond-rd-rn-operand-rm-shift-amount-1to32-t32-ands.h"
#include "a32/traces/simulator-cond-rd-rn-operand-rm-shift-amount-1to32-t32-bic.h"
#include "a32/traces/simulator-cond-rd-rn-operand-rm-shift-amount-1to32-t32-bics.h"
#include "a32/traces/simulator-cond-rd-rn-operand-rm-shift-amount-1to32-t32-eor.h"
#include "a32/traces/simulator-cond-rd-rn-operand-rm-shift-amount-1to32-t32-eors.h"
#include "a32/traces/simulator-cond-rd-rn-operand-rm-shift-amount-1to32-t32-orn.h"
#include "a32/traces/simulator-cond-rd-rn-operand-rm-shift-amount-1to32-t32-orns.h"
#include "a32/traces/simulator-cond-rd-rn-operand-rm-shift-amount-1to32-t32-orr.h"
#include "a32/traces/simulator-cond-rd-rn-operand-rm-shift-amount-1to32-t32-orrs.h"
#include "a32/traces/simulator-cond-rd-rn-operand-rm-shift-amount-1to32-t32-rsb.h"
#include "a32/traces/simulator-cond-rd-rn-operand-rm-shift-amount-1to32-t32-rsbs.h"
#include "a32/traces/simulator-cond-rd-rn-operand-rm-shift-amount-1to32-t32-sbc.h"
#include "a32/traces/simulator-cond-rd-rn-operand-rm-shift-amount-1to32-t32-sbcs.h"
#include "a32/traces/simulator-cond-rd-rn-operand-rm-shift-amount-1to32-t32-sub.h"
#include "a32/traces/simulator-cond-rd-rn-operand-rm-shift-amount-1to32-t32-subs.h"

// The maximum number of errors to report in detail for each test.
static const unsigned kErrorReportLimit = 8;

typedef void (MacroAssembler::*Fn)(Condition cond, Register rd, Register rn,
                                   const Operand& op);

static void TestHelper(Fn instruction, const char* mnemonic,
                       const TestResult reference[]) {
  SETUP();
  masm.SetT32(true);
  START();

  // Data to compare to `reference`.
  TestResult* results[ARRAY_SIZE(kTests)];

  // Test cases for memory bound instructions may allocate a buffer and save its
  // address in this array.
  byte* scratch_memory_buffers[ARRAY_SIZE(kTests)];

  // Generate a loop for each element in `kTests`. Each loop tests one specific
  // instruction.
  for (unsigned i = 0; i < ARRAY_SIZE(kTests); i++) {
    // Allocate results on the heap for this test.
    results[i] = new TestResult;
    results[i]->outputs = new Inputs[kTests[i].input_size];
    results[i]->output_size = kTests[i].input_size;

    uintptr_t input_address = reinterpret_cast<uintptr_t>(kTests[i].inputs);
    uintptr_t result_address = reinterpret_cast<uintptr_t>(results[i]->outputs);

    scratch_memory_buffers[i] = NULL;

    Label loop;
    UseScratchRegisterScope scratch_registers(&masm);
    // Include all registers from r0 ro r12.
    scratch_registers.Include(RegisterList(0x1fff));

    // Values to pass to the macro-assembler.
    Condition cond = kTests[i].operands.cond;
    Register rd = kTests[i].operands.rd;
    Register rn = kTests[i].operands.rn;
    Register rm = kTests[i].operands.rm;
    ShiftType shift = kTests[i].operands.shift;
    uint32_t amount = kTests[i].operands.amount;
    Operand op(rm, shift, amount);
    scratch_registers.Exclude(rd);
    scratch_registers.Exclude(rn);
    scratch_registers.Exclude(rm);

    // Allocate reserved registers for our own use.
    Register input_ptr = scratch_registers.Acquire();
    Register input_end = scratch_registers.Acquire();
    Register result_ptr = scratch_registers.Acquire();

    // Initialize `input_ptr` to the first element and `input_end` the address
    // after the array.
    __ Mov(input_ptr, input_address);
    __ Add(input_end, input_ptr,
           sizeof(kTests[i].inputs[0]) * kTests[i].input_size);
    __ Mov(result_ptr, result_address);
    __ Bind(&loop);

    {
      UseScratchRegisterScope temp_registers(&masm);
      Register nzcv_bits = temp_registers.Acquire();
      Register saved_q_bit = temp_registers.Acquire();
      // Save the `Q` bit flag.
      __ Mrs(saved_q_bit, APSR);
      __ And(saved_q_bit, saved_q_bit, QFlag);
      // Set the `NZCV` and `Q` flags together.
      __ Ldr(nzcv_bits, MemOperand(input_ptr, offsetof(Inputs, apsr)));
      __ Orr(nzcv_bits, nzcv_bits, saved_q_bit);
      __ Msr(APSR_nzcvq, nzcv_bits);
    }
    __ Ldr(rd, MemOperand(input_ptr, offsetof(Inputs, rd)));
    __ Ldr(rn, MemOperand(input_ptr, offsetof(Inputs, rn)));
    __ Ldr(rm, MemOperand(input_ptr, offsetof(Inputs, rm)));

    (masm.*instruction)(cond, rd, rn, op);

    {
      UseScratchRegisterScope temp_registers(&masm);
      Register nzcv_bits = temp_registers.Acquire();
      __ Mrs(nzcv_bits, APSR);
      // Only record the NZCV bits.
      __ And(nzcv_bits, nzcv_bits, NZCVFlag);
      __ Str(nzcv_bits, MemOperand(result_ptr, offsetof(Inputs, apsr)));
    }
    __ Str(rd, MemOperand(result_ptr, offsetof(Inputs, rd)));
    __ Str(rn, MemOperand(result_ptr, offsetof(Inputs, rn)));
    __ Str(rm, MemOperand(result_ptr, offsetof(Inputs, rm)));

    // Advance the result pointer.
    __ Add(result_ptr, result_ptr, sizeof(kTests[i].inputs[0]));
    // Loop back until `input_ptr` is lower than `input_base`.
    __ Add(input_ptr, input_ptr, sizeof(kTests[i].inputs[0]));
    __ Cmp(input_ptr, input_end);
    __ B(ne, &loop);
  }

  END();

  RUN();

  if (Test::generate_test_trace()) {
    // Print the results.
    for (size_t i = 0; i < ARRAY_SIZE(kTests); i++) {
      printf("static const Inputs kOutputs_%s_%s[] = {\n", mnemonic,
             kTests[i].identifier);
      for (size_t j = 0; j < results[i]->output_size; j++) {
        printf("  { ");
        printf("0x%08" PRIx32, results[i]->outputs[j].apsr);
        printf(", ");
        printf("0x%08" PRIx32, results[i]->outputs[j].rd);
        printf(", ");
        printf("0x%08" PRIx32, results[i]->outputs[j].rn);
        printf(", ");
        printf("0x%08" PRIx32, results[i]->outputs[j].rm);
        printf(" },\n");
      }
      printf("};\n");
    }
    printf("static const TestResult kReference%s[] = {\n", mnemonic);
    for (size_t i = 0; i < ARRAY_SIZE(kTests); i++) {
      printf("  {\n");
      printf("    ARRAY_SIZE(kOutputs_%s_%s),\n", mnemonic,
             kTests[i].identifier);
      printf("    kOutputs_%s_%s,\n", mnemonic, kTests[i].identifier);
      printf("  },\n");
    }
    printf("};\n");
  } else {
    // Check the results.
    unsigned total_error_count = 0;
    for (size_t i = 0; i < ARRAY_SIZE(kTests); i++) {
      bool instruction_has_errors = false;
      for (size_t j = 0; j < kTests[i].input_size; j++) {
        uint32_t apsr = results[i]->outputs[j].apsr;
        uint32_t rd = results[i]->outputs[j].rd;
        uint32_t rn = results[i]->outputs[j].rn;
        uint32_t rm = results[i]->outputs[j].rm;
        uint32_t apsr_input = kTests[i].inputs[j].apsr;
        uint32_t rd_input = kTests[i].inputs[j].rd;
        uint32_t rn_input = kTests[i].inputs[j].rn;
        uint32_t rm_input = kTests[i].inputs[j].rm;
        uint32_t apsr_ref = reference[i].outputs[j].apsr;
        uint32_t rd_ref = reference[i].outputs[j].rd;
        uint32_t rn_ref = reference[i].outputs[j].rn;
        uint32_t rm_ref = reference[i].outputs[j].rm;

        if (((apsr != apsr_ref) || (rd != rd_ref) || (rn != rn_ref) ||
             (rm != rm_ref)) &&
            (++total_error_count <= kErrorReportLimit)) {
          // Print the instruction once even if it triggered multiple failures.
          if (!instruction_has_errors) {
            printf("Error(s) when testing \"%s %s\":\n", mnemonic,
                   kTests[i].operands_description);
            instruction_has_errors = true;
          }
          // Print subsequent errors.
          printf("  Input:    ");
          printf("0x%08" PRIx32, apsr_input);
          printf(", ");
          printf("0x%08" PRIx32, rd_input);
          printf(", ");
          printf("0x%08" PRIx32, rn_input);
          printf(", ");
          printf("0x%08" PRIx32, rm_input);
          printf("\n");
          printf("  Expected: ");
          printf("0x%08" PRIx32, apsr_ref);
          printf(", ");
          printf("0x%08" PRIx32, rd_ref);
          printf(", ");
          printf("0x%08" PRIx32, rn_ref);
          printf(", ");
          printf("0x%08" PRIx32, rm_ref);
          printf("\n");
          printf("  Found:    ");
          printf("0x%08" PRIx32, apsr);
          printf(", ");
          printf("0x%08" PRIx32, rd);
          printf(", ");
          printf("0x%08" PRIx32, rn);
          printf(", ");
          printf("0x%08" PRIx32, rm);
          printf("\n\n");
        }
      }
    }

    if (total_error_count > kErrorReportLimit) {
      printf("%u other errors follow.\n",
             total_error_count - kErrorReportLimit);
    }
// TODO: Do this check for the simulator too when it is ready.
#ifndef VIXL_INCLUDE_SIMULATOR
    VIXL_CHECK(total_error_count == 0);
#endif
  }

  for (size_t i = 0; i < ARRAY_SIZE(kTests); i++) {
    delete[] results[i]->outputs;
    delete results[i];
    delete scratch_memory_buffers[i];
  }

  TEARDOWN();
}

// Instantiate tests for each instruction in the list.
#define TEST(mnemonic)                                                      \
  static void Test_##mnemonic() {                                           \
    TestHelper(&MacroAssembler::mnemonic, #mnemonic, kReference##mnemonic); \
  }                                                                         \
  static Test test_##mnemonic(                                              \
      "AARCH32_SIMULATOR_COND_RD_RN_OPERAND_RM_SHIFT_AMOUNT_1TO32_"         \
      "T32_" #mnemonic,                                                     \
      &Test_##mnemonic);
FOREACH_INSTRUCTION(TEST)
#undef TEST

}  // aarch32
}  // vixl
