#pragma once

#include "IPlug_include_in_plug_hdr.h"
#include "Freeze.h"

#include "FrameLib_FromHost.h"

const int kNumPrograms = 1;

enum EParams
{
    kFFTSize = 0,
    kOverlap,
    kBlur,
    kTime,
    kFiltInterval,
    kFiltRandom,
    kFiltTilt,
    kFiltStrength,
    kFiltNum,
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
    
    void ProcessBlock(sample** inputs, sample** outputs, int nFrames) override;
    void OnReset() override;
    void OnParamChange(int paramIdx, EParamSource source, int sampleOffset) override;

    void OnTimeChange();
    void OnFilterStrengthChange();
    void OnFilterTimeChange();

private:
    
    FromPlugProxy *mProxy;  // N.B. - owned by mDSP
    Freeze mDSP;
};
