/*

  == Explanation and rational of testing ==

  Explain and justify how you approached testing, the degree
   to which you're certain you have covered all possibilities,
   and why you think your tests are that thorough.

*/

#include "assignments/ev/euclidean_vector.h"
#include "catch.h"

using Catch::Matchers::Contains;

SCENARIO("1. Check that default constructor returns auto EuclideanVector with the specified number "
         "of dimensions set to 0.0") {
  GIVEN("You have called the default constructor") {
    EuclideanVector e;
    THEN("Check that 1 dimensions set to 0.0") {
      REQUIRE(e.GetNumDimensions() == 1);
      CHECK(e.at(0) == 0.0);
      REQUIRE_THROWS_WITH(e.at(1), Contains("is not valid for this EuclideanVector object"));
    }

    EuclideanVector e2(2);
    THEN("Check that 2 dimensions set to 0.0") {
      REQUIRE(e2.GetNumDimensions() == 2);
      CHECK(e2.at(0) == 0.0);
      CHECK(e2.at(1) == 0.0);
      REQUIRE_THROWS_WITH(e2.at(2), Contains("is not valid for this EuclideanVector object"));
    }

    EuclideanVector e3(0);
    THEN("Check that 0 dimensions are set") {
      REQUIRE(e3.GetNumDimensions() == 0);
      REQUIRE_THROWS_WITH(e3.at(0), Contains("is not valid for this EuclideanVector object"));
    }
  }
}
