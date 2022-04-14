using System;
using System.Collections.Generic;
using System.IO;	  
using System.Windows.Forms;

namespace Decompiler
{
	class NativeParamInfo
	{
		Dictionary<uint, Tuple<Stack.DataType, Stack.DataType[]>> Natives;

		public NativeParamInfo()
		{
			loadfile();
		}

		public void savefile()
		{
			Stream natfile =
				File.Create(Path.Combine(Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location),
					"nativeinfo.dat"));
			IO.Writer writer = new IO.Writer(natfile);
			foreach (KeyValuePair<uint, Tuple<Stack.DataType, Stack.DataType[]>> native in Natives)
			{
				writer.Write(native.Key);
				writer.Write(Types.indexof(native.Value.Item1));
				writer.Write((byte) native.Value.Item2.Length);
				for (int i = 0; i < native.Value.Item2.Length; i++)
				{
					writer.Write(Types.indexof(native.Value.Item2[i]));
				}
			}
			writer.Close();
		}


		public void updatenative(uint hash, Stack.DataType returns, params Stack.DataType[] param)
		{
			lock (Program.ThreadLock)
			{
				if (!Natives.ContainsKey(hash))
				{
					Natives.Add(hash, new Tuple<Stack.DataType, Stack.DataType[]>(returns, param));
					return;
				}
			}

			Stack.DataType curret = Natives[hash].Item1;
			Stack.DataType[] curpar = Natives[hash].Item2;

			if (Types.gettype(curret).precedence < Types.gettype(returns).precedence)
			{
				curret = returns;
			}
			for (int i = 0; i < curpar.Length; i++)
			{
				if (Types.gettype(curpar[i]).precedence < Types.gettype(param[i]).precedence)
				{
					curpar[i] = param[i];
				}
			}
			Natives[hash] = new Tuple<Stack.DataType, Stack.DataType[]>(curret, curpar);
		}

		public bool updateparam(uint hash, Stack.DataType type, int paramindex)
		{
			if (!Natives.ContainsKey(hash))
				return false;
			Stack.DataType[] paramslist = Natives[hash].Item2;
			paramslist[paramindex] = type;
			Natives[hash] = new Tuple<Stack.DataType, Stack.DataType[]>(Natives[hash].Item1, paramslist);
			return true;
		}

		public Stack.DataType getrettype(uint hash)
		{
			if (!Natives.ContainsKey(hash))
				return Stack.DataType.Unk;
			return Natives[hash].Item1;
		}

		public Stack.DataType getparamtype(uint hash, int index)
		{
			if (!Natives.ContainsKey(hash))
				return Stack.DataType.Unk;
			return Natives[hash].Item2[index];
		}

		public void updaterettype(uint hash, Stack.DataType returns, bool over = false)
		{
			if (!Natives.ContainsKey(hash))
				return;
			if (Types.gettype(Natives[hash].Item1).precedence < Types.gettype(returns).precedence || over)
			{
				Natives[hash] = new Tuple<Stack.DataType, Stack.DataType[]>(returns, Natives[hash].Item2);
			}
		}

		public void loadfile()
		{
			Natives = new Dictionary<uint, Tuple<Stack.DataType, Stack.DataType[]>>();
			string file = Path.Combine(Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location),
				"nativeinfo.dat");
			if (!File.Exists(file))
				return;
			Stream natfile = File.OpenRead(file);
			IO.Reader reader = new IO.Reader(natfile, true);
			while (natfile.Position < natfile.Length)
			{
				uint native = reader.ReadUInt32();
				Stack.DataType returntype = Types.getatindex(reader.ReadByte());
				byte count = reader.ReadByte();
				Stack.DataType[] param = new Stack.DataType[count];
				for (byte i = 0; i < count; i++)
				{
					param[i] = Types.getatindex(reader.ReadByte());
				}
				Natives.Add(native, new Tuple<Stack.DataType, Stack.DataType[]>(returntype, param));
			}

		}

		public string getnativeinfo(uint hash)
		{
			if (!Natives.ContainsKey(hash))
			{
				throw new Exception("Native not found");
			}
			string dec = Types.gettype(Natives[hash].Item1).returntype + Program.nativefile.nativefromhash(hash) + "(";
			int max = Natives[hash].Item2.Length;
			if (max == 0)
				return dec + ");";
			for (int i = 0; i < max; i++)
			{
				dec += Types.gettype(Natives[hash].Item2[i]).vardec + i + ", ";
			}
			return dec.Remove(dec.Length - 2) + ");";
		}

		public void exportnativeinfo()
		{
			Stream natfile =
				File.Create(Path.Combine(Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location),
					"natives.h"));
			StreamWriter sw = new StreamWriter(natfile);
			sw.WriteLine("/*************************************************************");
			sw.WriteLine("****************** GTA V Native Header file ******************");
			sw.WriteLine("*************************************************************/\n");
			sw.WriteLine("#ifndef NATIVE_HEADER\n#define NATIVE_HEADER");
			sw.WriteLine("typedef unsigned int uint;");
			sw.WriteLine("typedef uint bool;");
			sw.WriteLine("typedef uint var;");
			sw.WriteLine("");
			List<Tuple<string, string>> natives = new List<Tuple<string, string>>();

			foreach (KeyValuePair<uint, Tuple<Stack.DataType, Stack.DataType[]>> native in Natives)
			{
				string type = Types.gettype(native.Value.Item1).returntype;
				string line = Program.nativefile.nativefromhash(native.Key) + "(";

				int max = native.Value.Item2.Length;
				if (max == 0)
				{
					natives.Add(new Tuple<string, string>(line + ");\n", type));
					continue;
				}
				for (int i = 0; i < max; i++)
				{
					line += Types.gettype(native.Value.Item2[i]).vardec + i + ", ";
				}
				natives.Add(new Tuple<string, string>(line.Remove(line.Length - 2) + ");\n", type));
			}
			natives.Sort();
			foreach (Tuple<string, string> native in natives)
			{
				sw.Write("extern " + native.Item2 + native.Item1);
			}
			sw.WriteLine("#endif");
			sw.Close();
		}

		public string TypeToString(Stack.DataType type)
		{
			return Types.gettype(type).singlename;
		}

		public Stack.DataType StringToType(string _string)
		{
			foreach (Types.DataTypes type in Types._types)
			{
				if (type.singlename == _string)
					return type.type;
			}
			throw new Exception("Type not found");
		}

		public bool StringTypeExists(string _string)
		{
			foreach (Types.DataTypes type in Types._types)
			{
				if (type.singlename == _string)
					return true;
			}
			return false;
		}

	}
}
