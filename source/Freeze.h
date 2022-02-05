
#include <FrameLib_Multistream.h>
#include <vector>

class Freeze
{

public:

    Freeze(FrameLib_Proxy *proxy = new FrameLib_Proxy());
    ~Freeze();

    void reset(double samplerate, unsigned long maxvectorsize);
    void process(double **inputs, double **output, unsigned long blockSize);

    unsigned long getNumAudioIns() const { return mNumAudioIns; }
    unsigned long getNumAudioOuts() const  { return mNumAudioOuts; }

private:

    FrameLib_Global *mGlobal;
    std::vector<FrameLib_Multistream *> mObjects;
    std::vector<FrameLib_Multistream *> mAudioObjects;
    unsigned long mNumAudioIns;
    unsigned long mNumAudioOuts;
    FrameLib_Proxy *mProxy;
};