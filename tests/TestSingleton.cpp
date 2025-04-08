#define CATCH_CONFIG_MAIN
#include "catch2.hpp"
#include "Singleton.h"
#include "DatabaseConnection.h"

TEST_CASE("Singleton basic functionality", "[singleton]") {
    SECTION("Default instance") {
        auto& db1 = SingletonHolder<DatabaseConnection>::Instance();
        auto& db2 = SingletonHolder<DatabaseConnection>::Instance();
        
        REQUIRE(&db1 == &db2);
    }
    
    SECTION("Thread-safe instance") {
        using ThreadSafeDB = SingletonHolder<DatabaseConnection, CreateUsingNew, ClassLevelLocking>;
        
        auto& db1 = ThreadSafeDB::Instance();
        auto& db2 = ThreadSafeDB::Instance();
        
        REQUIRE(&db1 == &db2);
    }
    
    SECTION("Database connection") {
        auto& db = SingletonHolder<DatabaseConnection>::Instance();
        
        REQUIRE_FALSE(db.isConnected());
        db.connect("test_connection");
        REQUIRE(db.isConnected());
        REQUIRE(db.connectionString() == "test_connection");
        
        db.disconnect();
        REQUIRE_FALSE(db.isConnected());
    }
}

TEST_CASE("Different creation policies", "[singleton]") {
    SECTION("CreateUsingNew policy") {
        using NewPolicySingleton = SingletonHolder<DatabaseConnection, CreateUsingNew>;
        
        auto& instance = NewPolicySingleton::Instance();
        REQUIRE_NOTHROW(NewPolicySingleton::Instance());
    }
    
    SECTION("CreateStatic policy") {
        using StaticPolicySingleton = SingletonHolder<DatabaseConnection, CreateStatic>;
        
        auto& instance = StaticPolicySingleton::Instance();
        REQUIRE_NOTHROW(StaticPolicySingleton::Instance());
    }
}