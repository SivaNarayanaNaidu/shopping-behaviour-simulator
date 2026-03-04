#include "customer_agent.h"
#include <random>

CustomerAgent::CustomerAgent(int id, AgentType type) : id_(id), type_(type) {
}

int CustomerAgent::get_id() const {
    return id_;
}

AgentType CustomerAgent::get_type() const {
    return type_;
}

std::string CustomerAgent::get_type_string() const {
    switch (type_) {
        case AgentType::BudgetShopper: return "BudgetShopper";
        case AgentType::ImpulseBuyer: return "ImpulseBuyer";
        case AgentType::BrandLoyal: return "BrandLoyal";
        case AgentType::DiscountHunter: return "DiscountHunter";
        case AgentType::AverageJoe: return "AverageJoe";
        default: return "Unknown";
    }
}

CustomerAgent CustomerAgent::generate_random_agent(int id) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> type_dist(0, 4);
    
    AgentType t = static_cast<AgentType>(type_dist(gen));
    CustomerAgent agent(id, t);
    
    std::uniform_int_distribution<> age_dist(18, 70);
    std::uniform_real_distribution<> income_dist(20000.0, 150000.0);
    
    agent.age = age_dist(gen);
    agent.income = income_dist(gen);
    
    // Assign specific traits based on type
    std::uniform_real_distribution<> prob(0.0, 1.0);
    
    switch (t) {
        case AgentType::BudgetShopper:
            agent.price_sensitivity = 0.8 + 0.2 * prob(gen); // 0.8 - 1.0
            agent.brand_preference = 0.1 + 0.2 * prob(gen);  // Low
            agent.purchase_probability = 0.3;
            break;
            
        case AgentType::ImpulseBuyer:
            agent.price_sensitivity = 0.1 + 0.3 * prob(gen); // Low
            agent.brand_preference = 0.3 + 0.4 * prob(gen);
            agent.purchase_probability = 0.8;
            break;
            
        case AgentType::BrandLoyal:
            agent.price_sensitivity = 0.3 + 0.3 * prob(gen);
            agent.brand_preference = 0.8 + 0.2 * prob(gen); // High
            agent.purchase_probability = 0.5;
            break;
            
        case AgentType::DiscountHunter:
            agent.price_sensitivity = 0.6 + 0.3 * prob(gen);
            agent.brand_preference = 0.2 + 0.3 * prob(gen);
            agent.purchase_probability = 0.4;
            break;
            
        case AgentType::AverageJoe:
            agent.price_sensitivity = 0.4 + 0.3 * prob(gen); // 0.4 - 0.7
            agent.brand_preference = 0.4 + 0.3 * prob(gen);
            agent.purchase_probability = 0.5;
            break;
    }
    
    // For a real simulation, we'd pick a random category/brand from the dataset
    // We'll leave it empty for general cases, and let Simulator populate it or rely on the logic
    agent.preferred_category = ""; 
    agent.preferred_brand = "";

    return agent;
}
