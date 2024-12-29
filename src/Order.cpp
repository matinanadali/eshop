#include "Order.h"

void Order::showOrderDetails(int orderIndex) const {
    std::cout << "---Cart " << orderIndex << " START---\n";
    for (const auto &product : products) {
        std::cout << product.getAmount() << " " << product.getTitle() << "\n";
    }
    std::cout << "---Cart " << orderIndex << " END---\n";
    std::cout << "Total Cost: " << totalCost << "\n";
}