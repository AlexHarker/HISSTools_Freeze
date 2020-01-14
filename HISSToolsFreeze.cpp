
#include "HISSToolsFreeze.h"

#include "IPlug_include_in_plug_src.h"
#include "HISSTools_Controls.hpp"
#include "IControls.h"

enum Modes
{
    kRegular,
    kRandomised,
    kManual
};

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
: Plugin(info, MakeConfig(kNumParams, kNumPrograms)), mProxy(new FromPlugProxy()), mDSP(mProxy), mManualTrigger(false), mLastFreeze(false)
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
    
    GetParam(kMode)->InitEnum("Mode", 1, 3);
    GetParam(kMode)->SetDisplayText(0, "Regular");
    GetParam(kMode)->SetDisplayText(1, "Random");
    GetParam(kMode)->SetDisplayText(2, "Manual");

    GetParam(kFreeze)->InitBool("Freeze", false);

    GetParam(kSampleTime)->InitDouble("Sample", 200., 5., 5000.0, 1, "ms", 0, "", IParam::ShapePowCurve(2.0));
    GetParam(kBlur)->InitDouble("Blur", 200., 0., 2000.0, 1, "ms", 0, "", IParam::ShapePowCurve(2.0));
    GetParam(kXFadeTime)->InitDouble("Morph", 0., 0., 10000.0, 1, "ms", 0, "", IParam::ShapePowCurve(2.0));
    GetParam(kFragment)->InitDouble("Fragment", 0., 0., 100.0, 1, "%");

    GetParam(kFiltNum)->InitInt("Number Filters", 12, 2, 60, "");
    GetParam(kFiltInterval)->InitDouble("Filter Interval", 800., 20., 4000.0, 1, "ms", 0, "", IParam::ShapePowCurve(2.0));
    GetParam(kFiltRandom)->InitDouble("Filter Random", 100., 0., 4000.0, 1, "ms", 0, "", IParam::ShapePowCurve(2.0));
    GetParam(kFiltTilt)->InitDouble("Filter Tilt", 0.0, -100.0, 100.0, 1, "%");
    GetParam(kFiltStrength)->InitDouble("Filter Strength", 0.0, 0.0, 24.0, 0.1, "dB");
    
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
            
            return new HISSTools_Button(idx, cb.L, cb.T, 100, 30, types, &designScheme);
        };
        
        const IRECT b = pGraphics->GetBounds();
        
        // Name
        
        pGraphics->AttachControl(new HISSTools_TextBlock(0, 20, PLUG_WIDTH, 50, "HISSTools Freeze", kHAlignCenter, kVAlignCenter, "name", &designScheme));
        
        pGraphics->AttachControl(paramPanel(b, kFFTSize, -30, -140, ""));
        pGraphics->AttachControl(paramPanel(b, kOverlap, -30, -90, ""));
        pGraphics->AttachControl(paramPanel(b, kMode, -30, -40, ""));

        pGraphics->AttachControl(button(b, kFreeze, -180, -140, "tight"));
        
        pGraphics->AttachControl(dial(b, kSampleTime, -100, -20, ""));
        pGraphics->AttachControl(dial(b, kFragment, -100, 100, ""));
        pGraphics->AttachControl(dial(b, kBlur, 100, -20, ""));
        pGraphics->AttachControl(dial(b, kXFadeTime, 100, 100, ""));
        
        pGraphics->AttachControl(smallDial(b, kFiltNum, -200, 220, "2"));
        pGraphics->AttachControl(smallDial(b, kFiltInterval, -100, 220, "3"));
        pGraphics->AttachControl(smallDial(b, kFiltRandom, 0, 220, "3"));
        pGraphics->AttachControl(smallDial(b, kFiltStrength, 100, 220, "5"));
        pGraphics->AttachControl(smallDial(b, kFiltTilt, 200, 220, "5 bipolar"));
        
        pGraphics->AttachControl(smallDial(b, kGain, 100, -140, "4 bipolar"));
        pGraphics->AttachControl(smallDial(b, kWidth, 200, -140, "4 bipolar"));
    }
}

void HISSToolsFreeze::OnReset()
{
    mDSP.reset(GetSampleRate(), GetBlockSize());
    
    mGainSmoother.reset(GetSampleRate());
    mWidthSmoother.reset(GetSampleRate());
    
    mLastGain = mGainSmoother.target();
    mLastWidth = mWidthSmoother.target();
    
    mPhase = 1.0;
    
    mManualTrigger = false;
    mLastFreeze = GetParam(kFreeze)->Bool();
    
    mTriggers.Resize(GetBlockSize());
}

void HISSToolsFreeze::OnFragmentChange()
{
    auto scaled = [](double interp, double lo, double hi) {
        return hi * interp + lo * (1.0 - interp);
    };
    
    double fragment = GetParam(kFragment)->GetNormalized();
    double bounds[4];
    
    bounds[0] = scaled(fragment, 0.50, 0.00);
    bounds[1] = scaled(fragment, 0.50, 1.00);
    bounds[2] = scaled(fragment, 0.50, 0.03);
    bounds[3] = scaled(fragment, 0.50, 0.05);
    
    mProxy->sendFromHost(5, bounds, 4);
}

void HISSToolsFreeze::OnFilterTimeChange()
{
    double lo = GetParam(kFiltInterval)->Value();
    double random = GetParam(kFiltRandom)->Value();
    double hi = lo + random;
    
    FrameLib_Parameters::AutoSerial serial;
    
    serial.write("outlo", &lo, 1);
    serial.write("outhi", &hi, 1);
    
    mProxy->sendFromHost(2, &serial);
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
    
    mProxy->sendFromHost(7, &serial);
}

void HISSToolsFreeze::OnParamChange(int paramIdx, EParamSource source, int sampleOffset)
{
    switch (paramIdx)
    {
        case kFFTSize:
        {
            double FFT = 1 << (GetParam(kFFTSize)->Int() + 9);
            mProxy->sendFromHost(1, &FFT, 1);
            break;
        }
        
        case kOverlap:
        {
            double overlap = 1 << (GetParam(kOverlap)->Int() + 1);
            mProxy->sendFromHost(0, &overlap, 1);
            break;
        }
            
        case kBlur:
        {
            double blurTime = GetParam(kBlur)->Value();
            mProxy->sendFromHost(3, &blurTime, 1);
            break;
        }
            
        case kXFadeTime:
        {
            double time = GetParam(kXFadeTime)->Value();
            mProxy->sendFromHost(4, &time, 1);
            break;
        }
        
        case kFragment:
        {
            OnFragmentChange();
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
            mProxy->sendFromHost(6, "length", &num, 1);
            break;
        }
            
        case kFreeze:
        {
            Modes mode = (Modes) GetParam(kMode)->Int();

            if (mode == kManual)
            {
                bool freeze = GetParam(kFreeze)->Bool();
                mManualTrigger |= freeze && !mLastFreeze;
                mLastFreeze = GetParam(kFreeze)->Bool();
            }
        }
        default:
            break;
    }
}

void HISSToolsFreeze::OnParamChangeUI(int paramIdx, EParamSource source)
{
    switch (paramIdx)
    {
        case kFiltStrength:
        {
            if (GetUI())
            {
                bool zero = GetParam(kFiltStrength)->Value() == 0.0;
                
                GetUI()->DisableControl(kFiltNum, zero);
                GetUI()->DisableControl(kFiltStrength, zero);
                GetUI()->DisableControl(kFiltTilt, zero);
                GetUI()->DisableControl(kFiltInterval, zero);
                GetUI()->DisableControl(kFiltRandom, zero);
                break;
            }
        }
            
        default:
            break;
    }
}


void HISSToolsFreeze::ProcessBlock(double** inputs, double** outputs, int nFrames)
{
    Modes mode = (Modes) GetParam(kMode)->Int();
    
    double* triggers = mTriggers.Get();
    double* dspInputs[3];
    double* plugInputs[2];

    const double rootTwo = 1.0 / sqrt(2.0);
    
    plugInputs[0] = inputs[0];
    plugInputs[1] = NChannelsConnected(kInput) > 1 ?  inputs[1] : inputs[0];
    
    dspInputs[0] = outputs[0];
    dspInputs[1] = outputs[1];
    dspInputs[2] = triggers;

    // Parameters
    
    double sampling = GetParam(kSampleTime)->Value();
    bool freeze = GetParam(kFreeze)->Bool();
    double samplingRecip = 1000.0 / (GetSampleRate() * sampling);
    double threshold = freeze ? 2.0 : 1.0 - samplingRecip;
    double phase = freeze ? 0.0 : samplingRecip;
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
        double L = plugInputs[0][i] * rootTwo;
        double R = plugInputs[1][i] * rootTwo;
        
        outputs[0][i] = (L + R);
        outputs[1][i] = (L - R);
    }
    
    // Sampling
    
    switch (mode)
    {
        case kRegular:
            for (int i = 0; i < nFrames; i++)
            {
                mPhase += phase;
                if (mPhase > 1.0)
                {
                    triggers[i] = 1.0;
                    mPhase -= 1.0;
                }
                else
                    triggers[i] = 0.0;
            }
            break;
            
        case kRandomised:
            for (int i = 0; i < nFrames; i++)
                triggers[i] = (std::rand() / (RAND_MAX + 1.0)) > threshold;
            break;
            
        case kManual:
            triggers[0] = mManualTrigger ? 1.0 : 0.0;
            for (int i = 1; i < nFrames; i++)
                triggers[i] = 0.0;
            mManualTrigger = false;
            break;
    }
    
    
    // Main process
    
    mDSP.process(dspInputs, outputs, nFrames);
    
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
