using Pik;
using Pik.IO;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace RAGE.RDR2
{
  public class _ST
  {
    private uint _VMT;

    public uint VMT => this._VMT;

    public uint TableModValue { get; set; }

    public uint AllCount => (uint) this.Entries.Count;

    public List<_ST._STEntry> Entries { get; set; }

    public _ST() => this.Entries = new List<_ST._STEntry>();

    public _ST(Stream xIn)
    {
      this.Entries = new List<_ST._STEntry>();
      this.Read((Stream) new MemoryStream(ResourceUtils.ResourceInfo.GetDataFromStream(xIn)));
    }

    public static bool IsValidSTResource(Stream xIn)
    {
      (bool, string, int, int, int) resourceInformation = ResourceUtils.ResourceInfo.GetResourceInformation(xIn);
      return resourceInformation.Item1 && resourceInformation.Item3 == 1;
    }

    private void Read(Stream xIn)
    {
      PikIO pikIo = new PikIO(xIn, PikIO.Endianess.Big);
      this._VMT = pikIo.ReadUInt32();
      pikIo.Seek(4L, SeekOrigin.Current);
      uint num1 = pikIo.ReadUInt32() & 268435455U;
      pikIo.Position = (long) num1;
      uint num2 = pikIo.ReadUInt32();
      uint num3 = pikIo.ReadUInt32() & 268435455U;
      pikIo.Seek(4L, SeekOrigin.Current);
      pikIo.ReadUInt32();
      pikIo.Position = (long) num3;
      this.TableModValue = num2;
      for (int index = 0; (long) index < (long) num2; ++index)
      {
        uint num4 = pikIo.ReadUInt32() & 268435455U;
        long position = pikIo.Position;
        if (num4 > 0U)
        {
          pikIo.Position = (long) num4;
          pikIo.ReadUInt32();
          uint num5 = pikIo.ReadUInt32() & 268435455U;
          uint num6 = pikIo.ReadUInt32() & 268435455U;
          int num7 = 0;
          while (num5 > 0U)
          {
            pikIo.Position = (long) num5;
            uint num8 = pikIo.ReadUInt32();
            uint num9 = pikIo.ReadUInt32() & 268435455U;
            pikIo.Position = (long) num9;
            string empty = string.Empty;
            while (true)
            {
              byte num10 = pikIo.ReadByte();
              if (num10 != (byte) 0)
                empty += ((char) num10).ToString();
              else
                break;
            }
            this.Entries.Add(new _ST._STEntry()
            {
              Key = num8,
              Level = num7,
              StrValue = empty
            });
            if (num6 != 0U && num8 > 0U)
            {
              pikIo.Position = (long) num6;
              pikIo.ReadUInt32();
              num5 = pikIo.ReadUInt32() & 268435455U;
              num6 = pikIo.ReadUInt32() & 268435455U;
            }
            else
              num5 = 0U;
            ++num7;
          }
        }
        pikIo.Position = position;
      }
    }

    public void Write(Stream xOut)
    {
      Dictionary<string, long> dictionary1 = new Dictionary<string, long>();
      Dictionary<uint, long> dictionary2 = new Dictionary<uint, long>();
      Dictionary<uint, long> dictionary3 = new Dictionary<uint, long>();
      bool[] flagArray = new bool[(int) this.TableModValue];
      dictionary1.Add("PositionOf_OffsetToStringTableOffset", 0L);
      dictionary1.Add("TempOffset", 0L);
      MemoryStream memoryStream = new MemoryStream();
      PikIO pikIo = new PikIO((Stream) memoryStream, PikIO.Endianess.Big);
      pikIo.Write(this._VMT);
      pikIo.Write(1342177312);
      pikIo.Write(1342177840);
      pikIo.Write(0);
      pikIo.Write(0);
      for (int index = 0; index < 3; ++index)
        pikIo.Write(3452816845U);
      pikIo.Write(0);
      for (int index = 0; index < 131; ++index)
        pikIo.Write(3452816845U);
      pikIo.Write(this.TableModValue);
      dictionary1["PositionOf_OffsetToStringTableOffset"] = pikIo.Position;
      pikIo.Write(0);
      pikIo.Write((ushort) this.TableModValue);
      pikIo.Write((ushort) this.TableModValue);
      pikIo.Write(this.AllCount);
      Func<int, uint, int> func1 = (Func<int, uint, int>) ((index, modVal) => this.Entries.Count<_ST._STEntry>((Func<_ST._STEntry, bool>) (x => (long) (x.Key % modVal) == (long) index)));
      Func<int, uint, _ST._STEntry[]> func2 = (Func<int, uint, _ST._STEntry[]>) ((index, modVal) =>
      {
        List<_ST._STEntry> stEntryList = new List<_ST._STEntry>();
        stEntryList.AddRange((IEnumerable<_ST._STEntry>) this.Entries.Where<_ST._STEntry>((Func<_ST._STEntry, bool>) (x => (long) (x.Key % modVal) == (long) index)).ToList<_ST._STEntry>().OrderBy<_ST._STEntry, uint>((Func<_ST._STEntry, uint>) (x => x.Key % modVal)));
        return stEntryList.ToArray();
      });
      dictionary1["TempOffset"] = pikIo.Position;
      pikIo.Position = dictionary1["PositionOf_OffsetToStringTableOffset"];
      pikIo.Write((uint) (1342177280 | (int) (uint) dictionary1["TempOffset"] & 268435455));
      pikIo.Position = dictionary1["TempOffset"];
      pikIo.WriteBytes(new byte[4 * (int) this.TableModValue]);
      for (int index = 0; (long) index < (long) this.TableModValue; ++index)
      {
        int num1 = func1(index, this.TableModValue);
        if (!flagArray[index])
        {
          dictionary1["TempOffset"] = pikIo.Position;
          pikIo.Position = dictionary1["PositionOf_OffsetToStringTableOffset"] + 12L + (long) (index * 4);
          if (num1 == 0)
            pikIo.Write(0);
          else
            pikIo.Write((uint) (1342177280 | (int) (uint) dictionary1["TempOffset"] & 268435455));
          pikIo.Position = dictionary1["TempOffset"];
          flagArray[index] = true;
        }
        int num2 = 0;
        _ST._STEntry[] stEntryArray = func2(index, this.TableModValue);
        foreach (_ST._STEntry stEntry in stEntryArray)
        {
          pikIo.Write(stEntry.Key);
          dictionary2.Add(stEntry.Key, pikIo.Position);
          pikIo.Write(0);
          if (stEntryArray.Length > num2 + 1)
            pikIo.Write(1342177280U | (uint) ((ulong) (pikIo.Position + 4L) & 268435455UL));
          else
            pikIo.Write(0);
          ++num2;
        }
      }
      for (int index = 0; (long) index < (long) this.TableModValue; ++index)
      {
        foreach (_ST._STEntry stEntry in func2(index, this.TableModValue))
        {
          dictionary1["TempOffset"] = pikIo.Position;
          pikIo.Position = dictionary2[stEntry.Key];
          pikIo.Write(1342177280U | (uint) ((ulong) dictionary1["TempOffset"] & 268435455UL));
          pikIo.Position = dictionary1["TempOffset"];
          pikIo.Write(stEntry.Key);
          dictionary3.Add(stEntry.Key, pikIo.Position);
          pikIo.Write(0);
        }
      }
      foreach (_ST._STEntry entry in this.Entries)
      {
        dictionary1["TempOffset"] = pikIo.Position;
        pikIo.Position = dictionary3[entry.Key];
        pikIo.Write(1342177280U | (uint) ((ulong) dictionary1["TempOffset"] & 268435455UL));
        pikIo.Position = dictionary1["TempOffset"];
        pikIo.WriteBytes(Encoding.ASCII.GetBytes(entry.StrValue + "\0"));
      }
      byte[] b = new byte[DataUtils.NumLeftTill((int) pikIo.Length, (int) AppGlobals.Platform)];
      for (int index = 0; index < b.Length; ++index)
        b[index] = (byte) 205;
      pikIo.WriteBytes(b);
      byte[] buffer = ResourceUtils.FlagInfo.RSC05_PackResource(memoryStream.ToArray(), (int) memoryStream.Length, 0, 1, AppGlobals.Platform);
      xOut.Write(buffer, 0, buffer.Length);
    }

    public void SetVMT(uint vmt_val) => this._VMT = vmt_val;

    public void AddEntry(uint key, string val) => this.Entries.Add(new _ST._STEntry()
    {
      Key = key,
      StrValue = val
    });

    public void AddEntry(string key, string val) => this.AddEntry(DataUtils.GetHash(key), val);

    public void RemoveEntry(uint key)
    {
      for (int index = 0; index < this.Entries.Count; ++index)
      {
        if ((int) this.Entries[index].Key == (int) key)
        {
          this.Entries.RemoveAt(index);
          break;
        }
      }
    }

    public void RemoveEntry(string key) => this.RemoveEntry(DataUtils.GetHash(key));

    public class _STEntry
    {
      public string StrValue { get; set; }

      public uint Key { get; set; }

      public int Level { get; set; }

      public string KeyString
      {
        set => this.Key = DataUtils.GetHash(value);
      }
    }
  }
}
