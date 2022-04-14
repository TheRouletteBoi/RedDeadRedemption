using System.Runtime.InteropServices;

namespace Pik
{
  public static class xcompress
  {
    public const int XMEMCOMPRESS_STREAM = 1;

    [DllImport("xcompress32.dll")]
    public static extern int XMemCreateDecompressionContext(
      xcompress.XMEMCODEC_TYPE CodecType,
      int pCodecParams,
      int Flags,
      ref int pContext);

    [DllImport("xcompress32.dll")]
    public static extern void XMemDestroyDecompressionContext(int Context);

    [DllImport("xcompress32.dll")]
    public static extern int XMemResetDecompressionContext(int Context);

    [DllImport("xcompress32.dll")]
    public static extern int XMemDecompress(
      int Context,
      byte[] pDestination,
      ref int pDestSize,
      byte[] pSource,
      int pSrcSize);

    [DllImport("xcompress32.dll")]
    public static extern int XMemDecompressStream(
      int Context,
      byte[] pDestination,
      ref int pDestSize,
      byte[] pSource,
      ref int pSrcSize);

    [DllImport("xcompress32.dll")]
    public static extern int XMemCreateCompressionContext(
      xcompress.XMEMCODEC_TYPE CodecType,
      ref xcompress.XMEMCODEC_PARAMETERS_LZX prams,
      int Flags,
      ref int pContext);

    [DllImport("xcompress32.dll")]
    public static extern void XMemDestroyCompressionContext(int Context);

    [DllImport("xcompress32.dll")]
    public static extern int XMemResetCompressionContext(int Context);

    [DllImport("xcompress32.dll")]
    public static extern int XMemCompress(
      int Context,
      byte[] pDestination,
      ref int pDestSize,
      byte[] pSource,
      int pSrcSize);

    [DllImport("xcompress32.dll")]
    public static extern int XMemCompressStream(
      int Context,
      byte[] pDestination,
      ref int pDestSize,
      byte[] pSource,
      ref int pSrcSize);

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
