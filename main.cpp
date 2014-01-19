#include <iostream>
#include <tinyxml.h>
//#include ".\fieldWrapper.h"
#include ".\fieldWrapper2.h"
#include <map>
using namespace std;
struct aStruct
{
    int a;
    std::vector<int> aVec;
    std::map<int, int> aMap;
    struct anInner{
        int a;
        void parse(const char* name, const TiXmlElement& root){
            ::parse(a,"a",root);
        }
    };
    std::map<int, anInner> anInnerMap;
    void parse(const char* name, const TiXmlElement& root)
    {
//        fieldWrapper fa(a);
//        fa.parse("a",root);
//        fieldWrapper faVec(aVec);
//        faVec.parse("aVec", root);
        ::parse(a, "a", root);
        ::parse(aVec, "aVec", root);
        ::parse(aMap, "aMap", root);
        ::parse(anInnerMap,"anInnerMap", root);
    }
};
int main()
{
    TiXmlDocument doc;
    //怎么设置相对于源代码的路径？这是个问题。。
    std::string s (__FILE__);
    std::string::size_type lastBackSlashPos = s.find_last_of("\\");
    s.replace(lastBackSlashPos+1, strlen("main.cpp"),"test/test.xml");
    doc.LoadFile(s.c_str());

    //std::vector<int> a;
    //AtomWrapper<int> anInt(a);
    //fieldWrapper<std::vector<int> > anInt(a);

    aStruct a;
    fieldWrapper<aStruct> anInt(a);


    TiXmlElement* root = doc.RootElement();
    anInt.parse("aStruct",*root);
//    cout << anInt.get();
    cout << a.a << endl;
    for(std::vector<int>::const_iterator it = a.aVec.begin(); it != a.aVec.end(); ++it)
    {
        cout << *it << endl;
    }
    for(std::map<int, int>::const_iterator it = a.aMap.begin(); it != a.aMap.end(); ++it)
    {
        cout << it->first << " " << it->second << endl;
    }
    cout << a.anInnerMap[133].a << endl;
    return 0;
}

