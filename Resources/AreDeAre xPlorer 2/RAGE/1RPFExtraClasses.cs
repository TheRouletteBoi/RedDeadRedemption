using System;

namespace RAGE.ExtraClasses
{
  public class RPF6Report : EventArgs
  {
    public string StatusOperationText { get; set; }

    public string StatusText { get; set; }

    public string TitleText { get; set; }

    public int CurrentOperation { get; set; }

    public int TotalOperations { get; set; }

    public int Percent => this.TotalOperations == 0 ? 100 : this.CurrentOperation * 100 / this.TotalOperations;
  }
}
