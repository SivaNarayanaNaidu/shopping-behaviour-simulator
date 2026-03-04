#include "session_runner.h"
#include "../core/cart_system.h"
#include "../agents/behavior_model.h"
#include <iostream>

SessionRunner::SessionRunner(int day, CustomerAgent& agent, const ProductManager& product_manager, DataLogger& logger)
    : day_(day), agent_(agent), product_manager_(product_manager), logger_(logger) {
}

void SessionRunner::run() {
    CartSystem cart;
    std::vector<Event> session_events;
    
    // 1. Browse Products (Simulate browsing randomly 5 to 20 products)
    int browse_count = 5 + (agent_.get_id() % 15);
    auto products = product_manager_.get_random_products(browse_count);
    
    for (const auto* product : products) {
        if (!product) continue;

        // 2. View Product Decision
        if (BehaviorModel::decides_to_view(agent_, *product)) {
            session_events.push_back({
                day_,
                agent_.get_id(),
                agent_.get_type_string(),
                EventType::ProductView,
                product->id,
                product->price,
                "00:00:00"
            });
            
            // 3. Buy Decision
            if (BehaviorModel::decides_to_buy(agent_, *product)) {
                cart.add_item(product, 1);
                
                session_events.push_back({
                    day_,
                    agent_.get_id(),
                    agent_.get_type_string(),
                    EventType::CartAddition,
                    product->id,
                    product->get_discounted_price(),
                    "00:00:00"
                });
            }
        }
    }
    
    // 4. Checkout or Abandon Cart
    if (!cart.is_empty()) {
        double total_value = cart.get_total_value();
        
        if (BehaviorModel::decides_to_abandon_cart(agent_, cart.get_total_items(), total_value)) {
            session_events.push_back({
                day_,
                agent_.get_id(),
                agent_.get_type_string(),
                EventType::CartAbandonment,
                "",
                total_value,
                "00:00:00"
            });
        } else {
            // Purchase
            session_events.push_back({
                day_,
                agent_.get_id(),
                agent_.get_type_string(),
                EventType::Purchase,
                "",
                total_value,
                "00:00:00"
            });
        }
    }
    
    // Batch log all events for this session
    logger_.log_events(session_events);
}
