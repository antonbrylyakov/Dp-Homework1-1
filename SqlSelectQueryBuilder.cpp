#include "SqlSelectQueryBuilder.h"
#include <utility>
#include <sstream>
#include <iostream>
#include <stdexcept>

SqlSelectQueryBuilder::SqlSelectQueryBuilder()
{
}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddColumn(const std::string& columnName) noexcept
{
	m_columns.push_back(columnName);
	return *this;
}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddFrom(const std::string& tableName) noexcept
{
	m_tableName = tableName;
	return *this;
}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddWhere(const std::string& fieldName, const std::string& fieldValue) noexcept
{
	return AddBinaryWhere<SqlEqualityCondition>(fieldName, fieldValue);
}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddColumns(const std::vector<std::string>& columns) noexcept
{
	for (auto& col : columns)
	{
		AddColumn(col);
	}

	return *this;
}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddWhere(const std::map<std::string, std::string>& kv) noexcept
{
	for (auto& cnd : kv)
	{
		AddWhere(cnd.first, cnd.second);
	}

	return *this;
}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddWhereGreaterThan(const std::string& fieldName, const std::string& fieldValue) noexcept
{
	return AddBinaryWhere<SqlGreaterThanCondition>(fieldName, fieldValue);
}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddWhereLessThan(const std::string& fieldName, const std::string& fieldValue) noexcept
{
	return AddBinaryWhere<SqlLessThanThanCondition>(fieldName, fieldValue);
}

std::string SqlSelectQueryBuilder::BuildQuery() const noexcept
{
	if (m_tableName.empty())
	{
		throw std::runtime_error("Имя таблицы не инициализировано");
	}

	std::stringstream s;
	s << "SELECT ";
	if (m_columns.empty())
	{
		s << "*";
	}
	else
	{
		bool first = true;
		for (auto& col : m_columns)
		{
			if (!first) { s << ", "; }
			s << col;
			first = false;
		}
	}

	s << " FROM " << m_tableName;
	
	if (!m_conditions.empty())
	{
		s << " WHERE";
	}

	bool first = true;
	for (auto& cnd: m_conditions)
	{
		s << " ";
		if (!first) { s << "AND "; }
		s << cnd->getSqlString();
		first = false;
	}

	s << ";";
	return s.str();
}
