#ifndef SESSION_RUNNER_H
#define SESSION_RUNNER_H

#include "../agents/customer_agent.h"
#include "../core/product_manager.h"
#include "../analytics/data_logger.h"
#include <vector>

class SessionRunner {
public:
    SessionRunner(int day, CustomerAgent& agent, const ProductManager& const_product_manager, DataLogger& logger);

    // Runs a single shopping session for the agent
    void run();

private:
    int day_;
    CustomerAgent& agent_;
    const ProductManager& product_manager_;
    DataLogger& logger_;
};

#endif // SESSION_RUNNER_H
