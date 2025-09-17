#include <geometrycentral/utilities/utilities.h>

namespace geometrycentral {

std::random_device util_random_device;
std::mt19937 util_mersenne_twister(util_random_device());

} // namespace geometrycentral
