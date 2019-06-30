#include "assignments/ev/euclidean_vector.h"

#include <algorithm>  // Look at these - they are helpful https://en.cppreference.com/w/cpp/algorithm


EuclideanVector::EuclideanVector(int i, double m): magnitudes_{std::make_unique<double[]>(i)}, num_dim_{i} {
  for(int j = 0; j < num_dim_; j++) {
    magnitudes_[j] = m;
  }
}

EuclideanVector::EuclideanVector(std::vector<double>::const_iterator b, std::vector<double>::const_iterator e) {
  num_dim_ = std::distance(b, e);
  magnitudes_ = std::make_unique<double[]>(num_dim_);

  int i = 0;
  for (auto it = b; it != e; ++it, ++i) {
    magnitudes_[i] = *it;
  }
}

EuclideanVector::EuclideanVector(const EuclideanVector& original)
    : magnitudes_{std::make_unique<double[]>(original.GetNumDimensions())}, num_dim_{original.GetNumDimensions()} {
  for(int j = 0; j < num_dim_; j++) {
    magnitudes_[j] = original.magnitudes_[j];
  }
}

// What happens when the dimensions arent equal
EuclideanVector& EuclideanVector::operator=(const EuclideanVector& original) {
  for(int j = 0; j < num_dim_; j++) {
    magnitudes_[j] = original.magnitudes_[j];
  }
  return *this;
}

int EuclideanVector::GetNumDimensions() const {
  return num_dim_;
}

std::ostream& operator<<(std::ostream& os, const EuclideanVector& v) {
  os << "[" << v.GetNumDimensions() << "," << "]";
  return os;
}
