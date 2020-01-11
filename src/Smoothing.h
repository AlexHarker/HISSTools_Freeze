
#ifndef SMOOTHING_H
#define SMOOTHING_H

#include <algorithm>

struct GainSmooth
{
    GainSmooth()
    {
        reset(1.0, 44100.0);
    }
    
    inline void reset(double samplingRate)
    {
        reset(mTarget, samplingRate);
    }
    
    inline void reset(double value, double samplingRate)
    {
        mSamplingRate = samplingRate;
        mStart = y1 = mTarget = mLo = mHi = value;
        mSampleMultiply = 1.0;
    }
    
    inline double operator()()
    {
        return (y1 = clip(y1 * mSampleMultiply));
    }
    
    inline double value()
    {
        return y1;
    }
    
    inline void set(const double value, double s)
    {
        if (s > 0.0)
        {
            mStart = y1;
            mTarget = value;
            mSampleMultiply = pow(value / y1, 1.0 / (s * mSamplingRate));
            mLo = std::min(y1, value);
            mHi = std::max(y1, value);
        }
        else
            reset(value, mSamplingRate);
    }
    
    inline double target()
    {
        return mTarget;
    }
    
private:
    
    double clip(double value)
    {
        return std::min(std::max(value, mLo), mHi);
    }
    
    double mSampleMultiply;
    double mSamplingRate;
    double mStart;
    double mTarget;
    double mLo;
    double mHi;
    double y1;
};

#endif /* SMOOTHING_H */
