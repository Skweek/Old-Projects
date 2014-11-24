using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;

namespace ActorEditor
{
    class XMLHandler
    {
        static private XmlDocument xmlDoc;
        static private XmlNode xmlMainNode;
        static private XmlElement xmlActorElement;
        static private XmlElement xmlLimbsElement;
        static private XmlElement xmlLimbElement;


        static public void ExportActor(MainWindow instance)
        {
            Console.Write("Writing XML document...");
            Console.WriteLine();

            // Create the document
            xmlDoc = new XmlDocument();

            xmlMainNode = xmlDoc.CreateNode(XmlNodeType.XmlDeclaration, "", "");
            xmlDoc.AppendChild(xmlMainNode);

            xmlActorElement = xmlDoc.CreateElement("actor");
            xmlDoc.AppendChild(xmlActorElement);

            // Create limbs element
            xmlLimbsElement = xmlDoc.CreateElement("limbs");
            xmlLimbsElement.SetAttribute("count", "6");
            xmlActorElement.AppendChild(xmlLimbsElement);

            // Create each individual limb element
            for (int i = 0; i < 6; ++i)
            {
                xmlLimbElement = xmlDoc.CreateElement("limb");
                xmlLimbElement.SetAttribute("id", i.ToString());
                xmlLimbElement.SetAttribute("X", "0");
                xmlLimbElement.SetAttribute("Y", "0");
                xmlLimbElement.SetAttribute("W", "32");
                xmlLimbElement.SetAttribute("H", "32");
                xmlLimbElement.SetAttribute("imagerow", (1 + instance.ActorPartsRows[i]).ToString());

                xmlLimbsElement.AppendChild(xmlLimbElement);
            }

            Console.Write("Saving XML document...");
            Console.WriteLine();

            xmlDoc.Save( instance.AppPath + "test.xml");

            Console.Write("XML document saved to " + instance.AppPath + "test.xml");
            Console.WriteLine();
        }
    }
}
