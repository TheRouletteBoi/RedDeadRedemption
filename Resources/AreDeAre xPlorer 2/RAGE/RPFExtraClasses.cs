using System;

namespace RAGE.ExtraClasses
{
  public class RPF6ErrorReport : EventArgs
  {
    public string Message { get; set; }

    public Exception Ex { get; set; }
  }
}
