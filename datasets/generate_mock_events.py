import csv
import random

def generate_mock_events():
    products = []
    try:
        with open("products.csv", 'r', encoding='utf-8') as f:
            reader = csv.DictReader(f)
            for row in reader:
                products.append(row)
    except FileNotFoundError:
        print("Required file 'products.csv' not found.")
        return

    agent_types = ["BudgetShopper", "ImpulseBuyer", "BrandLoyal", "DiscountHunter", "AverageJoe"]
    
    with open("events.csv", 'w', newline='', encoding='utf-8') as f:
        writer = csv.writer(f)
        writer.writerow(["day", "agent_id", "agent_type", "event_type", "product_id", "value", "timestamp"])
        
        # Simulate 30 days, 200 sessions per day
        for day in range(1, 31):
            num_sessions = random.randint(50, 200)
            
            for _ in range(num_sessions):
                agent_id = random.randint(1, 1000)
                agent_type = random.choice(agent_types)
                
                # A session
                num_views = random.randint(1, 10)
                cart_value = 0.0
                
                for _ in range(num_views):
                    prod = random.choice(products)
                    price = float(prod['price'])
                    discount = float(prod['discount'])
                    
                    # View
                    writer.writerow([day, agent_id, agent_type, "ProductView", prod['id'], price, "00:00:00"])
                    
                    # Add to cart?
                    if random.random() < 0.2: # 20% add to cart
                        cart_value += price * (1 - discount)
                        writer.writerow([day, agent_id, agent_type, "CartAddition", prod['id'], price * (1 - discount), "00:00:00"])
                
                # Checkout or Abandon?
                if cart_value > 0:
                    if random.random() < 0.3: # 30% abandon
                        writer.writerow([day, agent_id, agent_type, "CartAbandonment", "", cart_value, "00:00:00"])
                    else:
                        writer.writerow([day, agent_id, agent_type, "Purchase", "", cart_value, "00:00:00"])

if __name__ == "__main__":
    generate_mock_events()
    print("Generated mock events in events.csv")
