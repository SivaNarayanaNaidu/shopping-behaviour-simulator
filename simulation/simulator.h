#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "../agents/customer_agent.h"
#include "../core/product_manager.h"
#include "../analytics/data_logger.h"
#include "session_runner.h"
#include <vector>

class Simulator {
public:
    Simulator(int num_agents, int num_days, const std::string& products_csv, const std::string& output_csv);

    // Initialize the environment (load products, log headers, etc.)
    bool initialize();

    // Generate random agents
    void generate_agents();

    // Run the main simulation loop over iterations/days
    void run();

private:
    int num_agents_;
    int num_days_;
    std::string products_csv_;
    std::string output_csv_;

    ProductManager product_manager_;
    std::vector<CustomerAgent> agents_;
};

#endif // SIMULATOR_H
