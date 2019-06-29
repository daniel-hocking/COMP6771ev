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