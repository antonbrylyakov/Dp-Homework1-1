#pragma once
#include <string>
#include <vector>
#include <memory>
#include <map>
#include "SqlCondition.h"

class SqlSelectQueryBuilder 
{
public:
	SqlSelectQueryBuilder();
	SqlSelectQueryBuilder& AddColumn(const std::string& columnName) noexcept;
	SqlSelectQueryBuilder& AddFrom(const std::string& tableName) noexcept;
	SqlSelectQueryBuilder& AddWhere(const std::string& fieldName, const std::string& fieldValue) noexcept;
	SqlSelectQueryBuilder& AddColumns(const std::vector<std::string>& columns) noexcept;
	SqlSelectQueryBuilder& AddWhere(const std::map<std::string, std::string>& kv) noexcept;
	SqlSelectQueryBuilder& AddWhereGreaterThan(const std::string& fieldName, const std::string& fieldValue) noexcept;
	SqlSelectQueryBuilder& AddWhereLessThan(const std::string& fieldName, const std::string& fieldValue) noexcept;
	std::string BuildQuery() const noexcept;
protected:
	std::string m_tableName;
	std::vector<std::string> m_columns;
	// Храним условия как указатели, чтобы полиморфно хранить условия разных типов
	std::vector<std::unique_ptr<SqlCondition>> m_conditions;
	// Метод добавления условий разных типов
	template <typename T>
	SqlSelectQueryBuilder& AddBinaryWhere(const std::string& fieldName, const std::string& fieldValue) noexcept
	{
		auto condPtr = std::make_unique<T>(fieldName, fieldValue);
		m_conditions.push_back(std::move(condPtr));
		return *this;
	}
};