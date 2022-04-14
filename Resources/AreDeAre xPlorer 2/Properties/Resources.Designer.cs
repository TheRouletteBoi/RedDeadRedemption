using System.CodeDom.Compiler;
using System.ComponentModel;
using System.Diagnostics;
using System.Globalization;
using System.Resources;
using System.Runtime.CompilerServices;

namespace AreDeAre_xPlorer_2.Properties
{
  [GeneratedCode("System.Resources.Tools.StronglyTypedResourceBuilder", "4.0.0.0")]
  [DebuggerNonUserCode]
  [CompilerGenerated]
  internal class Resources
  {
    private static ResourceManager resourceMan;
    private static CultureInfo resourceCulture;

    internal Resources()
    {
    }

    [EditorBrowsable(EditorBrowsableState.Advanced)]
    internal static ResourceManager ResourceManager
    {
      get
      {
        if (AreDeAre_xPlorer_2.Properties.Resources.resourceMan == null)
          AreDeAre_xPlorer_2.Properties.Resources.resourceMan = new ResourceManager("AreDeAre_xPlorer_2.Properties.Resources", typeof (AreDeAre_xPlorer_2.Properties.Resources).Assembly);
        return AreDeAre_xPlorer_2.Properties.Resources.resourceMan;
      }
    }

    [EditorBrowsable(EditorBrowsableState.Advanced)]
    internal static CultureInfo Culture
    {
      get => AreDeAre_xPlorer_2.Properties.Resources.resourceCulture;
      set => AreDeAre_xPlorer_2.Properties.Resources.resourceCulture = value;
    }
  }
}
