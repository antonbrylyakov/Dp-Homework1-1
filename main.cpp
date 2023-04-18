#include <iostream>
#ifdef _WIN32
#include "windows.h"
#include <cassert>
#endif

#include "SqlSelectQueryBuilder.h"

int main()
{
	setlocale(LC_ALL, "Russian");
#ifdef _WIN32
	SetConsoleCP(1251);
#endif

    // Задание 1

    {
        // Набор колонок (пример из задания)
        SqlSelectQueryBuilder query_builder;
        query_builder.AddColumn("name").AddColumn("phone");
        query_builder.AddFrom("students");
        query_builder.AddWhere("id", "42").AddWhere("name", "'John'");

        assert(query_builder.BuildQuery() ==
            "SELECT name, phone FROM students WHERE id=42 AND name='John';");
    }

    {
        // Все колонки
        SqlSelectQueryBuilder query_builder;
        query_builder.AddFrom("students");
        query_builder.AddWhere("id", "42").AddWhere("name", "'John'");

        assert(query_builder.BuildQuery() ==
            "SELECT * FROM students WHERE id=42 AND name='John';");
    }

    // Задание 2
    {
        // Набор колонок (пример из задания)
        SqlSelectQueryBuilder query_builder;
        query_builder.AddColumns(std::vector<std::string>{ "name", "phone" });
        query_builder.AddFrom("students");
        query_builder.AddWhere(std::map<std::string, std::string> {{ "id", "42" }, { "name", "'John'"}});

        assert(query_builder.BuildQuery() ==
            "SELECT name, phone FROM students WHERE id=42 AND name='John';");
    }

    // Задание 3
    {
        SqlSelectQueryBuilder query_builder;
        query_builder.AddColumns(std::vector<std::string>{ "name", "phone" });
        query_builder.AddFrom("students");
        query_builder.AddWhere("name", "'John'");
        query_builder.AddWhereGreaterThan("id", "42");

        assert(query_builder.BuildQuery() ==
            "SELECT name, phone FROM students WHERE name='John' AND id>42;");
    }
}