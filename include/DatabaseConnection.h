#pragma once

#include <string>

class DatabaseConnection {
public:
    void connect(const std::string& connectionString) {
        connectionString_ = connectionString;
        connected_ = true;
    }
    
    void disconnect() { connected_ = false; }
    bool isConnected() const { return connected_; }
    std::string connectionString() const { return connectionString_; }
    
private:
    DatabaseConnection() = default;
    ~DatabaseConnection() = default;
    
    // Дружественные классы политик создания
    template <typename> friend struct CreateUsingNew;
    template <typename> friend struct CreateStatic;
    
    bool connected_ = false;
    std::string connectionString_;
};