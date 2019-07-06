/*

  == Explanation and rational of testing ==

  Explain and justify how you approached testing, the degree
   to which you're certain you have covered all possibilities,
   and why you think your tests are that thorough.

*/

#include "assignments/ev/euclidean_vector.h"
#include "catch.h"

using Catch::Matchers::Contains;

SCENARIO("1. Check that default constructor returns a EuclideanVector with the specified number "
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

SCENARIO("2. Check that int + double constructor returns a EuclideanVector with the specified "
         "number of dimensions set to value of second argument") {
  GIVEN("You have called the int + double constructor") {
    EuclideanVector e(1, 5.0);
    THEN("Check that 1 dimensions set to 5.0") {
      REQUIRE(e.GetNumDimensions() == 1);
      CHECK(e.at(0) == 5.0);
      REQUIRE_THROWS_WITH(e.at(1), Contains("is not valid for this EuclideanVector object"));
    }

    EuclideanVector e2(2, 1.0);
    THEN("Check that 2 dimensions set to 1.0") {
      REQUIRE(e2.GetNumDimensions() == 2);
      CHECK(e2.at(0) == 1.0);
      CHECK(e2.at(1) == 1.0);
      REQUIRE_THROWS_WITH(e2.at(2), Contains("is not valid for this EuclideanVector object"));
    }

    EuclideanVector e3(2, -1.0);
    THEN("Check that 2 dimensions set to -1.0") {
      REQUIRE(e3.GetNumDimensions() == 2);
      CHECK(e3.at(0) == -1.0);
      CHECK(e3.at(1) == -1.0);
      REQUIRE_THROWS_WITH(e3.at(2), Contains("is not valid for this EuclideanVector object"));
    }

    EuclideanVector e4(0, 3.0);
    THEN("Check that 0 dimensions are set") {
      REQUIRE(e4.GetNumDimensions() == 0);
      REQUIRE_THROWS_WITH(e4.at(0), Contains("is not valid for this EuclideanVector object"));
    }
  }
}

/*SCENARIO("3. Check that vector iterator constructor returns a EuclideanVector with the specified "
         "elements set from the vector") {
  GIVEN("You have called the vector iterator constructor") {
    std::vector<double> l{1, 2, 3};
    EuclideanVector e{l.begin(), l.end()};
    THEN("Check that dimensions have been set to elements from vector") {
      REQUIRE(e.GetNumDimensions() == l.size());
      for (int j = 0; j < l.size(); ++j) {
        CHECK(e.at(j) == l.at(j));
      }

      REQUIRE_THROWS_WITH(e.at(l.size()), Contains("is not valid for this EuclideanVector object"));
    }

    std::vector<double> l2{};
    EuclideanVector e2{l2.begin(), l2.end()};
    THEN("Check that dimensions have not been set as vector empty") {
      REQUIRE(e2.GetNumDimensions() == l2.size());
      for (unsigned j = 0; j < l2.size(); ++j) {
        CHECK(e2.at(j) == l2.at(j));
      }

      REQUIRE_THROWS_WITH(e2.at(l2.size()), Contains("is not valid for this EuclideanVector object"));
    }
  }
}*/