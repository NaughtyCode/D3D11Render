#include "stdafx.h"
#include "TXmlParser.h"

TXmlParser::TXmlParser()
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
	}
	else
	{
		printf("�����ļ�%sʧ��\n",FileName);
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
	}
	else
	{
		printf("�����ַ���ʧ��\n%s\n",Text);
	}
}
