import csv
import random

def generate_products(filename, count=500):
    categories = ['Electronics', 'Clothing', 'Home', 'Books', 'Sports', 'Toys']
    brands = {
        'Electronics': ['Sony', 'Samsung', 'Apple', 'LG', 'Dell'],
        'Clothing': ['Nike', 'Adidas', 'Zara', 'H&M', 'Gucci'],
        'Home': ['IKEA', 'Ashley', 'Williams-Sonoma', 'Wayfair', 'Pottery Barn'],
        'Books': ['Penguin', 'HarperCollins', 'Scholastic', 'Macmillan', 'Simon & Schuster'],
        'Sports': ['Under Armour', 'Puma', 'Reebok', 'Columbia', 'Patagonia'],
        'Toys': ['Lego', 'Hasbro', 'Mattel', 'Fisher-Price', 'Nerf']
    }

    with open(filename, 'w', newline='') as f:
        writer = csv.writer(f)
        writer.writerow(['id', 'category', 'brand', 'price', 'rating', 'discount', 'popularity_score'])

        for i in range(1, count + 1):
            prod_id = f"PROD_{i:04d}"
            category = random.choice(categories)
            brand = random.choice(brands[category])
            
            # Pricing based on category roughly
            if category == 'Electronics':
                price = round(random.uniform(50.0, 2000.0), 2)
            elif category == 'Clothing':
                price = round(random.uniform(10.0, 200.0), 2)
            else:
                price = round(random.uniform(5.0, 500.0), 2)
                
            rating = round(random.uniform(1.0, 5.0), 1)
            
            # 30% chance of no discount
            if random.random() < 0.3:
                discount = 0.0
            else:
                discount = round(random.uniform(0.05, 0.50), 2)
                
            popularity = round(random.uniform(0.0, 100.0), 1)

            writer.writerow([prod_id, category, brand, price, rating, discount, popularity])

if __name__ == "__main__":
    generate_products('products.csv', 500)
    print("Generated 500 products in products.csv")
