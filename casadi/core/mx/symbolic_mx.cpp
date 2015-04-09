/*
 *    This file is part of CasADi.
 *
 *    CasADi -- A symbolic framework for dynamic optimization.
 *    Copyright (C) 2010-2014 Joel Andersson, Joris Gillis, Moritz Diehl,
 *                            K.U. Leuven. All rights reserved.
 *    Copyright (C) 2011-2014 Greg Horn
 *
 *    CasADi is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License as published by the Free Software Foundation; either
 *    version 3 of the License, or (at your option) any later version.
 *
 *    CasADi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with CasADi; if not, write to the Free Software
 *    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */


#include "symbolic_mx.hpp"
#include "../std_vector_tools.hpp"

using namespace std;

namespace casadi {

  SymbolicMX::SymbolicMX(const std::string& name, int nrow, int ncol) : name_(name) {
    setSparsity(Sparsity::dense(nrow, ncol));
  }

  SymbolicMX::SymbolicMX(const std::string& name, const Sparsity & sp) : name_(name) {
    setSparsity(sp);
  }

  SymbolicMX* SymbolicMX::clone() const {
    return new SymbolicMX(*this);
  }

  void SymbolicMX::printPart(std::ostream &stream, int part) const {
    stream << name_;
  }

  void SymbolicMX::evalD(cp_double* input, p_double* output,
                             int* itmp, double* rtmp) {
  }

  void SymbolicMX::evalSX(cp_SXElement* input, p_SXElement* output,
                              int* itmp, SXElement* rtmp) {
  }

  void SymbolicMX::evalMX(const std::vector<MX>& arg, std::vector<MX>& res) {
  }

  void SymbolicMX::evalFwd(const std::vector<std::vector<MX> >& fseed,
                           std::vector<std::vector<MX> >& fsens) {
  }

  void SymbolicMX::evalAdj(const std::vector<std::vector<MX> >& aseed,
                           std::vector<std::vector<MX> >& asens) {
  }

  const std::string& SymbolicMX::getName() const {
    return name_;
  }

  void SymbolicMX::spFwd(cp_bvec_t* arg,
                         p_bvec_t* res, int* itmp, bvec_t* rtmp) {
    fill_n(res[0], nnz(), 0);
  }

  void SymbolicMX::spAdj(p_bvec_t* arg,
                         p_bvec_t* res, int* itmp, bvec_t* rtmp) {
    fill_n(res[0], nnz(), 0);
  }

  void SymbolicMX::splitPrimitives(const MX& x, std::vector<MX>::iterator& it) const {
    *it++ = x;
  }

  MX SymbolicMX::joinPrimitives(std::vector<MX>::const_iterator& it) const {
    MX ret = *it++;
    if (ret.shape()==shape()) {
      return ret;
    } else {
      casadi_assert(ret.isEmpty(true));
      return MX(shape());
    }
  }

  bool SymbolicMX::hasDuplicates() {
    if (this->temp!=0) {
      cerr << "Duplicate expression: " << getName() << endl;
      return true;
    } else {
      this->temp = 1;
      return false;
    }
  }

  void SymbolicMX::resetInput() {
    this->temp = 0;
  }

  void SymbolicMX::getPrimitives(std::vector<MXNode*>& v) {
    v.push_back(this);
  }

} // namespace casadi
