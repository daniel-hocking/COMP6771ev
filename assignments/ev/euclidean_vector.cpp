#include "assignments/ev/euclidean_vector.h"

#include <algorithm>  // Look at these - they are helpful https://en.cppreference.com/w/cpp/algorithm
#include <cmath>


EuclideanVector::EuclideanVector(int i, double m): magnitudes_{std::make_unique<double[]>(i)}, num_dim_{i} {
  for(int j = 0; j < this->GetNumDimensions(); j++) {
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
  for(int j = 0; j < this->GetNumDimensions(); j++) {
    magnitudes_[j] = original.magnitudes_[j];
  }
}

// What happens when the dimensions arent equal
EuclideanVector& EuclideanVector::operator=(const EuclideanVector& original) {
  for(int j = 0; j < this->GetNumDimensions(); j++) {
    magnitudes_[j] = original.magnitudes_[j];
  }
  return *this;
}

double EuclideanVector::at(int i) const {
  if (i < 0 || i >= this->GetNumDimensions()) {
    throw EuclideanVectorError{std::string{"Index "} + std::to_string(i) + std::string{" is not valid for this EuclideanVector object"}};
  }
  return magnitudes_[i];
}

int EuclideanVector::GetNumDimensions() const {
  return num_dim_;
}

double EuclideanVector::GetEuclideanNorm() const {
  if(this->GetNumDimensions() == 0) {
    throw EuclideanVectorError{"EuclideanVector with no dimensions does not have a norm"};
  }
  double sums = 0;
  for(int j = 0; j < this->GetNumDimensions(); j++) {
    sums += magnitudes_[j] * magnitudes_[j];
  }
  return std::sqrt(sums);
}

EuclideanVector EuclideanVector::CreateUnitVector() {
  if(this->GetNumDimensions() == 0) {
    throw EuclideanVectorError{"EuclideanVector with no dimensions does not have a unit vector"};
  }
  double euclidean_norm = this->GetEuclideanNorm();
  // Is this comparison valid?
  if(euclidean_norm == 0.0) {
    throw EuclideanVectorError{"EuclideanVector with euclidean normal of 0 does not have a unit vector"};
  }

  auto unit_vector = std::vector<double>{};
  for(int j = 0; j < this->GetNumDimensions(); j++) {
    unit_vector.emplace_back(this->at(j) / euclidean_norm);
  }

  EuclideanVector e{unit_vector.begin(), unit_vector.end()};
  return e;
}

std::ostream& operator<<(std::ostream& os, const EuclideanVector& v) {
  os << "[";
  if (v.GetNumDimensions() > 0) {
    for(int j = 0; j < v.GetNumDimensions(); j++) {
      if(j > 0) {
        os << " ";
      }
      os << v.at(j);
    }
  }
  os << "]";
  return os;
}
