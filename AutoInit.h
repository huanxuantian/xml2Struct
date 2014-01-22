#ifndef AUTOINIT_H
#define AUTOINIT_H
//对有默认构造函数的类型，我们在创建它们的时候，就调用下。注意，C++给所有的基本类型都创建了默认构造函数
template<typename T>
struct AutoInit
{
    AutoInit():m_value(){}
    operator T&() {return m_value;}
protected:
    T m_value;
};
#endif // AUTOINIT_H
