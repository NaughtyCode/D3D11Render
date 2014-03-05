#ifndef TXMLPARSER_H
#define TXMLPARSER_H

#if _MSC_VER > 1000
# pragma once
#endif


typedef struct ShaderNode
{
    char FileName[MAXFILENAME];
    char Profile[MAXSHADERPROFILE];
    char Entry[MAXSHADERENTRY];
}ShaderNode;


typedef struct ModelNode
{
    char FileName[MAXFILENAME];
}ModelNode;


typedef struct TextureNode
{
    char FileName[MAXFILENAME];
}TextureNode;


class TXmlParser
{
public:
    TXmlParser();
    ~TXmlParser();
    void ParseFile(const char* FileName);
    void ParseText(const char* Text);
    BOOL NoError();
    
private:
    BOOL IsOk;
};



#endif



