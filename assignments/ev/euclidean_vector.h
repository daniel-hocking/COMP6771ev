// TODO(you): Include header guards

#include <exception>
#include <string>
#include <memory>
#include <vector>
#include <iostream>

class EuclideanVectorError : public std::exception {
 public:
  explicit EuclideanVectorError(const std::string& what) : what_(what) {}
  const char* what() const noexcept{ return what_.c_str(); }
 private:
  std::string what_;
};

class EuclideanVector {
 public:
  // Constructors
  EuclideanVector(): EuclideanVector{1} {}
  explicit EuclideanVector(int i): EuclideanVector{i, 0.0} {}
  EuclideanVector(int i, double m);
  EuclideanVector(std::vector<double>::const_iterator b, std::vector<double>::const_iterator e);
  // Copy constructor
  EuclideanVector(const EuclideanVector& original) noexcept;
  // Move constructor
  EuclideanVector(EuclideanVector&& original) noexcept: magnitudes_{std::move(original.magnitudes_)}, num_dim_{std::move(original.num_dim_)} {}

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