#ifndef CUSTOMER_AGENT_H
#define CUSTOMER_AGENT_H

#include <string>
#include <vector>
#include "../core/product_manager.h"

enum class AgentType {
    BudgetShopper,
    ImpulseBuyer,
    BrandLoyal,
    DiscountHunter,
    AverageJoe
};

class CustomerAgent {
public:
    CustomerAgent(int id, AgentType type);
    virtual ~CustomerAgent() = default;

    int get_id() const;
    AgentType get_type() const;
    std::string get_type_string() const;

    // Attributes
    int age;
    double income;
    double price_sensitivity;   // 0.0 to 1.0 (high sensitivity means they care more about price)
    double brand_preference;    // 0.0 to 1.0
    double purchase_probability;// Base baseline probability
    std::string preferred_category;
    std::string preferred_brand;

    static CustomerAgent generate_random_agent(int id);

private:
    int id_;
    AgentType type_;
};

#endif // CUSTOMER_AGENT_H
