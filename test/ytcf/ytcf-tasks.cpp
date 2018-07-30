#include "ytcf-tasks.h"

namespace test {
namespace ytcf {

size_t calculate_distance(std::vector<unsigned int>& points, size_t a, size_t b)
{
    long dd = (long)points[a] - (long)points[b];

    size_t d = 0;
    if (dd < 0) {
        d = -dd;
    }
    else {
        d = dd;
    }
    return d;
}

/**
 * calculate mutual points distance  
 * find maxNeighbours where distance < rmax(R)
 */
size_t find_nearest_points(std::vector<unsigned int>& points, size_t rMax,
                           size_t groupCount)
{
    size_t maxNearestNeighbourCount = 0;
    size_t maxNeighbourIndex = 0;
    std::vector<unsigned int> maxFarPoints;

    for (size_t i = 0; i < points.size(); i++) {
        size_t neighbourCount = 0;
        std::vector<unsigned int> farPoints;
        for (size_t j = 0; j < points.size(); j++) {
            if (i == j) {
                continue;
            }

            size_t d = calculate_distance(points, i, j);
            if (d <= rMax) {
                neighbourCount++;
            }
            else {
                farPoints.push_back(points[j]);
            }
        }

        if (neighbourCount > maxNearestNeighbourCount) {
            maxNearestNeighbourCount = neighbourCount;
            maxNeighbourIndex = i;
            // assign operator
            maxFarPoints = farPoints;
        }
    }

    LOG(WARN, "maxNearestNeighbourCount %lu", maxNearestNeighbourCount);
    LOG(WARN, "maxNeighbourIndex %lu", maxNeighbourIndex);

    if (maxFarPoints.size() != 0) {
        //groupCount++;
        groupCount +=
            find_nearest_points(maxFarPoints, rMax, groupCount);
        return 1;
    }
    return 0;

    // LOG(WARN, "groupCount %lu", groupCount);
    //return groupCount;
    // if(maxNearestNeighbourCount == 0) {
    // return points.size();
    //}
}

size_t group_min_points(std::vector<unsigned int>& points, size_t rMax)
{
    find_nearest_points(points, rMax, 0);

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

            // LOG(WARN, "dd %ld", dd);
            size_t d = 0;
            if (dd < 0) {
                d = -dd;
            }
            else {
                d = dd;
            }
            // LOG(WARN, "d %ld", d);
            if (d <= rMax) {
                LOG(WARN, "d %ld, rMax %ld", d, rMax);
                if (d > dmax) {
                    // if (count == 0) {
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
    size_t minCount = group_min_points(points, 1);
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
