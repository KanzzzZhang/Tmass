#ifndef NPSTAT_INTERVAL_HH_
#define NPSTAT_INTERVAL_HH_

/*!
// \file Interval.hh
//
// \brief Template to represent intervals in one dimension
//
// Author: I. Volobouev
//
// March 2010
*/

#include <stdexcept>
#include <algorithm>
#include <utility>

namespace npstat {
    /**
    // Representation of 1-d intervals. The following invariant
    // is maintained: min() will not exceed max().
    //
    // See BoxND class for rectangles, boxes, and hyperboxes.
    */
    template <typename Numeric>
    class Interval
    {
    public:
        /** Both lower and upper interval bounds are set to Numeric() */
        inline Interval() : min_(Numeric()), max_(Numeric()) {}

        /** 
        // Minimum is set to Numeric(), maximum to the given argument.
        // An exception is thrown if the argument is smaller than Numeric().
        */
        inline explicit Interval(const Numeric max)
            : min_(Numeric()), max_(max)
        {
            if (min_ > max_) throw std::invalid_argument(
                "In npstat::Interval constructor: invalid limits");
        }

        /** 
        // Constructor from both bounds. Set "swapIfOutOfOrder" argument
        // to "true" if the minimum can be larger than the maximum (in this
        // case the bounds will be swapped internally).
        */
        inline Interval(const Numeric min, const Numeric max,
                        const bool swapIfOutOfOrder = false)
            : min_(min), max_(max)
        {
            if (min_ > max_)
            {
                if (swapIfOutOfOrder)
                    std::swap(min_, max_);
                else
                    throw std::invalid_argument(
                        "In npstat::Interval constructor: invalid limits");
            }
        }

        /** Set the lower interval bound */
        inline void setMin(const Numeric value)
        {
            if (value > max_) throw std::invalid_argument(
                "In npstat::Interval::setMin: argument above max");
            min_ = value; 
        }

        /** Set the upper interval bound */
        inline void setMax(const Numeric value)
        {
            if (value < min_) throw std::invalid_argument(
                "In npstat::Interval::setMax: argument below min");
            max_ = value;
        }

        /** Set both interval bounds */
        inline void setBounds(const Numeric minval, const Numeric maxval,
                              const bool swapIfOutOfOrder = false)
        {
            if (maxval < minval && !swapIfOutOfOrder)
                throw std::invalid_argument(
                    "In npstat::Interval::setBounds: invalid limits");
            min_ = minval;
            max_ = maxval;
            if (swapIfOutOfOrder && min_ > max_)
                std::swap(min_, max_);
        }

        /** Return the lower bound */
        inline const Numeric min() const {return min_;}

        /** Return the upper bound */
        inline const Numeric max() const {return max_;}

        /** Return both bounds */
        inline void getBounds(Numeric* pmin, Numeric* pmax) const
            {*pmin = min_; *pmax = max_;}

        /** Interval length */
        inline Numeric length() const {return max_ - min_;}

        /** The middle point of the interval */
        inline Numeric midpoint() const
            {return static_cast<Numeric>((max_ + min_)*0.5);}

        /** Is the point inside the interval or on the lower boundary? */
        inline bool isInsideLower(const Numeric value) const
            {return value >= min_ && value < max_;}

        /** Is the point inside the interval or on the upper boundary? */
        inline bool isInsideUpper(const Numeric value) const
            {return value > min_ && value <= max_;}

        /** Is the point inside the interval or on one of the boundaries? */
        inline bool isInsideWithBounds(const Numeric value) const
            {return value >= min_ && value <= max_;}

        /** 
        // Is the point completely inside the interval
        // (and does not coincide with any bound)?
        */
        inline bool isInside(const Numeric value) const
            {return value > min_ && value < max_;}

        //@{
        /**
        // Scaling of both the minimum and the maximum by a constant.
        // Minimum and maximum will be swapped internally in case the
        // constant is negative.
        */
        Interval& operator*=(double r);
        Interval& operator/=(double r);
        //@}

        //@{
        /** Shift both interval bounds by a constant */
        Interval& operator+=(const Numeric value);
        Interval& operator-=(const Numeric value);
        //@}

        /** Move the interval so that the midpoint ends up at 0 */
        Interval& moveMidpointTo0();

        //@{
        /**
        // Scaling the bounds by a constant in such a way
        // that the midpoint remains unchanged
        */
        Interval& expand(double r);
        //@}

        /**
        // The following function returns default-constructed empty interval
        // in case this interval and the argument interval do not overlap
        */
        Interval overlap(const Interval& r) const;

        /** Same as overlap.length() but a tad faster */
        Numeric overlapLength(const Interval& r) const;

        /** Same as overlapLength(r)/length() but a tad faster */
        double overlapFraction(const Interval& r) const;

        /**
        // Which points are inside this interval but outside the argument
        // interval? The result can have 0, 1, or 2 intervals. The default
        // constructed empty interval will be substituted for the absence
        // of the first and/or the second interval in the result.
        */
        std::pair<Interval,Interval> logicalDifference(const Interval& r) const;

        /**
        // Derive the coefficients a and b such that the linear
        // mapping y = a*x + b maps the lower limit of this interval
        // into the lower limit of the argument interval and the
        // upper limit of this interval into the upper limit of the
        // argument interval
        */
        template <typename Num2>
        void linearMap(const Interval<Num2> &r, double* a, double* b) const;

    private:
        Numeric min_;
        Numeric max_;
    };
}

//@{
/** Binary comparison for equality */
template <typename Numeric>
bool operator==(const npstat::Interval<Numeric>& l,const npstat::Interval<Numeric>& r);

template <typename Numeric>
bool operator!=(const npstat::Interval<Numeric>& l,const npstat::Interval<Numeric>& r);
//@}

#include "npstat/nm/Interval.icc"

#endif // NPSTAT_INTERVAL_HH_
