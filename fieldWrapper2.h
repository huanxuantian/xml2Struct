#ifndef FIELDWRAPPER2_H
#define FIELDWRAPPER2_H
#include <tinyxml.h>
#include <vector>
#include <map>
#include <string>
#include ".\AutoInit.h"
//前向声明，这样，就可以在fieldWrapper调用它了
//但是它本身也会调用fieldWrapper的，间接递归调用。
template <typename fieldType>
void parse(fieldType& field, const char* name, const TiXmlElement& root);

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
//------------------------------------
//原子数据的特化：原子数据，指的是可以放在一个attribute里面的数据。包括关键字数据和自定义原子数据
//------------------------------------

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

//<root name="333.5"></root>
template <>
class fieldWrapper<double>
{
public:
    typedef double elementType;
    fieldWrapper<elementType>(elementType& value):m_value(value) {}
    void parse(const char* name, const TiXmlElement& root)
    {
        root.Attribute(name, &m_value);
    }
protected:
    elementType& m_value;
};

//<root name="333.5"></root>
template <>
class fieldWrapper<float>
{
public:
    typedef float elementType;
    fieldWrapper<elementType>(elementType& value):m_value(value) {}
    void parse(const char* name, const TiXmlElement& root)
    {
        root.QueryFloatAttribute(name, &m_value);
    }
protected:
    elementType& m_value;
};

//<root name="Xinggang Li"></root>
template <>
class fieldWrapper<std::string>
{
public:
    typedef std::string elementType;
    fieldWrapper<elementType>(elementType& value):m_value(value) {}
    void parse(const char* name, const TiXmlElement& root)
    {
        const char* value = root.Attribute(name);
        if(value)
        {
            m_value = value;
        }
    }
protected:
    elementType& m_value;
};

//------------------------------------
//原子数据的特化结束
//------------------------------------

//------------------------------------
//集合数据的特化。目前支持vector和map
//------------------------------------
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
            ::parse(newElement, keyName, *ele);
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
            ::parse(newKey, keyName, *ele);
            ::parse(newValue, valueName, *ele);
            m_value[newKey] = newValue;
        }
    }
protected:
    fieldMap& m_value;
};
//定长数组的特化.我们的游戏中大量使用.虽然以前在巨人的时候没有用过
  //<a key="v" num="3">
  //  <item v="2" />
  //  <item v="3" />
  //  <item v="4" />
  //</a>
template <typename elementType, int elementNum>
class fieldWrapper<elementType[elementNum] >
{
public:
   // typedef elementType[elementNum] fieldVec;
    fieldWrapper<elementType[elementNum]>(elementType* value)
		:m_value(value) {}
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
		int idx = 0;
        for(const TiXmlElement* ele = pRoot->FirstChildElement(); ele && idx < elementNum; ele = ele->NextSiblingElement())
        {
            ::parse(newElement, keyName, *ele);
            m_value[idx] = newElement;
			idx++;
        }
    }
protected:
    elementType* m_value;
};
//------------------------------------
//集合数据的特化结束
//------------------------------------




//------------------------------------
//使用此函数来使得fieldWrapper可以自动匹配。
//------------------------------------
template <typename fieldType>
void parse(fieldType& field, const char* name, const TiXmlElement& root)
{
    fieldWrapper<fieldType> wrapper(field);
    wrapper.parse(name,root);
}

template <typename fieldType>
void parse(AutoInit<fieldType>& field, const char* name, const TiXmlElement& root)
{
    fieldWrapper<fieldType> wrapper(field.operator fieldType&());
    wrapper.parse(name,root);
}

#endif // FIELDWRAPPER2_H
