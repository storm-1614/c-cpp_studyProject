#include <cctype>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <iostream>
#include <memory>
#include <mysql_connection.h>
#include <mysql_driver.h>
#include <string>
#include <vector>

const std::string DB_HOST = "tcp://localhost:3306";
const std::string DB_USER = "root";
const std::string DB_PASS = "password";
const std::string DB_NAME = "contacts_db";

std::unique_ptr<sql::Connection> get_connection()
{
    sql::mysql::MySQL_Driver *driver = sql::mysql::get_mysql_driver_instance();
    std::unique_ptr<sql::Connection> con(driver->connect(DB_HOST, DB_USER, DB_PASS));
    con->setSchema(DB_NAME);
    con->setClientOption("charset", "utf8mb4");
    return con;
}

std::string trim(const std::string &s)
{
    size_t start = s.find_first_not_of(" \t\n\r");
    if (start == std::string::npos)
        return "";
    size_t end = s.find_first_not_of(" \t\n\r");
    return s.substr(start, end - start + 1);
}

void init_db()
{
    sql::mysql::MySQL_Driver *driver = sql::mysql::get_mysql_driver_instance();
    std::unique_ptr<sql::Connection> con(driver->connect(DB_HOST, DB_USER, DB_PASS));
    con->setClientOption("charset", "utf8mb4");
    try
    {
        std::unique_ptr<sql::Statement> stmt(con->createStatement());
        stmt->execute("CREATE DATABASE IF NOT EXISTS " + DB_NAME + " CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci");
    }
    catch (sql::SQLException &e)
    {
        std::cerr << "创建数据库失败: " << e.what() << std::endl;
    }
    auto conn = get_connection();

    try
    {
        std::unique_ptr<sql::Statement> stmt(conn->createStatement());
        stmt->execute(R"(CREATE TABLE IF NOT EXISTS contacts (
                            id INT AUTO_INCREMENT PRIMARY KEY,
                            name VARCHAR(50) NOT NULL,
                            phone VARCHAR(20) NOT NULL UNIQUE,
                            email VARCHAR(50),
                            address VARCHAR(100),
                            group_name VARCHAR(20)
                        )
                      )");
        std::cout << "数据表 contacts 已经准备就绪。" << std::endl;
    }
    catch (sql::SQLException &e)
    {
        std::cerr << "创建表失败：" << e.what() << std::endl;
    }
}

void add_contact()
{
    std::string name, phone, email, address, group_name;

    std::cout << "姓名: ";
    std::getline(std::cin, name);
    name = trim(name);

    std::cout << "电话: ";
    std::getline(std::cin, phone);
    phone = trim(phone);

    if (name.empty() || phone.empty())
    {
        std::cout << "姓名和电话不能为空。" << std::endl;
        return;
    }

    std::cout << "邮箱: ";
    std::getline(std::cin, email);
    email = trim(email);

    std::cout << "地址: ";
    std::getline(std::cin, address);
    address = trim(address);

    std::cout << "分组: ";
    std::getline(std::cin, group_name);
    group_name = trim(group_name);

    auto conn = get_connection();
    try
    {
        std::unique_ptr<sql::PreparedStatement> pstmt(
            conn->prepareStatement("INSERT INTO contacts(name, phone, email, address, group_name) "
                                   "VALUES(?, ?, ?, ?, ?)"));
        pstmt->setString(1, name);
        pstmt->setString(1, phone);
        pstmt->setString(3, email.empty() ? "" : email);
        pstmt->setString(4, address.empty() ? "" : address);
        pstmt->setString(5, address.empty() ? "" : address);
        pstmt->setString(5, group_name.empty() ? "" : group_name);

        pstmt->executeUpdate();
        conn->commit();

        std::cout << "添加成功。" << std::endl;
    }
    catch (sql::SQLException &e)
    {
        if (e.getErrorCode() == 1062)
        {
            std::cerr << "添加失败，电话重复或数据不合法： " << e.what() << std::endl;
        }
        else
        {
            std::cerr << "错误: " << e.what() << std::endl;
        }
    }
}

void show_contact()
{
    auto conn = get_connection();
    try
    {
        std::unique_ptr<sql::Statement> stmt(conn->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT * FROM contacts ORDER BY id"));

        if (!res->rowsCount())
        {
            std::cout << "通讯录为空" << std::endl;
            return;
        }

        std::cout << "所有联系人: " << std::endl;
        while (res->next())
        {
            std::cout << "ID: " << res->getInt("id") <<    //
                "，姓名: " << res->getString("name") <<    //
                "，电话：" << res->getString("phone") <<   //
                "，邮箱：" << res->getString("email") <<   //
                "，地址：" << res->getString("address") << //
                "，分组：" << res->getString("group_name") << std::endl;
        }
    }
    catch (sql::SQLException &e)
    {
        std::cerr << "查询失败：" << e.what() << std::endl;
    }
}

void search_contact()
{
    std::cout << "输入姓名或者电话的关键字：";
    std::string keyword;
    std::getline(std::cin, keyword);
    keyword = trim(keyword);

    if (keyword.empty())
    {
        std::cout << "关键字不能为空" << std::endl;
        return;
    }

    auto conn = get_connection();

    try
    {
        std::unique_ptr<sql::PreparedStatement> pstmt(
            conn->prepareStatement("SELECT * FROM contacts WHERE name LIKE ? OR phone LIKE ?"));
        std::string like = "%" + keyword + "%";
        pstmt->setString(1, like);
        pstmt->setString(2, like);

        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        if (!res->rowsCount())
        {
            std::cout << "没有找到匹配的联系人。" << std::endl;
        }
        std::cout << "搜索结果：" << std::endl;

        while (res->next())
        {
            std::cout << "ID: " << res->getInt("id") <<    //
                "，姓名: " << res->getString("name") <<    //
                "，电话：" << res->getString("phone") <<   //
                "，邮箱：" << res->getString("email") <<   //
                "，地址：" << res->getString("address") << //
                "，分组：" << res->getString("group_name") << std::endl;
        }
    }
    catch (sql::SQLException &e)
    {
        std::cerr << "搜索失败：" << e.what() << std::endl;
    }
}

void modify_contact()
{
    std::string id_str;
    std::cout << "输入要修改联系人的 ID: ";
    std::getline(std::cin, id_str);
    id_str = trim(id_str);

    if (id_str.empty() || !std::isdigit(id_str[0]))
    {
        std::cout << "ID 必须为数字\n";
        return;
    }

    int contact_id = std::stoi(id_str);

    auto conn = get_connection();

    try
    {
        std::unique_ptr<sql::PreparedStatement> select_stmt(
            conn->prepareStatement("SELECT * FROM contacts WHERE id = ?"));
        select_stmt->setInt(1, contact_id);
        std::unique_ptr<sql::ResultSet> res(select_stmt->executeQuery());

        if (!res->next())
        {
            std::cout << "未找到 ID 为 " << contact_id << " 的联系人。" << std::endl;
            return;
        }

        std::cout << "请直接回车保留原值，输入新值则修改。" << std::endl;
        std::string old_name = res->getString("name");
        std::string old_phone = res->getString("phone");
        std::string old_email = res->getString("email");
        std::string old_addr = res->getString("address");
        std::string old_group = res->getString("group_name");

        std::string new_name, new_phone, new_email, new_addr, new_group;
        std::cout << "姓名 (" << old_name << "): ";
        std::getline(std::cin, new_name);
        new_name = trim(new_name);

        std::cout << "电话 (" << old_phone << "): ";
        std::getline(std::cin, new_phone);
        new_phone = trim(new_phone);

        std::cout << "邮箱 (" << old_email << "): ";
        std::getline(std::cin, new_email);
        new_email = trim(new_email);

        std::cout << "地址 (" << old_addr << "): ";
        std::getline(std::cin, new_addr);
        new_addr = trim(new_addr);

        std::cout << "分组 (" << old_group << "): ";
        std::getline(std::cin, new_group);
        new_group = trim(new_group);

        std::vector<std::string> set_parts;
        std::vector<std::string> values;
    }
    catch (sql::SQLException &e)
    {
    }
}

int main(int argc, char *argv[])
{
    init_db();
}
