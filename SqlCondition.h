#pragma once
#include <string>

class SqlCondition
{
public:
	virtual std::string getSqlString() const = 0;
};

class BinarySqlCondition : public SqlCondition
{
public:
	// ”дал€ем конструктор по умолчанию, т.к. не планируем использовать неинициализированные услови€
	BinarySqlCondition() = delete;
	BinarySqlCondition(const std::string& expr1, const std::string& expr2) : m_expr1(expr1), m_expr2(expr2) {}
protected:
	std::string m_expr1;
	std::string m_expr2;
};

class SqlEqualityCondition: public BinarySqlCondition
{
public:
	SqlEqualityCondition() = delete;
	SqlEqualityCondition(const std::string& expr1, const std::string& expr2) : BinarySqlCondition(expr1, expr2) {}
	std::string getSqlString() const override;
};

class SqlGreaterThanCondition : public BinarySqlCondition
{
public:
	SqlGreaterThanCondition() = delete;
	SqlGreaterThanCondition(const std::string& expr1, const std::string& expr2) : BinarySqlCondition(expr1, expr2) {}
	std::string getSqlString() const override;
};

class SqlLessThanThanCondition : public BinarySqlCondition
{
public:
	SqlLessThanThanCondition() = delete;
	SqlLessThanThanCondition(const std::string& expr1, const std::string& expr2) : BinarySqlCondition(expr1, expr2) {}
	std::string getSqlString() const override;
};