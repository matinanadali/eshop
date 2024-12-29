#include "Order.h"

void Order::showOrderDetails(std::ostream &out, int orderIndex) const {
    out << "---Cart " << orderIndex << " START---\n";
    for (const auto &product : products) {
        out << product.getAmount() << " " << product.getTitle() << "\n";
    }
    out << "---Cart " << orderIndex << " END---\n";
    out << "Total Cost: " << totalCost;
}