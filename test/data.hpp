//
// Copyright (c) 2012-2013 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_DI_DATA_HPP
#define BOOST_DI_DATA_HPP

#include <memory>
#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/noncopyable.hpp>
#include <boost/function.hpp>
#include <boost/mpl/string.hpp>
#include "boost/di/ctor.hpp"
#include "boost/di/named.hpp"
#include "boost/di/provider.hpp"

namespace boost {
namespace di {

class a { };
class b { };
class c { };
class d { };
class i { };
class impl : public i { };

struct if0
{
    virtual ~if0() { }
    virtual void dummy() = 0;
};

struct c0if0 : if0
{
    virtual void dummy() { }
};

struct c1if0 : if0
{
    virtual void dummy() { }
};

struct c2if0 : if0
{
    virtual void dummy() { }
};

struct c3if0 : if0
{
    BOOST_DI_CTOR(c3if0
        , int i
        , double d
    )
        : i(i), d(d)
    { }

    virtual void dummy() { }

    int i = 0;
    double d = 0.0;
};

struct c0
{
    //trivial ctor
};

struct c1 : private noncopyable
{
    explicit c1(int = 0) { }
};

struct c2
{
    BOOST_DI_CTOR(c2
        , int i
        , double d
        , char c
    )
        : i(i), d(d), c(c)
    { }

    int i = 0;
    double d = 0.0;
    char c = 0;
};

struct c3
{
    BOOST_DI_CTOR(explicit c3
        , int i = 0
    )
        : i(i)
    { }

    int i = 0;
};

struct c4
{
    BOOST_DI_CTOR(c4
        , shared_ptr<c3> c3_
        , named<int, mpl::string<'1'>> i1
        , named<int, mpl::string<'2'>> i2
    )
        : c3_(c3_), i1(i1), i2(i2)
    { }

    shared_ptr<c3> c3_;
    int i1 = 0;
    int i2 = 0;
};

struct c5
{
    BOOST_DI_CTOR(c5
        , shared_ptr<if0> if0_
        , shared_ptr<c2> c2_
        , shared_ptr<c1> c1_
    )
        : if0_(if0_), c2_(c2_), c1_(c1_)
    { }

    shared_ptr<if0> if0_;
    shared_ptr<c2> c2_;
    shared_ptr<c1> c1_;
};

struct c6
{
    BOOST_DI_CTOR(c6
        , shared_ptr<c3> c3_
        , shared_ptr<c4> c4_
        , c5 c5_
    )
        : c3_(c3_), c4_(c4_), c5_(c5_)
    { }

    shared_ptr<c3> c3_;
    shared_ptr<c4> c4_;
    c5 c5_;
};

struct c7
{
    BOOST_DI_CTOR(c7
        , shared_ptr<if0> if0_
        , shared_ptr<c6> c6_
    )
        : if0_(if0_), c6_(c6_)
    { }

    shared_ptr<if0> if0_;
    shared_ptr<c6> c6_;
};

struct c8
{
    BOOST_DI_CTOR(c8
        , shared_ptr<c7> c7_
        , c0 c0_
        , shared_ptr<c1> c1_
        , int i
    )
        : c7_(c7_), c0_(c0_), c1_(c1_), i(i)
    { }

    shared_ptr<c7> c7_;
    c0 c0_;
    shared_ptr<c1> c1_;
    int i = 0;
};

struct c9 : c2
{
    BOOST_DI_CTOR(c9
        , int i
        , double d
        , char c
        , std::string s = "string"
    )
        : c2(i, d, c), s(s)
    { }

    std::string s;
};

struct c10
{
    BOOST_DI_CTOR_TRAITS(
        named<int, mpl::string<'1'>>
      , named<int, mpl::string<'2'>>
    );

    c10(int i1, int i2)
        : i1(i1), i2(i2)
    { }

    int i1 = 0;
    int i2 = 0;
};

struct c11
{
    BOOST_DI_CTOR(c11
        , named<shared_ptr<int>, mpl::string<'1'>> i
    )
        : i(i)
    { }

    shared_ptr<int> i;
};

struct c12
{
    BOOST_DI_CTOR(c12
        , named<shared_ptr<if0>, mpl::string<'1'>> if0_
        , named<shared_ptr<c2>, mpl::string<'2'>> c2_
    )
        : if0_(if0_), c2_(c2_)
    { }

    shared_ptr<if0> if0_;
    shared_ptr<c2> c2_;
};

struct c13
{
    BOOST_DI_CTOR(c13
        , named<shared_ptr<if0>> if0_
        , c3 c3_
    )
        : if0_(if0_), c3_(c3_)
    { }

    shared_ptr<if0> if0_;
    c3 c3_;
};

struct c14
{
    c14(int i, double d)
        : i(i), d(d)
    { }

    int i = 0;
    double d = 0.0;
};

struct c15
{
    BOOST_DI_CTOR(c15
        , shared_ptr<c3> c3_
        , c6 c6_
    )
        : c3_(c3_), c6_(c6_)
    { }

    shared_ptr<c3> c3_;
    c6 c6_;
};

struct c16 : noncopyable
{
    BOOST_DI_CTOR(c16
        , c14& c14_
        , const c3& c3_
    )
        : c14_(c14_), c3_(c3_)
    { }

    c14& c14_;
    const c3& c3_;
};

struct c17
{
    BOOST_DI_CTOR(c17
        , const c3& c3_
        , function<int()> f_
        , const std::string& s_
    )
        : c3_(c3_), f_(f_), s_(s_)
    { }

    c3 c3_;
    function<int()> f_;
    std::string s_;
};

struct c18 : private noncopyable
{
    BOOST_DI_CTOR(c18
        , c0 c0_ // per_request
        , shared_ptr<c1> c1_ // singleton
        , c3& c3_ // external
    )
        : c0_(c0_), c1_(c1_), c3_(c3_)
    { }

    c0 c0_;
    shared_ptr<c1> c1_;
    c3& c3_;
};

struct c19
{
    BOOST_DI_CTOR(c19
        , shared_ptr<c1> c1_
        , shared_ptr<c1> c1__
    )
        : c1_(c1_), c1__(c1__)
    { }

    shared_ptr<c1> c1_;
    shared_ptr<c1> c1__;
};

struct c20
{
    BOOST_DI_CTOR(c20
        , shared_ptr<if0> if0_
        , shared_ptr<if0> if0__
    )
        : if0_(if0_), if0__(if0__)
    { }

    shared_ptr<if0> if0_;
    shared_ptr<if0> if0__;
};

struct c21
{
    BOOST_DI_CTOR(c21
        , std::shared_ptr<if0> if0_
        , std::unique_ptr<if0> if0__
    )
        : if0_(if0_), if0__(std::move(if0__))
    { }

    std::shared_ptr<if0> if0_;
    std::unique_ptr<if0> if0__;
};

struct c22
{
    BOOST_DI_CTOR(c22
        , named<shared_ptr<int>, mpl::string<'1'>> i
        , shared_ptr<c11> c11_
    )
        : i(i), c11_(c11_)
    { }

    shared_ptr<int> i;
    shared_ptr<c11> c11_;
};

struct c23
{
    BOOST_DI_CTOR(c23
        , shared_ptr<if0> if0_
    )
        : if0_(if0_)
    { }

    shared_ptr<if0> if0_;
};

struct c24
{
    BOOST_DI_CTOR(c24
        , c2
        , shared_ptr<int>
        , double*
        , const std::string&
    ) { }
};

struct c25
{
    BOOST_DI_CTOR(c25
        , std::shared_ptr<int> s1_
        , boost::shared_ptr<int> s2_
        , boost::weak_ptr<int> w1_
    )
        : s1_(s1_), s2_(s2_), w1_(w1_)
    { }

    std::shared_ptr<int> s1_;
    boost::shared_ptr<int> s2_;
    boost::weak_ptr<int> w1_;
};

struct c26
{
    BOOST_DI_CTOR(c26
        , std::vector<boost::shared_ptr<if0>> v1_
        , std::vector<int> v2_
    )
        : v1_(v1_), v2_(v2_)
    { }

    std::vector<boost::shared_ptr<if0>> v1_;
    std::vector<int> v2_;
};

enum eid
{
    e0 = 1
  , e1 = 2
};

class if0_factory
{
public:
    if0* BOOST_DI_CREATE(eid id) {
        switch(id) {
            case e0: return new c0if0();
            case e1: return new c1if0();
        }

        return nullptr;
    }
};

struct cd2;
struct cd5;

struct cd1
{
    BOOST_DI_CTOR(cd1, cd2*) { };
};

struct cd2
{
    BOOST_DI_CTOR(cd2, cd1*) { };
};

struct cd3
{
    BOOST_DI_CTOR(cd3, cd5*) { };
};

struct cd4
{
    BOOST_DI_CTOR(cd4, cd3*) { };
};

struct cd5
{
    BOOST_DI_CTOR(cd5, cd4*) { };
};

struct ub1
{
    BOOST_DI_CTOR(ub1, int i_)
        : i_(i_)
    { };

    int i_ = 0;
};

struct ub2
{
    BOOST_DI_CTOR(ub2, shared_ptr<ub1> ub1_)
        : ub1_(ub1_)
    { }

    shared_ptr<ub1> ub1_;
};

struct ub3
{
    BOOST_DI_CTOR(ub3, shared_ptr<ub1> ub1_, shared_ptr<ub2> ub2_)
        : ub1_(ub1_), ub2_(ub2_)
    { }

    shared_ptr<ub1> ub1_;
    shared_ptr<ub2> ub2_;
};

struct transaction
{
    transaction(int i)
        : i(i)
    { }

    int i = 0;
};

struct transaction_provider
    : provider<shared_ptr<transaction>>
{
    BOOST_DI_CTOR(transaction_provider
        , shared_ptr<c3> c3_
    )
        : c3_(c3_)
    { }

    virtual shared_ptr<transaction> get() const
    {
        return make_shared<transaction>(c3_->i);
    }

    shared_ptr<c3> c3_;
};

struct transaction_usage
{
    BOOST_DI_CTOR(transaction_usage
        , shared_ptr<provider<shared_ptr<transaction>>> p
    )
        : p(p)
    { }

    shared_ptr<provider<shared_ptr<transaction>>> p;
};

template<>
struct ctor_traits<c14>
{
    BOOST_DI_CTOR_TRAITS(int, double);
};

} // namespace di
} // namespace boost

#endif

