#ifndef ASSIGNMENTS_EV_EUCLIDEAN_VECTOR_H_
#define ASSIGNMENTS_EV_EUCLIDEAN_VECTOR_H_

#include <exception>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <list>

class EuclideanVectorError : public std::exception {
 public:
  explicit EuclideanVectorError(const std::string& what) : what_(what) {}
  const char* what() const noexcept { return what_.c_str(); }

 private:
  std::string what_;
};

class EuclideanVector {
 public:
  // Constructors
  EuclideanVector() noexcept : EuclideanVector{1} {}
  explicit EuclideanVector(const int i) noexcept : EuclideanVector{i, 0.0} {}
  EuclideanVector(int i, double m) noexcept;
  EuclideanVector(std::vector<double>::const_iterator b, std::vector<double>::const_iterator e) noexcept;
  // Copy constructor
  EuclideanVector(const EuclideanVector& original) noexcept;
  // Move constructor
  EuclideanVector(EuclideanVector&& original) noexcept;

  // Destructor
  ~EuclideanVector() noexcept = default;

  // Operators
  EuclideanVector& operator=(const EuclideanVector& original) noexcept;
  EuclideanVector& operator=(EuclideanVector&& original) noexcept;
  double operator[](int i) const;
  double& operator[](int i);
  EuclideanVector& operator+=(const EuclideanVector& rhs);
  EuclideanVector& operator-=(const EuclideanVector& rhs);
  EuclideanVector& operator*=(int scalar) noexcept;
  EuclideanVector& operator/=(int scalar);
  explicit operator std::vector<double>() noexcept;
  explicit operator std::list<double>() noexcept;

  // Methods
  double at(int i) const;
  double& at(int i);
  int GetNumDimensions() const noexcept;
  double GetEuclideanNorm() const;
  EuclideanVector CreateUnitVector();

  // Friends
  //==
  //!=
  friend EuclideanVector operator+(const EuclideanVector& lhs, const EuclideanVector& rhs);
  friend EuclideanVector operator-(const EuclideanVector& lhs, const EuclideanVector& rhs);
  friend double operator*(const EuclideanVector& lhs, const EuclideanVector& rhs);
  friend EuclideanVector operator*(const EuclideanVector& lhs, int scalar) noexcept;
  friend EuclideanVector operator*(int scalar, const EuclideanVector& lhs) noexcept;
  friend std::ostream& operator<<(std::ostream& os, const EuclideanVector& v);

 private:
  std::unique_ptr<double[]> magnitudes_;
  int num_dim_;

  friend void CheckDimMatches(int x, int y);
  EuclideanVector& OperatorAddSubEquals(const EuclideanVector& rhs, bool add);
  friend EuclideanVector OperatorAddSub(const EuclideanVector& lhs, const EuclideanVector& rhs, bool add);
  friend EuclideanVector OperatorMultiScalar(const EuclideanVector& lhs, int scalar) noexcept;
};

#endif  // ASSIGNMENTS_EV_EUCLIDEAN_VECTOR_H_
