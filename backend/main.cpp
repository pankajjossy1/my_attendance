#include "crow.h"
#include "upload_task.h"           // optional, if needed later
#include "routes/upload_route.h"   // ✅ Header only

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([]() {
        return "Face Attendance Backend is running!";
    });

    setup_upload_route(app);  // Register the upload route

    app.port(18080).multithreaded().run();
}
