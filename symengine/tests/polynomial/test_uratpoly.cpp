#include "catch.hpp"
#include <chrono>

#include <symengine/polys/uratpoly.h>
#include <symengine/pow.h>

using SymEngine::URatPoly;
using SymEngine::Symbol;
using SymEngine::symbol;
using SymEngine::Pow;
using SymEngine::RCP;
using SymEngine::make_rcp;
using SymEngine::print_stack_on_segfault;
using SymEngine::map_uint_mpq;
using SymEngine::Basic;
using SymEngine::one;
using SymEngine::zero;
using SymEngine::integer;
using SymEngine::vec_basic_eq_perm;
using SymEngine::rational_class;
using SymEngine::URatDict;
using SymEngine::add;

using namespace SymEngine::literals;
using rc = rational_class;

// TEST_CASE("Constructor of URatPoly", "[URatPoly]")
// {
//     RCP<const Symbol> x = symbol("x");

//     RCP<const URatPoly> P
//         = URatPoly::from_dict(x, {{0, rc(1_z, 2_z)}, {2, rc(3_z, 2_z)}});
//     REQUIRE(P->__str__() == "3/2*x**2 + 1/2");

//     RCP<const URatPoly> Q
//         = URatPoly::from_vec(x, {rc(0_z), rc(1_z, 2_z), rc(3_z, 6_z)});
//     REQUIRE(Q->__str__() == "1/2*x**2 + 1/2*x");

//     RCP<const URatPoly> S = URatPoly::from_dict(x, {{0, rc(2_z, 1_z)}});
//     REQUIRE(S->__str__() == "2");

//     RCP<const URatPoly> T = URatPoly::from_dict(x, {});
//     REQUIRE(T->__str__() == "0");
// }

// TEST_CASE("Adding two URatPoly", "[URatPoly]")
// {
//     RCP<const Symbol> x = symbol("x");
//     RCP<const Symbol> y = symbol("y");
//     URatDict adict_({{0, rc(1_z, 2_z)}, {1, rc(2_z, 3_z)}, {2, rc(1_z)}});
//     URatDict bdict_({{0, rc(2_z, 3_z)}, {1, rc(3_z)}, {2, rc(4_z, 2_z)}});
//     URatDict gdict_({{0, rc(2_z)}, {1, rc(-3_z, 2_z)}, {2, rc(1_z, 4_z)}});
//     const URatPoly a(x, std::move(adict_));
//     const URatPoly b(x, std::move(bdict_));

//     RCP<const Basic> c = add_upoly(a, b);
//     REQUIRE(c->__str__() == "3*x**2 + 11/3*x + 7/6");

//     RCP<const URatPoly> d = URatPoly::from_dict(x, {{0, rc(1_z, 2_z)}});
//     RCP<const Basic> e = add_upoly(a, *d);
//     RCP<const Basic> f = add_upoly(*d, a);
//     REQUIRE(e->__str__() == "x**2 + 2/3*x + 1");
//     REQUIRE(f->__str__() == "x**2 + 2/3*x + 1");

//     const URatPoly g(y, std::move(gdict_));
//     CHECK_THROWS_AS(add_upoly(a, g), std::runtime_error);
// }

// TEST_CASE("Negative of a URatPoly", "[URatPoly]")
// {
//     RCP<const Symbol> x = symbol("x");
//     URatDict adict_({{0, rc(-1_z, 2_z)}, {1, rc(2_z, 1_z)}, {2, rc(3_z)}});
//     const URatPoly a(x, std::move(adict_));

//     RCP<const URatPoly> b = neg_upoly(a);
//     REQUIRE(b->__str__() == "-3*x**2 - 2*x + 1/2");
// }

// TEST_CASE("Subtracting two URatPoly", "[URatPoly]")
// {
//     RCP<const Symbol> x = symbol("x");
//     RCP<const Symbol> y = symbol("y");
//     URatDict adict_({{0, rc(1_z, 2_z)}, {1, rc(2_z, 3_z)}, {2, rc(1_z)}});
//     URatDict bdict_({{0, rc(2_z, 3_z)}, {1, rc(3_z)}, {2, rc(4_z, 2_z)}});
//     URatDict cdict_({{0, rc(2_z)}, {1, rc(-3_z, 2_z)}, {2, rc(1_z, 4_z)}});
//     URatDict fdict_({{0, rc(2_z)}});

//     const URatPoly a(x, std::move(adict_));
//     const URatPoly b(x, std::move(bdict_));
//     const URatPoly c(x, std::move(cdict_));
//     const URatPoly f(y, std::move(fdict_));

//     RCP<const Basic> d = sub_upoly(b, a);
//     REQUIRE(d->__str__() == "x**2 + 7/3*x + 1/6");
//     d = sub_upoly(c, a);
//     REQUIRE(d->__str__() == "-3/4*x**2 - 13/6*x + 3/2");
//     d = sub_upoly(a, c);
//     REQUIRE(d->__str__() == "3/4*x**2 + 13/6*x - 3/2");
//     CHECK_THROWS_AS(sub_upoly(a, f), std::runtime_error);
// }

// TEST_CASE("Multiplication of two URatPoly", "[URatPoly]")
// {
//     RCP<const Symbol> x = symbol("x");
//     RCP<const Symbol> y = symbol("y");

//     URatDict adict_({{0, rc(1_z, 2_z)}, {1, rc(2_z, 3_z)}, {2, rc(1_z)}});
//     URatDict bdict_({{0, rc(2_z, 3_z)}, {1, rc(3_z)}, {2, rc(4_z, 2_z)}});
//     URatDict edict_({{0, rc(2_z)}, {1, rc(-3_z, 2_z)}, {2, rc(1_z, 4_z)}});
//     URatDict fdict_({{0, rc(1_z)}, {1, rc(1_z, 2_z)}});

//     const URatPoly a(x, std::move(adict_));
//     const URatPoly b(x, std::move(bdict_));
//     const URatPoly e(x, std::move(edict_));
//     const URatPoly f(x, std::move(fdict_));

//     RCP<const URatPoly> c = mul_upoly(a, a);
//     RCP<const URatPoly> d = mul_upoly(a, b);
//     RCP<const URatPoly> g = mul_upoly(e, e);
//     RCP<const URatPoly> h = mul_upoly(e, f);
//     RCP<const URatPoly> i = mul_upoly(f, f);

//     REQUIRE(c->__str__() == "x**4 + 4/3*x**3 + 13/9*x**2 + 2/3*x + 1/4");
//     REQUIRE(d->__str__() == "2*x**4 + 13/3*x**3 + 11/3*x**2 + 35/18*x + 1/3");
//     REQUIRE(g->__str__() == "1/16*x**4 - 3/4*x**3 + 13/4*x**2 - 6*x + 4");
//     REQUIRE(h->__str__() == "1/8*x**3 - 1/2*x**2 - 1/2*x + 2");
//     REQUIRE(i->__str__() == "1/4*x**2 + x + 1");

//     c = URatPoly::from_dict(x, {{0, rc(-1_z)}});
//     REQUIRE(mul_upoly(a, *c)->__str__() == "-x**2 - 2/3*x - 1/2");
//     REQUIRE(mul_upoly(*c, a)->__str__() == "-x**2 - 2/3*x - 1/2");

//     c = URatPoly::from_dict(y, {{0, rc(-1_z)}});
//     CHECK_THROWS_AS(mul_upoly(a, *c), std::runtime_error);
// }

// TEST_CASE("Comparing two URatPoly", "[URatPoly]")
// {
//     RCP<const Symbol> x = symbol("x");
//     RCP<const Symbol> y = symbol("y");
//     RCP<const URatPoly> P = URatPoly::from_dict(x, {{0, rc(1_z)}, {1, rc(2_z, 3_z)}});
//     RCP<const URatPoly> Q
//         = URatPoly::from_dict(x, {{0, rc(1_z)}, {1, rc(2_z)}, {2, rc(1_z)}});

//     REQUIRE(P->compare(*Q) == -1);

//     P = URatPoly::from_dict(x, {{0, 1_z}, {1, 2_z}, {2, 3_z}, {3, 2_z}});
//     REQUIRE(P->compare(*Q) == 1);

//     P = URatPoly::from_dict(x, {{0, rc(1_z)}, {1, rc(2_z)}, {2, rc(1_z)}});
//     REQUIRE(P->compare(*Q) == 0);

//     P = URatPoly::from_dict(y, {{0, rc(1_z)}, {1, rc(2_z, 3_z)}});
//     REQUIRE(P->compare(*Q) == -1);
// }

// TEST_CASE("URatPoly as_symbolic", "[URatPoly]")
// {
//     RCP<const Symbol> x = symbol("x");
//     RCP<const URatPoly> a
//         = URatPoly::from_dict(x, {{0, rc(1_z, 2_z)}, {1, 2_z}, {2, 1_z}});

//     REQUIRE(eq(*a->as_symbolic(),
//                *add({div(one, integer(2)), mul(integer(2), x), pow(x, integer(2))})));

//     RCP<const URatPoly> b
//         = URatPoly::from_dict(x, {{1, rc(3_z, 2_z)}, {2, 2_z}});
//     REQUIRE(eq(*b->as_symbolic(),
//                *add(mul(x, div(integer(3), integer(2))), mul(integer(2), pow(x, integer(2))))));

//     RCP<const URatPoly> c = URatPoly::from_dict(x, {});
//     REQUIRE(eq(*c->as_symbolic(), *zero));
// }

TEST_CASE("URatPoly expand", "[URatPoly][expand]")
{
    RCP<const Symbol> x = symbol("x");
    RCP<const URatPoly> a = URatPoly::from_dict(x, {});
    RCP<const Basic> b = pow(a, integer(3));
    // RCP<const Basic> c = expand(b);

    // REQUIRE(a->__str__() == "(x**3 - 1/2*x**2 + 1/3*x)**3");
    // REQUIRE(c->__str__()
    //         == "x**9 + 3*x**8 + 6*x**7 + 7*x**6 + 6*x**5 + 3*x**4 + x**3");
}

// TEST_CASE("Evaluation of URatPoly", "[URatPoly]")
// {
//     RCP<const Symbol> x = symbol("x");
//     RCP<const URatPoly> a
//         = URatPoly::from_dict(x, {{0, 1_z}, {1, 2_z}, {2, 1_z}});
//     RCP<const URatPoly> b
//         = URatPoly::from_dict(x, {{0, 1_z}, {1, 0_z}, {2, -1_z}});

//     REQUIRE(a->eval(2_z) == 9);
//     REQUIRE(a->eval(10_z) == 121);
//     REQUIRE(b->eval(-1_z) == 0);
//     REQUIRE(b->eval(0_z) == 1);

//     vec_rational_class resa = {9_z, 121_z, 0_z, 1_z};
//     vec_rational_class resb = {-3_z, -99_z, 0_z, 1_z};
//     REQUIRE(a->multieval({2_z, 10_z, -1_z, 0_z}) == resa);
//     REQUIRE(b->multieval({2_z, 10_z, -1_z, 0_z}) == resb);
// }

// TEST_CASE("Derivative of URatPoly", "[URatPoly]")
// {
//     RCP<const Symbol> x = symbol("x");
//     RCP<const Symbol> y = symbol("y");
//     RCP<const URatPoly> a
//         = URatPoly::from_dict(x, {{0, 1_z}, {1, 2_z}, {2, 1_z}});
//     RCP<const URatPoly> b = URatPoly::from_dict(y, {{2, 4_z}});

//     REQUIRE(a->diff(x)->__str__() == "2*x + 2");
//     REQUIRE(a->diff(y)->__str__() == "0");
//     REQUIRE(b->diff(y)->__str__() == "8*y");
// }