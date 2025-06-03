#include "Lists/headers/lists_main.h"
#include "PriorityQueues/headers/priority_queues_main.h"
#include "HashTables/headers/hash_tables_main.h"

int main() {
    // lists_main({5000, 10000, 15000, 20000, 25000, 30000, 35000, 40000, 45000, 50000, 55000, 60000, 65000, 70000, 75000, 80000, 85000, 90000, 95000, 100000}, 50);
    // priority_queues_main({5000, 10000, 15000, 20000, 25000, 30000, 35000, 40000, 45000, 50000, 55000, 60000, 65000, 70000, 75000, 80000, 85000, 90000, 95000, 100000}, 10);
    hash_tables_main({10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000, 200000, 300000, 400000, 500000}, 10);
    return 0;
}