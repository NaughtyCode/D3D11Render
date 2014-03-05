#ifndef TXMLPARSER_H
#define TXMLPARSER_H

#if _MSC_VER > 1000
# pragma once
#endif



class TXmlParser
{
public:
    TXmlParser();
    ~TXmlParser();
    
    void ParseFile(const char* FileName);
    
    void ParseText(const char* Text);
    
private:
    
};



#endif



