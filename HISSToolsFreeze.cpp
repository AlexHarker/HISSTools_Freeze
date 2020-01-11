
#include "HISSToolsFreeze.h"

#include "IPlug_include_in_plug_src.h"
#include "HISSTools_Controls.hpp"
#include "IControls.h"

// Visual Design

class Design : public HISSTools_Design_Scheme
{
    
public:
    
    Design() : HISSTools_Design_Scheme(true)
    {
        HISSTools_Color_Spec *col1 = new HISSTools_Color_Spec(0.7, 0.0, 0.0, 0.9);
        HISSTools_Color_Spec *col2 = new HISSTools_Color_Spec(0.2, 0.7, 0.3, 0.9);
        HISSTools_Color_Spec *col3 = new HISSTools_Color_Spec(0.35, 0.0, 0.35, 0.9);
        HISSTools_Color_Spec *col4 = new HISSTools_Color_Spec(0.0, 0.5, 0.5, 0.9);
        HISSTools_Color_Spec *col5 = new HISSTools_Color_Spec(0.5, 0.5, 0.0, 0.9);
        HISSTools_Color_Spec *col6 = new HISSTools_Color_Spec(0.1, 0.4, 0.7, 0.9);
        HISSTools_Color_Spec *col7 = new HISSTools_Color_Spec(0.8, 0.4, 0.1, 0.9);
        
        HISSTools_Color_Spec *blackCS = new HISSTools_Color_Spec(0., 0., 0., 1.0);
        HISSTools_Color_Spec *greyCS = new HISSTools_Color_Spec(0.9, 0.9, 0.9, 0.5);
        
        HISSTools_LICE_VGradient* activeFillCS = new HISSTools_LICE_VGradient;
        HISSTools_LICE_VGradient* activeOffFillCS = new HISSTools_LICE_VGradient;
        
        activeOffFillCS->addStop(HISSTools_Color(0.415, 0.415, 0.415, 1.0), 0.0);
        activeOffFillCS->addStop(HISSTools_Color(0.169, 0.169, 0.169, 1.0), 1.0);
        
        activeFillCS->addStop(HISSTools_Color(0.6, 0.6, 0.6, 1.0), 0);
        activeFillCS->addStop(HISSTools_Color(0.3, 0.3, 0.3, 1.0), 1.);
        
        HISSTools_LICE_VGradient* panelFillCS = new HISSTools_LICE_VGradient;
        panelFillCS->addStop(HISSTools_Color(0.4, 0.4, 0.4, 0.4), 0.0);
        panelFillCS->addStop(HISSTools_Color(0.2, 0.2, 0.2, 0.5), 0.94);
        panelFillCS->addStop(HISSTools_Color(0.075, 0.075, 0.075, 0.6), 1.0);
        
        HISSTools_Color_Spec *shadowCS = new HISSTools_Color_Spec(HISSTools_Color(0.00, 0.00, 0.00, 0.90));
        HISSTools_Shadow *shadowSpec = new HISSTools_Shadow(shadowCS, 4, 4, 6);
        
        addColorSpec("PanelFill", "upper", panelFillCS);
        addColorSpec("PanelFill", "main", panelFillCS);
        addColorSpec("PanelFill", "thick", blackCS);
        
        addColorSpec("ButtonHandleLabelOff", "alt", greyCS);
        addColorSpec("ButtonHandleOff", "alt", activeOffFillCS);
        addColorSpec("ButtonHandleOn", "alt", activeFillCS);
        
        addShadow("TextBlock", "name", shadowSpec);
        
        HISSTools_Color_Spec *textColor = new HISSTools_Color_Spec(0.9, 0.9, 0.9, 0.80);
        HISSTools_Text *nameTxt = new HISSTools_Text(42, "Arial Bold");
        
        addColorSpec("TextBlock", "name", textColor);
        addTextStyle("TextBlock", "name", nameTxt);
        
        addColorSpec("DialIndicator", "1", col1);
        addColorSpec("DialIndicator", "2", col2);
        addColorSpec("DialIndicator", "3", col3);
        addColorSpec("DialIndicator", "4", col4);
        addColorSpec("DialIndicator", "5", col5);
        addColorSpec("DialIndicator", "6", col6);
        addColorSpec("DialIndicator", "7", col7);
        
        addDimension("PanelRoundnessTL","tighter", 5);
        addDimension("PanelRoundnessTR","tighter", 5);
        addDimension("PanelRoundnessBL","tighter", 5);
        addDimension("PanelRoundnessBR","tighter", 5);
        
        addDimension("DialRefValue", "gain", 2.0/7.0);
        addDimension("DialRefValue", "vol", 6.0/7.0);
        
        addDimension("ValueTextArea", "spacious", 25);
        
        addFlag("ValueDrawTriangle", "small", false);
        addFlag("ValueDrawLabel", "nolabel", false);
        
        addFlag("ValueLabelBelow", true);
        addFlag("ValueLabelBelow", "above", false);
        addFlag("DialDrawValOnlyOnMO", true);
    }
};

Design designScheme;

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

    GetParam(kSampleTime)->InitDouble("Sampling", 200., 20., 5000.0, 0.1, "ms");
    GetParam(kFreeze)->InitBool("Freeze", false);
    
    GetParam(kBlur)->InitDouble("Blur", 200., 0., 2000.0, 0.1, "ms");
    GetParam(kXFadeTime)->InitDouble("Time", 0., 0., 10000.0, 0.1, "ms");

    GetParam(kFiltInterval)->InitDouble("Filter Interval", 800., 20., 4000.0, 0.1, "ms");
    GetParam(kFiltRandom)->InitDouble("Filter Random", 100., 0., 4000.0, 0.1, "ms");
    GetParam(kFiltTilt)->InitDouble("Filter Tilt", 0.0, -100.0, 100.0, 0.1, "%");
    GetParam(kFiltStrength)->InitDouble("Filter Strength", 0.0, 0.0, 24.0, 0.1, "dB");
    GetParam(kFiltNum)->InitInt("Number Filters", 12, 2, 60, "");
    
    GetParam(kGain)->InitDouble("Gain", 0., -12.0, 12.0, 0.1, "dB");
    GetParam(kWidth)->InitDouble("Width", 0., -12.0, 12.0, 0.1, "dB");
}

IGraphics* HISSToolsFreeze::CreateGraphics()
{
    return MakeGraphics(*this, PLUG_WIDTH, PLUG_HEIGHT, PLUG_FPS, 1.);
}

void HISSToolsFreeze::LayoutUI(IGraphics* pGraphics)
{
    if (!pGraphics->NControls())
    {
        pGraphics->HandleMouseOver(true);
        pGraphics->AttachPanelBackground(COLOR_GRAY);
        
        pGraphics->LoadFont("Roboto-Regular", ROBOTO_FN);
        pGraphics->LoadFont("Arial Bold", "Arial", ETextStyle::Bold);
        
        auto smallDial = [](const IRECT& b, int idx, int hs, int vs, const char *types) {
            IRECT cb = b.GetCentredInside(80).GetVShifted(vs).GetHShifted(hs);
            
            WDL_String var("small");
            var.Append(" ");
            var.Append(types);
            
            return new HISSTools_Dial(idx, cb.L, cb.T, var.Get(), &designScheme);
        };
        
        auto dial = [](const IRECT& b, int idx, int hs, int vs, const char *types) {
            IRECT cb = b.GetCentredInside(80).GetVShifted(vs).GetHShifted(hs);
            
            return new HISSTools_Dial(idx, cb.L, cb.T, types, &designScheme);
        };
        
        auto paramPanel = [](const IRECT& b, int idx, int hs, int vs, const char *types) {
            IRECT cb = b.GetCentredInside(80).GetVShifted(vs).GetHShifted(hs);
            
            return new HISSTools_Value(idx, cb.L, cb.T, 100, 20, types, &designScheme);
        };
        
        auto button = [](const IRECT& b, int idx, int hs, int vs, const char *types) {
            IRECT cb = b.GetCentredInside(80).GetVShifted(vs).GetHShifted(hs);
            
            return new HISSTools_Button(idx, cb.L, cb.T, 100, 20, types, &designScheme);
        };
        
        const IRECT b = pGraphics->GetBounds();
        
        // Name
        
        pGraphics->AttachControl(new HISSTools_TextBlock(0, 20, PLUG_WIDTH, 50, "HISSTools Freeze", kHAlignCenter, kVAlignCenter, "name", &designScheme));
        
        pGraphics->AttachControl(paramPanel(b, kFFTSize, -30, -140, ""));
        pGraphics->AttachControl(paramPanel(b, kOverlap, -30, -90, ""));
        
        pGraphics->AttachControl(dial(b, kSampleTime, -100, -20, ""));
        pGraphics->AttachControl(button(b, kFreeze, -100, 140, ""));
        pGraphics->AttachControl(dial(b, kBlur, 100, -20, ""));
        pGraphics->AttachControl(dial(b, kXFadeTime, 100, 100, ""));
        
        pGraphics->AttachControl(smallDial(b, kFiltNum, -200, 220, "2"));
        pGraphics->AttachControl(smallDial(b, kFiltInterval, -100, 220, "3"));
        pGraphics->AttachControl(smallDial(b, kFiltRandom, 0, 220, "3"));
        pGraphics->AttachControl(smallDial(b, kFiltStrength, 100, 220, "5"));
        pGraphics->AttachControl(smallDial(b, kFiltTilt, 200, 220, "5"));
        
        pGraphics->AttachControl(smallDial(b, kGain, 100, -140, "4"));
        pGraphics->AttachControl(smallDial(b, kWidth, 200, -140, "4"));
    }
}

void HISSToolsFreeze::OnReset()
{
    mDSP.reset(GetSampleRate(), GetBlockSize());
    
    mGainSmoother.reset(GetSampleRate());
    mWidthSmoother.reset(GetSampleRate());
    
    mLastGain = mGainSmoother.target();
    mLastWidth = mWidthSmoother.target();
}

void HISSToolsFreeze::OnTimeChange()
{
    int FFT = 1 << (GetParam(kFFTSize)->Int() + 9);
    int overlap = 1 << (GetParam(kOverlap)->Int() + 1);

    double blurTime = GetParam(kBlur)->Value();
    double hopTime = 1000 * FFT / (overlap * GetSampleRate());
    double frames = std::round(blurTime / hopTime) + 1;
    
    mProxy->sendFromHost(2, "num_frames", &frames, 1);
}

void HISSToolsFreeze::OnFilterTimeChange()
{
    double lo = GetParam(kFiltInterval)->Value();
    double random = GetParam(kFiltRandom)->Value();
    double hi = lo + random;
    
    FrameLib_Parameters::AutoSerial serial;
    
    serial.write("outlo", &lo, 1);
    serial.write("outhi", &hi, 1);
    
    mProxy->sendFromHost(4, &serial);
}

void HISSToolsFreeze::OnFilterStrengthChange()
{
    double tilt = GetParam(kFiltTilt)->Value() / 100.0;
    double strength = GetParam(kFiltStrength)->Value();
    double lo = (1.0 - std::max(0.0,  tilt)) * strength;
    double hi = (1.0 - std::max(0.0, -tilt)) * strength;
    
    FrameLib_Parameters::AutoSerial serial;
    
    serial.write("outlo", &lo, 1);
    serial.write("outhi", &hi, 1);
    
    mProxy->sendFromHost(6, &serial);
}

void HISSToolsFreeze::OnParamChange(int paramIdx, EParamSource source, int sampleOffset)
{
    switch (paramIdx)
    {
        case kFFTSize:
        {
            double FFT = 1 << (GetParam(kFFTSize)->Int() + 9);
            mProxy->sendFromHost(1, &FFT, 1);
            OnTimeChange();
            break;
        }
        
        case kOverlap:
        {
            double overlap = 1 << (GetParam(kOverlap)->Int() + 1);
            mProxy->sendFromHost(0, &overlap, 1);
            OnTimeChange();
            break;
        }
            
        case kBlur:
        {
            OnTimeChange();
            break;
        }
            
        case kXFadeTime:
        {
            double time = GetParam(kXFadeTime)->Value();
            mProxy->sendFromHost(3, &time, 1);
            break;
        }
        
        case kFiltInterval:
        case kFiltRandom:
        {
            OnFilterTimeChange();
            break;
        }
            
        case kFiltTilt:
        case kFiltStrength:
        {
            OnFilterStrengthChange();
            break;
        }
         
        case kFiltNum:
        {
            double num = GetParam(kFiltNum)->Value();
            mProxy->sendFromHost(5, "length", &num, 1);
            break;
        }
            
        default:
            break;
    }
}

void HISSToolsFreeze::ProcessBlock(sample** inputs, sample** outputs, int nFrames)
{
    sample triggers[nFrames];
    sample* allInputs[3];
    
    const double rootTwo = 1.0 / sqrt(2.0);
    
    allInputs[0] = outputs[0];
    allInputs[1] = outputs[1];
    allInputs[2] = triggers;

    // Parameters
    
    double sampling = GetParam(kSampleTime)->Value();
    bool freeze = GetParam(kFreeze)->Bool();
    double threshold = freeze ? 2.0 : 1.0 - (1000.0 / (GetSampleRate() * sampling));
    double currentGain = DBToAmp(GetParam(kGain)->Value());
    double currentWidth = DBToAmp(GetParam(kWidth)->Value());
    
    if (currentGain != mLastGain)
    {
        mGainSmoother.set(currentGain, 0.03);
        mLastGain = currentGain;
    }
    
    if (currentWidth != mLastWidth)
    {
        mWidthSmoother.set(currentWidth, 0.03);
        mLastWidth = currentWidth;
    }
    
    // MS Processing
    
    for (int i = 0; i < nFrames; i++)
    {
        double L = inputs[0][i] * rootTwo;
        double R = inputs[1][i] * rootTwo;
        
        outputs[0][i] = (L + R);
        outputs[1][i] = (L - R);
    }
    
    // Sampling
    
    for (int i = 0; i < nFrames; i++)
        triggers[i] = (std::rand() / (RAND_MAX + 1.0)) > threshold;
    
    // Main process
    
    mDSP.process(allInputs, outputs, nFrames);
    
    // MS Processing
    
    for (int i = 0; i < nFrames; i++)
    {
        const double gain = mGainSmoother() * rootTwo;
        const double width = mWidthSmoother();
        double M = outputs[0][i] * gain;
        double S = outputs[1][i] * gain * width;
        
        outputs[0][i] = (M + S);
        outputs[1][i] = (M - S);
    }
}
