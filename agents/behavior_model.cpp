#include "behavior_model.h"
#include "customer_agent.h"
#include <random>
#include <algorithm>

static std::mt19937 gen{std::random_device{}()};
static std::uniform_real_distribution<double> runif(0.0, 1.0);

double BehaviorModel::calculate_buy_probability(const CustomerAgent& agent, const Product& product) {
    double base_prob = agent.purchase_probability;
    
    // Impact of discount
    double discount_factor = product.discount * 2.0; // 50% discount = 1.0 impact
    if (agent.get_type() == AgentType::DiscountHunter) {
        discount_factor *= 1.5;
    } else if (agent.get_type() == AgentType::BudgetShopper) {
        discount_factor *= 2.0;
        if (product.get_discounted_price() > agent.income * 0.01) { // Too expensive
            base_prob *= 0.1;
        }
    }
    
    // Impact of rating
    double rating_factor = (product.rating - 2.5) / 2.5; // -1 to 1 based on 0-5 rating
    if (rating_factor < 0) {
        base_prob *= (1.0 + rating_factor); // Decrease prob for < 2.5 rating
    } else {
        base_prob += rating_factor * 0.1; // Increase slightly for high rating
    }
    
    // Impact of preference
    double personal_interest = 0.5;
    if (!agent.preferred_brand.empty() && product.brand == agent.preferred_brand) {
        personal_interest += agent.brand_preference;
    }
    if (!agent.preferred_category.empty() && product.category == agent.preferred_category) {
        personal_interest += 0.3;
    }
    
    // Combine factors
    double final_prob = base_prob * 0.4 + discount_factor * 0.3 + personal_interest * 0.3;
    
    // Clamp to [0, 1]
    return std::max(0.0, std::min(1.0, final_prob));
}

bool BehaviorModel::decides_to_view(const CustomerAgent& agent, const Product& product) {
    double view_prob = 0.5; // Base
    
    // Impulse buyers view more often
    if (agent.get_type() == AgentType::ImpulseBuyer) {
        view_prob += 0.3;
    }
    
    // High rating / popularity increases view chance
    if (product.rating >= 4.0) view_prob += 0.1;
    if (product.popularity_score > 80.0) view_prob += 0.2;
    if (product.discount > 0.2) view_prob += 0.1;
    
    return runif(gen) < view_prob;
}

bool BehaviorModel::decides_to_buy(const CustomerAgent& agent, const Product& product) {
    double prob = calculate_buy_probability(agent, product);
    return runif(gen) < prob;
}

bool BehaviorModel::decides_to_abandon_cart(const CustomerAgent& agent, int cart_size, double cart_value) {
    if (cart_size == 0) return true;
    
    double abandon_prob = 0.1; // Base 10% abandonment
    
    // Budget shoppers abandon if cart value is too high
    if (agent.get_type() == AgentType::BudgetShopper && cart_value > 500.0) {
        abandon_prob += 0.6;
    }
    
    // More items = higher chance of abandonment (friction)
    if (cart_size > 5) abandon_prob += 0.1;
    if (cart_size > 10) abandon_prob += 0.2;
    
    return runif(gen) < abandon_prob;
}
