#ifndef BEHAVIOR_MODEL_H
#define BEHAVIOR_MODEL_H

#include "../core/product_manager.h"

class CustomerAgent; // forward declaration

class BehaviorModel {
public:
    // Calculates the probability that a specific agent buys a specific product
    // Returns a value between 0.0 and 1.0
    static double calculate_buy_probability(const CustomerAgent& agent, const Product& product);

    // Determines if an agent decides to view a product they are browsing
    static bool decides_to_view(const CustomerAgent& agent, const Product& product);

    // Determines if an agent decides to buy a product after viewing
    static bool decides_to_buy(const CustomerAgent& agent, const Product& product);

    // Determines if an agent abandons the cart at checkout
    static bool decides_to_abandon_cart(const CustomerAgent& agent, int cart_size, double cart_value);
};

#endif // BEHAVIOR_MODEL_H
