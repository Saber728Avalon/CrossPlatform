#pragma once
 /**
 * @file		Any.h
 * @brief		可以放入任何类型。使用时候使用Any_Cast转到到原始类型，就可以使用了。相当于C语言的void指针，可以做任何类型的转换.
 *				这样，当你放入一个vector,list,map时候，你就放入甚至是不同种类的数据类型。这样就可以克服STL一些固有缺陷，扩大其功能
 *				但是注意，所有使用都要用Any_Cast做类型的转换。特别是使用多台特性时候，一定要注意，他不会自动做多态的转换
 *				如:
 *				 std::vector<duan::Any> vectTmp;
 *				 vectTmp.push_back(10);
 *				 vectTmp.push_back(11.11);
 *				 vectTmp.push_back(std::string("abcdefg"));
 *				 vectTmp.push_back(TestXX());
 * @author		duanqiang
 * @date		2020/12/09
 * @version 	1.0.0.1
 * @copyright	Copyright (C) 2009 duanqiang <email@2891018428@qq.com>
 */


#include <iostream>

namespace duan
{
	class Any
	{
	public:


		class PlaceHolder
		{
		public:
			virtual ~PlaceHolder()
			{

			}

			virtual const std::string type() const = 0;
			virtual PlaceHolder* Clone() const = 0;
		};


		template<typename ValueType >
		class Holder : public PlaceHolder
		{
		public:
			Holder(const ValueType& value) : m_hold(value)
			{

			}

			virtual const std::string type() const
			{
				std::string strType = typeid(ValueType).name();
				return strType;
			}

			virtual PlaceHolder* Clone() const
			{
				return new Holder(m_hold);
			}

			//会访问私有变量，设置为友员函数
			template<typename ValueType>
			friend ValueType Any_Cast(const Any & oper);
		private:
			ValueType m_hold;
		};


	public:
		Any()
		{
			m_pContent = NULL;
		}

		//模板构造函数，蚕食可以是任意类型。真正的数据保存在content中
		template<typename ValueType>
		Any(const ValueType & value) : m_pContent(new Holder<ValueType>(value))
		{

		}

		//拷贝构造函数
		Any(const Any &otherObj) : m_pContent(otherObj.m_pContent ? otherObj.m_pContent->Clone() : NULL)
		{

		}

		Any & operator =(const Any &otherObj)
		{
			m_pContent = (otherObj.m_pContent ? otherObj.m_pContent->Clone() : NULL);
			return *this;
		}

		~Any()
		{
			if (NULL != m_pContent)
			{
				delete m_pContent;
				m_pContent = NULL;
			}
		}

		//获取真实的数据类型
		const std::string type() const
		{
			std::string strType = m_pContent ? m_pContent->type() : typeid(void).name();
			return strType;
		}

		//会访问私有变量，设置为友员函数
		template<typename ValueType>
		friend ValueType Any_Cast(const Any & oper);
	private:
		PlaceHolder *m_pContent;
	};

	//做任意的类型转换
	template<typename ValueType>
	ValueType Any_Cast(const Any & oper)
	{
		return static_cast<Any::Holder<ValueType> *>(oper.m_pContent)->m_hold;
	}

}