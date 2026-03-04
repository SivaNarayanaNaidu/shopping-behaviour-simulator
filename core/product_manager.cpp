#include "product_manager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <random>
#include <algorithm>

ProductManager::ProductManager() {
}

bool ProductManager::load_products(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Failed to open dataset at " << filepath << std::endl;
        return false;
    }

    std::string line;
    // Read header line
    if (!std::getline(file, line)) return false;

    // Parse each line
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string token;
        Product p;

        // Assuming format: id,category,brand,price,rating,discount,popularity_score
        if (!std::getline(ss, p.id, ',')) continue;
        std::getline(ss, p.category, ',');
        std::getline(ss, p.brand, ',');

        if (std::getline(ss, token, ',')) p.price = std::stod(token);
        if (std::getline(ss, token, ',')) p.rating = std::stod(token);
        if (std::getline(ss, token, ',')) p.discount = std::stod(token);
        if (std::getline(ss, token, ',')) p.popularity_score = std::stod(token);

        products_.push_back(p);
        product_index_[p.id] = products_.size() - 1;
    }

    file.close();
    return true;
}

const Product* ProductManager::get_product(const std::string& id) const {
    auto it = product_index_.find(id);
    if (it != product_index_.end()) {
        return &products_[it->second];
    }
    return nullptr;
}

const std::vector<Product>& ProductManager::get_all_products() const {
    return products_;
}

std::vector<const Product*> ProductManager::get_products_by_category(const std::string& category) const {
    std::vector<const Product*> result;
    for (const auto& product : products_) {
        // case-insensitive match or simple match
        if (product.category == category) {
            result.push_back(&product);
        }
    }
    return result;
}

std::vector<const Product*> ProductManager::get_random_products(int count) const {
    std::vector<const Product*> result;
    if (products_.empty()) return result;

    // We can simply pick `count` random indices
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dist(0, products_.size() - 1);

    int actual_count = std::min(count, static_cast<int>(products_.size()));
    for (int i = 0; i < actual_count; ++i) {
        result.push_back(&products_[dist(gen)]);
    }

    return result;
}
