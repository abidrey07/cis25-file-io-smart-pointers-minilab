// Problem 4: Implement RAII
// This code has a DatabaseConnection class that requires manual connect/disconnect calls.
// Your task: Implement a RAII wrapper class that automatically manages the connection.
//
// Instructions:
//   1. Create a class called "ConnectionGuard" that:
//      - Takes a DatabaseConnection* in its constructor
//      - Calls connect() in the constructor
//      - Calls disconnect() in the destructor
//   2. Modify the functions below to use ConnectionGuard instead of manual connect/disconnect
//   3. Ensure connections are properly closed even with early returns
//
// When fixed, the program should:
//   - Show "Connected to database" at start of each operation
//   - Show "Disconnected from database" at end of each operation (even with early return!)
//   - Never leave a connection open

#include <iostream>
#include <string>

// Simulates a database connection (don't modify this class)
class DatabaseConnection {
private:
    bool connected;
    std::string dbName;
public:
    DatabaseConnection(const std::string& name) : connected(false), dbName(name) {}

    void connect() {
        if (!connected) {
            connected = true;
            std::cout << "  [DB] Connected to " << dbName << std::endl;
        }
    }

    void disconnect() {
        if (connected) {
            connected = false;
            std::cout << "  [DB] Disconnected from " << dbName << std::endl;
        }
    }

    bool isConnected() const { return connected; }

    void query(const std::string& sql) {
        if (connected) {
            std::cout << "  [DB] Executing: " << sql << std::endl;
        } else {
            std::cout << "  [DB] ERROR: Not connected!" << std::endl;
        }
    }
};

// TODO: Implement the ConnectionGuard class here
// class ConnectionGuard {
//     // Your implementation here
// };

// This function has a bug: if simulateError is true, disconnect() is never called
void queryDatabase(DatabaseConnection& db, bool simulateError) {
    // TODO: Replace manual connect/disconnect with ConnectionGuard
    db.connect();

    db.query("SELECT * FROM users");

    if (simulateError) {
        std::cout << "  Error occurred during query!" << std::endl;
        // BUG: Connection is left open!
        return;
    }

    db.query("SELECT * FROM orders");
    db.disconnect();
}

// This function also forgets to disconnect on early return
void updateDatabase(DatabaseConnection& db, bool hasData) {
    // TODO: Replace manual connect/disconnect with ConnectionGuard
    db.connect();

    if (!hasData) {
        std::cout << "  No data to update, returning early." << std::endl;
        // BUG: Connection is left open!
        return;
    }

    db.query("UPDATE users SET active = true");
    db.disconnect();
}

int main() {
    DatabaseConnection db("MainDatabase");

    std::cout << "=== Test 1: Query with error (connection should still close) ===" << std::endl;
    queryDatabase(db, true);
    std::cout << "Connection still open? " << (db.isConnected() ? "YES (bug!)" : "No (correct)") << std::endl;

    std::cout << "\n=== Test 2: Query without error ===" << std::endl;
    queryDatabase(db, false);
    std::cout << "Connection still open? " << (db.isConnected() ? "YES (bug!)" : "No (correct)") << std::endl;

    std::cout << "\n=== Test 3: Update with no data (early return) ===" << std::endl;
    updateDatabase(db, false);
    std::cout << "Connection still open? " << (db.isConnected() ? "YES (bug!)" : "No (correct)") << std::endl;

    std::cout << "\n=== Test 4: Update with data ===" << std::endl;
    updateDatabase(db, true);
    std::cout << "Connection still open? " << (db.isConnected() ? "YES (bug!)" : "No (correct)") << std::endl;

    std::cout << "\n=== All tests complete ===" << std::endl;
    return 0;
}
