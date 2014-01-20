#ifndef FIELDWRAPPER2_H
#define FIELDWRAPPER2_H
#include <tinyxml.h>
#include <vector>
#include <map>

//对于struct，对应于一个新的xml节点。
//<root>
//    <aStruct prop1="34"></aStruct>
//</root>
template<typename fieldType>
class fieldWrapper
{
public:
    fieldWrapper(fieldType& value):m_value(value) {}
    void parse(const char* name, const TiXmlElement& root)
    {//默认我们调用m_value自己的parse，从而，m_value需要自己生成一个parse函数。
        const TiXmlElement* pRoot = root.FirstChildElement(name);
        if(pRoot)
        {//这里的name是该struct的名字，在parse的时候实际上是用不到的。
            m_value.parse(/*name*/"", *pRoot);
        }
    }
protected:
    fieldType& m_value;
};
//<root name="333"></root>
template <>
class fieldWrapper<int>
{
public:
    fieldWrapper<int>(int& value):m_value(value) {}
    void parse(const char* name, const TiXmlElement& root)
    {
        root.Attribute(name, &m_value);
    }
protected:
    int& m_value;
};
//<aVec key="v">
//    <item v="32"/>
//    <item v="14"/>
//    <item v="512"/>
//</aVec>
template <typename elementType>
class fieldWrapper<std::vector<elementType> >
{
public:
    typedef std::vector<elementType> fieldVec;
    fieldWrapper<fieldVec>(fieldVec& value):m_value(value) {}
    void parse(const char* name, const TiXmlElement& root)
    {
        const TiXmlElement* pRoot = root.FirstChildElement(name);
        if(!pRoot)
        {//如果没有相应的节点
            return;
        }
        elementType newElement;
        const char* keyName = pRoot->Attribute("key");
        if(!keyName)
        {//如果没有设置"key"属性，那么就不能找到节点
            return;
        }
        for(const TiXmlElement* ele = pRoot->FirstChildElement(); ele; ele = ele->NextSiblingElement())
        {
            fieldWrapper<elementType> newElementWrapper(newElement);
            newElementWrapper.parse(keyName, *ele);
            m_value.push_back(newElement);
        }
    }
protected:
    fieldVec& m_value;
};
//<aMap key="k" value="v">
//    <item k="12" v="32"/>
//    <item k="22" v="14"/>
//    <item k="123" v="52"/>
//</aMap>
template <typename keyType, typename valueType>
class fieldWrapper<std::map<keyType, valueType> >
{
public:
    typedef std::map<keyType, valueType> fieldMap;
    fieldWrapper<fieldMap>(fieldMap& value):m_value(value) {}
    void parse(const char* name, const TiXmlElement& root)
    {
        const TiXmlElement* pRoot = root.FirstChildElement(name);
        if(!pRoot)
        {//如果没有相应的节点
            return;
        }
        keyType newKey;
        valueType newValue;
        const char* keyName = pRoot->Attribute("key");
        const char* valueName = pRoot->Attribute("value");
        if(!keyName || !valueName)
        {//如果没有设置"key","value"属性，那么就不能找到节点
            return;
        }
        for(const TiXmlElement* ele = pRoot->FirstChildElement(); ele; ele = ele->NextSiblingElement())
        {
            fieldWrapper<keyType> newKeyWrapper(newKey);
            newKeyWrapper.parse(keyName, *ele);
            fieldWrapper<valueType> newValueWrapper(newValue);
            newValueWrapper.parse(valueName, *ele);
            m_value[newKey] = newValue;
        }
    }
protected:
    fieldMap& m_value;
};






template <typename fieldType>
void parse(fieldType& field, const char* name, const TiXmlElement& root)
{
    fieldWrapper<fieldType> wrapper(field);
    wrapper.parse(name,root);
}
#endif // FIELDWRAPPER2_H
