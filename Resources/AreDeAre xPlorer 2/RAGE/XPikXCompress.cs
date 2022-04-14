using System.Runtime.InteropServices;

namespace Pik
{
  public static class XPikXCompress
  {
    [DllImport("XCP.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern int XCompressCreateDecompressionContext(
      XPikXCompress.XMEMCODEC_TYPE CodecType,
      ref XPikXCompress.XMEMCODEC_PARAMETERS_LZX prams,
      uint flags,
      ref int pContext);

    [DllImport("XCP.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern void XCompressDestroyDecompressionContext(int context);

    [DllImport("XCP.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern int XCompressResetDecompressionContext(int context);

    [DllImport("XCP.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern int XCompressGetDecompressionContextSize(
      XPikXCompress.XMEMCODEC_TYPE CodecType,
      ref XPikXCompress.XMEMCODEC_PARAMETERS_LZX prams,
      uint flags);

    [DllImport("XCP.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern int XCompressDecompress(
      int context,
      byte[] dest,
      ref int destSize,
      byte[] source,
      int sourceSize);

    public enum XMEMCODEC_TYPE
    {
      XMEMCODEC_DEFAULT,
      XMEMCODEC_LZX,
    }

    [StructLayout(LayoutKind.Explicit)]
    public struct XMEMCODEC_PARAMETERS_LZX
    {
      [FieldOffset(0)]
      public uint Flags;
      [FieldOffset(4)]
      public uint WindowSize;
      [FieldOffset(8)]
      public uint CompressionPartitionSize;
    }
  }
}
