#pragma once

#include "IPlug_include_in_plug_hdr.h"
#include "src/Freeze.h"

#include "FrameLib_FromHost.h"
#include "src/Smoothing.h"

const int kNumPrograms = 1;

enum EParams
{
    kFFTSize = 0,
    kOverlap,
    kMode,
    kSampleTime,
    kFreeze,
    kFragment,
    kBlur,
    kXFadeTime,
    kFiltInterval,
    kFiltRandom,
    kFiltTilt,
    kFiltStrength,
    kFiltNum,
    kGain,
    kWidth,
    kNumParams
};

using namespace iplug;
using namespace igraphics;

class HISSToolsFreeze : public Plugin
{
    struct FromPlugProxy : public FrameLib_FromHost::Proxy
    {
        FromPlugProxy() : FrameLib_FromHost::Proxy(true, true) {}
    };
    
public:
    
    HISSToolsFreeze(const InstanceInfo& info);

    void ProcessBlock(double** inputs, double** outputs, int nFrames) override;
    void OnReset() override;
    void OnParamChange(int paramIdx, EParamSource source, int sampleOffset) override;
    void OnParamChangeUI(int paramIdx, EParamSource source) override;

    void OnFragmentChange();
    void OnFilterStrengthChange();
    void OnFilterTimeChange();

private:
    
    IGraphics* CreateGraphics() override;
    void LayoutUI(IGraphics* pGraphics) override;
    
    FromPlugProxy *mProxy;  // N.B. - owned by mDSP
    Freeze mDSP;
    
    WDL_TypedBuf<double> mTriggers;
    
    GainSmooth mGainSmoother;
    GainSmooth mWidthSmoother;
    
    double mLastGain;
    double mLastWidth;
    double mPhase;
    
    bool mManualTrigger;
    bool mLastFreeze;
};
