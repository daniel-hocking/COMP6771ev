/*

  == Explanation and rational of testing ==

  Explain and justify how you approached testing, the degree
   to which you're certain you have covered all possibilities,
   and why you think your tests are that thorough.

*/

#include <utility>

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

SCENARIO("3. Check that vector iterator constructor returns a EuclideanVector with the specified "
         "elements set from the vector") {
  GIVEN("You have called the vector iterator constructor") {
    std::vector<double> l{1, 2, 3};
    int size = static_cast<int>(l.size());
    EuclideanVector e{l.begin(), l.end()};
    THEN("Check that dimensions have been set to elements from vector") {
      REQUIRE(e.GetNumDimensions() == size);
      for (int j = 0; j < size; ++j) {
        CHECK(e.at(j) == l.at(j));
      }

      REQUIRE_THROWS_WITH(e.at(size), Contains("is not valid for this EuclideanVector object"));
    }

    std::vector<double> l2{};
    int size2 = static_cast<int>(l2.size());
    EuclideanVector e2{l2.begin(), l2.end()};
    THEN("Check that dimensions have not been set as vector empty") {
      REQUIRE(e2.GetNumDimensions() == size2);
      for (int j = 0; j < size2; ++j) {
        CHECK(e2.at(j) == l2.at(j));
      }

      REQUIRE_THROWS_WITH(e2.at(size2), Contains("is not valid for this EuclideanVector object"));
    }

    std::vector<double> l3{3.0, 5.7, -2.2, -1, 6.32, 9.2};
    int size3 = static_cast<int>(l3.size());
    EuclideanVector e3{l3.begin(), l3.end()};
    THEN("Check that dimensions have been set to elements from longer vector with negatives") {
      REQUIRE(e3.GetNumDimensions() == size3);
      for (int j = 0; j < size3; ++j) {
        CHECK(e3.at(j) == l3.at(j));
      }

      REQUIRE_THROWS_WITH(e3.at(size3), Contains("is not valid for this EuclideanVector object"));
    }
  }
}

SCENARIO("4. Check that the copy constructor returns a EuclideanVector that is a copy of the one "
         "provided") {
  GIVEN("You have called the copy constructor") {
    EuclideanVector a;
    EuclideanVector b{a};
    THEN("Check that b has been set to 1 dimension euclidean vector like a") {
      REQUIRE(b.GetNumDimensions() == 1);
      CHECK(b.at(0) == a.at(0));
      REQUIRE_THROWS_WITH(b.at(1), Contains("is not valid for this EuclideanVector object"));
    }

    EuclideanVector c(3, 5.0);
    EuclideanVector d{c};
    THEN("Check that d has been set to copy of euclidean vector c") {
      REQUIRE(d.GetNumDimensions() == c.GetNumDimensions());
      for (int j = 0; j < d.GetNumDimensions(); ++j) {
        CHECK(d.at(j) == c.at(j));
      }
      REQUIRE_THROWS_WITH(d.at(c.GetNumDimensions()),
                          Contains("is not valid for this EuclideanVector object"));
    }

    EuclideanVector e(5, 7.7);
    EuclideanVector f = e;
    THEN("Check that f has been set to copy of euclidean vector e using implicit call") {
      REQUIRE(f.GetNumDimensions() == e.GetNumDimensions());
      for (int j = 0; j < f.GetNumDimensions(); ++j) {
        CHECK(f.at(j) == e.at(j));
      }
      REQUIRE_THROWS_WITH(f.at(e.GetNumDimensions()),
                          Contains("is not valid for this EuclideanVector object"));
    }
  }
}

SCENARIO("5. Check that the move constructor returns a EuclideanVector that is a copy of the one "
         "provided and leaves original with 0 dimensions (empty)") {
  GIVEN("You have called the move constructor") {
    EuclideanVector a;
    EuclideanVector b{std::move(a)};
    THEN("Check that b has been set to 1 dimension euclidean vector like a") {
      REQUIRE(b.GetNumDimensions() == 1);
      CHECK(b.at(0) == 0.0);
      REQUIRE_THROWS_WITH(b.at(1), Contains("is not valid for this EuclideanVector object"));
    }
    AND_THEN("Check that a has been set to 0 dimensions") {
      REQUIRE(a.GetNumDimensions() == 0);
      REQUIRE_THROWS_WITH(a.at(0), Contains("is not valid for this EuclideanVector object"));
    }

    EuclideanVector c(3, 5.0);
    EuclideanVector d{std::move(c)};
    THEN("Check that d has been set to copy of euclidean vector c") {
      REQUIRE(d.GetNumDimensions() == 3);
      for (int j = 0; j < d.GetNumDimensions(); ++j) {
        CHECK(d.at(j) == 5.0);
      }
      REQUIRE_THROWS_WITH(d.at(3), Contains("is not valid for this EuclideanVector object"));
    }
    AND_THEN("Check that c has been set to 0 dimensions") {
      REQUIRE(c.GetNumDimensions() == 0);
      REQUIRE_THROWS_WITH(c.at(0), Contains("is not valid for this EuclideanVector object"));
    }

    EuclideanVector e(5, 7.7);
    EuclideanVector f = std::move(e);
    THEN("Check that f has been set to copy of euclidean vector e using implicit call") {
      REQUIRE(f.GetNumDimensions() == 5);
      for (int j = 0; j < f.GetNumDimensions(); ++j) {
        CHECK(f.at(j) == 7.7);
      }
      REQUIRE_THROWS_WITH(f.at(5), Contains("is not valid for this EuclideanVector object"));
    }
    AND_THEN("Check that e has been set to 0 dimensions") {
      REQUIRE(e.GetNumDimensions() == 0);
      REQUIRE_THROWS_WITH(e.at(0), Contains("is not valid for this EuclideanVector object"));
    }
  }
}
