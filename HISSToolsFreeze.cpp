
#include "HISSToolsFreeze.h"

#include "IPlug_include_in_plug_src.h"
#include "IControls.h"

HISSToolsFreeze::HISSToolsFreeze(const InstanceInfo& info)
: Plugin(info, MakeConfig(kNumParams, kNumPrograms)), mProxy(new FromPlugProxy()), mDSP(mProxy)
{
    GetParam(kFFTSize)->InitEnum("FFT Size", 3, 8);
    GetParam(kFFTSize)->SetDisplayText(0, "512");
    GetParam(kFFTSize)->SetDisplayText(1, "1024");
    GetParam(kFFTSize)->SetDisplayText(2, "2048");
    GetParam(kFFTSize)->SetDisplayText(3, "4096");
    GetParam(kFFTSize)->SetDisplayText(4, "8192");
    GetParam(kFFTSize)->SetDisplayText(5, "16384");
    GetParam(kFFTSize)->SetDisplayText(6, "32768");
    GetParam(kFFTSize)->SetDisplayText(7, "65536");
    
    GetParam(kOverlap)->InitEnum("Overlap", 2, 3);
    GetParam(kOverlap)->SetDisplayText(0, "2");
    GetParam(kOverlap)->SetDisplayText(1, "4");
    GetParam(kOverlap)->SetDisplayText(2, "8");
                                                                                                                                                                                                                                                                                                                               
    GetParam(kTime)->InitDouble("Time", 0., 0., 10000.0, 0.1, "ms");
    
    mMakeGraphicsFunc = [&]() {
        return MakeGraphics(*this, PLUG_WIDTH, PLUG_HEIGHT, PLUG_FPS, 1.);
    };
    
    mLayoutFunc = [&](IGraphics* pGraphics) {
        pGraphics->AttachCornerResizer(EUIResizerMode::Scale, false);
        pGraphics->AttachPanelBackground(COLOR_GRAY);
        pGraphics->LoadFont("Roboto-Regular", ROBOTO_FN);
        const IRECT b = pGraphics->GetBounds();
        pGraphics->AttachControl(new ITextControl(b.GetMidVPadded(50), "Hello iPlug 2!", IText(50)));
        pGraphics->AttachControl(new IVKnobControl(b.GetCentredInside(100).GetVShifted(-100), kTime));
    };
}

void HISSToolsFreeze::OnReset()
{
    mDSP.reset(GetSampleRate(), GetBlockSize());
    
    
}

void HISSToolsFreeze::OnParamChange(int paramIdx, EParamSource source, int sampleOffset)
{
    switch (paramIdx)
    {
        case kFFTSize:
        {
            double FFT = 1 << (GetParam(kFFTSize)->Int() + 9);
            mProxy->sendFromHost(1, &FFT, 1);
        }
        
        case kOverlap:
        {
            double overlap = 1 << (GetParam(kOverlap)->Int() + 1);
            mProxy->sendFromHost(0, &overlap, 1);
        }
            
        case kTime:
        {
            double time = GetParam(kTime)->Value();
            mProxy->sendFromHost(3, &time, 1);
        }
        
        default:
            break;
    }
}

void HISSToolsFreeze::ProcessBlock(sample** inputs, sample** outputs, int nFrames)
{
    sample triggers[nFrames];
    sample* allInputs[3];
    
    allInputs[0] = inputs[0];
    allInputs[1] = inputs[1];
    allInputs[2] = triggers;

    for (int i = 0; i < nFrames; i++)
        triggers[i] = (std::rand() / (RAND_MAX + 1.0)) > 0.9999;
    
    mDSP.process(allInputs, outputs, nFrames);
}


