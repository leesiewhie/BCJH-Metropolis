#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "Calculator.hpp"
#include <algorithm>
#include <cmath>
#include "globalConfig.hpp"
#include "chef.hpp"


class SARunner;
struct States {
    Chef *chef[MAX_CHEFS];
    ToolEnum toolCKPT[MAX_CHEFS];
    Recipe *recipe[DISH_PER_CHEF * MAX_CHEFS];
};
namespace r00 {
// void unrepeatedRandomChef(CList *, Chef **&, int);
void unrepeatedRandomRecipe(std::vector<Recipe *> *, Recipe **, int, int);
} // namespace r00

void swap(Recipe *&a, Recipe *&b);

template <typename T> bool inArray(T **array, int size, T *value) {
    for (int i = 0; i < size; i++) {
        if (array[i] == value) {
            return true;
        }
    }
    return false;
}
bool chefCanCook(Chef *, Recipe *);

namespace r {
typedef States (*RandomMove)(States, CList *, RList *);
States randomRecipe(States, CList *, RList *);
States randomChef(States, CList *, RList *);

} // namespace r
namespace e0 {
int sumPrice(States s, CList *c = NULL, RList *r = NULL, int log = false,
             bool exactChefTool = false);
}
namespace e {

typedef int (*GetEnergy)(States, CList *, RList *,  bool);
int getTotalPrice(States s, CList *c, RList *r,  bool vb = false);
} // namespace e

namespace f {
typedef double (*CoolingSchedule)(int, int, double, double);
double exponential_multiplicative(int stepMax, int step, double tMax,
                                  double tMin);
double linear(int stepMax, int step, double tMax, double tMin);
double t_dist_fast(int stepMax, int step, double tMax, double tMin);
double t_dist_slow(int stepMax, int step, double tMax, double tMin);
double linear_mul(int stepMax, int step, double tMax, double tMin);
double zipf(int stepMax, int step, double tMax, double tMin);
double one_over_n(int stepMax, int step, double tMax, double tMin);
} // namespace f
States perfectChef(States &s, CList *c);
#endif