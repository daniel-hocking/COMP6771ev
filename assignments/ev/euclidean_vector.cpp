#include "assignments/ev/euclidean_vector.h"

#include <algorithm>  // Look at these - they are helpful https://en.cppreference.com/w/cpp/algorithm
#include <cassert>
#include <cmath>
#include <utility>

EuclideanVector::EuclideanVector(const int i, const double m) noexcept
  : magnitudes_{std::make_unique<double[]>(i)}, num_dim_{i} {
  for (int j = 0; j < this->GetNumDimensions(); j++) {
    magnitudes_[j] = m;
  }
}

EuclideanVector::EuclideanVector(std::vector<double>::const_iterator b,
                                 std::vector<double>::const_iterator e) noexcept {
  num_dim_ = std::distance(b, e);
  magnitudes_ = std::make_unique<double[]>(num_dim_);

  int i = 0;
  for (auto it = b; it != e; ++it, ++i) {
    magnitudes_[i] = *it;
  }
}

EuclideanVector::EuclideanVector(const EuclideanVector& original) noexcept
  : magnitudes_{std::make_unique<double[]>(original.GetNumDimensions())},
    num_dim_{original.GetNumDimensions()} {
  for (int j = 0; j < this->GetNumDimensions(); j++) {
    magnitudes_[j] = original[j];
  }
}

EuclideanVector& EuclideanVector::operator=(const EuclideanVector& original) noexcept {
  num_dim_ = original.GetNumDimensions();
  magnitudes_ = std::make_unique<double[]>(this->GetNumDimensions());

  for (int j = 0; j < this->GetNumDimensions(); j++) {
    magnitudes_[j] = original[j];
  }

  return *this;
}

EuclideanVector& EuclideanVector::operator=(EuclideanVector&& original) noexcept {
  num_dim_ = original.GetNumDimensions();
  magnitudes_ = std::move(original.magnitudes_);
  original.num_dim_ = 0;

  return *this;
}

double EuclideanVector::operator[](const int i) const {
  assert(i >= 0);
  assert(i < this->GetNumDimensions());

  return magnitudes_[i];
}

double& EuclideanVector::operator[](const int i) {
  assert(i >= 0);
  assert(i < this->GetNumDimensions());

  return magnitudes_[i];
}

EuclideanVector& EuclideanVector::OperatorAddSubEquals(const EuclideanVector& rhs, const bool add) {
  EuclideanVector::CheckDimMatches(this->GetNumDimensions(), rhs.GetNumDimensions());

  for (int j = 0; j < this->GetNumDimensions(); j++) {
    if (add) {
      magnitudes_[j] += rhs[j];
    } else {
      magnitudes_[j] -= rhs[j];
    }
  }

  return *this;
}

EuclideanVector& EuclideanVector::operator*=(const double scalar) noexcept {
  for (int j = 0; j < this->GetNumDimensions(); j++) {
    magnitudes_[j] *= scalar;
  }

  return *this;
}

EuclideanVector& EuclideanVector::operator/=(const double scalar) {
  if (scalar == 0.0) {
    throw EuclideanVectorError{"Invalid vector division by 0"};
  }

  for (int j = 0; j < this->GetNumDimensions(); j++) {
    magnitudes_[j] /= scalar;
  }

  return *this;
}

EuclideanVector::operator std::vector<double>() const noexcept {
  auto vector_ev = std::vector<double>();

  for (int j = 0; j < this->GetNumDimensions(); j++) {
    vector_ev.emplace_back(magnitudes_[j]);
  }

  return vector_ev;
}

EuclideanVector::operator std::list<double>() const noexcept {
  auto list_ev = std::list<double>();

  for (int j = 0; j < this->GetNumDimensions(); j++) {
    list_ev.emplace_back(magnitudes_[j]);
  }

  return list_ev;
}

double EuclideanVector::at(const int i) const {
  if (i < 0 || i >= this->GetNumDimensions()) {
    throw EuclideanVectorError{std::string("Index ") + std::to_string(i) +
                               std::string(" is not valid for this EuclideanVector object")};
  }

  return magnitudes_[i];
}

double& EuclideanVector::at(const int i) {
  if (i < 0 || i >= this->GetNumDimensions()) {
    throw EuclideanVectorError{std::string("Index ") + std::to_string(i) +
                               std::string(" is not valid for this EuclideanVector object")};
  }

  return magnitudes_[i];
}

double EuclideanVector::GetEuclideanNorm() const {
  if (this->GetNumDimensions() == 0) {
    throw EuclideanVectorError{"EuclideanVector with no dimensions does not have a norm"};
  }

  double sums = 0;
  for (int j = 0; j < this->GetNumDimensions(); j++) {
    sums += magnitudes_[j] * magnitudes_[j];
  }

  return std::sqrt(sums);
}

EuclideanVector EuclideanVector::CreateUnitVector() const {
  if (this->GetNumDimensions() == 0) {
    throw EuclideanVectorError{"EuclideanVector with no dimensions does not have a unit vector"};
  }

  double euclidean_norm = this->GetEuclideanNorm();
  if (euclidean_norm == 0.0) {
    throw EuclideanVectorError{
        "EuclideanVector with euclidean normal of 0 does not have a unit vector"};
  }

  auto unit_vector = std::vector<double>{};
  for (int j = 0; j < this->GetNumDimensions(); j++) {
    unit_vector.emplace_back(this->at(j) / euclidean_norm);
  }

  EuclideanVector e{unit_vector.begin(), unit_vector.end()};

  return e;
}

EuclideanVector OperatorAddSub(const EuclideanVector& lhs, const EuclideanVector& rhs, bool add) {
  EuclideanVector::CheckDimMatches(lhs.GetNumDimensions(), rhs.GetNumDimensions());

  EuclideanVector ev(lhs.GetNumDimensions());
  for (int j = 0; j < ev.GetNumDimensions(); j++) {
    if (add) {
      ev[j] = lhs[j] + rhs[j];
    } else {
      ev[j] = lhs[j] - rhs[j];
    }
  }

  return ev;
}

EuclideanVector OperatorMultiScalar(const EuclideanVector& lhs, const double scalar) noexcept {
  EuclideanVector ev = lhs;
  for (int j = 0; j < ev.GetNumDimensions(); j++) {
    ev.magnitudes_[j] *= scalar;
  }

  return ev;
}

void EuclideanVector::CheckDimMatches(const int x, const int y) {
  if (x != y) {
    throw EuclideanVectorError{std::string("Dimensions of LHS(") + std::to_string(x) +
                               std::string(") and RHS(") + std::to_string(y) +
                               std::string(") do not match")};
  }
}
