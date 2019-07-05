#ifndef ASSIGNMENTS_EV_EUCLIDEAN_VECTOR_H_
#define ASSIGNMENTS_EV_EUCLIDEAN_VECTOR_H_

#include <exception>
#include <iostream>
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
  // Constructors
  EuclideanVector() : EuclideanVector{1} {}
  explicit EuclideanVector(int i) : EuclideanVector{i, 0.0} {}
  EuclideanVector(int i, double m);
  EuclideanVector(std::vector<double>::const_iterator b, std::vector<double>::const_iterator e);
  // Copy constructor
  EuclideanVector(const EuclideanVector& original) noexcept;
  // Move constructor
  EuclideanVector(EuclideanVector&& original) noexcept = default;

  // Copy assignment
  EuclideanVector& operator=(const EuclideanVector& original);

  // Destructor
  ~EuclideanVector() noexcept = default;

  // Methods
  double at(int i) const;
  int GetNumDimensions() const;
  double GetEuclideanNorm() const;
  EuclideanVector CreateUnitVector();
  bool MovedObject() const noexcept;

  friend std::ostream& operator<<(std::ostream& os, const EuclideanVector& v);

 private:
  std::unique_ptr<double[]> magnitudes_;
  int num_dim_;
};

#endif  // ASSIGNMENTS_EV_EUCLIDEAN_VECTOR_H_
