/*

  == Explanation and rational of testing ==

  It's pretty simple really, there is a scenario for each constructor, operator and method
  that puts it through a series of tests including standard operation and edge cases

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

SCENARIO("6. Check that the copy assignment updates a EuclideanVector to be a copy of the one "
         "provided") {
  GIVEN("You have called the copy assignment") {
    EuclideanVector a;
    EuclideanVector b;
    b = a;
    THEN("Check that b has been set to 1 dimension euclidean vector like a (note by default they "
         "are the same)") {
      REQUIRE(b.GetNumDimensions() == 1);
      CHECK(b.at(0) == a.at(0));
      REQUIRE_THROWS_WITH(b.at(1), Contains("is not valid for this EuclideanVector object"));
    }

    EuclideanVector c(3, 5.0);
    EuclideanVector d(3, 7.5);
    d = c;
    THEN("Check that d has been set to copy of euclidean vector const (this time they have the "
         "same dimensions but different values") {
      REQUIRE(d.GetNumDimensions() == 3);
      for (int j = 0; j < d.GetNumDimensions(); ++j) {
        CHECK(d.at(j) == 5.0);
      }
      REQUIRE_THROWS_WITH(d.at(3), Contains("is not valid for this EuclideanVector object"));
    }

    EuclideanVector e(5, -2.1);
    EuclideanVector f(2, 4.0);
    f = e;
    THEN("Check that f has been set to copy of euclidean vector e (this time with different "
         "dimensions and values)") {
      REQUIRE(f.GetNumDimensions() == 5);
      for (int j = 0; j < f.GetNumDimensions(); ++j) {
        CHECK(f.at(j) == -2.1);
      }
      REQUIRE_THROWS_WITH(f.at(5), Contains("is not valid for this EuclideanVector object"));
    }
  }
}

SCENARIO("7. Check that the move assignment updates a EuclideanVector to be a copy of the one "
         "provided and leaves original with 0 dimensions (empty)") {
  GIVEN("You have called the move assignment") {
    EuclideanVector a;
    EuclideanVector b;
    b = std::move(a);
    THEN("Check that b has been set to 1 dimension euclidean vector like a (note by default "
         "they are the same)") {
      REQUIRE(b.GetNumDimensions() == 1);
      CHECK(b.at(0) == 0.0);
      REQUIRE_THROWS_WITH(b.at(1), Contains("is not valid for this EuclideanVector object"));
    }
    AND_THEN("Check that a has been set to 0 dimensions") {
      REQUIRE(a.GetNumDimensions() == 0);
      REQUIRE_THROWS_WITH(a.at(0), Contains("is not valid for this EuclideanVector object"));
    }

    EuclideanVector c(3, 5.0);
    EuclideanVector d(3, 7.5);
    d = std::move(c);
    THEN("Check that d has been set to copy of euclidean vector const (this time they have the "
         "same dimensions but different values)") {
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
    EuclideanVector f(2, 4.0);
    f = std::move(e);
    THEN("Check that f has been set to copy of euclidean vector e (this time with different "
         "dimensions and values)") {
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

SCENARIO("8. Check that the subscript operator works as expected for both access and updates") {
  GIVEN("You have setup a default 1 dimensional EuclideanVector") {
    EuclideanVector a;
    THEN("Check that an index can be accessed") { REQUIRE(a[0] == 0.0); }
    AND_THEN("Check that an index can be updated") {
      a[0] = 1.5;
      REQUIRE(a[0] == 1.5);
    }
  }
  AND_GIVEN("You have setup a EuclideanVector with multiple values") {
    std::vector<double> l{1, 2, 3, -5, 9};
    int size = static_cast<int>(l.size());
    EuclideanVector b{l.begin(), l.end()};
    THEN("Check that all index can be accessed") {
      for (int j = 0; j < size; ++j) {
        REQUIRE(b[j] == l[j]);
      }
    }
    AND_THEN("Check that an index can be updated") {
      b[2] = 70.5;
      REQUIRE(b[2] == 70.5);
    }
  }
  AND_GIVEN("You have setup a const EuclideanVector") {
    const EuclideanVector c(3, 5.0);
    THEN("Check that all index can be accessed") {
      for (int j = 0; j < 3; ++j) {
        REQUIRE(c[j] == 5.0);
      }
    }
  }
  AND_GIVEN("You have setup a EuclideanVector that you copy assign to a larger EV") {
    EuclideanVector d(4, 5.0);
    EuclideanVector e(2, 3.0);
    e = d;
    THEN("Check that all index can be accessed") {
      for (int j = 0; j < 4; ++j) {
        REQUIRE(e[j] == 5.0);
      }
    }
  }
  AND_GIVEN("You have setup a EuclideanVector that you copy assign to a smaller EV") {
    EuclideanVector f(4, 5.0);
    EuclideanVector g(6, 3.0);
    g = f;
    THEN("Check that all index can be accessed") {
      for (int j = 0; j < 4; ++j) {
        REQUIRE(g[j] == 5.0);
      }
    }
  }
}

SCENARIO("9. Check that the += and -= operator work as expected") {
  GIVEN("You have setup two simple EuclideanVector and add second to first") {
    EuclideanVector a(3, 2.0);
    EuclideanVector b(3, 3.0);
    a += b;
    THEN("Check that result sum is correct") {
      for (int j = 0; j < 3; ++j) {
        REQUIRE(a[j] == 5.0);
      }
    }
    AND_THEN("Check that subtracting b results in the original") {
      a -= b;
      for (int j = 0; j < 3; ++j) {
        REQUIRE(a[j] == 2.0);
      }
    }
  }
  AND_GIVEN(
      "You have setup two EuclideanVector with second being negative and add second to first") {
    EuclideanVector a(7, 3.0);
    EuclideanVector b(7, -3.0);
    a += b;
    THEN("Check that result sum is correct") {
      for (int j = 0; j < 7; ++j) {
        REQUIRE(a[j] == 0.0);
      }
    }
    AND_THEN("Check that subtracting b results in the original") {
      a -= b;
      for (int j = 0; j < 7; ++j) {
        REQUIRE(a[j] == 3.0);
      }
    }
  }
  AND_GIVEN("You have setup two complex EuclideanVector and add second to first") {
    std::vector<double> l{1, 2, 3, -5, 9};
    EuclideanVector a{l.begin(), l.end()};
    std::vector<double> l2{3, -1, 3, -7, -9};
    EuclideanVector b{l2.begin(), l2.end()};
    a += b;
    THEN("Check that result sum is correct") {
      for (int j = 0; j < 5; ++j) {
        REQUIRE(a[j] == l[j] + l2[j]);
      }
    }
    AND_THEN("Check that subtracting b results in the original") {
      a -= b;
      for (int j = 0; j < 5; ++j) {
        REQUIRE(a[j] == l[j]);
      }
    }
  }
  AND_GIVEN("You have setup two EuclideanVector that have different number of dimensions") {
    EuclideanVector a(7, 3.0);
    EuclideanVector b(5, 3.0);
    THEN("Check that adding results in an exception") {
      REQUIRE_THROWS_WITH(a += b, Contains("Dimensions of LHS"));
    }
    AND_THEN("Check that subtracting b results in an exception") {
      REQUIRE_THROWS_WITH(a -= b, Contains("Dimensions of LHS"));
    }
  }
}

SCENARIO("10. Check that the *= and /= operator work as expected") {
  GIVEN("You have setup a EuclideanVector and scalar") {
    EuclideanVector a(3, 2.0);
    a *= 3;
    THEN("Check that result multiplication is correct") {
      for (int j = 0; j < 3; ++j) {
        REQUIRE(a[j] == 6.0);
      }
    }
    AND_THEN("Check that division results in the original") {
      a /= 3;
      for (int j = 0; j < 3; ++j) {
        REQUIRE(a[j] == 2.0);
      }
    }
  }
  AND_GIVEN("You have setup a EuclideanVector and negative scalar") {
    EuclideanVector a(7, 3.0);
    a *= -5;
    THEN("Check that result multiplication is correct") {
      for (int j = 0; j < 7; ++j) {
        REQUIRE(a[j] == -15.0);
      }
    }
    AND_THEN("Check that division results in the original") {
      a /= -5;
      for (int j = 0; j < 7; ++j) {
        REQUIRE(a[j] == 3.0);
      }
    }
  }
  AND_GIVEN("You have setup a complex EuclideanVector and scalar") {
    std::vector<double> l{1, 2, 3, -5, 9};
    EuclideanVector a{l.begin(), l.end()};
    a *= 11;
    THEN("Check that result multiplication is correct") {
      for (int j = 0; j < 5; ++j) {
        REQUIRE(a[j] == l[j] * 11);
      }
    }
    AND_THEN("Check that division results in the original") {
      a /= 11;
      for (int j = 0; j < 5; ++j) {
        REQUIRE(a[j] == l[j]);
      }
    }
  }
  AND_GIVEN("You have setup a EuclideanVector and scalar of 0") {
    EuclideanVector a(5, 5.0);
    a *= 0;
    THEN("Check that multiplication results in 0") {
      for (int j = 0; j < 5; ++j) {
        REQUIRE(a[j] == 0.0);
      }
    }
    AND_THEN("Check that division results in an exception") {
      REQUIRE_THROWS_WITH(a /= 0, Contains("Invalid vector division by 0"));
    }
  }
  AND_GIVEN("You have setup a EuclideanVector and fractional scalar") {
    EuclideanVector a(7, 3.0);
    a *= 1.5;
    THEN("Check that result multiplication is correct") {
      for (int j = 0; j < 7; ++j) {
        REQUIRE(a[j] == 4.5);
      }
    }
    AND_THEN("Check that division results in the original") {
      a /= 1.5;
      for (int j = 0; j < 7; ++j) {
        REQUIRE(a[j] == 3.0);
      }
    }
  }
}

SCENARIO("11. Check that type conversion operator work as expected") {
  GIVEN("You have setup a default EuclideanVector") {
    EuclideanVector a;
    THEN("Check that conversion to vector is correct") {
      REQUIRE(static_cast<std::vector<double>>(a) == std::vector<double>{0.0});
    }
    AND_THEN("Check that conversion to list is correct") {
      REQUIRE(static_cast<std::list<double>>(a) == std::list<double>{0.0});
    }
  }
  AND_GIVEN("You have setup a EuclideanVector") {
    EuclideanVector a(7, 3.0);
    THEN("Check that conversion to vector is correct") {
      REQUIRE(static_cast<std::vector<double>>(a) == std::vector<double>(7, 3.0));
    }
    AND_THEN("Check that conversion to list is correct") {
      REQUIRE(static_cast<std::list<double>>(a) == std::list<double>(7, 3.0));
    }
  }
  AND_GIVEN("You have setup a complex EuclideanVector") {
    std::vector<double> l{1, 2, 3, -5, 9};
    EuclideanVector a{l.begin(), l.end()};
    THEN("Check that conversion to vector is correct") {
      REQUIRE(static_cast<std::vector<double>>(a) == l);
    }
    AND_THEN("Check that conversion to list is correct") {
      auto ev_list = static_cast<std::list<double>>(a);
      int index = 0;
      for (auto it = ev_list.begin(); it != ev_list.end(); ++it) {
        REQUIRE(*it == l[index]);
        ++index;
      }
    }
  }
}

SCENARIO("12. Check that the at method works as expected for both access and updates") {
  GIVEN("You have setup a default 1 dimensional EuclideanVector") {
    EuclideanVector a;
    THEN("Check that an index can be accessed") { REQUIRE(a.at(0) == 0.0); }
    AND_THEN("Check that an index can be updated") {
      a[0] = 1.5;
      REQUIRE(a.at(0) == 1.5);
    }
    AND_THEN("Check that access out of bounds throws exception") {
      REQUIRE_THROWS_WITH(a.at(1), Contains("is not valid for this EuclideanVector object"));
      REQUIRE_THROWS_WITH(a.at(-1), Contains("is not valid for this EuclideanVector object"));
    }
  }
  AND_GIVEN("You have setup a EuclideanVector with multiple values") {
    std::vector<double> l{1, 2, 3, -5, 9};
    int size = static_cast<int>(l.size());
    EuclideanVector b{l.begin(), l.end()};
    THEN("Check that all index can be accessed") {
      for (int j = 0; j < size; ++j) {
        REQUIRE(b.at(j) == l[j]);
      }
    }
    AND_THEN("Check that an index can be updated") {
      b.at(2) = 70.5;
      REQUIRE(b.at(2) == 70.5);
    }
    AND_THEN("Check that access out of bounds throws exception") {
      REQUIRE_THROWS_WITH(b.at(5), Contains("is not valid for this EuclideanVector object"));
    }
  }
  AND_GIVEN("You have setup a const EuclideanVector") {
    const EuclideanVector c(3, 5.0);
    THEN("Check that all index can be accessed") {
      for (int j = 0; j < 3; ++j) {
        REQUIRE(c.at(j) == 5.0);
      }
    }
  }
  AND_GIVEN("You have setup a EuclideanVector that you copy assign to a larger EV") {
    EuclideanVector d(4, 5.0);
    EuclideanVector e(2, 3.0);
    e = d;
    THEN("Check that all index can be accessed") {
      for (int j = 0; j < 4; ++j) {
        REQUIRE(e.at(j) == 5.0);
      }
    }
    AND_THEN("Check that access out of bounds throws exception") {
      REQUIRE_THROWS_WITH(e.at(4), Contains("is not valid for this EuclideanVector object"));
    }
  }
  AND_GIVEN("You have setup a EuclideanVector that you copy assign to a smaller EV") {
    EuclideanVector f(4, 5.0);
    EuclideanVector g(6, 3.0);
    g = f;
    THEN("Check that all index can be accessed") {
      for (int j = 0; j < 4; ++j) {
        REQUIRE(g.at(j) == 5.0);
      }
    }
    AND_THEN("Check that access to old index values throws exception") {
      REQUIRE_THROWS_WITH(g.at(4), Contains("is not valid for this EuclideanVector object"));
      REQUIRE_THROWS_WITH(g.at(5), Contains("is not valid for this EuclideanVector object"));
    }
  }
}

SCENARIO("13. Check that GetNumDimensions method works as expected") {
  GIVEN("You have setup a default EuclideanVector") {
    EuclideanVector a;
    THEN("Check that it has only 1 dimension") { REQUIRE(a.GetNumDimensions() == 1); }
  }
  AND_GIVEN("You have setup a EuclideanVector") {
    EuclideanVector a(7, 3.0);
    THEN("Check that it has 7 dimensions") { REQUIRE(a.GetNumDimensions() == 7); }
  }
  AND_GIVEN("You have setup a complex EuclideanVector") {
    std::vector<double> l{1, 2, 3, -5, 9};
    int size = static_cast<int>(l.size());
    EuclideanVector a{l.begin(), l.end()};
    THEN("Check that it dimensions equal to size of vector") {
      REQUIRE(a.GetNumDimensions() == size);
    }
  }
  AND_GIVEN("You have setup a EuclideanVector that you copy assign to a larger EV") {
    EuclideanVector d(4, 5.0);
    EuclideanVector e(2, 3.0);
    THEN("Check that it has 2 dimensions") { REQUIRE(e.GetNumDimensions() == 2); }
    e = d;
    AND_THEN("Check that it has 4 dimensions after assignment") {
      REQUIRE(e.GetNumDimensions() == 4);
    }
  }
  AND_GIVEN("You have setup a EuclideanVector that you copy assign to a smaller EV") {
    EuclideanVector f(4, 5.0);
    EuclideanVector g(6, 3.0);
    THEN("Check that it has 6 dimensions") { REQUIRE(g.GetNumDimensions() == 6); }
    g = f;
    AND_THEN("Check that it has 4 dimensions after assignment") {
      REQUIRE(g.GetNumDimensions() == 4);
    }
  }
}

SCENARIO("14. Check that GetEuclideanNorm method works as expected") {
  GIVEN("You have setup a default EuclideanVector") {
    EuclideanVector a;
    THEN("Check that it has euclidean norm of 0") { REQUIRE(a.GetEuclideanNorm() == 0.0); }
  }
  AND_GIVEN("You have setup a 0 dimension EuclideanVector") {
    EuclideanVector a(0);
    THEN("Check that it has no euclidean norm") {
      REQUIRE_THROWS_WITH(a.GetEuclideanNorm(),
                          Contains("EuclideanVector with no dimensions does not have a norm"));
    }
  }
  AND_GIVEN("You have setup a EuclideanVector") {
    EuclideanVector a(4, 3.0);
    THEN("Check that it has euclidean norm of 6") { REQUIRE(a.GetEuclideanNorm() == 6.0); }
  }
  AND_GIVEN("You have setup a complex EuclideanVector") {
    std::vector<double> l{2, 6, 5, -5, 3, 1};
    EuclideanVector a{l.begin(), l.end()};
    THEN("Check that it has euclidean norm of 10") { REQUIRE(a.GetEuclideanNorm() == 10.0); }
  }
  AND_GIVEN("You have setup a EuclideanVector that you move assign to a different EV") {
    EuclideanVector d(4, 5.0);
    EuclideanVector e(4, 4.0);
    THEN("Check that it has euclidean norm of 8") { REQUIRE(e.GetEuclideanNorm() == 8.0); }
    e = std::move(d);
    AND_THEN("Check that it has euclidean norm of 10 after assignment") {
      REQUIRE(e.GetEuclideanNorm() == 10.0);
    }
    AND_THEN("Check that that moved EV has no euclidean norm after assignment") {
      REQUIRE_THROWS_WITH(d.GetEuclideanNorm(),
                          Contains("EuclideanVector with no dimensions does not have a norm"));
    }
  }
}

SCENARIO("15. Check that CreateUnitVector method works as expected") {
  GIVEN("You have setup a default EuclideanVector") {
    EuclideanVector a;
    THEN("Check that it has no unit vector") {
      REQUIRE_THROWS_WITH(
          a.CreateUnitVector(),
          Contains("EuclideanVector with euclidean normal of 0 does not have a unit vector"));
    }
  }
  AND_GIVEN("You have setup a 0 dimension EuclideanVector") {
    EuclideanVector a(0);
    THEN("Check that it has no unit vector") {
      REQUIRE_THROWS_WITH(
          a.CreateUnitVector(),
          Contains("EuclideanVector with no dimensions does not have a unit vector"));
    }
  }
  AND_GIVEN("You have setup a EuclideanVector and found the unit vector") {
    EuclideanVector a(4, 3.0);
    EuclideanVector b = a.CreateUnitVector();
    THEN("Check that unit vector has magnitudes of 0.5") {
      for (int j = 0; j < 4; ++j) {
        REQUIRE(b.at(j) == 0.5);
      }
    }
  }
  AND_GIVEN("You have setup a complex EuclideanVector and found the unit vector") {
    std::vector<double> l{2, 6, 5, -5, 3, 1};
    std::vector<double> l_unit{0.2, 0.6, 0.5, -0.5, 0.3, 0.1};
    EuclideanVector a{l.begin(), l.end()};
    EuclideanVector b = a.CreateUnitVector();
    THEN("Check that it has unit vector as specified by l_unit") {
      for (int j = 0; j < 6; ++j) {
        REQUIRE(b.at(j) == l_unit[j]);
      }
    }
  }
  AND_GIVEN("You have setup a EuclideanVector that you move assign to a different EV") {
    EuclideanVector d(16, 2.0);
    EuclideanVector e(4, 4.0);
    EuclideanVector f = e.CreateUnitVector();
    THEN("Check that unit vector has magnitudes of 0.5") {
      for (int j = 0; j < 4; ++j) {
        REQUIRE(f.at(j) == 0.5);
      }
    }
    e = std::move(d);
    f = e.CreateUnitVector();
    AND_THEN("Check that unit vector has magnitudes of 0.25 after assignment") {
      for (int j = 0; j < 16; ++j) {
        REQUIRE(f.at(j) == 0.25);
      }
    }
    AND_THEN("Check that that moved EV has no unit vector after assignment") {
      REQUIRE_THROWS_WITH(
          d.CreateUnitVector(),
          Contains("EuclideanVector with no dimensions does not have a unit vector"));
    }
  }
}
