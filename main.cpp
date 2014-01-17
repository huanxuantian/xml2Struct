#include <iostream>
#include <tinyxml.h>
//#include ".\fieldWrapper.h"
#include ".\fieldWrapper2.h"
using namespace std;
struct aStruct
{
    int a;
    std::vector<int> aVec;
    void parse(const char* name, const TiXmlElement& root)
    {
//        fieldWrapper fa(a);
//        fa.parse("a",root);
//        fieldWrapper faVec(aVec);
//        faVec.parse("aVec", root);
        ::parse(a, "a", root);
        ::parse(aVec, "aVec", root);
    }
};
int main()
{
    TiXmlDocument doc;
    doc.LoadFile("test.xml");

    //std::vector<int> a;
    //AtomWrapper<int> anInt(a);
    //fieldWrapper<std::vector<int> > anInt(a);

    aStruct a;
    fieldWrapper<aStruct> anInt(a);


    TiXmlElement* root = doc.RootElement();
    anInt.parse("a",*root);
//    cout << anInt.get();
    //cout << a;
    for(std::vector<int>::const_iterator it = a.aVec.begin(); it != a.aVec.end(); ++it)
    {
        cout << *it << endl;
    }
    return 0;
}

