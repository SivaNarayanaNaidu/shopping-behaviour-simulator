#ifndef METRICS_H
#define METRICS_H

#include "../analytics/data_logger.h"
#include <string>
#include <vector>

class Metrics {
public:
    // Helper function to calculate basic metrics over a list of events
    static double calculate_conversion_rate(const std::vector<Event>& events);
    
    // Additional metric calculation hints could be here,
    // though the Python dashboard will do the heavy lifting later.
};

#endif // METRICS_H
