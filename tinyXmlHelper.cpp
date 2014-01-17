//#include <tinyxml.h>
//#include <string>
//#include <vector>
//#include <map>
//class tinyXmlHelper
//{
//public:
//	tinyXmlHelper(const TiXmlElement& root);
//	~tinyXmlHelper();
	
//	void parse(const char* name, int& value)
//	{
//		root.Attribute(name, value);
//	}
//	void parse(const char* name, double& value)
//	{
//		root.Attribute(name, value);
//	}
//	void parse(const char* name, float& value)
//	{
//		root.QueryFloatAttribute(name, &value);
//	}
//	void parse(const char* name, std::string& value)
//	{
//		const char* attr = root.Attribute(name);
//		if (attr)
//		{
//			value = attr;
//		}
//		value = "";
//	}
//	/*
//	单个元素的parse,属性名从root的“key”属性读出。结构为：
//	<root key="aKey">
//	 	<item aKey="3"/>
//	 	<item aKey="4"/>
//	 	<item aKey="5"/>
//	</root>
//	*/
//	template<typename T>
//	void parse(const TiXmlElement& root, std::vector<T>& vec)
//	{
		
//		for(TiXmlElement* child = root.FirstChildElement("item"); child != NULL; child = child->NextSiblingElement())
//		{
//			tinyXmlHelper helper(child);
//			T v;
//			helper.parse(root.Attribute(key), v);
//			vec.push_back(v);
//		}
//	}
//	//多元素的parse，包括嵌套的单元素vector等，也算是多元素的
//	//征途2那边，是将所有的元素都封装了下，那么，这2个vector的parse自然就可以统一起来了。但是我没有这么做，现在就显得有些重复了
//	/*
//	单个元素的parse,属性名从root的“key”属性读出。结构为：
//	<root key="aKey">
//	 	<aKey prop1="3" prop2="aaa"/>
//	 	<aKey prop1="4" prop2="aaa"/>
//	 	<aKey prop1="5" prop2="aaa"/>
//	</root>
//	*/
//	template<typename T>
//	void parse(const TiXmlElement& root, std::vector<T>& vec)
//	{
		
//		for(TiXmlElement* child = root.FirstChildElement(root.Attribute("key")); child != NULL; child = child->NextSiblingElement())
//		{
//			tinyXmlHelper helper(child);
//			T v;
//			v.parse(child);
//			vec.push_back(v);
//		}
//	}
//	//单个元素key,单元素value的parse
//	/*
//	单个元素的parse,属性名从root的“key”属性读出。结构为：
//	<root keyName="aKey" valueName="aValue">
//	 	<item aKey="3" aValue="aaa"/>
//	 	<item aKey="4" aValue="aaa"/>
//	 	<item aKey="5" aValue="aaa"/>
//	</root>
//	*/
//	template<typename KeyType, typename ValueType>
//	void parse(const TiXmlElement& root, std::map<KeyType, ValueType>& map)
//	{
//		for(TiXmlElement* child = root.FirstChildElement("item"); child != NULL; child = child->NextSiblingElement())
//		{
//			tinyXmlHelper helper(child);
//			KeyType key;
//			helper.parse(keyName, key);
//			ValueType value;
//			helper.parse(valueName, value);
//			map[key] = value;
//		}
//	}
//	//单个元素key,多元素value的parse
//	/*
//	单个元素的parse,属性名从root的“key”属性读出。结构为：
//	<root keyName="aKey" valueName="aValue">
//	 	<item aKey="p1">
//	 		<aValue prop1="3" prop2="lish" prop3="name"/>
//	 	</item>
//	 	<item aKey="p2">
//	 		<aValue prop1="3" prop2="lish" prop3="name"/>
//	 	</item>
//	 	<item aKey="p3">
//	 		<aValue prop1="3" prop2="lish" prop3="name"/>
//	 	</item>
//	</root>
//	*/
//	template<typename KeyType, typename ValueType>
//	void parse(const TiXmlElement& root, std::map<KeyType, ValueType>& map)
//	{
//		for(TiXmlElement* child = root.FirstChildElement(root.Attribute("keyName")); child != NULL; child = child->NextSiblingElement())
//		{
//			tinyXmlHelper helper(child);
//			KeyType key;
//			helper.parse(keyName, key);
//			ValueType value;
//			value.parse(root);
//			map[key] = value;
//		}
//	}
//};
//template<typename T>
//class ValueWrapper
//{
//public:
//	ValueWrapper(T& value)m_value(value){}
//	~ValueWrapper();
//	T& parse(const TiXmlElement& root, const char* name)
//	{
//		m_value.parse(root.FirstChildElement(name));
//		return m_value;
//	}
//protected:
//	T& m_value;
//};
////特化一些版本供使用
//template<>
//class ValueWrapper
//{
//public:
//	ValueWrapper(int& value)m_value(value){}
//	~ValueWrapper();
//	int& parse(const TiXmlElement& root, const char* name)
//	{
//		root.Attribute(name, &m_value);
//		return m_value;
//	}
//protected:
//	T& m_value;
//};
//template<>
//class ValueWrapper
//{
//public:
//	ValueWrapper(double& value)m_value(value){}
//	~ValueWrapper();
//	double& parse(const TiXmlElement& root, const char* name)
//	{
//		root.Attribute(name, &m_value);
//		return m_value;
//	}
//protected:
//	T& m_value;
//};
//template<>
//class ValueWrapper
//{
//public:
//	ValueWrapper(float& value)m_value(value){}
//	~ValueWrapper();
//	float& parse(const TiXmlElement& root, const char* name)
//	{
//		root.QueryFloatAttribute(name, &m_value);
//		return m_value;
//	}
//protected:
//	T& m_value;
//};






//struct aStruct
//{
//	int a;
//	double b;
//	struct anInner
//	{
//		std::string s;
//		void parse(const TiXmlElement& root)
//		{
//			tinyXmlHelper helper(root);
//			helper.parse("s", s);
//		}
//	};
//	anInner ai;
//	std::vector<int> vLists;
//	void parse(const TiXmlElement& root)
//	{
//		tinyXmlHelper helper(root);
//		helper.parse("a", a);
//		helper.parse("b", b);
//		ai.parse(root.FirstChildElement("ai"));
//        helper.parse(root.FirstChildElement("vLists"), "value", vLists));
//	}
//};
