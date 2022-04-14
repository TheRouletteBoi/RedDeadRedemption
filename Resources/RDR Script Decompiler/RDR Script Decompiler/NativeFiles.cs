using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.IO.Compression;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Decompiler
{
	class NativeFile : Dictionary<uint, string>
	{
		public string nativefromhash(uint hash)
		{
			if (Program.nativefile.ContainsKey(hash))
			{
				return this[hash];
			}
			else
			{
				string temps = hash.ToString("X");
				while (temps.Length < 8)
					temps = "0" + temps;
				return "unk_0x" + temps;
			}
		}
		public Dictionary<string, uint> revmap = new Dictionary<string, uint>();
		public NativeFile(Stream Nativefile) : base()
		{
			StreamReader sr = new StreamReader(Nativefile);
			while (!sr.EndOfStream)
			{
				string line = sr.ReadLine();
				if (line.Length > 1)
				{
					string[] data = line.Split(':');
					if (data.Length != 3)
						continue;
					string val = data[0];	
					if(val.StartsWith("0x"))
					{
						val = val.Substring(2);
					}
					uint value;
					if (uint.TryParse(val, NumberStyles.HexNumber, CultureInfo.InvariantCulture, out value))
					{
						if (!ContainsKey(value))
						{
							string nat = (Program.Show_Nat_Namespace ? (data[1] + "::") : "");
							if(Program.Upper_Natives)
							{
								nat = nat.ToUpper();
								if(data[2].StartsWith("_0x"))
								{
									nat += data[2].Remove(3) + data[2].Substring(3).ToUpper();
								}
								else
								{
									nat += data[2].ToUpper();
								}
							}
							else
							{
								nat = nat.ToLower();
								if(data[2].StartsWith("_0x"))
								{
									nat += data[2].Remove(3) + data[2].Substring(3).ToUpper();
								}
								else
								{
									nat += data[2].ToLower();
								}
							}
							Add(value, nat);
							revmap.Add(nat, value);
						}
					}
				}
			}
			sr.Close();
		}
	}
}
