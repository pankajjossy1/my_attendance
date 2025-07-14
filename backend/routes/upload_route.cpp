#include "crow.h"
#include "upload_route.h"
#include "logger.h"
#include <nlohmann/json.hpp>  // JSON parsing

using json = nlohmann::json;

void setup_upload_route(crow::SimpleApp& app) {
    CROW_ROUTE(app, "/upload").methods("POST"_method)([](const crow::request& req) {
        json body_json;

        // Parse the incoming JSON body
        try {
            body_json = json::parse(req.body);
        } catch (const std::exception& e) {
            return crow::response(400, "Invalid JSON format");
        }

        // Extract required fields
        std::string teacher_id     = body_json.value("teacher_id", "");
        std::string teacher_name   = body_json.value("teacher_name", "");
        std::string subject_code   = body_json.value("subject_code", "");
        int semester               = body_json.value("semester", 0);
        std::string session_id     = body_json.value("session_id", "");
        std::string timestamp      = body_json.value("timestamp", "");
        auto images                = body_json.value("images", std::vector<std::string>{});

        // Log the upload
        std::string log_message = 
            "Upload received from " + teacher_name + " (ID: " + teacher_id + 
            ") | Subject: " + subject_code + 
            " | Semester: " + std::to_string(semester) + 
            " | Session ID: " + session_id + 
            " | Timestamp: " + timestamp + 
            " | Photo count: " + std::to_string(images.size());

        write_log(log_message);

        return crow::response(200, "Upload received and logged.");
    });
}
