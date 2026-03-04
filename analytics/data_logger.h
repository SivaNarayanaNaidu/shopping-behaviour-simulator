#ifndef DATA_LOGGER_H
#define DATA_LOGGER_H

#include <string>
#include <fstream>
#include <mutex>
#include <vector>

enum class EventType {
    ProductView,
    CartAddition,
    Purchase,
    CartAbandonment
};

struct Event {
    int day;
    int agent_id;
    std::string agent_type;
    EventType type;
    std::string product_id; // Empty if general cart event
    double value;           // e.g. price or total cart value
    std::string timestamp;  // Simulated or real
};

class DataLogger {
public:
    static DataLogger& get_instance();

    // Initialize the log file and write headers
    bool initialize(const std::string& filepath);

    // Stop logging and flush to disk
    void close();

    // Log an event
    void log_event(const Event& event);

    // Thread-safe batch log
    void log_events(const std::vector<Event>& events);

private:
    DataLogger();
    ~DataLogger();
    
    // Prevent copy/move
    DataLogger(const DataLogger&) = delete;
    DataLogger& operator=(const DataLogger&) = delete;

    std::string event_type_to_string(EventType type);

    std::ofstream file_;
    std::mutex mutex_;
    bool initialized_ = false;
};

#endif // DATA_LOGGER_H
