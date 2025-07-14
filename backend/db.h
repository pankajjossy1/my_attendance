#pragma once

#include <pqxx/pqxx>
#include <memory>
#include <string>
#include <iostream>

// Wrapper for PostgreSQL connection using libpqxx
class DB {
public:
    DB(const std::string& connection_str) {
        try {
            conn = std::make_unique<pqxx::connection>(connection_str);
            if (!conn->is_open()) {
                throw std::runtime_error("Failed to connect to database.");
            }
        } catch (const std::exception& e) {
            std::cerr << "Database connection error: " << e.what() << std::endl;
            throw;
        }
    }

    pqxx::connection* get_connection() {
        return conn.get();
    }

private:
    std::unique_ptr<pqxx::connection> conn;
};
