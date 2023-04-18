#include "SqlCondition.h"

std::string SqlEqualityCondition::getSqlString() const
{
	return m_expr1 + "=" + m_expr2;
}

std::string SqlGreaterThanCondition::getSqlString() const
{
	return m_expr1 + ">" + m_expr2;
}

std::string SqlLessThanThanCondition::getSqlString() const
{
	return m_expr1 + "<" + m_expr2;
}
