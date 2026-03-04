#include "simulator.h"
#include <iostream>
#include <random>

Simulator::Simulator(int num_agents, int num_days, const std::string& products_csv, const std::string& output_csv)
    : num_agents_(num_agents), num_days_(num_days), products_csv_(products_csv), output_csv_(output_csv) {
}

bool Simulator::initialize() {
    std::cout << "Initializing Simulator..." << std::endl;
    
    // Load products
    if (!product_manager_.load_products(products_csv_)) {
        return false;
    }
    std::cout << "Loaded " << product_manager_.get_all_products().size() << " products." << std::endl;
    
    // Initialize Logger
    if (!DataLogger::get_instance().initialize(output_csv_)) {
        return false;
    }
    
    return true;
}

void Simulator::generate_agents() {
    std::cout << "Generating " << num_agents_ << " agents..." << std::endl;
    for (int i = 1; i <= num_agents_; ++i) {
        agents_.push_back(CustomerAgent::generate_random_agent(i));
    }
}

void Simulator::run() {
    std::cout << "Starting Simulation for " << num_days_ << " days..." << std::endl;
    
    for (int day = 1; day <= num_days_; ++day) {
        if (day % 5 == 0 || day == 1) {
            std::cout << "Simulating Day " << day << "..." << std::endl;
        }
        
        for (auto& agent : agents_) {
            // Give each agent a chance (e.g., 50%) to shop on a given day
            static std::mt19937 gen{std::random_device{}()};
            static std::uniform_real_distribution<double> runif(0.0, 1.0);
            
            if (runif(gen) < 0.5) {
                SessionRunner runner(day, agent, product_manager_, DataLogger::get_instance());
                runner.run();
            }
        }
    }
    
    DataLogger::get_instance().close();
    std::cout << "Simulation completed successfully!" << std::endl;
}
