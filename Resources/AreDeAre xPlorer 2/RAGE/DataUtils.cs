using ICSharpCode.SharpZipLib.Zip.Compression;
using System;
using System.Runtime.ExceptionServices;
using System.Security.Cryptography;

namespace Pik
{
  public static class DataUtils
  {
    public static byte[] Decrypt(byte[] dataIn, byte[] key)
    {
      byte[] numArray = new byte[dataIn.Length];
      dataIn.CopyTo((Array) numArray, 0);
      if (numArray == null)
        return (byte[]) null;
      int inputCount = numArray.Length & -16;
      if (inputCount > 0)
      {
        Rijndael rijndael = Rijndael.Create();
        rijndael.BlockSize = 128;
        rijndael.KeySize = 256;
        rijndael.Mode = CipherMode.ECB;
        rijndael.Key = key;
        rijndael.IV = new byte[16];
        rijndael.Padding = PaddingMode.None;
        ICryptoTransform decryptor = rijndael.CreateDecryptor();
        for (int index = 0; index < 16; ++index)
          decryptor.TransformBlock(numArray, 0, inputCount, numArray, 0);
      }
      return numArray;
    }

    public static byte[] Encrypt(byte[] dataIn, byte[] key)
    {
      byte[] numArray = new byte[dataIn.Length];
      dataIn.CopyTo((Array) numArray, 0);
      if (numArray == null)
        return (byte[]) null;
      int inputCount = numArray.Length & -16;
      if (inputCount > 0)
      {
        Rijndael rijndael = Rijndael.Create();
        rijndael.BlockSize = 128;
        rijndael.KeySize = 256;
        rijndael.Mode = CipherMode.ECB;
        rijndael.Key = key;
        rijndael.IV = new byte[16];
        rijndael.Padding = PaddingMode.None;
        ICryptoTransform encryptor = rijndael.CreateEncryptor();
        for (int index = 0; index < 16; ++index)
          encryptor.TransformBlock(numArray, 0, inputCount, numArray, 0);
      }
      return numArray;
    }

    public static uint GetHash(string str)
    {
      char[] charArray = str.ToLower().ToCharArray();
      uint num1;
      uint num2;
      for (num2 = num1 = 0U; (long) num1 < (long) charArray.Length; ++num1)
      {
        uint num3 = num2 + (uint) charArray[(int) num1];
        uint num4 = num3 + (num3 << 10);
        num2 = num4 ^ num4 >> 6;
      }
      uint num5 = num2 + (num2 << 3);
      uint num6 = num5 ^ num5 >> 11;
      return num6 + (num6 << 15);
    }

    public static byte[] DecompressDeflate(byte[] data, int decompSize, bool noHeader = true)
    {
      byte[] buffer = new byte[decompSize];
      Inflater inflater = new Inflater(noHeader);
      inflater.SetInput(data);
      inflater.Inflate(buffer);
      return buffer;
    }

    public static byte[] Compress(byte[] input, int level, bool noHeader = true)
    {
      byte[] output = new byte[input.Length];
      Deflater deflater = new Deflater(level, noHeader);
      byte[] numArray;
      try
      {
        deflater.SetInput(input, 0, input.Length);
        deflater.Finish();
        numArray = new byte[deflater.Deflate(output)];
      }
      catch (Exception ex)
      {
        throw ex;
      }
      Array.Copy((Array) output, 0, (Array) numArray, 0, numArray.Length);
      return numArray;
    }

    [HandleProcessCorruptedStateExceptions]
    public static int DecompressLZX(
      byte[] compressedData,
      out byte[] decompressedData,
      ref int dLen,
      uint windowSize = 131072)
    {
      int pContext = 0;
      XPikXCompress.XMEMCODEC_PARAMETERS_LZX xmemcodecParametersLzx;
      xmemcodecParametersLzx.Flags = 0U;
      xmemcodecParametersLzx.CompressionPartitionSize = 0U;
      xmemcodecParametersLzx.WindowSize = windowSize;
      decompressedData = (byte[]) null;
      if (xcompress.XMemCreateDecompressionContext(xcompress.XMEMCODEC_TYPE.XMEMCODEC_LZX, 0, 0, ref pContext) != 0)
        throw new Exception("LZX Error:  CREATE_DECOMPRESSION_CONTEXT");
      xcompress.XMemResetDecompressionContext(pContext);
      byte[] pDestination = new byte[dLen];
      int length = compressedData.Length;
      int num = xcompress.XMemDecompressStream(pContext, pDestination, ref dLen, compressedData, ref length);
      decompressedData = pDestination;
      xcompress.XMemDestroyDecompressionContext(pContext);
      return num;
    }

    public static byte[] CompressLZX(byte[] decompressedData, uint windowSize = 131072)
    {
      int pContext = 0;
      int num = 0;
      xcompress.XMEMCODEC_PARAMETERS_LZX prams;
      prams.Flags = 0U;
      prams.CompressionPartitionSize = 0U;
      prams.WindowSize = windowSize;
      num = xcompress.XMemCreateCompressionContext(xcompress.XMEMCODEC_TYPE.XMEMCODEC_LZX, ref prams, 0, ref pContext) == 0 ? xcompress.XMemResetCompressionContext(pContext) : throw new Exception("LZX Error: CREATE_COMPRESSION_CONTEXT");
      byte[] array = new byte[decompressedData.Length * 2];
      int length1 = array.Length;
      int length2 = decompressedData.Length;
      num = xcompress.XMemCompress(pContext, array, ref length1, decompressedData, length2);
      Array.Resize<byte>(ref array, length1);
      xcompress.XMemDestroyCompressionContext(pContext);
      return array;
    }

    public static int SetBit(int val, int bit, bool trueORfalse)
    {
      bool flag = (uint) (val & 1 << bit) > 0U;
      if (trueORfalse)
      {
        if (!flag)
          return val |= 1 << bit;
      }
      else if (flag)
        return val ^ 1 << bit;
      return val;
    }

    public static int IntFromUInt(uint x) => (int) x;

    public static uint UIntFromInt(int x) => (uint) x;

    public static int NumLeftTill(int current, int roundTo)
    {
      int num = Math.Abs(roundTo - current % roundTo);
      return num == roundTo ? 0 : num;
    }

    public static long RoundUp(long num, long multiple)
    {
      if (multiple == 0L)
        return 0;
      long num1 = multiple / Math.Abs(multiple);
      long num2 = (num + multiple - num1) / multiple * multiple;
      return (num + multiple - num1) / multiple * multiple;
    }

    public static int TrailingZeroes(int n)
    {
      int num1 = 1;
      int num2 = 0;
      while (num2 < 32)
      {
        if ((uint) (n & num1) > 0U)
          return num2;
        ++num2;
        num1 <<= 1;
      }
      return 32;
    }

    public static int LeadingZeros(int x)
    {
      x |= x >> 1;
      x |= x >> 2;
      x |= x >> 4;
      x |= x >> 8;
      x |= x >> 16;
      x -= x >> 1 & 1431655765;
      x = (x >> 2 & 858993459) + (x & 858993459);
      x = (x >> 4) + x & 252645135;
      x += x >> 8;
      x += x >> 16;
      return 32 - (x & 63);
    }

    public static int GenerateMask32(int maskBegin, int maskEnd)
    {
      int num = 0;
      for (int index = maskBegin; index <= maskEnd; ++index)
        num |= 1 << index;
      return num;
    }

    public static uint ReverseBytes(uint value) => (uint) (((int) value & (int) byte.MaxValue) << 24 | ((int) value & 65280) << 8) | (value & 16711680U) >> 8 | (value & 4278190080U) >> 24;
  }
}
