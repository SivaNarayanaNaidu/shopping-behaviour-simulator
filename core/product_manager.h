#ifndef PRODUCT_MANAGER_H
#define PRODUCT_MANAGER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

struct Product {
    std::string id;
    std::string category;
    std::string brand;
    double price;
    double rating;
    double discount;
    double popularity_score;

    // Derived fields or helpers
    double get_discounted_price() const {
        return price * (1.0 - discount);
    }
};

class ProductManager {
public:
    ProductManager();
    ~ProductManager() = default;

    // Load products from a CSV file
    bool load_products(const std::string& filepath);

    // Get a specific product by ID
    const Product* get_product(const std::string& id) const;

    // Get all products
    const std::vector<Product>& get_all_products() const;

    // Get products by category
    std::vector<const Product*> get_products_by_category(const std::string& category) const;

    // Get a random sample of products (for browsing)
    std::vector<const Product*> get_random_products(int count) const;

private:
    std::vector<Product> products_;
    std::unordered_map<std::string, size_t> product_index_; // Maps id to index in products_
};

#endif // PRODUCT_MANAGER_H
