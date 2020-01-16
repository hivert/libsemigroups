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

#include "catch.hpp"      // for TEST_CASE
#include "order.hpp"      // for shortlex_words
#include "report.hpp"     // for ReportGuard
#include "test-main.hpp"  // for LIBSEMIGROUPS_TEST_CASE
#include "types.hpp"      // for word_type

namespace libsemigroups {

  constexpr bool REPORT = false;

  LIBSEMIGROUPS_TEST_CASE("shortlex_words",
                          "000",
                          "shortlex_words",
                          "[quick]") {
    auto rg = ReportGuard(REPORT);
    REQUIRE(
        shortlex_words(2, 2)
        == std::vector<word_type>({{0}, {1}, {0, 0}, {0, 1}, {1, 0}, {1, 1}}));
    REQUIRE(shortlex_words(2, 2, 2)
            == std::vector<word_type>({{0, 0}, {0, 1}, {1, 0}, {1, 1}}));
  }

}  // namespace libsemigroups
