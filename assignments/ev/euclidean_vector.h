// TODO(you): Include header guards

#include <exception>
#include <string>
#include <memory>
#include <vector>

class EuclideanVectorError : public std::exception {
 public:
  explicit EuclideanVectorError(const std::string& what) : what_(what) {}
  const char* what() const noexcept{ return what_.c_str(); }
 private:
  std::string what_;
};

class EuclideanVector {
 public:
  EuclideanVector(): EuclideanVector{1} {}
  explicit EuclideanVector(int i): EuclideanVector{i, 0.0} {}
  EuclideanVector(int i, double m);
  EuclideanVector(std::vector<double>::const_iterator b, std::vector<double>::const_iterator e);
  friend std::ostream& operator<<(std::ostream& os, const EuclideanVector& v);
 private:
  std::unique_ptr<double[]> magnitudes_;
  int num_dim_;
};
