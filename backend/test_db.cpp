#include <iostream>
#include <pqxx/pqxx>

int main() {
    try {
        // Replace these with your actual DB credentials
        std::string conn_str = "host=localhost port=5432 dbname=face_attendance_db user=postgres password=YOUR_PASSWORD";

        pqxx::connection conn(conn_str);
        if (conn.is_open()) {
            std::cout << "✅ Connected to database: " << conn.dbname() << std::endl;
        } else {
            std::cerr << "❌ Failed to connect to database." << std::endl;
            return 1;
        }

        pqxx::work txn(conn);
        pqxx::result res = txn.exec("SELECT COUNT(*) FROM teachers;");
        std::cout << "👨‍🏫 Teachers in database: " << res[0][0].as<int>() << std::endl;

        conn.disconnect();
    } catch (const std::exception &e) {
        std::cerr << "Database connection error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
