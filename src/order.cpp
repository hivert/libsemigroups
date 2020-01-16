//
// libsemigroups - C++ library for semigroups and monoids
// Copyright (C) 2019 James D. Mitchell
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

// This file contains some functionality missing in some implementations of the
// stl, or to augment the stl implementations.

#include "order.hpp"

#include "types.hpp"  // for word_type
#include <vector>     // for vector

namespace libsemigroups {
  std::vector<word_type> shortlex_words(size_t nr_gens,
                                        size_t minlen,
                                        size_t maxlen) {
    std::vector<word_type> out;
    size_t                 cut = 0;
    for (size_t i = 0; i < nr_gens; ++i) {
      out.push_back({i});
    }
    size_t frst = 0;
    size_t last = nr_gens;
    for (size_t i = 2; i <= maxlen; ++i) {
      for (size_t j = frst; j < last; ++j) {
        for (size_t k = 0; k < nr_gens; ++k) {
          word_type nxt = out.at(j);
          nxt.push_back(k);
          out.push_back(nxt);
        }
      }
      if (i == minlen) {
        cut = last;
      }
      frst = last;
      last = out.size();
    }
    out.erase(out.begin(), out.begin() + cut);
    return out;
  }
}  // namespace libsemigroups
