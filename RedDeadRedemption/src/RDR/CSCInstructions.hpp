#pragma once
#include <stdint.h>

struct OpcodeDesc
{
   const char* instructionName;
   uint32_t instructionLength;

} ops[156] = {
   { "nop", 1 },  // 0 - skip command, switch page if necessary
   { "iadd", 1 },  // 1 - integer +, stack operands
   { "isub", 1 },  // 2 - integer -, stack operands
   { "imul", 1 },  // 3 - integer *, stack operands
   { "idiv", 1 },  // 4 - integer /, stack operands
   { "imod", 1 },  // 5 - integer %, stack operands
   { "inot", 1 },  // 6 - logical not, stack operand
   { "ineg", 1 },  // 7 - integer negate, stack operand
   { "icmpeq", 1 },  // 8 - integer compare =, stack operands
   { "icmpne", 1 },  // 9 - integer compare !=, stack operands
   { "icmpgt", 1 },  // 10 - integer compare >, stack operands
   { "icmpge", 1 },  // 11 - integer compare >=, stack operands
   { "icmplt", 1 },  // 12 - integer compare <, stack operands
   { "icmple", 1 },  // 13 - integer compare <=, stack operands
   { "fadd", 1 },  // 14 - float +, stack operands
   { "fsub", 1 },  // 15
   { "fmul", 1 },  // 16
   { "fdiv", 1 },  // 17
   { "fmod", 1 },  // 18
   { "fneg", 1 },  // 19
   { "fcmpeq", 1 },  // 20
   { "fcmpne", 1 },  // 21
   { "fcmpgt", 1 },  // 22
   { "fcmpge", 1 },  // 23
   { "fcmplt", 1 },  // 24
   { "fcmple", 1 },  // 25
   { "vadd", 1 },  // 26 - vector +, stack operands
   { "vsub", 1 },  // 27
   { "vmul", 1 },  // 28
   { "vdiv", 1 },  // 29
   { "vneg", 1 },  // 30
   { "iand", 1 },  // 31 - integer &, stack operands
   { "ior", 1 },  // 32
   { "ixor", 1 },  // 33
   { "itof", 1 },  // 34
   { "ftoi", 1 },  // 35
   { "dup2", 1 },  // 36
   { "ipush1", 2 },  // 37   ipush imm1
   { "ipush12", 3 },  // 38   ipush imm1, imm1
   { "ipush13", 4 },  // 39   ipush imm1, imm1, imm1
   { "ipush", 5 },  // 40
   { "fpush", 5 },  // 41
   { "dup", 1 },  // 42
   { "drop", 1 },  // 43
   { "native", 3 },  // 44
   { "enter", 0 },  // 45   - length = 5 + last byte (function name length)
   { "ret", 3 },  // 46 
   { "pget", 1 },  // 47
   { "pset", 1 },  // 48
   { "ppeekset", 1 },  // 49
   { "tostack", 1 },  // 50
   { "fromstack", 1 },  // 51
   { "parray", 2 },  // 52
   { "aget",2 },  // 53 - get an array element to the stack
   { "aset",2 },  // 54 - set an array element from the stack
   { "pframe1",  2 },  // 55
   { "getf",   2 },  // 56 - get value from the stack frame, immediate 1-byte offset
   { "setf",   2 },  // 57 - set value to the stack frame, immediate 1-byte offset
   { "stackgetp",2 },  // 58
   { "stackget", 2 },  // 59
   { "stackset", 2 },  // 60
   { "iaddimm1", 2 },  // 61
   { "pgetimm1", 2 },  // 62
   { "psetimm1", 2 },  // 63
   { "imulimm1", 2 },  // 64
   { "ipush2", 3 },  // 65
   { "iaddimm2", 3 },  // 66
   { "pgetimm2", 3 },  // 67
   { "psetimm2", 3 },  // 68
   { "imulimm2", 3 },  // 69
   { "arraygetp2", 3 }, // 70 
   { "arrayget2", 3 },  // 71 
   { "arrayset2", 3 },  // 72
   { "pframe2", 3 },  // 73
   { "frameget2", 3 },  // 74
   { "frameset2", 3 },  // 75
   { "pstatic2", 3 },  // 76
   { "staticget2", 3 }, // 77
   { "staticset2", 3 }, // 78
   { "pglobal2", 3 },  // 79
   { "globalget2",3 },  // 80
   { "globalset2",3 },  // 81
   { "call2", 3 },  // 82   call imm2
   { "call2h1", 3 },  // 83   call (imm2|0x1000)
   { "call2h2", 3 },  // 84   call (imm2|0x2000)
   { "call2h3", 3 },  // 85   call (imm2|0x3000)
   { "call2h4", 3 },  // 86   call (imm2|0x4000)
   { "call2h5", 3 },  // 87   call (imm2|0x5000)
   { "call2h6", 3 },  // 88   call (imm2|0x6000)
   { "call2h7", 3 },  // 89   call (imm2|0x7000)
   { "call2h8", 3 },  // 90   call (imm2|0x8000)
   { "call2h9", 3 },  // 91   call (imm2|0x9000)
   { "call2ha", 3 },  // 92   call (imm2|0xA000)
   { "call2hb", 3 },  // 93   call (imm2|0xB000)
   { "call2hc", 3 },  // 94   call (imm2|0xC000)
   { "call2hd", 3 },  // 95   call (imm2|0xD000)
   { "call2he", 3 },  // 96   call (imm2|0xE000)
   { "call2hf", 3 },  // 97   call (imm2|0xF000)
   { "jr2", 3 },  // 98   jump relative signed imm2
   { "jfr2", 3 },  // 99   jump if false relative signed imm2
   { "jner2", 3 },  // 100
   { "jeqr2", 3 },  // 101
   { "jler2", 3 },  // 102  TODO: <= or > ?
   { "jltr2", 3 },  // 103  TODO: < or >= ?
   { "jger2", 3 },  // 104  TODO: >= or < ?
   { "jgtr2", 3 },  // 105  TODO: > or <= ?
   { "pglobal3", 4 },  // 106
   { "globalget3",4 },  // 107
   { "globalset3",4 },  // 108
   { "ipush3", 4 },  // 109
   { "switchr2", 0 },  // 110  length = 2 + byte[1]*6
   { "spush", 0 },  // 111  length = 2 + byte[1]
   { "spushl", 0 },  // 112  length = 5 + dword[1]
   { "spush0", 1 },  // 113  push ""
   { "scpy", 2 },  // 114
   { "itos", 2 },  // 115
   { "sadd", 2 },  // 116
   { "saddi", 2 },  // 117
   { "sncpy", 1 },  // 118
   { "catch", 1 },  // 119
   { "throw", 1 },  // 120
   { "pcall", 1 },  // 121
   { "ret0r0", 1 },  // 122 - return: 0 parameters, 0 results
   { "ret0r1", 1 },  // 123 - return: 0 parameters, 1 result 
   { "ret0r2", 1 },  // 124 - return: 0 parameters, 2 results
   { "ret0r3", 1 },  // 125 - return: 0 parameters, 3 results
   { "ret1r0", 1 },  // 126 - return: 1 parameter, 0 results
   { "ret1r1", 1 },  // 127 - return: 1 parameter, 1 result
   { "ret1r2", 1 },  // 128 - return: 1 parameter, 2 results
   { "ret1r3", 1 },  // 129 - return: 1 parameter, 3 results
   { "ret2r0", 1 },  // 130 - return: 2 parameters, 0 results 
   { "ret2r1", 1 },  // 131 - return: 2 parameters, 1 result
   { "ret2r2", 1 },  // 132 - return: 2 parameters, 2 results 
   { "ret2r3", 1 },  // 133 - return: 2 parameters, 3 results 
   { "ret3r0", 1 },  // 134 - return: 3 parameters, 0 results 
   { "ret3r1", 1 },  // 135 - return: 3 parameters, 1 result
   { "ret3r2", 1 },  // 136 - return: 3 parameters, 2 results 
   { "ret3r3", 1 },  // 137 - return: 3 parameters, 3 results 
   { "iimmn1",1 }, // 138  push -1
   { "iimm0", 1 }, // 139  push 0
   { "iimm1", 1 }, // 140  push 1
   { "iimm2", 1 }, // 141  push 2
   { "iimm3", 1 }, // 142  push 3
   { "iimm4", 1 }, // 143  push 4
   { "iimm5", 1 }, // 144  push 5
   { "iimm6", 1 }, // 145  push 6
   { "iimm7", 1 }, // 146  push 7
   { "fimmn1", 1 }, // 147  push -1.0f
   { "fimm0", 1 },  // 148  push 0.0f
   { "fimm1", 1 },  // 149  push 1.0f
   { "fimm2", 1 },  // 150  push 2.0f
   { "fimm3", 1 },  // 151  push 3.0f
   { "fimm4", 1 },  // 152  push 4.0f
   { "fimm5", 1 },  // 153  push 5.0f
   { "fimm6", 1 },  // 154  push 6.0f
   { "fimm7", 1 }   // 155  push 7.0f
};

enum opCodes
{
   nop = 0,
   iadd = 1,
   isub = 2,
   imul = 3,
   idiv = 4,
   imod = 5,
   inot = 6,
   ineg = 7,
   icmpeq = 8,
   icmpne = 9,
   icmpgt = 10,
   icmpge = 11,
   icmplt = 12,
   icmple = 13,
   fadd = 14,
   fsub = 15,
   fmul = 16,
   fdiv = 17,
   _fmod = 18,
   fneg = 19,
   fcmpeq = 20,
   fcmpne = 21,
   fcmpgt = 22,
   fcmpge = 23,
   fcmplt = 24,
   fcmple = 25,
   vadd = 26,
   vsub = 27,
   vmul = 28,
   vdiv = 29,
   vneg = 30,
   iand = 31,
   ior = 32,
   ixor = 33,
   itof = 34,
   ftoi = 35,
   dup2 = 36,
   ipush1 = 37,
   ipush12 = 38,
   ipush13 = 39,
   ipush = 40,
   fpush = 41,
   dup = 42,
   drop = 43,
   native = 44,
   enter = 45,
   ret = 46,
   pget = 47,
   pset = 48,
   ppeekset = 49,
   tostack = 50,
   fromstack = 51,
   parray = 52,
   aget = 53,
   aset = 54,
   pframe1 = 55,
   getf = 56,
   setf = 57,
   stackgetp = 58,
   stackget = 59,
   stackset = 60,
   iaddimm1 = 61,
   pgetimm1 = 62,
   psetimm1 = 63,
   imulimm1 = 64,
   ipush2 = 65,
   iaddimm2 = 66,
   pgetimm2 = 67,
   psetimm2 = 68,
   imulimm2 = 69,
   arraygetp2 = 70,
   arrayget2 = 71,
   arrayset2 = 72,
   pframe2 = 73,
   frameget2 = 74,
   frameset2 = 75,
   pstatic2 = 76,
   staticget2 = 77,
   staticset2 = 78,
   pglobal2 = 79,
   globalget2 = 80,
   globalset2 = 81,
   call2 = 82,
   call2h1 = 83,
   call2h2 = 84,
   call2h3 = 85,
   call2h4 = 86,
   call2h5 = 87,
   call2h6 = 88,
   call2h7 = 89,
   call2h8 = 90,
   call2h9 = 91,
   call2ha = 92,
   call2hb = 93,
   call2hc = 94,
   call2hd = 95,
   call2he = 96,
   call2hf = 97,
   jr2 = 98,
   jfr2 = 99,
   jner2 = 100,
   jeqr2 = 101,
   jler2 = 102,
   jltr2 = 103,
   jger2 = 104,
   jgtr2 = 105,
   pglobal3 = 106,
   globalget3 = 107,
   globalset3 = 108,
   ipush3 = 109,
   switchr2 = 110,
   spush = 111,
   spushl = 112,
   spush0 = 113,
   scpy = 114,
   itos = 115,
   sadd = 116,
   saddi = 117,
   sncpy = 118,
   Catch = 119,
   Throw = 120,
   pcall = 121,
   ret0r0 = 122,
   ret0r1 = 123,
   ret0r2 = 124,
   ret0r3 = 125,
   ret1r0 = 126,
   ret1r1 = 127,
   ret1r2 = 128,
   ret1r3 = 129,
   ret2r0 = 130,
   ret2r1 = 131,
   ret2r2 = 132,
   ret2r3 = 133,
   ret3r0 = 134,
   ret3r1 = 135,
   ret3r2 = 136,
   ret3r3 = 137,
   iimmn1 = 138,
   iimm0 = 139,
   iimm1 = 140,
   iimm2 = 141,
   iimm3 = 142,
   iimm4 = 143,
   iimm5 = 144,
   iimm6 = 145,
   iimm7 = 146,
   fimmn1 = 147,
   fimm0 = 148,
   fimm1 = 149,
   fimm2 = 150,
   fimm3 = 151,
   fimm4 = 152,
   fimm5 = 153,
   fimm6 = 154,
   fimm7 = 155
};