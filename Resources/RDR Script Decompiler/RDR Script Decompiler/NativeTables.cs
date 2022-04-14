using System;
using System.Collections.Generic;
using System.IO;

namespace Decompiler
{
	//These classes are generated from a script and are used to translate the index a native is called with to its hash/reversed name
	//X64 corresponds to the PC version of the gane. Would likely include PS4/X1 version but no work has been done with those systems
	public class NativeTable
	{
		List<string> _natives;
		List<uint> _nativehash;
		public NativeTable(Stream scriptFile, int position, int length)
		{
			IO.Reader reader = new IO.Reader(scriptFile, true);
			int count = 0;
			uint nat;
			reader.BaseStream.Position = position;
			_natives = new List<string>();
			_nativehash = new List<uint>();
			while (count < length)
			{
				nat = reader.SReadUInt32();
				_nativehash.Add(nat);
				if (Program.nativefile.ContainsKey(nat))
				{
					_natives.Add(Program.nativefile[nat]);
				}
				else
				{
					string temps = nat.ToString("X");
					while (temps.Length < 8)
						temps = "0" + temps;
					_natives.Add("unk_0x" + temps);
				}
				count++;
			}

		}
		public string[] GetNativeTable()
		{
			List<string> table = new List<string>();
			int i = 0;
			foreach (string native in _natives)
			{
				table.Add(i++.ToString("X2") + ": " + native);
			}
			return table.ToArray();
		}
		public string[] GetNativeHeader()
		{
			List<string> NativesHeader = new List<string>();
			foreach (uint hash in _nativehash)
			{
				NativesHeader.Add(ScriptFile.npi.getnativeinfo(hash));
			}

			return NativesHeader.ToArray();
		}
		public string GetNativeFromIndex(int index)
		{
			if (index < 0)
				throw new ArgumentOutOfRangeException("Index must be a positive integer");
			if (index >= _natives.Count)
				throw new ArgumentOutOfRangeException("Index is greater than native table size");
			return _natives[index];
		}
		public uint GetNativeHashFromIndex(int index)
		{
			if (index < 0)
				throw new ArgumentOutOfRangeException("Index must be a positive integer");
			if (index >= _nativehash.Count)
				throw new ArgumentOutOfRangeException("Index is greater than native table size");
			return _nativehash[index];
		}
		public void dispose()
		{
			_natives.Clear();
		}
	}
}
