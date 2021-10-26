using System;
using System.Collections.Generic;
using System.Linq;

namespace Decompiler
{
	internal class HLInstruction
	{
		int offset;
		Instruction instruction;
		byte[] operands;
		private bool _consoleVer;

		public HLInstruction(Instruction Instruction, IEnumerable<byte> Operands, int Offset, bool consoleVer)
		{
			instruction = Instruction;
			operands = Operands.ToArray();
			offset = Offset;
			_consoleVer = consoleVer;
		}

		public HLInstruction(byte Instruction, IEnumerable<byte> Operands, int Offset, bool consoleVer)
		{
			instruction = (Instruction) Instruction;
			operands = Operands.ToArray();
			offset = Offset;
			_consoleVer = consoleVer;
		}

		public HLInstruction(Instruction Instruction, int Offset, bool consoleVer)
		{
			instruction = Instruction;
			operands = new byte[0];
			offset = Offset;
			_consoleVer = consoleVer;
		}

		public HLInstruction(byte Instruction, int Offset, bool consoleVer)
		{
			instruction = (Instruction) Instruction;
			operands = new byte[0];
			offset = Offset;
			_consoleVer = consoleVer;
		}

		public Instruction Instruction
		{
			get { return instruction; }
		}

		public void NopInstruction()
		{
			instruction = Instruction.Nop;
		}

		public int Offset
		{
			get { return offset; }
		}

		public int InstructionLength
		{
			get { return 1 + operands.Count(); }
		}

		public int GetOperandsAsInt
		{
			get
			{
				if (_consoleVer)
				{
					switch (operands.Count())
					{
						case 1:
							return operands[0];
						case 2:
							return Utils.SwapEndian(BitConverter.ToInt16(operands, 0));
						case 3:
							return operands[0] << 16 | operands[1] << 8 | operands[2];
						case 4:
							return Utils.SwapEndian(BitConverter.ToInt32(operands, 0));
					}
				}
				else
				{
					switch (operands.Count())
					{
						case 1:
							return operands[0];
						case 2:
							return BitConverter.ToInt16(operands, 0);
						case 3:
							return operands[2] << 16 | operands[1] << 8 | operands[0];
						case 4:
							return BitConverter.ToInt32(operands, 0);
					}
				}
				throw new Exception("Invalid amount of operands (" + operands.Count().ToString() + ")");
			}
		}

		public float GetFloat
		{
			get
			{
				if (operands.Count() != 4)
					throw new Exception("Not a Float");
				if (_consoleVer)
					return Utils.SwapEndian(BitConverter.ToSingle(operands, 0));
				else
					return BitConverter.ToSingle(operands, 0);
			}
		}

		public byte GetOperand(int index)
		{
			return operands[index];
		}

		public uint GetOperandsAsUInt
		{
			get
			{
				if (_consoleVer)
				{
					switch (operands.Count())
					{
						case 1:
							return operands[0];
						case 2:
							return Utils.SwapEndian(BitConverter.ToUInt16(operands, 0));
						case 3:
							return (uint) (operands[0] << 16 | operands[1] << 8 | operands[2]);
						case 4:
							return Utils.SwapEndian(BitConverter.ToUInt32(operands, 0));
					}
				}
				else
				{
					switch (operands.Count())
					{
						case 1:
							return operands[0];
						case 2:
							return BitConverter.ToUInt16(operands, 0);
						case 3:
							return (uint) (operands[2] << 16 | operands[1] << 8 | operands[0]);
						case 4:
							return BitConverter.ToUInt32(operands, 0);
					}
				}
				throw new Exception("Invalid amount of operands (" + operands.Count().ToString() + ")");
			}
		}

		public int GetJumpOffset
		{
			get
			{
				if (IsJumpInstruction)
					if (_consoleVer)
						return Utils.SwapEndian(BitConverter.ToInt16(operands, 0)) + offset + 3;
					else
						return BitConverter.ToInt16(operands, 0) + offset + 3;
				throw new Exception("Not A jump");
			}
		}

		public byte GetNativeParams
		{
			get
			{
				if (instruction == Instruction.Native)
				{
					return (byte) (operands[0] >> 2);
				}
				throw new Exception("Not A Native");
			}
		}

		public byte GetNativeReturns
		{
			get
			{
				if (instruction == Instruction.Native)
				{
					return (byte) (operands[0] & 0x3);
				}
				throw new Exception("Not A Native");
			}
		}

		public ushort GetNativeIndex
		{
			get
			{
				if (instruction == Instruction.Native)
				{
					// if (_consoleVer)
					return Utils.SwapEndian(BitConverter.ToUInt16(operands, 1));
					//else
					//	return BitConverter.ToUInt16(operands, 1);
				}
				throw new Exception("Not A Native");
			}
		}

		/*public int GetSwitchCase(int index)
		{
			if (instruction == Instruction.Switch)
			{
				int cases = GetOperand(0);
				if (index >= cases)
					throw new Exception("Out Or Range Script Case");
				return Utils.SwapEndian(BitConverter.ToInt32(operands, 1 + index * 6));
			}
			throw new Exception("Not A Switch Statement");
		}*/

		public string GetSwitchStringCase(int index)
		{
			if (instruction == Instruction.Switch)
			{
				int cases = GetOperand(0);
				if (index >= cases)
					throw new Exception("Out Or Range Script Case");
				if (_consoleVer)
					return Program.getIntType == Program.IntType._uint
						? ScriptFile.hashbank.GetHash(Utils.SwapEndian(BitConverter.ToUInt32(operands, 1 + index*6)))
						: ScriptFile.hashbank.GetHash(Utils.SwapEndian(BitConverter.ToInt32(operands, 1 + index*6)));
				else
					return Program.getIntType == Program.IntType._uint
						? ScriptFile.hashbank.GetHash(BitConverter.ToUInt32(operands, 1 + index*6))
						: ScriptFile.hashbank.GetHash(BitConverter.ToInt32(operands, 1 + index*6));
			}
			throw new Exception("Not A Switch Statement");
		}

		public int GetSwitchOffset(int index)
		{
			if (instruction == Instruction.Switch)
			{
				int cases = GetOperand(0);
				if (index >= cases)
					throw new Exception("Out of range script case");
				if (_consoleVer)
					return offset + 8 + index*6 + Utils.SwapEndian(BitConverter.ToInt16(operands, 5 + index*6));
				else
					return offset + 8 + index*6 + BitConverter.ToInt16(operands, 5 + index*6);
			}
			throw new Exception("Not A Switch Statement");
		}

		public int GetImmBytePush
		{
			get
			{
				int _instruction = (int) Instruction;
				if (_instruction >= 109 && _instruction <= 117)
				{
					return _instruction - 110;
				}
				throw new Exception("Not An Immediate Int Push");
			}
		}

		public float GetImmFloatPush
		{
			get
			{
				int _instruction = (int) Instruction;
				if (_instruction >= 118 && _instruction <= 126)
				{
					return (float) (_instruction - 119);
				}
				throw new Exception("Not An Immediate Float Push");
			}
		}

		public bool IsJumpInstruction
		{
			get { return (int) instruction > 84 && (int) instruction < 93; }
		}

		public bool IsConditionJump
		{
			get { return (int) instruction > 85 && (int) instruction < 93; }
		}

		public bool IsWhileJump
		{
			get
			{
				if (instruction == Instruction.Jump)
				{
					if (GetJumpOffset <= 0) return false;
					return (GetOperandsAsInt < 0);
				}
				return false;
			}
		}

		public string GetGlobalString
		{
			get
			{
				switch (instruction)
				{
					case Instruction.pGlobal2:
					case Instruction.GlobalGet2:
					case Instruction.GlobalSet2:
						return "Global_" +
								(Program.Hex_Index ? GetOperandsAsUInt.ToString("X") : GetOperandsAsUInt.ToString());
					case Instruction.pGlobal3:
					case Instruction.GlobalGet3:
					case Instruction.GlobalSet3:
						return "Global_" +
								(Program.Hex_Index ? GetOperandsAsUInt.ToString("X") : GetOperandsAsUInt.ToString());
				}
				throw new Exception("Not a global variable");
			}
		}
	}

	internal enum Instruction //opcodes https://bitbucket.org/scclteam/sc-cl/src/master/Include/Compiler/OpcodeConsts.h
	{
		Nop = 0,
		iAdd = 1,
		iSub = 2,
		iMult = 3,
		iDiv = 4,
		iMod = 5,
		iNot = 6,
		iNeg = 7,
		iCmpEq = 8,
		iCmpNe = 9,
		iCmpGt = 10,
		iCmpGe = 11,
		iCmpLt = 12,
		iCmpLe = 13,
		fAdd = 14,
		fSub = 15,
		fMult = 16,
		fDiv = 17,
		fMod = 18,
		fNeg = 19,
		fCmpEq = 20,
		fCmpNe = 21,
		fCmpGt = 22,
		fCmpGe = 23,
		fCmpLt = 24,
		fCmpLe = 25,
		vAdd = 26,
		vSub = 27,
		vMult = 28,
		vDiv = 29,
		vNeg = 30,
		And = 31,
		Or = 32,
		Xor = 33,
		ItoF = 34,
		FtoI = 35,
		FtoV = 36,
		iPushByte1 = 37,
		iPushByte2 = 38,
		iPushByte3 = 39,
		iPushInt = 40,
		fPush = 41,
		dup = 42,
		pop = 43,
		Native = 44,
		Enter = 45,
		Return = 46,
		pGet = 47,
		pSet = 48,
		pPeekSet = 49,
		ToStack = 50,
		FromStack = 51,
		pArray1 = 52,
		ArrayGet1 = 53,
		ArraySet1 = 54,
		pFrame1 = 55,
		GetFrame1 = 56,
		SetFrame1 = 57,
		pStatic1 = 58,
		StaticGet1 = 59,
		StaticSet1 = 60,
		Add1 = 61,
		GetStruct1 = 62,
		SetStruct1 = 63,
		Mult1 = 64,
		iPushShort = 65,
		Add2 = 66,
		GetStruct2 = 67,
		SetStruct2 = 68,
		Mult2 = 69,
		pArray2 = 70,
		ArrayGet2 = 71,
		ArraySet2 = 72,
		pFrame2 = 73,
		GetFrame2 = 74,
		SetFrame2 = 75,
		pStatic2 = 76,
		StaticGet2 = 77,
		StaticSet2 = 78,
		pGlobal2 = 79,
		GlobalGet2 = 80,
		GlobalSet2 = 81,

		// RDR Extra op codes
		Call2 = 82,
		Call2h1 = 83,
		Call2h2 = 84,
		Call2h3 = 85,
		Call2h4 = 86,
		Call2h5 = 87,
		Call2h6 = 88,
		Call2h7 = 89,
		Call2h8 = 90,
		Call2h9 = 91,
		Call2ha = 92,
		Call2hb = 93,
		Call2hc = 94,
		Call2hd = 95,
		Call2he = 96,
		Call2hf = 97,


		Jump = 98,
		JumpFalse = 99,
		JumpNe = 100,
		JumpEq = 101,
		JumpLe = 102,
		JumpLt = 103,
		JumpGe = 104,
		JumpGt = 105,
		pGlobal3 = 106,
		GlobalGet3 = 107,
		GlobalSet3 = 108,
		iPushI24 = 109,
		Switch = 110,
		PushString = 111,
		PushArrayP = 112, // RDR extra opcodes
		PushStringNull = 113, // RDR extra opcodes
		StrCopy = 114,
		ItoS = 115,
		StrConCat = 116,
		StrConCatInt = 117,
		MemCopy = 118,
		Catch = 119,
		Throw = 120,
		pCall = 121,


		// RDR extra opcodes
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


		iPush_n1 = 138,
		iPush_0 = 139,
		iPush_1 = 140,
		iPush_2 = 141,
		iPush_3 = 142,
		iPush_4 = 143,
		iPush_5 = 144,
		iPush_6 = 145,
		iPush_7 = 146,
		fPush_n1 = 147,
		fPush_0 = 148,
		fPush_1 = 149,
		fPush_2 = 150,
		fPush_3 = 151,
		fPush_4 = 152,
		fPush_5 = 153,
		fPush_6 = 154,
		fPush_7 = 155,
	}
}
