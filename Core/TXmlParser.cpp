#include "stdafx.h"
#include "TXmlParser.h"

TXmlParser::TXmlParser():IsOk(FALSE)
{
	
}

TXmlParser::~TXmlParser()
{
	
}

void TXmlParser::ParseFile(const char* FileName)
{
	TiXmlDocument Doc(FileName);
	if (Doc.LoadFile())
	{
		TiXmlNode*      Node ;
		TiXmlAttribute* Attribute;
		TiXmlElement*   Element;
		
		for( Node = Doc.LastChild();
		    Node!=0;
		    Node = Node->PreviousSibling() )
		{
			for( Element = Node->FirstChildElement();
			    Element!=0;
			    Element = Element->NextSiblingElement() )
			{
				printf("-------%s-------\n",Element->Value());
				Attribute = Element->FirstAttribute();
				while(Attribute)
				{
					printf("%s:%s\n",Attribute->Name(),Attribute->Value());
					Attribute=Attribute->Next();
				}
			}
		}
		IsOk=TRUE;
	}
	else
	{
		printf("¼ÓÔØÎÄ¼þ%sÊ§°Ü\n",FileName);
		IsOk=FALSE;
	}
}

void TXmlParser::ParseText(const char* Text)
{
	TiXmlDocument Doc;
	Doc.Parse(Text);
	if (!Doc.Error())
	{
		TiXmlNode*      Node ;
		TiXmlAttribute* Attribute;
		TiXmlElement*   Element;
		
		for( Node = Doc.LastChild();
		    Node!=0;
		    Node = Node->PreviousSibling() )
		{
			for( Element = Node->FirstChildElement();
			    Element!=0;
			    Element = Element->NextSiblingElement() )
			{
				printf("-------------%s---------------\n",Element->Value());
				Attribute = Element->FirstAttribute();
				while(Attribute)
				{
					printf("%s:%s\n",Attribute->Name(),Attribute->Value());
					Attribute=Attribute->Next();
				}
			}
		}
		IsOk=TRUE;
	}
	else
	{
		printf("½âÎö×Ö·û´®Ê§°Ü\n%s\n",Text);
		IsOk=FALSE;
	}
}



BOOL TXmlParser::NoError()
{
	
	return IsOk;
}