# AI Shopping Behaviour Simulator

An AI-powered online shopping simulator that relies on probabilistic behavioral models (Budget Shoppers, Impulse Buyers, Brand Loyal Customers, etc.) and analyzes their purchase patterns using Python data visualization.

---

## 📂 Project Structure
```text
shopping-behaviour-simulator
├── agents/             (C++ AI customer models)
├── analytics/          (C++ data logging and metrics tracking)
├── core/               (C++ product manager and cart system)
├── dashboard/          (Python Streamlit visualization)
├── datasets/           (Python scripts to build synthetic databases)
├── simulation/         (C++ loop runner and session manager)
├── main.cpp            (C++ simulator entrypoint)
├── CMakeLists.txt      (C++ Build configuration)
```

---

## 🚀 How to Run the Project

### Part 1: See the AI Analytics Dashboard
We provided some sample `events.csv` data so you can view the dashboard immediately!

1. Install the required Python dependencies:
   ```bash
   pip install -r dashboard/requirements.txt
   ```
2. Run the Streamlit app:
   ```bash
   streamlit run dashboard/app.py
   ```
3. Open the provided `localhost` URL in your browser to view the generated purchase funnel and revenue metrics.

---

### Part 2: Generate New Synthetic Datasets
If you want to create a fresh catalog of products and simulate new events:

1. Generate standard eCommerce products (`products.csv`):
   ```bash
   python datasets/generate_products.py
   ```
2. Generate mock interaction logs (`events.csv`) based on AI profiles:
   ```bash
   python datasets/generate_mock_events.py
   ```
*Note: Refresh the Streamlit dashboard to see the latest data.*

---

### Part 3: Run the Native C++ Simulator Engine (Optional)
If you have a C++ compiler (like GCC or MSVC via Visual Studio) and CMake installed, you can compile the core simulator:

1. Generate build files:
   ```bash
   cmake -B build
   ```
2. Compile the binaries:
   ```bash
   cmake --build build
   ```
3. Run the simulator executable (Windows):
   ```bash
   .\build\Debug\simulator.exe
   ```
   *(Or just `.\build\simulator` on Linux/macOS)*

The execution will simulate 1000 AI agents over 30 days and write an updated `events.csv` to monitor their simulated decisions.
