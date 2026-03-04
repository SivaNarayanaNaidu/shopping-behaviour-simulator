#include "cart_system.h"
#include <algorithm>

CartSystem::CartSystem() {
}

void CartSystem::add_item(const Product* product, int quantity) {
    if (!product || quantity <= 0) return;

    for (auto& item : items_) {
        if (item.product->id == product->id) {
            item.quantity += quantity;
            return;
        }
    }

    // Item not found, add a new one
    CartItem new_item;
    new_item.product = product;
    new_item.quantity = quantity;
    new_item.price_at_addition = product->get_discounted_price();
    items_.push_back(new_item);
}

void CartSystem::remove_item(const std::string& product_id) {
    items_.erase(std::remove_if(items_.begin(), items_.end(),
        [&](const CartItem& item) {
            return item.product->id == product_id;
        }), items_.end());
}

void CartSystem::clear_cart() {
    items_.clear();
}

double CartSystem::get_total_value() const {
    double total = 0.0;
    for (const auto& item : items_) {
        total += item.price_at_addition * item.quantity;
    }
    return total;
}

int CartSystem::get_total_items() const {
    int count = 0;
    for (const auto& item : items_) {
        count += item.quantity;
    }
    return count;
}

bool CartSystem::is_empty() const {
    return items_.empty();
}

const std::vector<CartItem>& CartSystem::get_items() const {
    return items_;
}
