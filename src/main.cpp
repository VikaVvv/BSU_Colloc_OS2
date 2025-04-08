#include <iostream>
#include "/Users/vvv/Documents/OS/colloc2ST/include/Singleton.h"
#include "/Users/vvv/Documents/OS/colloc2ST/include/DatabaseConnection.h"


int main() {
    // Вариант с политикой создания через new и классовой блокировкой
    using SafeDBSingleton = SingletonHolder<DatabaseConnection, CreateUsingNew, ClassLevelLocking>;
    
    SafeDBSingleton::Instance().connect("Server=localhost;Database=Production;");
    
    std::cout << "Database connection: " 
              << (SafeDBSingleton::Instance().isConnected() ? "OK" : "FAIL")
              << "\nConnection string: "
              << SafeDBSingleton::Instance().connectionString()
              << std::endl;
    
    SafeDBSingleton::Instance().disconnect();
    
    return 0;
}
