#ifndef ASSIGNMENTS_EV_EUCLIDEAN_VECTOR_H_
#define ASSIGNMENTS_EV_EUCLIDEAN_VECTOR_H_

#include <exception>
#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <vector>

class EuclideanVectorError : public std::exception {
 public:
  explicit EuclideanVectorError(const std::string& what) : what_(what) {}
  const char* what() const noexcept { return what_.c_str(); }

 private:
  std::string what_;
};

class EuclideanVector {
 public:
  // START CONSTRUCTORS

  /*
   * Default constructor
   * Is a delegating constructor to the constructor with single int as argument
   * assumes there should only be 1 dimension as default
   */
  EuclideanVector() noexcept : EuclideanVector{1} {}

  /*
   * Int constructor
   * Is a delegating constructor to the constructor with an int + double as argument
   * assumes that default value should be 0.0
   */
  explicit EuclideanVector(const int i) noexcept : EuclideanVector{i, 0.0} {}

  /*
   * Int + double constructor
   * Sets i dimensions to the value m
   */
  EuclideanVector(int, double) noexcept;

  /*
   * Vector iterator constructor
   * Takes a vector iterator as arguments copies values from vector into appropriately
   * an sized EuclideanVector
   */
  EuclideanVector(std::vector<double>::const_iterator,
                  std::vector<double>::const_iterator) noexcept;

  /*
   * Copy constructor
   */
  EuclideanVector(const EuclideanVector&) noexcept;

  /*
   * Move constructor
   */
  EuclideanVector(EuclideanVector&&) noexcept;

  // END CONSTRUCTORS

  /*
   * Destructor: just used the default
   */
  ~EuclideanVector() noexcept = default;

  // START OPERATORS

  /*
   * Copy assignment
   */
  EuclideanVector& operator=(const EuclideanVector&) noexcept;

  /*
   * Move assignment
   */
  EuclideanVector& operator=(EuclideanVector&&) noexcept;

  /*
   * Subscript operator
   */
  double operator[](int) const;
  double& operator[](int);

  /*
   * Maths equals operators
   */
  EuclideanVector& operator+=(const EuclideanVector&);
  EuclideanVector& operator-=(const EuclideanVector&);
  EuclideanVector& operator*=(int s) noexcept;
  EuclideanVector& operator/=(int s);

  /*
   * Explicit type conversions
   */
  explicit operator std::vector<double>() noexcept;
  explicit operator std::list<double>() noexcept;

  // END OPERATORS

  // START METHODS

  /*
   * At methods are equivalent to subscript operator however they have explicit boundary checks
   */
  double at(int i) const;
  double& at(int i);

  /*
   * Return the value stored by num_dim_ member variable
   */
  int GetNumDimensions() const noexcept;

  /*
   * The Euclidean norm is the square root of the sum of the squares of the magnitudes in each
   * dimension eg. for the vector [1 2 3] the Euclidean norm is sqrt(1*1 + 2*2 + 3*3) = 3.74
   */
  double GetEuclideanNorm() const;

  /*
   * Returns a unit vector for the given Euclidean vector, a unit vector is found by dividing
   * each magnitude by the Euclidean norm
   */
  EuclideanVector CreateUnitVector();

  // END METHODS

  // START FRIENDS

  /*
   * Equality operators
   */
  friend bool operator==(const EuclideanVector& lhs, const EuclideanVector& rhs) noexcept {
    if (lhs.GetNumDimensions() != rhs.GetNumDimensions()) {
      return false;
    }

    for (int j = 0; j < lhs.GetNumDimensions(); j++) {
      if (lhs[j] != rhs[j]) {
        return false;
      }
    }

    return true;
  }
  friend bool operator!=(const EuclideanVector& lhs, const EuclideanVector& rhs) noexcept {
    return !(lhs == rhs);
  }

  /*
   * Add/subtract operators
   */
  friend EuclideanVector operator+(const EuclideanVector& lhs, const EuclideanVector& rhs) {
    return OperatorAddSub(lhs, rhs, true);
  }
  friend EuclideanVector operator-(const EuclideanVector& lhs, const EuclideanVector& rhs) {
    return OperatorAddSub(lhs, rhs, false);
  }

  /*
   * Dot product multiplication
   * returns a double. E.g., [1 2] * [3 4] = 1 * 3 + 2 * 4 = 11
   */
  friend double operator*(const EuclideanVector& lhs, const EuclideanVector& rhs) {
    CheckDimMatches(lhs.GetNumDimensions(), rhs.GetNumDimensions());

    double dot_prod = 0.0;
    for (int j = 0; j < lhs.GetNumDimensions(); j++) {
      dot_prod += lhs[j] * rhs[j];
    }

    return dot_prod;
  }

  /*
   * Multiplication by scalar operators
   */
  friend EuclideanVector operator*(const EuclideanVector& lhs, int scalar) noexcept {
    return OperatorMultiScalar(lhs, scalar);
  }
  friend EuclideanVector operator*(int scalar, const EuclideanVector& lhs) noexcept {
    return OperatorMultiScalar(lhs, scalar);
  }

  /*
   * Division by scalar operator
   */
  friend EuclideanVector operator/(const EuclideanVector& lhs, int scalar) {
    if (scalar == 0) {
      throw EuclideanVectorError{"Invalid vector division by 0"};
    }

    EuclideanVector ev = lhs;
    for (int j = 0; j < ev.GetNumDimensions(); j++) {
      ev.magnitudes_[j] /= scalar;
    }

    return ev;
  }

  /*
   * Output stream operator
   */
  friend std::ostream& operator<<(std::ostream& os, const EuclideanVector& v) {
    os << "[";
    if (v.GetNumDimensions() > 0) {
      for (int j = 0; j < v.GetNumDimensions(); j++) {
        if (j > 0) {
          os << " ";
        }
        os << v.at(j);
      }
    }
    os << "]";

    return os;
  }

  // END FRIENDS

 private:
  // START MEMBER VARIABLES

  std::unique_ptr<double[]> magnitudes_;
  int num_dim_;

  // END MEMBER VARIABLES

  // START PRIVATE METHODS

  /*
   * Throws an exception if x and y aren't equal, as in if the number of dimensions doesn't
   * match between LHS and RHS
   */
  static void CheckDimMatches(int x, int y);

  /*
   * Both operator+= and operator-= are essential the same so they can both call same underlying
   * method
   */
  EuclideanVector& OperatorAddSubEquals(const EuclideanVector& rhs, bool add);

  /*
   * Both operator+ and operator- are essential the same so they can both call same underlying
   * method
   */
  friend EuclideanVector
  OperatorAddSub(const EuclideanVector& lhs, const EuclideanVector& rhs, bool add);

  /*
   * As scalar multiplication can happen in either order it is simpler to put functionality
   * into a separate method that both can use
   */
  friend EuclideanVector OperatorMultiScalar(const EuclideanVector& lhs, int scalar) noexcept;

  // END PRIVATE METHODS
};

#endif  // ASSIGNMENTS_EV_EUCLIDEAN_VECTOR_H_
