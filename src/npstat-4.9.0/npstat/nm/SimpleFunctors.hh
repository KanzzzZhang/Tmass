#ifndef NPSTAT_SIMPLEFUNCTORS_HH_
#define NPSTAT_SIMPLEFUNCTORS_HH_

/*!
// \file SimpleFunctors.hh
//
// \brief Interface definitions and concrete simple functors for
//        a variety of functor-based calculations
//
// Author: I. Volobouev
//
// March 2009
*/

#include <cmath>
#include <utility>

namespace npstat {
    /** Base class for a functor that takes no arguments */
    template <typename Result>
    struct Functor0
    {
        typedef Result result_type;

        inline virtual ~Functor0() {}
        virtual Result operator()() const = 0;
    };

    /** Base class for a functor that takes a single argument */
    template <typename Result, typename Arg1>
    struct Functor1
    {
        typedef Result result_type;
        typedef Arg1 first_argument_type;

        inline virtual ~Functor1() {}
        virtual Result operator()(const Arg1&) const = 0;
    };

    /** Base class for a functor that takes two arguments */
    template <typename Result, typename Arg1, typename Arg2>
    struct Functor2
    {
        typedef Result result_type;
        typedef Arg1 first_argument_type;
        typedef Arg2 second_argument_type;

        inline virtual ~Functor2() {}
        virtual Result operator()(const Arg1&, const Arg2&) const = 0;
    };

    /** Base class for a functor that takes three arguments */
    template <typename Result, typename Arg1, typename Arg2, typename Arg3>
    struct Functor3
    {
        typedef Result result_type;
        typedef Arg1 first_argument_type;
        typedef Arg2 second_argument_type;
        typedef Arg3 third_argument_type;

        inline virtual ~Functor3() {}
        virtual Result operator()(const Arg1&,const Arg2&,const Arg3&) const=0;
    };

    /** Base class for a functor that returns a pair */
    template <typename Numeric>
    struct PairFunctor
    {
        typedef std::pair<Numeric,Numeric> result_type;
        typedef Numeric first_argument_type;

        inline virtual ~PairFunctor() {}
        virtual std::pair<Numeric,Numeric> operator()(const Numeric&) const=0;
    };

    /** A simple functor which returns a copy of its argument */
    template <typename Result>
    struct Same : public Functor1<Result, Result>
    {
        inline virtual ~Same() {}

        inline Result operator()(const Result& a) const {return a;}

        inline bool operator==(const Same&) const {return true;}
        inline bool operator!=(const Same&) const {return false;}
    };

    /** A simple functor which adds a constant to its argument */
    template <typename Result>
    class Shift : public Functor1<Result, Result>
    {
    public:
        inline Shift(const Result& v) : value_(v) {}
        inline virtual ~Shift() {}

        inline Result operator()(const Result& a) const {return a + value_;}

        inline bool operator==(const Shift& r) const
            {return value_ == r.value_;}
        inline bool operator!=(const Shift& r) const
            {return !(*this == r);}

    private:
        Shift();
        Result value_;
    };

    /** A simple functor which returns a reference to its argument */
    template <typename Result>
    struct SameRef : public Functor1<const Result&, Result>
    {
        inline virtual ~SameRef() {}

        inline const Result& operator()(const Result& a) const {return a;}

        inline bool operator==(const SameRef&) const {return true;}
        inline bool operator!=(const SameRef&) const {return false;}
    };

    /**
    // Simple functor which ignores is arguments and instead
    // builds the result using the default constructor of the result type
    */
    template <typename Result>
    struct DefaultConstructor0 : public Functor0<Result>
    {
        inline virtual ~DefaultConstructor0() {}

        inline Result operator()() const {return Result();}

        inline bool operator==(const DefaultConstructor0&) const {return true;}
        inline bool operator!=(const DefaultConstructor0&) const {return false;}
    };

    /**
    // Simple functor which ignores is arguments and instead
    // builds the result using the default constructor of the result type
    */
    template <typename Result, typename Arg1>
    struct DefaultConstructor1 : public Functor1<Result, Arg1>
    {
        inline virtual ~DefaultConstructor1() {}

        inline Result operator()(const Arg1&) const {return Result();}

        inline bool operator==(const DefaultConstructor1&) const {return true;}
        inline bool operator!=(const DefaultConstructor1&) const {return false;}
    };

    /**
    // Simple functor which ignores is arguments and instead
    // builds the result using the default constructor of the result type
    */
    template <typename Result, typename Arg1, typename Arg2>
    struct DefaultConstructor2 : public Functor2<Result, Arg1, Arg2>
    {
        inline virtual ~DefaultConstructor2() {}

        inline Result operator()(const Arg1&, const Arg2&) const
            {return Result();}

        inline bool operator==(const DefaultConstructor2&) const {return true;}
        inline bool operator!=(const DefaultConstructor2&) const {return false;}
    };

    /**
    // Simple functor which ignores is arguments and instead
    // builds the result using the default constructor of the result type
    */
    template <typename Result, typename Arg1, typename Arg2, typename Arg3>
    struct DefaultConstructor3 : public Functor3<Result, Arg1, Arg2, Arg3>
    {
        inline virtual ~DefaultConstructor3() {}

        inline Result operator()(const Arg1&, const Arg2&, const Arg3&) const
            {return Result();}

        inline bool operator==(const DefaultConstructor3&) const {return true;}
        inline bool operator!=(const DefaultConstructor3&) const {return false;}
    };

    /** Simple functor which returns a constant */
    template <typename Result>
    class ConstValue0 : public Functor0<Result>
    {
    public:
        inline ConstValue0(const Result& v) : value_(v) {}
        inline virtual ~ConstValue0() {}

        inline Result operator()() const {return value_;}

        inline bool operator==(const ConstValue0& r) const
            {return value_ == r.value_;}
        inline bool operator!=(const ConstValue0& r) const
            {return !(*this == r);}

    private:
        ConstValue0();
        Result value_;
    };

    /** Simple functor which returns a constant */
    template <typename Result, typename Arg1>
    class ConstValue1 : public Functor1<Result, Arg1>
    {
    public:
        inline ConstValue1(const Result& v) : value_(v) {}
        inline virtual ~ConstValue1() {}

        inline Result operator()(const Arg1&) const {return value_;}

        inline bool operator==(const ConstValue1& r) const
            {return value_ == r.value_;}
        inline bool operator!=(const ConstValue1& r) const
            {return !(*this == r);}

    private:
        ConstValue1();
        Result value_;
    };

    /** Simple functor which returns a constant */
    template <typename Result, typename Arg1, typename Arg2>
    class ConstValue2 : public Functor2<Result, Arg1, Arg2>
    {
    public:
        inline ConstValue2(const Result& v) : value_(v) {}
        inline virtual ~ConstValue2() {}

        inline Result operator()(const Arg1&, const Arg2&) const
            {return value_;}

        inline bool operator==(const ConstValue2& r) const
            {return value_ == r.value_;}
        inline bool operator!=(const ConstValue2& r) const
            {return !(*this == r);}

    private:
        ConstValue2();
        Result value_;
    };

    /** Simple functor which returns a constant */
    template <typename Result, typename Arg1, typename Arg2, typename Arg3>
    class ConstValue3 : public Functor3<Result, Arg1, Arg2, Arg3>
    {
    public:
        inline ConstValue3(const Result& v) : value_(v) {}
        inline virtual ~ConstValue3() {}

        inline Result operator()(const Arg1&, const Arg2&, const Arg3&) const
            {return value_;}

        inline bool operator==(const ConstValue3& r) const
            {return value_ == r.value_;}
        inline bool operator!=(const ConstValue3& r) const
            {return !(*this == r);}

    private:
        ConstValue3();
        Result value_;
    };

    /**
    // Sometimes it becomes necessary to perform an explicit cast for proper
    // overload resolution of a converting copy constructor
    */
    template <typename Result, typename Arg1, typename CastType>
    struct CastingCopyConstructor : public Functor1<Result, Arg1>
    {
        inline virtual ~CastingCopyConstructor() {}

        inline Result operator()(const Arg1& a) const
            {return Result(static_cast<CastType>(a));}

        inline bool operator==(const CastingCopyConstructor&) const
            {return true;}
        inline bool operator!=(const CastingCopyConstructor&) const
            {return false;}
    };

    /**
    // Adaptation for using functors without arguments with simple
    // cmath-style functions
    */
    template <typename Result>
    struct FcnFunctor0 : public Functor0<Result>
    {
        inline explicit FcnFunctor0(Result (*fcn)()) : fcn_(fcn) {}
        inline virtual ~FcnFunctor0() {}

        inline Result operator()() const {return fcn_();}

        inline bool operator==(const FcnFunctor0& r) const
            {return fcn_ == r.fcn_;}
        inline bool operator!=(const FcnFunctor0& r) const
            {return !(*this == r);}

    private:
        FcnFunctor0();
        Result (*fcn_)();
    };

    /**
    // Adaptation for using single-argument functors with simple
    // cmath-style functions
    */
    template <typename Result, typename Arg1>
    struct FcnFunctor1 : public Functor1<Result, Arg1>
    {
        inline explicit FcnFunctor1(Result (*fcn)(Arg1)) : fcn_(fcn) {}
        inline virtual ~FcnFunctor1() {}

        inline Result operator()(const Arg1& a) const {return fcn_(a);}

        inline bool operator==(const FcnFunctor1& r) const
            {return fcn_ == r.fcn_;}
        inline bool operator!=(const FcnFunctor1& r) const
            {return !(*this == r);}

    private:
        FcnFunctor1();
        Result (*fcn_)(Arg1);
    };

    /**
    // Adaptation for using two-argument functors with simple
    // cmath-style functions
    */
    template <typename Result, typename Arg1, typename Arg2>
    struct FcnFunctor2 : public Functor2<Result, Arg1, Arg2>
    {
        inline explicit FcnFunctor2(Result (*fcn)(Arg1, Arg2)) : fcn_(fcn) {}
        inline virtual ~FcnFunctor2() {}

        inline Result operator()(const Arg1& x, const Arg2& y) const
            {return fcn_(x, y);}

        inline bool operator==(const FcnFunctor2& r) const
            {return fcn_ == r.fcn_;}
        inline bool operator!=(const FcnFunctor2& r) const
            {return !(*this == r);}

    private:
        FcnFunctor2();
        Result (*fcn_)(Arg1, Arg2);
    };

    /**
    // Adaptation for using three-argument functors with simple
    // cmath-style functions
    */
    template <typename Result, typename Arg1, typename Arg2, typename Arg3>
    struct FcnFunctor3 : public Functor3<Result, Arg1, Arg2, Arg3>
    {
        inline explicit FcnFunctor3(Result (*fcn)(Arg1,Arg2,Arg3)):fcn_(fcn) {}
        inline virtual ~FcnFunctor3() {}

        inline Result operator()(const Arg1&x,const Arg2&y,const Arg3&z) const
            {return fcn_(x, y, z);}

        inline bool operator==(const FcnFunctor3& r) const
            {return fcn_ == r.fcn_;}
        inline bool operator!=(const FcnFunctor3& r) const
            {return !(*this == r);}

    private:
        FcnFunctor3();
        Result (*fcn_)(Arg1, Arg2, Arg3);
    };

    /**
    // Functor which extracts a given element from a random access linear
    // container without bounds checking
    */
    template <class Container, class Result = typename Container::value_type>
    struct Element1D : public Functor1<Result, Container>
    {
        inline explicit Element1D(const unsigned long index) : idx(index) {}
        inline virtual ~Element1D() {}

        inline Result operator()(const Container& c) const {return c[idx];}

        inline bool operator==(const Element1D& r) const
            {return idx == r.idx;}
        inline bool operator!=(const Element1D& r) const
            {return !(*this == r);}

    private:
        Element1D();
        unsigned long idx;
    };

    /**
    // Functor which extracts a given element from a random access linear
    // container with bounds checking
    */
    template <class Container, class Result = typename Container::value_type>
    struct Element1DAt : public Functor1<Result, Container>
    {
        inline explicit Element1DAt(const unsigned long index) : idx(index) {}
        inline virtual ~Element1DAt() {}

        inline Result operator()(const Container& c) const {return c.at(idx);}

        inline bool operator==(const Element1DAt& r) const
            {return idx == r.idx;}
        inline bool operator!=(const Element1DAt& r) const
            {return !(*this == r);}

    private:
        Element1DAt();
        unsigned long idx;
    };

    /** 
    // Left assignment functor. Works just like normal binary
    // assignment operator in places where functor is needed.
    */
    template <typename T1, typename T2>
    struct assign_left
    {
        inline T1& operator()(T1& left, const T2& right) const
            {return left = right;}
    };

    /** 
    // Right assignment functor. Reverses the assignment direction
    // in comparison with the normal binary assignment operator.
    */
    template <typename T1, typename T2>
    struct assign_right
    {
        inline T2& operator()(const T1& left, T2& right) const
            {return right = left;}
    };

    /** In-place addition on the left side */
    template <typename T1, typename T2>
    struct pluseq_left
    {
        inline T1& operator()(T1& left, const T2& right) const
            {return left += right;}
    };

    /** In-place addition on the right side */
    template <typename T1, typename T2>
    struct pluseq_right
    {
        inline T2& operator()(const T1& left, T2& right) const
            {return right += left;}
    };

    /** 
    // In-place addition on the left side preceded by
    // multiplication of the right argument by a double
    */
    template <typename T1, typename T2>
    struct addmul_left
    {
        inline explicit addmul_left(const double weight) : w_(weight) {}

        inline T1& operator()(T1& left, const T2& right) const
            {return left += w_*right;}

    private:
        addmul_left();
        double w_;
    };

    /** 
    // In-place addition on the right side preceded by
    // multiplication of the left argument by a double
    */
    template <typename T1, typename T2>
    struct addmul_right
    {
        inline explicit addmul_right(const double weight) : w_(weight) {}

        inline T1& operator()(T1& left, const T2& right) const
            {return right += w_*left;}

    private:
        addmul_right();
        double w_;
    };

    /** In-place subtraction on the left side */
    template <typename T1, typename T2>
    struct minuseq_left
    {
        inline T1& operator()(T1& left, const T2& right) const
            {return left -= right;}
    };

    /** In-place subtraction on the right side */
    template <typename T1, typename T2>
    struct minuseq_right
    {
        inline T2& operator()(const T1& left, T2& right) const
            {return right -= left;}
    };

    /** In-place multiplication on the left side */
    template <typename T1, typename T2>
    struct multeq_left
    {
        inline T1& operator()(T1& left, const T2& right) const
            {return left *= right;}
    };

    /** In-place multiplication on the right side */
    template <typename T1, typename T2>
    struct multeq_right
    {
        inline T2& operator()(const T1& left, T2& right) const
            {return right *= left;}
    };

    /** In-place division on the left side without checking for division by 0 */
    template <typename T1, typename T2>
    struct diveq_left
    {
        inline T1& operator()(T1& left, const T2& right) const
            {return left /= right;}
    };

    /** In-place division on the right side without checking for division by 0 */
    template <typename T1, typename T2>
    struct diveq_right
    {
        inline T2& operator()(const T1& left, T2& right) const
            {return right /= left;}
    };

    /** In-place division on the left side. Allow 0/0 = const. */
    template <typename T1, typename T2>
    struct diveq_left_0by0isC
    {
        inline diveq_left_0by0isC() : 
            C(T1()), leftZero(T1()), rightZero(T2()) {}
        inline explicit diveq_left_0by0isC(const T1& value) :
            C(value), leftZero(T1()), rightZero(T2()) {}

        inline T1& operator()(T1& left, const T2& right) const
        {
            if (right == rightZero)
                if (left == leftZero)
                {
                    left = C;
                    return left;
                }
            return left /= right;
        }

    private:
        T1 C;
        T1 leftZero;
        T2 rightZero;
    };

    /** In-place division on the right side. Allow 0/0 = const. */
    template <typename T1, typename T2>
    struct diveq_right_0by0isC
    {
        inline diveq_right_0by0isC() :
            C(T2()), leftZero(T1()), rightZero(T2())  {}
        inline explicit diveq_right_0by0isC(const T2& value) :
            C(value), leftZero(T1()), rightZero(T2()) {}

        inline T2& operator()(const T1& left, T2& right) const
        {
            if (left == leftZero)
                if (right == rightZero)
                {
                    right = C;
                    return right;
                }
            return right /= left;
        }

    private:
        T2 C;
        T1 leftZero;
        T2 rightZero;
    };

    /** Left assignment functor preceded by a static cast */
    template <typename T1, typename T2, typename T3=T1>
    struct scast_assign_left
    {
        inline T1& operator()(T1& left, const T2& right) const
            {return left = static_cast<T3>(right);}
    };

    /** Right assignment functor preceded by a static cast */
    template <typename T1, typename T2, typename T3=T2>
    struct scast_assign_right
    {
        inline T2& operator()(const T1& left, T2& right) const
            {return right = static_cast<T3>(left);}
    };

    /** In-place addition on the left side preceded by a static cast */
    template <typename T1, typename T2, typename T3=T1>
    struct scast_pluseq_left
    {
        inline T1& operator()(T1& left, const T2& right) const
            {return left += static_cast<T3>(right);}
    };

    /** In-place addition on the right side preceded by a static cast */
    template <typename T1, typename T2, typename T3=T2>
    struct scast_pluseq_right
    {
        inline T2& operator()(const T1& left, T2& right) const
            {return right += static_cast<T3>(left);}
    };

    /** In-place subtraction on the left side preceded by a static cast */
    template <typename T1, typename T2, typename T3=T1>
    struct scast_minuseq_left
    {
        inline T1& operator()(T1& left, const T2& right) const
            {return left -= static_cast<T3>(right);}
    };

    /** In-place subtraction on the right side preceded by a static cast */
    template <typename T1, typename T2, typename T3=T2>
    struct scast_minuseq_right
    {
        inline T2& operator()(const T1& left, T2& right) const
            {return right -= static_cast<T3>(left);}
    };

    /** 
    // Useful functor for calculating ISE between a function and
    // a polynomial series
    */
    template <class Poly, class Functor>
    class DeltaSquaredSerFcn : public Functor1<double, double>
    {
    public:
        // Note that the series coefficients are not copied
        inline DeltaSquaredSerFcn(
            const Poly& poly, const Functor& fcn,
            const double* coeffs, const unsigned maxdeg)
            : poly_(poly), fcn_(fcn), coeffs_(coeffs), maxdeg_(maxdeg) {}

        inline double operator()(const double& x) const
        {
            const double delta = poly_.series(coeffs_, maxdeg_, x) - fcn_(x);
            return delta*delta;
        }

    private:
        const Poly& poly_;
        const Functor& fcn_;
        const double* coeffs_;
        unsigned maxdeg_;
    };

    /**
    // Useful functor for calculating powers of another functor or
    // a cmath-style function
    */
    template <class Functor>
    class FunctorPowerFcnHelper : public Functor1<double, double>
    {
    public:
        inline FunctorPowerFcnHelper(const Functor& fcn, const double power)
            : fcn_(fcn), power_(power) {}

        inline double operator()(const double& x) const
        {
            if (power_)
            {
                const double tmp = fcn_(x);
                if (power_ == 1.0)
                    return tmp;
                else if (power_ == 2.0)
                    return tmp*tmp;
                else
                    return std::pow(tmp, power_);
            }
            else
                return 1.0;
        }

    private:
        const Functor& fcn_;
        double power_;
    };

    /** Utility function for making FunctorPowerFcnHelper objects */
    template <class Functor>
    inline FunctorPowerFcnHelper<Functor> FunctorPowerFcn(const Functor& fcn,
                                                          const double power)
    {
        return FunctorPowerFcnHelper<Functor>(fcn, power);
    }

    /** Functor for multiplying the result of another functor by a constant */
    template <typename Result, typename Arg1>
    class MultiplyByConstHelper : public Functor1<Result, Arg1>
    {
    public:
        template <typename Numeric>
        inline MultiplyByConstHelper(const Functor1<Result, Arg1>& fcn,
                                     const Numeric& factor)
            : fcn_(fcn), factor_(static_cast<Result>(factor)) {}

        inline double operator()(const Arg1& x) const
            {return factor_*fcn_(x);}

    private:
        Functor1<Result, Arg1>& fcn_;
        Result factor_;
    };

    /** Utility function for making MultiplyByConstHelper objects */
    template <typename Result, typename Arg1, typename Numeric>
    inline MultiplyByConstHelper<Result, Arg1> MultiplyByConst(
        const Functor1<Result, Arg1>& fcn, const Numeric& factor)
    {
        return MultiplyByConstHelper<Result, Arg1>(fcn, factor);
    }
}

#endif // NPSTAT_SIMPLEFUNCTORS_HH_
