#ifndef CART_SYSTEM_H
#define CART_SYSTEM_H

#include "product_manager.h"
#include <vector>

struct CartItem {
    const Product* product;
    int quantity;
    double price_at_addition; // e.g. discounted price
};

class CartSystem {
public:
    CartSystem();
    ~CartSystem() = default;

    void add_item(const Product* product, int quantity = 1);
    void remove_item(const std::string& product_id);
    void clear_cart();

    double get_total_value() const;
    int get_total_items() const;
    bool is_empty() const;

    const std::vector<CartItem>& get_items() const;

private:
    std::vector<CartItem> items_;
};

#endif // CART_SYSTEM_H
