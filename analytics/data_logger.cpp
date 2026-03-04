#include "data_logger.h"
#include <iostream>

DataLogger::DataLogger() {}

DataLogger::~DataLogger() {
    close();
}

DataLogger& DataLogger::get_instance() {
    static DataLogger instance;
    return instance;
}

bool DataLogger::initialize(const std::string& filepath) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (initialized_) return true;
    
    file_.open(filepath);
    if (!file_.is_open()) {
        std::cerr << "Failed to open log file: " << filepath << std::endl;
        return false;
    }
    
    // Write CSV header
    file_ << "day,agent_id,agent_type,event_type,product_id,value,timestamp\n";
    initialized_ = true;
    return true;
}

void DataLogger::close() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (file_.is_open()) {
        file_.close();
    }
    initialized_ = false;
}

std::string DataLogger::event_type_to_string(EventType type) {
    switch (type) {
        case EventType::ProductView: return "ProductView";
        case EventType::CartAddition: return "CartAddition";
        case EventType::Purchase: return "Purchase";
        case EventType::CartAbandonment: return "CartAbandonment";
        default: return "Unknown";
    }
}

void DataLogger::log_event(const Event& event) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (!initialized_ || !file_.is_open()) return;
    
    file_ << event.day << ","
          << event.agent_id << ","
          << event.agent_type << ","
          << event_type_to_string(event.type) << ","
          << event.product_id << ","
          << event.value << ","
          << event.timestamp << "\n";
}

void DataLogger::log_events(const std::vector<Event>& events) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (!initialized_ || !file_.is_open()) return;
    
    for (const auto& event : events) {
        file_ << event.day << ","
              << event.agent_id << ","
              << event.agent_type << ","
              << event_type_to_string(event.type) << ","
              << event.product_id << ","
              << event.value << ","
              << event.timestamp << "\n";
    }
}
