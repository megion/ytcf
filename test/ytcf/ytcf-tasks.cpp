#include "ytcf-tasks.h"

namespace test {
namespace ytcf {

size_t group_min_points(std::vector<unsigned int> points, size_t rMax)
{
    size_t minCount = 0;
    size_t count = 0;
    for (size_t i = 0; i < points.size(); i++) {
        size_t dmax = 0;
        count = 0;
        for (size_t j = 0; j < points.size(); j++) {
            if (i == j) {
                continue;
            }

            long dd = (long)points[i] - (long)points[j];

            //LOG(WARN, "dd %ld", dd);
            size_t d = 0;
            if (dd < 0) {
                d = -dd;
            }
            else {
                d = dd;
            }
            //LOG(WARN, "d %ld", d);
            if (d <= rMax) {
                LOG(WARN, "d %ld, rMax %ld", d, rMax);
                if (d > dmax) {
                    //if (count == 0) {
                        count++;
                    //}
                    dmax = d;
                }
                else if (d == dmax) {
                    count++;
                }

                if ((minCount != 0) && count >= minCount) {
                    break;
                }
            }
        }

        LOG(WARN, "Count %lu", count);
        if ((count < minCount) || (minCount == 0)) {
            minCount = count;
        }
    }
    return minCount;
}

void test_group_min_points()
{
    std::vector<unsigned int> points = {6, 2, 4, 3, 5, 1};
    size_t minCount = group_min_points(points, 2);
    LOG(WARN, "minCount %lu", minCount);
    assert(minCount == 2);
}

void ytcf_tasks_test()
{
    suite("Task 1");
    mytest(group_min_points);
}
} // namespace ytcf
} // namespace test
