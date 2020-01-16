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

// The purpose of this file is to provide unit tests for the FpSemigroup class.

#include "catch.hpp"              // for LIBSEMIGROUPS_TEST_CASE
#include "element-helper.hpp"     // for Transf, Transf<>::type
#include "element.hpp"            // for Transf, Transf<>::type
#include "fpsemi-examples.hpp"    // for RennerTypeDMonoid, RennerTypeBMonoid
#include "fpsemi.hpp"             // for FpSemigroup
#include "froidure-pin-base.hpp"  // for FroidurePinBase
#include "froidure-pin.hpp"       // for FroidurePin<>::element_index_type
#include "knuth-bendix.hpp"       // for KnuthBendix
#include "report.hpp"             // for ReportGuard
#include "string.hpp"             // for printing relations
#include "test-main.hpp"
#include "todd-coxeter.hpp"  // for ToddCoxeter
#include "types.hpp"         // for relation_type

namespace libsemigroups {

  constexpr bool REPORT = false;

  constexpr congruence_type twosided = congruence_type::twosided;

  LIBSEMIGROUPS_TEST_CASE("FpSemigroup",
                          "001",
                          "Renner monoid type B2 (E. G. presentation), q = 1",
                          "[quick][fpsemi][hivert]") {
    auto        rg = ReportGuard(REPORT);
    FpSemigroup S;
    S.set_alphabet(6);

    for (relation_type const& rl : EGTypeBMonoid(2, 1)) {
      S.add_rule(rl);
    }
    REQUIRE(!S.is_obviously_infinite());
    REQUIRE(!S.is_obviously_finite());
    REQUIRE(!S.started());
    REQUIRE(!S.finished());
    REQUIRE(S.has_knuth_bendix());
    REQUIRE(S.has_todd_coxeter());
    REQUIRE(S.size() == 57);
    REQUIRE(S.started());
    REQUIRE(S.finished());
    REQUIRE(S.is_obviously_finite());
    if (!S.has_knuth_bendix()) {
      REQUIRE(S.has_todd_coxeter());
    } else {
      REQUIRE(S.has_knuth_bendix());
    }
  }

  LIBSEMIGROUPS_TEST_CASE("FpSemigroup",
                          "002",
                          "Renner monoid type B2 (E. G. presentation), q = 0",
                          "[quick][fpsemi][hivert]") {
    auto        rg = ReportGuard(REPORT);
    FpSemigroup S;
    S.set_alphabet(6);
    for (relation_type const& rl : EGTypeBMonoid(2, 0)) {
      S.add_rule(rl);
    }
    REQUIRE(!S.is_obviously_infinite());
    REQUIRE(!S.is_obviously_finite());
    REQUIRE(S.size() == 57);
    REQUIRE(S.is_obviously_finite());
  }

  // Loops for ever: Infinite monoid ???
  LIBSEMIGROUPS_TEST_CASE("FpSemigroup",
                          "003",
                          "Renner monoid type B3 (E. G. presentation), q = 1",
                          "[quick][fpsemi][hivert][no-valgrind]") {
    auto        rg = ReportGuard(REPORT);
    FpSemigroup S;
    S.set_alphabet(8);
    for (relation_type const& rl : EGTypeBMonoid(3, 1)) {
      S.add_rule(rl);
    }
    REQUIRE(!S.is_obviously_infinite());
    REQUIRE(!S.is_obviously_finite());
    S.froidure_pin()->enumerate(8000);
    REQUIRE(S.froidure_pin()->current_size() == 8200);
    REQUIRE(S.started());
    // REQUIRE(S.size() == 757);
  }

  // Loops for ever: Infinite monoid ???
  LIBSEMIGROUPS_TEST_CASE("FpSemigroup",
                          "004",
                          "Renner monoid type B3 (E. G. presentation), q = 0",
                          "[quick][fpsemi][hivert][no-valgrind]") {
    auto        rg = ReportGuard(REPORT);
    FpSemigroup S;
    S.set_alphabet(8);
    for (relation_type const& rl : EGTypeBMonoid(3, 0)) {
      S.add_rule(rl);
    }
    REQUIRE(!S.is_obviously_infinite());
    S.froidure_pin()->enumerate(8000);
    REQUIRE(S.froidure_pin()->current_size() == 8200);
    // REQUIRE(S.size() == 757);
  }

  LIBSEMIGROUPS_TEST_CASE(
      "FpSemigroup",
      "005",
      "Renner monoid type B2 (Gay-Hivert presentation), q = 1",
      "[quick][fpsemi][hivert]") {
    auto        rg = ReportGuard(REPORT);
    FpSemigroup S;
    S.set_alphabet(6);
    for (relation_type const& rl : RennerTypeBMonoid(2, 1)) {
      S.add_rule(rl);
    }
    REQUIRE(!S.is_obviously_infinite());
    S.run();
    REQUIRE(S.finished());
    REQUIRE(S.size() == 57);
  }

  LIBSEMIGROUPS_TEST_CASE(
      "FpSemigroup",
      "006",
      "Renner monoid type B2 (Gay-Hivert presentation), q = 0",
      "[quick][fpsemi][hivert]") {
    auto        rg = ReportGuard(REPORT);
    FpSemigroup S;
    S.set_alphabet(6);
    for (relation_type const& rl : RennerTypeBMonoid(2, 0)) {
      S.add_rule(rl);
    }
    REQUIRE(!S.is_obviously_infinite());
    REQUIRE(S.size() == 57);
  }

  LIBSEMIGROUPS_TEST_CASE(
      "FpSemigroup",
      "007",
      "Renner monoid type B3 (Gay-Hivert presentation), q = 1",
      "[quick][fpsemi][hivert][no-valgrind]") {
    auto        rg = ReportGuard(REPORT);
    FpSemigroup S;
    S.set_alphabet(8);
    for (relation_type const& rl : RennerTypeBMonoid(3, 1)) {
      S.add_rule(rl);
    }
    REQUIRE(!S.is_obviously_infinite());
    REQUIRE(S.size() == 757);
  }

  LIBSEMIGROUPS_TEST_CASE(
      "FpSemigroup",
      "008",
      "Renner monoid type B3 (Gay-Hivert presentation), q = 0",
      "[quick][fpsemi][hivert][no-valgrind]") {
    auto        rg = ReportGuard(REPORT);
    FpSemigroup S;
    S.set_alphabet(8);
    for (relation_type const& rl : RennerTypeBMonoid(3, 0)) {
      S.add_rule(rl);
    }
    REQUIRE(!S.is_obviously_infinite());
    REQUIRE(S.size() == 757);
  }

  LIBSEMIGROUPS_TEST_CASE(
      "FpSemigroup",
      "009",
      "Renner monoid type B4 (Gay-Hivert presentation), q = 1",
      "[quick][fpsemi][hivert][no-valgrind]") {
    auto        rg = ReportGuard(REPORT);
    FpSemigroup S;
    S.set_alphabet(10);
    for (relation_type const& rl : RennerTypeBMonoid(4, 1)) {
      S.add_rule(rl);
    }
    REQUIRE(S.nr_rules() == 110);
    REQUIRE(!S.is_obviously_infinite());
    REQUIRE(!S.knuth_bendix()->confluent());
    // S.knuth_bendix()->run(); // Works too but is slower :)
    REQUIRE(S.size() == 13889);
    REQUIRE(S.froidure_pin()->nr_rules() == 356);
  }

  LIBSEMIGROUPS_TEST_CASE(
      "FpSemigroup",
      "010",
      "Renner monoid type B4 (Gay-Hivert presentation), q = 0",
      "[quick][fpsemi][hivert][no-valgrind]") {
    auto        rg = ReportGuard(REPORT);
    FpSemigroup S;
    S.set_alphabet(10);
    for (relation_type const& rl : RennerTypeBMonoid(4, 0)) {
      S.add_rule(rl);
    }
    REQUIRE(S.nr_rules() == 110);
    REQUIRE(!S.is_obviously_infinite());
    REQUIRE(!S.knuth_bendix()->confluent());
    // S.knuth_bendix()->run(); // Works too :)
    REQUIRE(S.size() == 13889);
    REQUIRE(S.froidure_pin()->nr_rules() == 356);
  }

  // This appears to be an example where KB + FP is faster than TC
  LIBSEMIGROUPS_TEST_CASE(
      "FpSemigroup",
      "011",
      "Renner monoid type B5 (Gay-Hivert presentation), q = 1",
      "[extreme][fpsemi][hivert]") {
    auto        rg = ReportGuard(true);
    FpSemigroup S;
    S.set_alphabet(12);
    for (relation_type const& rl : RennerTypeBMonoid(5, 1)) {
      S.add_rule(rl);
    }
    REQUIRE(S.nr_rules() == 159);
    REQUIRE(!S.is_obviously_infinite());
    REQUIRE(!S.knuth_bendix()->confluent());
    // S.todd_coxeter()->run(); // Takes 2m30s or so to run
    REQUIRE(S.size() == 322021);
    REQUIRE(S.froidure_pin()->nr_rules() == 1453);
    {
      congruence::ToddCoxeter tc(
          twosided,
          S.froidure_pin(),
          congruence::ToddCoxeter::policy::froidure_pin::use_cayley_graph);
      REQUIRE(tc.nr_classes() == 322021);  // Works!
    }
    {
      fpsemigroup::ToddCoxeter tc(S.froidure_pin());
      REQUIRE(tc.nr_rules() == 1453);
      REQUIRE(tc.size() == 322021);  // Runs forever
    }
  }

  LIBSEMIGROUPS_TEST_CASE(
      "FpSemigroup",
      "012",
      "Renner monoid type B5 (Gay-Hivert presentation), q = 0",
      "[extreme][fpsemi][hivert]") {
    auto        rg = ReportGuard(true);
    FpSemigroup S;
    S.set_alphabet(12);
    for (relation_type const& rl : RennerTypeBMonoid(5, 0)) {
      S.add_rule(rl);
    }
    REQUIRE(S.nr_rules() == 159);
    REQUIRE(!S.is_obviously_infinite());
    REQUIRE(!S.knuth_bendix()->confluent());
    // Doesn't terminate, or show signs that it will, in 5 minutes or so
    // S.todd_coxeter()->run();
    REQUIRE(S.size() == 322021);
    REQUIRE(S.froidure_pin()->nr_rules() == 1453);

    congruence::ToddCoxeter tc(
        twosided,
        S.froidure_pin(),
        congruence::ToddCoxeter::policy::froidure_pin::use_cayley_graph);
    REQUIRE(tc.nr_classes() == 322021);  // Works!
  }

  LIBSEMIGROUPS_TEST_CASE("FpSemigroup",
                          "013",
                          "Renner monoid type D2 (E. G. presentation), q = 1",
                          "[quick][fpsemi][hivert]") {
    auto        rg = ReportGuard(REPORT);
    FpSemigroup S;
    S.set_alphabet(7);
    for (relation_type const& rl : EGTypeDMonoid(2, 1)) {
      S.add_rule(rl);
    }
    REQUIRE(S.nr_rules() == 44);
    REQUIRE(!S.is_obviously_infinite());
    REQUIRE(!S.knuth_bendix()->confluent());
    // S.knuth_bendix()->run(); // Works too :)
    REQUIRE(S.size() == 37);
    REQUIRE(S.froidure_pin()->nr_rules() == 54);
  }

  LIBSEMIGROUPS_TEST_CASE("FpSemigroup",
                          "014",
                          "Renner monoid type D2 (E. G. presentation), q = 0",
                          "[quick][fpsemi][hivert]") {
    auto        rg = ReportGuard(REPORT);
    FpSemigroup S;
    S.set_alphabet(7);
    for (relation_type const& rl : EGTypeDMonoid(2, 0)) {
      S.add_rule(rl);
    }
    REQUIRE(S.nr_rules() == 44);
    REQUIRE(!S.is_obviously_infinite());
    REQUIRE(!S.knuth_bendix()->confluent());
    // S.knuth_bendix()->run(); // Works too :)
    REQUIRE(S.size() == 37);
    REQUIRE(S.froidure_pin()->nr_rules() == 54);
  }

  LIBSEMIGROUPS_TEST_CASE("FpSemigroup",
                          "015",
                          "Renner monoid type D3 (E. G. presentation), q = 1",
                          "[quick][fpsemi][hivert][no-valgrind]") {
    auto        rg = ReportGuard(REPORT);
    FpSemigroup S;
    S.set_alphabet(9);
    for (relation_type const& rl : EGTypeDMonoid(3, 1)) {
      S.add_rule(rl);
    }
    REQUIRE(S.nr_rules() == 78);
    REQUIRE(!S.is_obviously_infinite());
    REQUIRE(!S.knuth_bendix()->confluent());
    // S.knuth_bendix()->run(); // Works too but is a bit slower :)
    REQUIRE(S.size() == 541);
    REQUIRE(S.froidure_pin()->nr_rules() == 148);
  }

  LIBSEMIGROUPS_TEST_CASE("FpSemigroup",
                          "016",
                          "Renner monoid type D3 (E. G. presentation), q = 0",
                          "[quick][fpsemi][hivert][no-valgrind]") {
    auto        rg = ReportGuard(REPORT);
    FpSemigroup S;
    S.set_alphabet(9);
    for (relation_type const& rl : EGTypeDMonoid(3, 0)) {
      S.add_rule(rl);
    }
    REQUIRE(S.nr_rules() == 78);
    REQUIRE(!S.is_obviously_infinite());
    REQUIRE(!S.knuth_bendix()->confluent());
    // S.knuth_bendix()->run(); // Works too but is a bit slower :)
    REQUIRE(S.size() == 541);
    REQUIRE(S.froidure_pin()->nr_rules() == 148);
  }

  LIBSEMIGROUPS_TEST_CASE("FpSemigroup",
                          "017",
                          "Renner monoid type D4 (E. G. presentation), q = 1",
                          "[quick][fpsemi][hivert][no-valgrind]") {
    auto        rg = ReportGuard(REPORT);
    FpSemigroup S;
    S.set_alphabet(11);
    for (relation_type const& rl : EGTypeDMonoid(4, 1)) {
      S.add_rule(rl);
    }
    REQUIRE(S.nr_rules() == 119);
    REQUIRE(!S.is_obviously_infinite());
    REQUIRE(!S.knuth_bendix()->confluent());

    S.froidure_pin()->enumerate(10626);
    REQUIRE(S.froidure_pin()->current_nr_rules() == 417);
    REQUIRE(S.froidure_pin()->current_size() == 10626);
    // REQUIRE(S.size() == 10625); // Runs forever
  }

  LIBSEMIGROUPS_TEST_CASE("FpSemigroup",
                          "018",
                          "Renner monoid type D4 (E. G. presentation), q = 0",
                          "[quick][fpsemi][hivert][no-valgrind]") {
    auto        rg = ReportGuard(REPORT);
    FpSemigroup S;
    S.set_alphabet(11);
    for (relation_type const& rl : EGTypeDMonoid(4, 0)) {
      S.add_rule(rl);
    }
    REQUIRE(S.nr_rules() == 119);
    REQUIRE(!S.is_obviously_infinite());
    REQUIRE(!S.knuth_bendix()->confluent());

    S.froidure_pin()->enumerate(10626);
    REQUIRE(S.froidure_pin()->current_nr_rules() == 417);
    REQUIRE(S.froidure_pin()->current_size() == 10626);
    // REQUIRE(S.size() == 10625); // Runs forever
  }

  LIBSEMIGROUPS_TEST_CASE(
      "FpSemigroup",
      "019",
      "Renner monoid type D2 (Gay-Hivert presentation), q = 1",
      "[quick][fpsemi][hivert]") {
    auto        rg = ReportGuard(REPORT);
    FpSemigroup S;
    S.set_alphabet(7);
    for (relation_type const& rl : RennerTypeDMonoid(2, 1)) {
      S.add_rule(rl);
    }
    REQUIRE(S.nr_rules() == 44);
    REQUIRE(!S.is_obviously_infinite());
    REQUIRE(!S.knuth_bendix()->confluent());
    // S.knuth_bendix()->run(); // Works too :)
    REQUIRE(S.size() == 37);
    REQUIRE(S.froidure_pin()->nr_rules() == 54);
  }

  LIBSEMIGROUPS_TEST_CASE(
      "FpSemigroup",
      "020",
      "Renner monoid type D2 (Gay-Hivert presentation), q = 0",
      "[quick][fpsemi][hivert]") {
    auto        rg = ReportGuard(REPORT);
    FpSemigroup S;
    S.set_alphabet(7);
    for (relation_type const& rl : RennerTypeDMonoid(2, 0)) {
      S.add_rule(rl);
    }
    REQUIRE(S.nr_rules() == 44);
    REQUIRE(!S.is_obviously_infinite());
    REQUIRE(!S.knuth_bendix()->confluent());
    // S.knuth_bendix()->run(); // Works too :)
    REQUIRE(S.size() == 37);
    REQUIRE(S.froidure_pin()->nr_rules() == 54);
  }

  LIBSEMIGROUPS_TEST_CASE(
      "FpSemigroup",
      "021",
      "Renner monoid type D3 (Gay-Hivert presentation), q = 1",
      "[quick][fpsemi][hivert][no-valgrind]") {
    auto        rg = ReportGuard(REPORT);
    FpSemigroup S;
    S.set_alphabet(9);
    for (relation_type const& rl : RennerTypeDMonoid(3, 1)) {
      S.add_rule(rl);
    }
    REQUIRE(S.nr_rules() == 78);
    REQUIRE(!S.is_obviously_infinite());
    REQUIRE(!S.knuth_bendix()->confluent());
    // S.knuth_bendix()->run(); // Works too but is a bit slower :)
    REQUIRE(S.size() == 541);
    REQUIRE(S.froidure_pin()->nr_rules() == 148);
  }

  LIBSEMIGROUPS_TEST_CASE(
      "FpSemigroup",
      "022",
      "Renner monoid type D3 (Gay-Hivert presentation), q = 0",
      "[quick][fpsemi][hivert][no-valgrind]") {
    auto        rg = ReportGuard(REPORT);
    FpSemigroup S;
    S.set_alphabet(9);
    for (relation_type const& rl : RennerTypeDMonoid(3, 0)) {
      S.add_rule(rl);
    }
    REQUIRE(S.nr_rules() == 78);
    REQUIRE(!S.is_obviously_infinite());
    REQUIRE(!S.knuth_bendix()->confluent());
    // S.knuth_bendix()->run(); // Works too but is a bit slower :)
    REQUIRE(S.size() == 541);
    REQUIRE(S.froidure_pin()->nr_rules() == 148);
  }

  LIBSEMIGROUPS_TEST_CASE(
      "FpSemigroup",
      "023",
      "Renner monoid type D4 (Gay-Hivert presentation), q = 1",
      "[quick][fpsemi][hivert][no-valgrind]") {
    auto        rg = ReportGuard(REPORT);
    FpSemigroup S;
    S.set_alphabet(11);
    for (relation_type const& rl : RennerTypeDMonoid(4, 1)) {
      S.add_rule(rl);
    }
    REQUIRE(S.nr_rules() == 121);
    REQUIRE(!S.is_obviously_infinite());
    REQUIRE(!S.knuth_bendix()->confluent());

    REQUIRE(S.size() == 10625);
    REQUIRE(S.froidure_pin()->nr_rules() == 419);
  }

  LIBSEMIGROUPS_TEST_CASE(
      "FpSemigroup",
      "024",
      "Renner monoid type D4 (Gay-Hivert presentation), q = 0",
      "[quick][fpsemi][hivert][no-valgrind]") {
    auto        rg = ReportGuard(false);
    FpSemigroup S;
    S.set_alphabet(11);
    for (relation_type const& rl : RennerTypeDMonoid(4, 0)) {
      S.add_rule(rl);
    }
    REQUIRE(S.nr_rules() == 121);
    REQUIRE(!S.is_obviously_infinite());
    REQUIRE(!S.knuth_bendix()->confluent());
    REQUIRE(S.size() == 10625);
    REQUIRE(S.froidure_pin()->nr_rules() == 419);
  }

  LIBSEMIGROUPS_TEST_CASE(
      "FpSemigroup",
      "025",
      "Renner monoid type D5 (Gay-Hivert presentation), q = 1",
      "[extreme][fpsemi][hivert]") {
    auto        rg = ReportGuard(true);
    FpSemigroup S;
    S.set_alphabet(13);
    for (relation_type const& rl : RennerTypeDMonoid(5, 1)) {
      S.add_rule(rl);
    }
    REQUIRE(S.nr_rules() == 173);
    REQUIRE(!S.is_obviously_infinite());
    REQUIRE(!S.knuth_bendix()->confluent());

    REQUIRE(S.size() == 258661);
    REQUIRE(S.froidure_pin()->nr_rules() == 1279);
  }

  LIBSEMIGROUPS_TEST_CASE(
      "FpSemigroup",
      "026",
      "Renner monoid type D5 (Gay-Hivert presentation), q = 0",
      "[extreme][fpsemi][hivert]") {
    auto        rg = ReportGuard(true);
    FpSemigroup S;
    S.set_alphabet(13);
    for (relation_type const& rl : RennerTypeDMonoid(5, 0)) {
      S.add_rule(rl);
    }
    REQUIRE(S.nr_rules() == 173);
    REQUIRE(!S.is_obviously_infinite());
    REQUIRE(!S.knuth_bendix()->confluent());
    REQUIRE(S.size() == 258661);
    REQUIRE(S.froidure_pin()->nr_rules() == 1279);
  }

  // Takes about 4 minutes
  LIBSEMIGROUPS_TEST_CASE(
      "FpSemigroup",
      "027",
      "Renner monoid type D6 (Gay-Hivert presentation), q = 1",
      "[extreme][fpsemi][hivert]") {
    auto        rg = ReportGuard(true);
    FpSemigroup S;
    S.set_alphabet(15);
    for (relation_type const& rl : RennerTypeDMonoid(6, 1)) {
      S.add_rule(rl);
    }
    REQUIRE(S.nr_rules() == 234);
    REQUIRE(!S.is_obviously_infinite());
    REQUIRE(!S.knuth_bendix()->confluent());

    REQUIRE(S.size() == 7464625);
    REQUIRE(S.froidure_pin()->nr_rules() == 4570);
  }

  // Takes about 4 minutes
  LIBSEMIGROUPS_TEST_CASE(
      "FpSemigroup",
      "028",
      "Renner monoid type D6 (Gay-Hivert presentation), q = 0",
      "[extreme][fpsemi][hivert]") {
    auto        rg = ReportGuard(true);
    FpSemigroup S;
    S.set_alphabet(15);
    for (relation_type const& rl : RennerTypeDMonoid(6, 0)) {
      S.add_rule(rl);
    }
    REQUIRE(S.nr_rules() == 234);
    REQUIRE(!S.is_obviously_infinite());
    REQUIRE(!S.knuth_bendix()->confluent());
    S.knuth_bendix()->knuth_bendix_by_overlap_length();
    REQUIRE(S.size() == 7464625);
    REQUIRE(S.froidure_pin()->nr_rules() == 4570);
  }

  LIBSEMIGROUPS_TEST_CASE("FpSemigroup",
                          "029",
                          "Rook monoid R5, q = 0",
                          "[quick][fpsemi][no-valgrind]") {
    auto        rg = ReportGuard(REPORT);
    FpSemigroup S;
    S.set_alphabet(6);
    for (relation_type const& rl : RookMonoid(5, 0)) {
      S.add_rule(rl);
    }
    REQUIRE(S.nr_rules() == 33);
    REQUIRE(!S.is_obviously_infinite());
    REQUIRE(!S.knuth_bendix()->confluent());
    REQUIRE(S.size() == 1546);
    REQUIRE(S.froidure_pin()->nr_rules() == 71);
  }

  LIBSEMIGROUPS_TEST_CASE("FpSemigroup",
                          "030",
                          "Rook monoid R5, q = 1",
                          "[quick][fpsemi][no-valgrind]") {
    auto        rg = ReportGuard(REPORT);
    FpSemigroup S;
    S.set_alphabet(6);
    for (relation_type const& rl : RookMonoid(5, 1)) {
      S.add_rule(rl);
    }
    REQUIRE(S.nr_rules() == 33);
    REQUIRE(!S.is_obviously_infinite());
    REQUIRE(!S.knuth_bendix()->confluent());
    REQUIRE(S.size() == 1546);
    REQUIRE(S.froidure_pin()->nr_rules() == 71);
  }

  LIBSEMIGROUPS_TEST_CASE("FpSemigroup",
                          "031",
                          "Rook monoid R6, q = 0",
                          "[quick][fpsemi][no-valgrind]") {
    auto        rg = ReportGuard(REPORT);
    FpSemigroup S;
    S.set_alphabet(7);
    for (relation_type const& rl : RookMonoid(6, 0)) {
      S.add_rule(rl);
    }
    REQUIRE(S.nr_rules() == 45);
    REQUIRE(!S.is_obviously_infinite());
    REQUIRE(!S.knuth_bendix()->confluent());
    REQUIRE(S.size() == 13327);
    REQUIRE(S.froidure_pin()->nr_rules() == 207);
  }

  LIBSEMIGROUPS_TEST_CASE("FpSemigroup",
                          "032",
                          "Rook monoid R6, q = 1",
                          "[quick][fpsemi][no-valgrind]") {
    auto        rg = ReportGuard(REPORT);
    FpSemigroup S;
    S.set_alphabet(7);
    for (relation_type const& rl : RookMonoid(6, 1)) {
      S.add_rule(rl);
    }
    REQUIRE(S.nr_rules() == 45);
    REQUIRE(!S.is_obviously_infinite());
    REQUIRE(!S.knuth_bendix()->confluent());
    REQUIRE(S.size() == 13327);
    REQUIRE(S.froidure_pin()->nr_rules() == 207);
  }

  LIBSEMIGROUPS_TEST_CASE("FpSemigroup",
                          "033",
                          "normal_form",
                          "[quick][fpsemi]") {
    auto rg = ReportGuard(REPORT);

    FpSemigroup S;
    S.set_alphabet(2);
    S.add_rule(relation_type({0, 0, 0}, {0}));
    S.add_rule(relation_type({0}, {1, 1}));

    REQUIRE(S.size() == 5);

    REQUIRE(S.normal_form({0, 0, 1}) == word_type({0, 0, 1}));
    REQUIRE(S.normal_form({0, 0, 0, 0, 1}) == word_type({0, 0, 1}));
    REQUIRE(S.normal_form({0, 1, 1, 0, 0, 1}) == word_type({0, 0, 1}));
    REQUIRE(S.normal_form({0, 0, 0}) == word_type({0}));
    REQUIRE(S.normal_form({1}) == word_type({1}));
  }

  LIBSEMIGROUPS_TEST_CASE("FpSemigroup",
                          "034",
                          "for a finite semigroup",
                          "[quick][fpsemi]") {
    auto rg = ReportGuard(REPORT);

    using Transf = TransfHelper<5>::type;
    FroidurePin<Transf> S({Transf({1, 3, 4, 2, 3}), Transf({3, 2, 1, 3, 3})});

    REQUIRE(S.size() == 88);
    REQUIRE(S.nr_rules() == 18);

    FpSemigroup T(S);
    T.add_rule(S.factorisation(Transf({3, 4, 4, 4, 4})),
               S.factorisation(Transf({3, 1, 3, 3, 3})));

    REQUIRE(T.size() == 21);
    REQUIRE(T.equal_to(S.factorisation(Transf({1, 3, 1, 3, 3})),
                       S.factorisation(Transf({4, 2, 4, 4, 2}))));
    REQUIRE(T.normal_form(S.factorisation(Transf({1, 3, 1, 3, 3})))
            == T.normal_form(S.factorisation(Transf({4, 2, 4, 4, 2}))));
  }

  LIBSEMIGROUPS_TEST_CASE("FpSemigroup",
                          "035",
                          "finite fp semigroup, dihedral group of order 6",
                          "[quick][fpsemi]") {
    auto        rg = ReportGuard(REPORT);
    FpSemigroup S;
    S.set_alphabet("abcde");
    S.add_rule("aa", "a");
    S.add_rule("ab", "b");
    S.add_rule("ba", "b");
    S.add_rule("ac", "c");
    S.add_rule("ca", "c");
    S.add_rule("ad", "d");
    S.add_rule("da", "d");
    S.add_rule("ae", "e");
    S.add_rule("ea", "e");
    S.add_rule("bc", "a");
    S.add_rule("cb", "a");
    S.add_rule("de", "a");
    S.add_rule("ed", "a");
    S.add_rule("cc", "a");
    S.add_rule("becdd", "a");
    S.add_rule("eee", "a");

    REQUIRE(S.size() == 6);
    REQUIRE(S.equal_to("b", "c"));
  }

  LIBSEMIGROUPS_TEST_CASE("FpSemigroup",
                          "036",
                          "finite fp semigroup, size 16",
                          "[quick][fpsemi][kbfp]") {
    auto        rg = ReportGuard(REPORT);
    FpSemigroup S;
    S.set_alphabet("0123");

    S.add_rule("3", "2");
    S.add_rule("03", "02");
    S.add_rule("11", "1");
    S.add_rule("13", "12");
    S.add_rule("21", "2");
    S.add_rule("22", "2");
    S.add_rule("23", "2");
    S.add_rule("000", "0");
    S.add_rule("001", "1");
    S.add_rule("002", "2");
    S.add_rule("012", "12");
    S.add_rule("100", "1");
    S.add_rule("102", "02");
    S.add_rule("200", "2");
    S.add_rule("0101", "101");
    S.add_rule("0202", "202");
    S.add_rule("1010", "101");
    S.add_rule("1201", "101");
    S.add_rule("1202", "202");
    S.add_rule("2010", "201");
    S.add_rule("2020", "202");

    REQUIRE(S.size() == 16);
    REQUIRE(S.equal_to("2", "3"));
  }

  LIBSEMIGROUPS_TEST_CASE("FpSemigroup",
                          "037",
                          "finite fp semigroup, size 16",
                          "[quick][fpsemi]") {
    auto        rg = ReportGuard(REPORT);
    FpSemigroup S;
    S.set_alphabet(11);

    S.add_rule(relation_type({2}, {1}));
    S.add_rule(relation_type({4}, {3}));
    S.add_rule(relation_type({5}, {0}));
    S.add_rule(relation_type({6}, {3}));
    S.add_rule(relation_type({7}, {1}));
    S.add_rule(relation_type({8}, {3}));
    S.add_rule(relation_type({9}, {3}));
    S.add_rule(relation_type({10}, {0}));
    S.add_rule(relation_type({0, 2}, {0, 1}));
    S.add_rule(relation_type({0, 4}, {0, 3}));
    S.add_rule(relation_type({0, 5}, {0, 0}));
    S.add_rule(relation_type({0, 6}, {0, 3}));
    S.add_rule(relation_type({0, 7}, {0, 1}));
    S.add_rule(relation_type({0, 8}, {0, 3}));
    S.add_rule(relation_type({0, 9}, {0, 3}));
    S.add_rule(relation_type({0, 10}, {0, 0}));
    S.add_rule(relation_type({1, 1}, {1}));
    S.add_rule(relation_type({1, 2}, {1}));
    S.add_rule(relation_type({1, 4}, {1, 3}));
    S.add_rule(relation_type({1, 5}, {1, 0}));
    S.add_rule(relation_type({1, 6}, {1, 3}));
    S.add_rule(relation_type({1, 7}, {1}));
    S.add_rule(relation_type({1, 8}, {1, 3}));
    S.add_rule(relation_type({1, 9}, {1, 3}));
    S.add_rule(relation_type({1, 10}, {1, 0}));
    S.add_rule(relation_type({3, 1}, {3}));
    S.add_rule(relation_type({3, 2}, {3}));
    S.add_rule(relation_type({3, 3}, {3}));
    S.add_rule(relation_type({3, 4}, {3}));
    S.add_rule(relation_type({3, 5}, {3, 0}));
    S.add_rule(relation_type({3, 6}, {3}));
    S.add_rule(relation_type({3, 7}, {3}));
    S.add_rule(relation_type({3, 8}, {3}));
    S.add_rule(relation_type({3, 9}, {3}));
    S.add_rule(relation_type({3, 10}, {3, 0}));
    S.add_rule(relation_type({0, 0, 0}, {0}));
    S.add_rule(relation_type({0, 0, 1}, {1}));
    S.add_rule(relation_type({0, 0, 3}, {3}));
    S.add_rule(relation_type({0, 1, 3}, {1, 3}));
    S.add_rule(relation_type({1, 0, 0}, {1}));
    S.add_rule(relation_type({1, 0, 3}, {0, 3}));
    S.add_rule(relation_type({3, 0, 0}, {3}));
    S.add_rule(relation_type({0, 1, 0, 1}, {1, 0, 1}));
    S.add_rule(relation_type({0, 3, 0, 3}, {3, 0, 3}));
    S.add_rule(relation_type({1, 0, 1, 0}, {1, 0, 1}));
    S.add_rule(relation_type({1, 3, 0, 1}, {1, 0, 1}));
    S.add_rule(relation_type({1, 3, 0, 3}, {3, 0, 3}));
    S.add_rule(relation_type({3, 0, 1, 0}, {3, 0, 1}));
    S.add_rule(relation_type({3, 0, 3, 0}, {3, 0, 3}));

    REQUIRE(S.size() == 16);
    REQUIRE(S.equal_to({0}, {5}));
    REQUIRE(S.equal_to({0}, {10}));
    REQUIRE(S.equal_to({1}, {2}));
    REQUIRE(S.equal_to({1}, {7}));
    REQUIRE(S.equal_to({3}, {4}));
    REQUIRE(S.equal_to({3}, {6}));
    REQUIRE(S.equal_to({3}, {8}));
    REQUIRE(S.equal_to({3}, {9}));
  }

  LIBSEMIGROUPS_TEST_CASE("FpSemigroup",
                          "038",
                          "fp semigroup, size 240",
                          "[quick][fpsemi]") {
    auto        rg = ReportGuard(REPORT);
    FpSemigroup S;
    S.set_alphabet("01");

    S.add_rule("000", "0");
    S.add_rule("1111", "1");
    S.add_rule("01110", "00");
    S.add_rule("1001", "11");
    S.add_rule("001010101010", "00");

    REQUIRE(S.size() == 240);
  }

  LIBSEMIGROUPS_TEST_CASE("FpSemigroup", "039", "add_rule", "[quick][fpsemi]") {
    auto        rg = ReportGuard(REPORT);
    FpSemigroup S;
    S.set_alphabet("ab");
    REQUIRE(S.is_obviously_infinite());
    REQUIRE(S.size() == POSITIVE_INFINITY);
    S.add_rule("aaa", "a");
    S.add_rule("a", "bb");
    REQUIRE(!S.is_obviously_infinite());
    REQUIRE(S.size() == 5);

    auto T = S.froidure_pin();
    REQUIRE(T->size() == 5);
    REQUIRE(T->nr_idempotents() == 1);
  }

  LIBSEMIGROUPS_TEST_CASE("FpSemigroup", "040", "add_rule", "[quick][fpsemi]") {
    auto        rg = ReportGuard(REPORT);
    FpSemigroup S;
    S.set_alphabet("ab");
    REQUIRE(S.is_obviously_infinite());
    S.add_rule("aaa", "a");
    S.add_rule("a", "bb");
    REQUIRE(!S.is_obviously_infinite());
    REQUIRE(S.knuth_bendix()->froidure_pin()->size() == 5);
    REQUIRE(S.size() == 5);

    auto T = S.froidure_pin();
    REQUIRE(T->size() == 5);
    REQUIRE(T->nr_idempotents() == 1);
  }

  LIBSEMIGROUPS_TEST_CASE("FpSemigroup", "041", "equal_to", "[quick][fpsemi]") {
    auto rg = ReportGuard(REPORT);

    FpSemigroup S;
    S.set_alphabet("ab");
    S.add_rule("aa", "a");
    S.add_rule("ab", "a");
    S.add_rule("ba", "a");

    REQUIRE(S.is_obviously_infinite());
    REQUIRE(S.equal_to("ab", "a"));
    REQUIRE(S.equal_to("ba", "a"));
    REQUIRE(S.equal_to("aa", "a"));
  }

  LIBSEMIGROUPS_TEST_CASE("FpSemigroup",
                          "042",
                          "cbegin/cend_rules",
                          "[quick][fpsemi]") {
    auto rg = ReportGuard(REPORT);

    FpSemigroup S;
    S.set_alphabet("ab");
    S.add_rule("aa", "a");
    S.add_rule("ab", "a");
    S.add_rule("ba", "a");

    using rules_type = std::vector<std::pair<std::string, std::string>>;
    REQUIRE(rules_type(S.cbegin_rules(), S.cend_rules())
            == rules_type({{"aa", "a"}, {"ab", "a"}, {"ba", "a"}}));
  }

  LIBSEMIGROUPS_TEST_CASE("FpSemigroup",
                          "043",
                          "semigroup of size 3",
                          "[todd-coxeter][quick]") {
    auto        rg = ReportGuard(REPORT);
    FpSemigroup S;
    S.set_alphabet("eab");
    S.set_identity("e");

    size_t const N   = 10;
    std::string  lhs = "a" + std::string(N, 'b');
    std::string  rhs = "e";
    S.add_rule(lhs, rhs);

    lhs = std::string(N, 'a');
    rhs = std::string(N + 1, 'b');
    S.add_rule(lhs, rhs);

    lhs = "ba";
    rhs = std::string(N, 'b') + "a";
    S.add_rule(lhs, rhs);

    REQUIRE(S.size() == 3);
  }

  LIBSEMIGROUPS_TEST_CASE("FpSemigroup",
                          "044",
                          "PlanarPartitionMonoid(1)",
                          "[quick]") {
    auto        rg = ReportGuard(REPORT);
    FpSemigroup S;
    S.set_alphabet(2);
    S.set_identity(0);
    std::cout << PlanarPartitionMonoid(1) << std::endl;
    for (relation_type const& rl : PlanarPartitionMonoid(1)) {
      S.add_rule(rl);
    }
    REQUIRE(!S.is_obviously_infinite());
    REQUIRE(S.size() == 2);
  }

  LIBSEMIGROUPS_TEST_CASE("FpSemigroup",
                          "045",
                          "PlanarPartitionMonoid(2)",
                          "[quick]") {
    auto        rg = ReportGuard(REPORT);
    FpSemigroup S;
    S.set_alphabet(4);
    S.set_identity(0);
    for (relation_type const& rl : PlanarPartitionMonoid(2)) {
      S.add_rule(rl);
    }
    REQUIRE(!S.is_obviously_infinite());
    REQUIRE(S.size() == 14);
  }

  LIBSEMIGROUPS_TEST_CASE("FpSemigroup",
                          "046",
                          "PlanarPartitionMonoid(3)",
                          "[quick]") {
    auto        rg = ReportGuard(REPORT);
    FpSemigroup S;
    S.set_alphabet(6);
    S.set_identity(0);
    for (relation_type const& rl : PlanarPartitionMonoid(3)) {
      S.add_rule(rl);
    }
    REQUIRE(!S.is_obviously_infinite());
    REQUIRE(S.size() == 132);
  }

  LIBSEMIGROUPS_TEST_CASE("FpSemigroup",
                          "047",
                          "PlanarPartitionMonoid(8)",
                          "[extreme]") {
    auto        rg = ReportGuard();
    FpSemigroup S;
    S.set_alphabet(16);
    S.set_identity(0);
    for (relation_type const& rl : PlanarPartitionMonoid(8)) {
      S.add_rule(rl);
    }
    REQUIRE(!S.is_obviously_infinite());
    REQUIRE(S.size() == 35357670);
  }

  LIBSEMIGROUPS_TEST_CASE("FpSemigroup",
                          "048",
                          "PartitionMonoid(2)",
                          "[quick]") {
    auto        rg = ReportGuard(REPORT);
    FpSemigroup S;
    S.set_alphabet(5);
    S.set_identity(0);
    // std::cout << PartitionMonoid(2, 1) << std::endl;

    for (relation_type const& rl : PartitionMonoid(2, 1)) {
      S.add_rule(rl);
    }
    REQUIRE(!S.is_obviously_infinite());
    REQUIRE(S.size() == 15);
  }

  LIBSEMIGROUPS_TEST_CASE("FpSemigroup",
                          "049",
                          "PartitionMonoid(3)",
                          "[quick]") {
    auto        rg = ReportGuard(REPORT);
    FpSemigroup S;
    S.set_alphabet(8);
    S.set_identity(0);
    // std::cout << PartitionMonoid(3, 1) << std::endl;

    for (relation_type const& rl : PartitionMonoid(3, 1)) {
      S.add_rule(rl);
    }
    REQUIRE(!S.is_obviously_infinite());
    REQUIRE(S.size() == 203);
  }

  LIBSEMIGROUPS_TEST_CASE("FpSemigroup",
                          "050",
                          "PartitionMonoid(5)",
                          "[standard]") {
    auto        rg = ReportGuard(REPORT);
    FpSemigroup S;
    S.set_alphabet(14);
    S.set_identity(0);
    // std::cout << PartitionMonoid(5, 1) << std::endl;

    for (relation_type const& rl : PartitionMonoid(5, 1)) {
      S.add_rule(rl);
    }
    REQUIRE(!S.is_obviously_infinite());
    REQUIRE(S.size() == 115975);
  }

  LIBSEMIGROUPS_TEST_CASE("FpSemigroup",
                          "051",
                          "EastPartitionMonoid(2)",
                          "[quick]") {
    auto        rg = ReportGuard(REPORT);
    FpSemigroup S;
    S.set_alphabet(3);
    S.set_identity(0);
    for (relation_type const& rl : EastPartitionMonoid(2, 1)) {
      S.add_rule(rl);
    }
    REQUIRE(!S.is_obviously_infinite());
    REQUIRE(S.size() == 3);
  }

  LIBSEMIGROUPS_TEST_CASE("FpSemigroup",
                          "052",
                          "EastPartitionMonoid(3)",
                          "[quick]") {
    auto        rg = ReportGuard(REPORT);
    FpSemigroup S;
    S.set_alphabet(4);
    S.set_identity(0);
    for (relation_type const& rl : EastPartitionMonoid(3, 1)) {
      S.add_rule(rl);
    }
    REQUIRE(!S.is_obviously_infinite());
    REQUIRE(S.size() == 16);
  }

  LIBSEMIGROUPS_TEST_CASE("FpSemigroup",
                          "053",
                          "EastPartitionMonoid(4)",
                          "[quick]") {
    auto        rg = ReportGuard(REPORT);
    FpSemigroup S;
    S.set_alphabet(5);
    S.set_identity(0);
    for (relation_type const& rl : EastPartitionMonoid(4, 1)) {
      S.add_rule(rl);
    }
    REQUIRE(!S.is_obviously_infinite());
    REQUIRE(S.size() == 131);
  }

  LIBSEMIGROUPS_TEST_CASE("FpSemigroup",
                          "054",
                          "EastPartitionMonoid(5)",
                          "[quick]") {
    auto        rg = ReportGuard(REPORT);
    FpSemigroup S;
    S.set_alphabet(6);
    S.set_identity(0);
    // std::cout << EastPartitionMonoid(4, 1) << std::endl;

    for (relation_type const& rl : EastPartitionMonoid(5, 1)) {
      S.add_rule(rl);
    }
    REQUIRE(!S.is_obviously_infinite());
    REQUIRE(S.size() == 1496);
  }

  LIBSEMIGROUPS_TEST_CASE("FpSemigroup",
                          "055",
                          "EastPartitionMonoid(2, q=0)",
                          "[quick]") {
    auto        rg = ReportGuard();
    FpSemigroup S;
    S.set_alphabet(3);
    S.set_identity(0);

    std::cout << EastPartitionMonoid(2, 0) << std::endl;

    for (relation_type const& rl : EastPartitionMonoid(2, 0)) {
      S.add_rule(rl);
    }
    REQUIRE(!S.is_obviously_infinite());
    REQUIRE(S.size() == 3);
  }

  LIBSEMIGROUPS_TEST_CASE("FpSemigroup",
                          "056",
                          "EastPartitionMonoid(3, q=0)",
                          "[quick]") {
    auto        rg = ReportGuard();
    FpSemigroup S;
    S.set_alphabet(4);
    S.set_identity(0);
    for (relation_type const& rl : EastPartitionMonoid(3, 1)) {
      S.add_rule(rl);
    }
    REQUIRE(!S.is_obviously_infinite());
    REQUIRE(S.size() == 16);
  }

  LIBSEMIGROUPS_TEST_CASE("FpSemigroup",
                          "057",
                          "EastPartitionMonoid(4, q=0)",
                          "[quick]") {
    auto        rg = ReportGuard();
    FpSemigroup S;
    S.set_alphabet(5);
    S.set_identity(0);
    for (relation_type const& rl : EastPartitionMonoid(4, 0)) {
      S.add_rule(rl);
    }
    REQUIRE(!S.is_obviously_infinite());
    REQUIRE(S.size() == 131);
  }

  LIBSEMIGROUPS_TEST_CASE("FpSemigroup",
                          "058",
                          "EastPartitionMonoid(5, q=0)",
                          "[quick]") {
    auto        rg = ReportGuard();
    FpSemigroup S;
    S.set_alphabet(6);
    S.set_identity(0);
    // std::cout << EastPartitionMonoid(4, 1) << std::endl;

    for (relation_type const& rl : EastPartitionMonoid(5, 0)) {
      S.add_rule(rl);
    }
    REQUIRE(!S.is_obviously_infinite());
    REQUIRE(S.size() == 1496);
  }

}  // namespace libsemigroups
