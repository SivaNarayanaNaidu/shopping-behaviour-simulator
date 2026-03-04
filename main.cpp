#include "simulation/simulator.h"
#include <iostream>

int main(int argc, char* argv[]) {
    std::cout << "========================================" << std::endl;
    std::cout << "  AI Shopping Behaviour Simulator  " << std::endl;
    std::cout << "========================================" << std::endl;
    
    // Configuration
    int num_agents = 1000;
    int num_days = 30;
    std::string products_csv = "products.csv";
    std::string output_events_csv = "events.csv";
    
    // Allow basic command line overrides
    if (argc > 1) num_agents = std::stoi(argv[1]);
    if (argc > 2) num_days = std::stoi(argv[2]);
    if (argc > 3) products_csv = argv[3];
    if (argc > 4) output_events_csv = argv[4];

    Simulator simulator(num_agents, num_days, products_csv, output_events_csv);
    
    if (!simulator.initialize()) {
        std::cerr << "Initialization failed. Check if " << products_csv << " exists." << std::endl;
        return 1;
    }
    
    simulator.generate_agents();
    simulator.run();
    
    std::cout << "Run complete. Insights saved to " << output_events_csv << std::endl;
    return 0;
}
