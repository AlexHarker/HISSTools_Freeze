
#include "HISSToolsFreeze.h"

#include "IPlug_include_in_plug_src.h"
#include <HISSTools_Controls.hpp>
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
        HISSTools_Color_Spec *col2 = new HISSTools_Color_Spec(0.5, 0.5, 0.0, 0.9);
        HISSTools_Color_Spec *col3 = new HISSTools_Color_Spec(0.1, 0.5, 0.2, 0.9);
        HISSTools_Color_Spec *col4 = new HISSTools_Color_Spec(0.0, 0.5, 0.5, 0.9);
        
        HISSTools_Color_Spec *blackCS = new HISSTools_Color_Spec(0., 0., 0., 1.0);
        HISSTools_Color_Spec *greyCS = new HISSTools_Color_Spec(0.9, 0.9, 0.9, 0.5);
        
        HISSTools_LICE_VGradient* activeFillCS = new HISSTools_LICE_VGradient;
        HISSTools_LICE_VGradient* activeOffFillCS = new HISSTools_LICE_VGradient;
        
        activeOffFillCS->addStop(HISSTools_Color(0.415, 0.415, 0.415, 1.0), 0.0);
        activeOffFillCS->addStop(HISSTools_Color(0.169, 0.169, 0.169, 1.0), 1.0);
        
        activeFillCS->addStop(HISSTools_Color(0.6, 0.6, 0.6, 1.0), 0);
        activeFillCS->addStop(HISSTools_Color(0.3, 0.3, 0.3, 1.0), 1.);
        
        HISSTools_LICE_VGradient* panelFillCS = new HISSTools_LICE_VGradient;
        panelFillCS->addStop(HISSTools_Color(0.40, 0.40, 0.40, 0.40), 0.0);
        panelFillCS->addStop(HISSTools_Color(0.35, 0.35, 0.35, 0.45), 0.94);
        panelFillCS->addStop(HISSTools_Color(0.19, 0.19, 0.19, 0.50), 1.0);
        
        HISSTools_Color_Spec shadowCS(HISSTools_Color(0.00, 0.00, 0.00, 0.90));
        HISSTools_Shadow *shadowSpec = new HISSTools_Shadow(shadowCS, 4, 4, 6);
        
        HISSTools_Color_Spec panelShadowCS(HISSTools_Color(0.00, 0.00, 0.00, 0.70));
        HISSTools_Shadow *panelShadowSpec = new HISSTools_Shadow(panelShadowCS, 2, 3, 4);
        
        HISSTools_Color_Spec dialTextShadowCS(HISSTools_Color(0.00, 0.00, 0.00, 1.0));
        HISSTools_Shadow *dialTextShadowSpec = new HISSTools_Shadow(shadowCS, 0, 0, 3);
        
        addShadow("Panel", "lightShadow", panelShadowSpec);
        addShadow("DialValue", dialTextShadowSpec);

        addColorSpec("PanelFill", "upper", panelFillCS);
        addColorSpec("PanelFill", "main", panelFillCS);
        addColorSpec("PanelFill", "thick", blackCS);
        
        addColorSpec("ButtonHandleLabelOff", "alt", greyCS);
        addColorSpec("ButtonHandleOff", "alt", activeOffFillCS);
        addColorSpec("ButtonHandleOn", "alt", activeFillCS);
        
        addShadow("TextBlock", "name", shadowSpec);
        
        HISSTools_Color_Spec *textColor = new HISSTools_Color_Spec(0.9, 0.9, 0.9, 0.80);
        HISSTools_Text *nameTxt = new HISSTools_Text(34, "Arial Bold");
        
        addColorSpec("TextBlock", "name", textColor);
        addTextStyle("TextBlock", "name", nameTxt);
        
        HISSTools_Color_Spec *labelColor = new HISSTools_Color_Spec(0.9, 0.9, 0.9, 0.80);
        HISSTools_Text *labelTxt = new HISSTools_Text(20, "Arial Bold");
        
        addColorSpec("TextBlock", "label", labelColor);
        addTextStyle("TextBlock", "label", labelTxt);
        
        addColorSpec("DialIndicator", "1", col1);
        addColorSpec("DialIndicator", "2", col2);
        addColorSpec("DialIndicator", "3", col3);
        addColorSpec("DialIndicator", "4", col4);
        
        addDimension("PanelRoundnessTL","tighter", 5);
        addDimension("PanelRoundnessTR","tighter", 5);
        addDimension("PanelRoundnessBL","tighter", 5);
        addDimension("PanelRoundnessBR","tighter", 5);
        
        addDimension("DialRefValue", "gain", 2.0/7.0);
        addDimension("DialRefValue", "vol", 6.0/7.0);
        
        addDimension("DialDiameter", "smallNormalLabel", 60);
        addDimension("DialDiameter", "medium", 74);

        addDimension("DialTextArea", "medium", 23);
        addDimension("DialTextArea", "smallNormalLabel", 20);

        addTextStyle("DialValue", "medium", new HISSTools_Text(13, "Arial Bold"));
        addTextStyle("DialValue", "smallNormalLabel", new HISSTools_Text(12, "Arial Bold"));

        addDimension("ValueTextArea", "spacious", 25);
        
        addFlag("ValueDrawTriangle", "small", false);
        addFlag("ValueDrawLabel", "nolabel", false);
        
        addFlag("ValueLabelBelow", true);
        addFlag("ValueLabelBelow", "above", false);
        addFlag("DialDrawValOnlyOnMO", true);
        
        addDimension("ValueWidth", 84);
        addDimension("ValueWidth", "mode", 100);
        
        addDimension("ValueHeight", 20);
        addDimension("ValueHeight", "mode", 26);
    }
};

Design scheme;

class Freeze_Button: public IControl, public HISSTools_Control_Layers
{
    
public:
    
    // Constructor
    
    Freeze_Button(int paramIdx, int modeParam, double x, double y, double w = 0, double h = 0, const char *type = 0, HISSTools_Design_Scheme *scheme = &DefaultDesignScheme, const char *label = "")
    : IControl(IRECT(), {paramIdx, modeParam}), HISSTools_Control_Layers(), mMouseIsDown(false)
    {
        // Dimensions
        
        mX = x;
        mY = y;
        mW = w <= 0 ? scheme->getDimension("ButtonWidth", type) : w;
        mH = h <= 0 ? scheme->getDimension("ButtonHeight", type) : h;
        
        double roundness = scheme->getDimension("ButtonRoundness", type);
        mRoundness = roundness < 0 ? mH / 2 : roundness;
        
        mTextPad = scheme->getDimension("ButtonTextPad", type);
        
        // Label Mode
        
        mLabelMode = scheme->getFlag("ButtonLabelMode", type);
        
        // Get Appearance
        
        mOutlineTK = scheme->getDimension("ButtonOutline", type);
        
        mShadow = scheme->getShadow("Button", type);
        
        mTextStyle = scheme->getTextStyle("Button", type);
        
        mOnCS = scheme->getColorSpec("ButtonHandleOn", type);
        mOffCS = scheme->getColorSpec("ButtonHandleOff", type);
        mHandleLabelCS = scheme->getColorSpec("ButtonHandleLabel", type);
        mHandleLabelOffCS = scheme->getColorSpec("ButtonHandleLabelOff", type);
        mHandleLabelOffCS = mHandleLabelOffCS ? mHandleLabelOffCS : mHandleLabelCS;
        mOutlineCS = scheme->getColorSpec("ButtonOutline", type);
        mBackgroundLabelCS = scheme->getColorSpec("ButtonBackgroundLabel", type);
        mInactiveOverlayCS = scheme->getColorSpec("ButtonInactiveOverlay", type);
        
        // Calculate Areas (including shadows and thicknesses)
        
        HISSTools_Bounds handleBounds(mX, mY, mLabelMode ? mH : mW, mH);
        HISSTools_Bounds fullBounds(mX, mY, mW, mH);
        
        handleBounds.addThickness(mOutlineTK);
        
        fullBounds = mShadow->getBlurBounds(handleBounds);
        fullBounds.include(fullBounds);
        
        mRECT = fullBounds;
        SetTargetRECT(handleBounds);
        
        mName = label;
        
        mDblAsSingleClick = true;
    }
    
public:
    
    void OnInit() override
    {
        if (GetParam() != nullptr)
            mName = GetParam()->GetNameForHost();
    }
    
    // Mousing Functions
    
    void OnMouseDown(float x, float y, const IMouseMod& pMod) override
    {
        Modes mode = (Modes) GetParam(1)->Int();
        
        mMouseIsDown = true;
        SetValue(GetValue() && mode != kManual ? 0 : 1.0);
        SetDirty(true, 0);
    }
    
    void OnMouseUp(float x, float y, const IMouseMod& pMod) override
    {
        Modes mode = (Modes) GetParam(1)->Int();

        if (mode == kManual)
            SetAnimation(DefaultAnimationFunc, 100.0);
        
        mMouseIsDown = false;
    }
    
    void OnMouseOver(float x, float y, const IMouseMod& pMod) override {}
    void OnMouseOut() override {}
    
    void OnEndAnimation() override
    {
        SetAnimation(nullptr);
        
        SetValue(0.0);
        SetDirty(true, 0);
    }
    
    // Draw
    
    void Draw(IGraphics& g) override
    {
        HISSTools_VecLib vecDraw(g);
        
        bool manualMode = ((Modes) GetParam(1)->Int()) == kManual;
        bool manualHighlight = mMouseIsDown || GetAnimationFunction();
        bool on = manualMode ? manualHighlight : GetValue() > 0.5;
        
        // Button Rectangle
        
        vecDraw.startShadow(mShadow, mRECT);
        vecDraw.setColor(on ? mOnCS : mOffCS);
        vecDraw.fillRoundRect(mX, mY, mLabelMode ? mH : mW, mH, mRoundness);
        vecDraw.setColor(mOutlineCS);
        vecDraw.frameRoundRect(mX, mY, mLabelMode ? mH : mW, mH, mRoundness, mOutlineTK);
        vecDraw.renderShadow();
        
        vecDraw.setColor(mLabelMode ? mBackgroundLabelCS : on ? mHandleLabelCS : mHandleLabelOffCS);
        vecDraw.text(mTextStyle, mName, mLabelMode ? mX + mH + mTextPad : mX, mY, mLabelMode ? mW - (mH + mTextPad) : mW, mH, mLabelMode ?  kHAlignLeft : kHAlignCenter);
        
        // Inactive
        
        if (IsDisabled())
        {
            // Inactive Overlay
            
            vecDraw.setColor(mInactiveOverlayCS);
            vecDraw.fillRoundRect(mX, mY, mLabelMode ? mH : mW, mH, mRoundness);
        }
    }
    
private:
    
    // Positioning / Dimensions
    
    double mX;
    double mY;
    double mW;
    double mH;
    double mTextPad;
    double mRoundness;
    
    // Line Thicknesses
    
    double mOutlineTK;
    
    // Shadow Spec
    
    HISSTools_Shadow *mShadow;
    
    // Text Spec
    
    HISSTools_Text *mTextStyle;
    
    // Color Specs
    
    HISSTools_Color_Spec *mOnCS;
    HISSTools_Color_Spec *mOffCS;
    HISSTools_Color_Spec *mOutlineCS;
    HISSTools_Color_Spec *mHandleLabelCS;
    HISSTools_Color_Spec *mHandleLabelOffCS;
    HISSTools_Color_Spec *mBackgroundLabelCS;
    HISSTools_Color_Spec *mInactiveOverlayCS;
    
    // Mouse
    
    bool mMouseIsDown;
    
    // Label Mode
    
    bool mLabelMode;
    
    // Text
    
    const char *mName;
};

HISSToolsFreeze::HISSToolsFreeze(const InstanceInfo& info)
: Plugin(info, MakeConfig(kNumParams, kNumPrograms)), mProxy(new FromPlugProxy()), mDSP(mProxy)
{
    GetParam(kFFTSize)->InitEnum("FFT Size", 3, 7);
    GetParam(kFFTSize)->SetDisplayText(0, "512");
    GetParam(kFFTSize)->SetDisplayText(1, "1024");
    GetParam(kFFTSize)->SetDisplayText(2, "2048");
    GetParam(kFFTSize)->SetDisplayText(3, "4096");
    GetParam(kFFTSize)->SetDisplayText(4, "8192");
    GetParam(kFFTSize)->SetDisplayText(5, "16384");
    GetParam(kFFTSize)->SetDisplayText(6, "32768");
    
    GetParam(kOverlap)->InitEnum("Overlap", 2, 3);
    GetParam(kOverlap)->SetDisplayText(0, "2");
    GetParam(kOverlap)->SetDisplayText(1, "4");
    GetParam(kOverlap)->SetDisplayText(2, "8");
    
    GetParam(kMode)->InitEnum("Mode", 1, 3);
    GetParam(kMode)->SetDisplayText(0, "Regular");
    GetParam(kMode)->SetDisplayText(1, "Random");
    GetParam(kMode)->SetDisplayText(2, "Manual");

    GetParam(kFreeze)->InitBool("Freeze", false);

    GetParam(kBlur)->InitDouble("Blur", 200., 0., 2000.0, 1, "ms", 0, "", IParam::ShapePowCurve(2.0));
    GetParam(kFragment)->InitDouble("Fragment", 0., 0., 100.0, 1, "%");
    GetParam(kSample)->InitDouble("Sample", 200., 5., 5000.0, 1, "ms", 0, "", IParam::ShapePowCurve(2.0));
    GetParam(kMorph)->InitDouble("Morph", 0., 0., 10000.0, 1, "ms", 0, "", IParam::ShapePowCurve(2.0));


    GetParam(kFiltNum)->InitInt("Filter Num Bands", 12, 2, 60, "");
    GetParam(kFiltInterval)->InitDouble("Filter Interval", 800., 20., 5000.0, 1, "ms", 0, "", IParam::ShapePowCurve(2.0));
    GetParam(kFiltRandom)->InitDouble("Filter Random", 100., 0., 5000.0, 1, "ms", 0, "", IParam::ShapePowCurve(2.0));
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
        
        pGraphics->LoadFont("Arial Bold", "Arial", ETextStyle::Bold);
        
        const int svs = 50;
        const int ovs = -(115 + svs);
        const int tvs = 295;
        
        auto dialControl = [&](const IRECT& b, int idx, int hs, int vs, const char *types, const char *name = nullptr)
        {
            double d = scheme.getDimension("DialDiameter", types);
            IRECT cb = b.GetCentredInside(d).GetVShifted(vs + ovs).GetHShifted(hs);
            
            return new HISSTools_Dial(idx, cb.L, cb.T, types, &scheme, name);
        };
        
        auto valueControl = [&](const IRECT& b, int idx, int hs, int vs, const char *types, const char *name = nullptr)
        {
            const double w = scheme.getDimension("ValueWidth", types);
            const double h = scheme.getDimension("ValueHeight", types);

            IRECT cb = b.GetCentredInside(w, h).GetVShifted(vs + ovs).GetHShifted(hs);
            
            return new HISSTools_Value(idx, cb.L, cb.T, w, h, types, &scheme, name);
        };
        
        auto buttonControl = [&](const IRECT& b, int idx, int midx, int hs, int vs, const char *types)
        {
            const double w = 120;
            const double h = 30;
            IRECT cb = b.GetCentredInside(w, h).GetVShifted(vs + ovs).GetHShifted(hs);
            
            return new Freeze_Button(idx, midx, cb.L, cb.T, w, h, types, &scheme);
        };
        
        auto panelControl = [&](const IRECT& b, const IRECT& p, const char *types)
        {
            IRECT cb = b.GetCentredInside(p.W(), p.H()).GetVShifted(p.T + ovs).GetHShifted(p.L);

            return new HISSTools_Panel(cb.L, cb.T, cb.W(), cb.H(), types, &scheme);
        };
        
        const IRECT b = pGraphics->GetBounds();
        
        // Name
        
        pGraphics->AttachControl(new HISSTools_TextBlock(0, 10 + tvs, PLUG_WIDTH, 50, "HISSTools Freeze", kHAlignCenter, kVAlignCenter, "name", &scheme));
        
        pGraphics->AttachControl(valueControl(b, kMode,    0,  80, "mode"));
        pGraphics->AttachControl(valueControl(b, kFFTSize, 0, -95, "above"));
        pGraphics->AttachControl(valueControl(b, kOverlap, 0, -65, ""));

        pGraphics->AttachControl(buttonControl(b, kFreeze, kMode, 0, 0, "tight"));
        
        pGraphics->AttachControl(dialControl(b, kBlur,     -120, -80, "1"));
        pGraphics->AttachControl(dialControl(b, kFragment,  120, -80, "1"));
        pGraphics->AttachControl(dialControl(b, kSample,   -120,  80, "1"));
        pGraphics->AttachControl(dialControl(b, kMorph,     120,  80, "1"));
        
        pGraphics->AttachControl(panelControl(b, HISSTools_Bounds(-65, 290 + svs, 290, 240), "lightShadow tighter"));
        
        pGraphics->AttachControl(new HISSTools_TextBlock(40, 570, 140, 20, "Morphing Filter", kHAlignCenter, kVAlignCenter, "label", &scheme));
        
        pGraphics->AttachControl(dialControl(b, kFiltStrength, -160, 290 + svs, "2 smallNormalLabel", "Strength"));
        pGraphics->AttachControl(dialControl(b, kFiltTilt,     -100, 220 + svs, "2 bipolar smallNormalLabel", "Tilt"));
        pGraphics->AttachControl(dialControl(b, kFiltInterval,  -30, 290 + svs, "3 smallNormalLabel", "Interval"));
        pGraphics->AttachControl(dialControl(b, kFiltRandom,     30, 220 + svs, "3 smallNormalLabel", "Random"));
        
        pGraphics->AttachControl(valueControl(b, kFiltNum, 20, 370 + svs, "", "Num Bands"));

        pGraphics->AttachControl(panelControl(b, HISSTools_Bounds(150, 290 + svs, 120, 240), "lightShadow tighter"));
        
        pGraphics->AttachControl(dialControl(b, kWidth, 150, 230 + svs, "4 bipolar medium"));
        pGraphics->AttachControl(dialControl(b, kGain,  150, 340 + svs, "4 bipolar medium"));
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
    
    mManualTriggers.Resize(GetBlockSize());
    mTriggers.Resize(GetBlockSize());
    
    ClearManualTriggers(GetBlockSize());
}

void HISSToolsFreeze::OnFragmentChange()
{
    auto scaled = [](double interp, double lo, double hi) {
        return hi * interp + lo * (1.0 - interp);
    };
    
    double fragment = pow(GetParam(kFragment)->GetNormalized(), 0.375);
    double bounds[4];
    
    const double octConvert = 1.0 / log2(16000.0 / 40.0);
    const double minOctave = 0.1;
    const double maxOctave = 0.3;
    const double minVal = minOctave * octConvert;
    const double maxVal = maxOctave * octConvert;
    
    bounds[0] = scaled(fragment, 0.50, 0.00 + (minVal * 0.5));
    bounds[1] = scaled(fragment, 0.50, 1.00 - (minVal * 0.5));
    bounds[2] = scaled(fragment, 0.50, minVal);
    bounds[3] = scaled(fragment, 0.50, maxVal);
    
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
            
        case kMorph:
        {
            double time = GetParam(kMorph)->Value();
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
                WDL_MutexLock lock(&mManualTriggerMutex);
 
                int offset = sampleOffset < 0 ? 0 : sampleOffset;
                bool freeze = GetParam(kFreeze)->Bool();
                mManualTriggers.Get()[offset] = freeze ? 1.0 : 0.0;
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
                
                GetUI()->DisableControl(kFiltStrength, zero);
                GetUI()->DisableControl(kFiltTilt, zero);
                GetUI()->DisableControl(kFiltInterval, zero);
                GetUI()->DisableControl(kFiltRandom, zero);
                break;
            }
        }
            
        case kMode:
        {
            if (GetUI())
            {
                Modes mode = (Modes) GetParam(kMode)->Int();
                
                GetUI()->DisableControl(kSample, mode == kManual);
                break;
            }
        }
        default:
            break;
    }
}

void HISSToolsFreeze::ClearManualTriggers(int nFrames)
{
    WDL_MutexLock lock(&mManualTriggerMutex);
    
    double* manualTriggers = mManualTriggers.Get();
    
    for (int i = 1; i < nFrames; i++)
        manualTriggers[i] = 0.0;
}

void HISSToolsFreeze::ProcessBlock(double** inputs, double** outputs, int nFrames)
{
    Modes mode = (Modes) GetParam(kMode)->Int();
    
    double* manualTriggers = mManualTriggers.Get();
    double* triggers = mTriggers.Get();
    double* dspInputs[3];
    double* plugInputs[2];
    
    plugInputs[0] = inputs[0];
    plugInputs[1] = NChannelsConnected(kInput) > 1 ?  inputs[1] : inputs[0];
    
    dspInputs[0] = outputs[0];
    dspInputs[1] = outputs[1];
    dspInputs[2] = triggers;

    // Parameters
    
    double sampling = GetParam(kSample)->Value();
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
    
    // Get Input
    
    for (int i = 0; i < nFrames; i++)
    {
        outputs[0][i] = plugInputs[0][i];
        outputs[1][i] = plugInputs[1][i];
    }
    
    // Sampling
    
    switch (mode)
    {
        case kRegular:
        {
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
            ClearManualTriggers(nFrames);
            break;
        }
            
        case kRandomised:
        {
            for (int i = 0; i < nFrames; i++)
                triggers[i] = (std::rand() / (RAND_MAX + 1.0)) > threshold;
            ClearManualTriggers(nFrames);
            break;
        }
            
        case kManual:
        {
            WDL_MutexLock lock(&mManualTriggerMutex);
            
            for (int i = 0; i < nFrames; i++)
            {
                triggers[i] = manualTriggers[i];
                manualTriggers[i] = 0.0;
            }
            break;
        }
    }
    
    
    // Main process
    
    mDSP.process(dspInputs, outputs, nFrames);
    
    // MS Processing
    
    for (int i = 0; i < nFrames; i++)
    {
        const double gain = mGainSmoother() * 0.5;
        const double width = mWidthSmoother();
        double L = outputs[0][i] * gain;
        double R = outputs[1][i] * gain;
        double M = (L + R);
        double S = (L - R) * width;
        
        outputs[0][i] = (M + S);
        outputs[1][i] = (M - S);
    }
}
