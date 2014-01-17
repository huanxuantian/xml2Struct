#ifndef FIELDWRAPPER_H
#define FIELDWRAPPER_H
#include <tinyxml.h>
#include <vector>
template<typename fieldType>
class fieldWrapper
{
public:
    fieldWrapper(fieldType& value):m_value(value) {}
    //模板函数，注意，因为返回值的原因，这个函数不能被重载！
    //fieldType& parse(const char* name, const TiXmlElement& root);
protected:
    fieldType& m_value;
};
template <typename fieldType>
class AtomWrapper : public fieldWrapper<fieldType>
{
public:
    AtomWrapper(fieldType& value) : fieldWrapper<fieldType>(value) {}
    fieldType& parse(const char* name, const TiXmlElement& root)
    {
        const char* attr = root.Attribute(name);
        if(attr)
        {
            //请注意！
            //对于不知道是什么类型的原子类型，我们统一使用该类型的fromString方法。
            //如果该类型没有提供fromString，这里就编译不过了。
            fieldWrapper<fieldType>::m_value.fromString(attr);
        }
        return fieldWrapper<fieldType>::m_value;
    }
//    fieldType& get()
//    {
//        //下面2种办法都可以编译通过，但是return m_value是不行的
//        //return this->m_value;
//        return fieldWrapper<fieldType>::m_value;
//    }
};
template <>
class AtomWrapper<int> : public fieldWrapper<int>
{
public:
    AtomWrapper<int>(int& value):fieldWrapper<int>(value) {}
    int& parse(const char* name, const TiXmlElement& root)
    {
        //注释的这个，又编译不过了-_-我很怀疑，这种代码能在vs 2005编译过？
        //root.Attribute(name, &fieldWrapper<int>::m_value);
        //明白了，像这样添加括号，就可以编译过了
        root.Attribute(name, &(fieldWrapper<int>::m_value));
        //root.Attribute(name, &this->m_value);这个也是可以编译过的
        return fieldWrapper<int>::m_value;
    }
};

template <typename elementType>
class vectorWrapper : public fieldWrapper<std::vector<elementType> >
{
public:
    typedef std::vector<elementType> fieldList;
    vectorWrapper(fieldList& value) : fieldWrapper<fieldList>(value) {}
    fieldList& parse(const char* name, const TiXmlElement& root)
    {
        const TiXmlElement* ele = root.FirstChildElement();
    }
};
#endif // FIELDWRAPPER_H
