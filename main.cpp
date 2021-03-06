#include <iostream>
#include <tinyxml.h>
//#include ".\fieldWrapper.h"
#include ".\fieldWrapper2.h"
#include ".\AutoInit.h"
#include <map>
using namespace std;
struct aStruct
{
    //AutoInit<int> a;
    int a[3];
    double b;
    float c;
    std::vector<int> aVec;
    std::map<int, int> aMap;

    struct anInner{
        int a;
        std::string aString;
//        void parse(const char* name, const TiXmlElement& root){
//            ::parse(a,"a",root);
//            ::parse(aString,"aString", root);
//        }
        void parse(const char* name, const TiXmlElement& root);
};
    std::map<int, anInner> anInnerMap;
//    void parse(const char* name, const TiXmlElement& root)
//    {
//        cout << a << endl;
//        ::parse(a, "a", root);
//        ::parse(b, "b", root);
//        ::parse(c, "c", root);
//        ::parse(aVec, "aVec", root);
//        ::parse(aMap, "aMap", root);
//        ::parse(anInnerMap,"anInnerMap", root);
//    }
    void parse(const char* name, const TiXmlElement& root);
};

void aStruct::anInner::parse(const char* name, const TiXmlElement& root){
	::parse(a, "a",root);
	::parse(aString, "aString",root);
}
void aStruct::parse(const char* name, const TiXmlElement& root){
	::parse(a, "a",root);
	::parse(b, "b",root);
	::parse(c, "c",root);
	::parse(aVec, "aVec",root);
	::parse(aMap, "aMap",root);
	::parse(anInnerMap, "anInnerMap",root);
}

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
    const TiXmlElement* root = doc.RootElement();
    ::parse(a, "aStruct", *root);

    cout /*<< a.a*/ << " " << a.b << " " << a.c << " " << endl;
	for(int i = 0; i < 3;i++)
	{
		cout << a.a[i] << " ";
	}
	cout<<endl;

    for(std::vector<int>::const_iterator it = a.aVec.begin(); it != a.aVec.end(); ++it)
    {
        cout << *it << endl;
    }
    for(std::map<int, int>::const_iterator it = a.aMap.begin(); it != a.aMap.end(); ++it)
    {
        cout << it->first << " " << it->second << endl;
    }
    cout << a.anInnerMap[133].a << " " << a.anInnerMap[133].aString << endl;
    return 0;
}

