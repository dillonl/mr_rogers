#pragma once

#include "core/utils/Noncopyable.hpp"

#include <memory>

namespace mr_rogers
{
	template< class T >
	class IDataItem : private Noncopyable
	{
	public:
		typedef std::shared_ptr< IDataItem > SharedPtr;
		IDataItem(T value, const std::string& data);
		~IDataItem();

		T getValue() { return m_value; }
		std::string getData() { return m_data; }
	private:
		T m_value;
		std::string m_data;
	};

	template< class T >
	class IDataItemComparator : private Noncopyable
	{
	public:
		typedef std::shared_ptr< IDataItemComparator > SharedPtr;
		bool operator()(const IDataItem< T >& rhs, const IDataItem< T >& lhs) const
		{
			return rhs.getValue() < lhs.getValue();
		}
	};
}
