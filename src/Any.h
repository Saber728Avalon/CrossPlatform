#pragma once
 /**
 * @file		Any.h
 * @brief		���Է����κ����͡�ʹ��ʱ��ʹ��Any_Castת����ԭʼ���ͣ��Ϳ���ʹ���ˡ��൱��C���Ե�voidָ�룬�������κ����͵�ת��.
 *				�������������һ��vector,list,mapʱ����ͷ��������ǲ�ͬ������������͡������Ϳ��Կ˷�STLһЩ����ȱ�ݣ������书��
 *				����ע�⣬����ʹ�ö�Ҫ��Any_Cast�����͵�ת�����ر���ʹ�ö�̨����ʱ��һ��Ҫע�⣬�������Զ�����̬��ת��
 *				��:
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

			//�����˽�б���������Ϊ��Ա����
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

		//ģ�幹�캯������ʳ�������������͡����������ݱ�����content��
		template<typename ValueType>
		Any(const ValueType & value) : m_pContent(new Holder<ValueType>(value))
		{

		}

		//�������캯��
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

		//��ȡ��ʵ����������
		const std::string type() const
		{
			std::string strType = m_pContent ? m_pContent->type() : typeid(void).name();
			return strType;
		}

		//�����˽�б���������Ϊ��Ա����
		template<typename ValueType>
		friend ValueType Any_Cast(const Any & oper);
	private:
		PlaceHolder *m_pContent;
	};

	//�����������ת��
	template<typename ValueType>
	ValueType Any_Cast(const Any & oper)
	{
		return static_cast<Any::Holder<ValueType> *>(oper.m_pContent)->m_hold;
	}

}