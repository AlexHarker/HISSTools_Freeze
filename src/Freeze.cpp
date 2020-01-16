
#include "Freeze.h"
#include "FrameLib_Objects.h"

Freeze::Freeze(FrameLib_Proxy *proxy) : mGlobal(nullptr), mNumAudioIns(0), mNumAudioOuts(0), mProxy(proxy)
{
    using Connection = FrameLib_Object<FrameLib_Multistream>::Connection;

    FrameLib_Global::get(&mGlobal, FrameLib_Thread::defaultPriorities());
    FrameLib_Context context(mGlobal, this);
    FrameLib_Parameters::AutoSerial parameters;

    mObjects.resize(163);

    double fl_0_vector_0[] = { 8 };
    parameters.clear();
    parameters.write("interval", fl_0_vector_0, 1);
    mObjects[0] = new FrameLib_Expand<FrameLib_Interval>(context, &parameters, mProxy, 1);

    parameters.clear();
    mObjects[1] = new FrameLib_Expand<FrameLib_FromHost>(context, &parameters, mProxy, 1);
    mObjects[1]->addConnection(Connection(mObjects[0], 0), 0);

    parameters.clear();
    mObjects[2] = new FrameLib_Expand<FrameLib_FromHost>(context, &parameters, mProxy, 1);
    mObjects[2]->addConnection(Connection(mObjects[0], 0), 0);

    parameters.clear();
    mObjects[3] = new FrameLib_Expand<FrameLib_BinaryOp<std::divides<double> > >(context, &parameters, mProxy, 1);
    mObjects[3]->addConnection(Connection(mObjects[2], 0), 0);
    mObjects[3]->addConnection(Connection(mObjects[1], 0), 1);

    parameters.clear();
    parameters.write("tag_01", "interval");
    mObjects[4] = new FrameLib_Expand<FrameLib_Tag>(context, &parameters, mProxy, 1);
    mObjects[4]->addConnection(Connection(mObjects[3], 0), 0);

    double fl_5_vector_0[] = { 512 };
    parameters.clear();
    parameters.write("interval", fl_5_vector_0, 1);
    mObjects[5] = new FrameLib_Expand<FrameLib_Interval>(context, &parameters, mProxy, 1);
    mObjects[5]->addConnection(Connection(mObjects[4], 0), 0);

    parameters.clear();
    parameters.write("tag_01", "length");
    mObjects[6] = new FrameLib_Expand<FrameLib_Tag>(context, &parameters, mProxy, 1);
    mObjects[6]->addConnection(Connection(mObjects[2], 0), 0);

    double fl_7_vector_0[] = { 65536 };
    double fl_7_vector_1[] = { 4096 };
    parameters.clear();
    parameters.write("buffer_size", fl_7_vector_0, 1);
    parameters.write("length", fl_7_vector_1, 1);
    mObjects[7] = new FrameLib_Expand<FrameLib_Source>(context, &parameters, mProxy, 2);
    mObjects[7]->addConnection(Connection(mObjects[5], 0), 0);
    mObjects[7]->addConnection(Connection(mObjects[6], 0), 1);

    parameters.clear();
    mObjects[8] = new FrameLib_Expand<FrameLib_BinaryOp<std::equal_to<double> > >(context, &parameters, mProxy, 1);
    double fl_8_inputs_1[] = { 2 };
    mObjects[8]->setFixedInput(1, fl_8_inputs_1 , 1);
    mObjects[8]->addConnection(Connection(mObjects[1], 0), 0);

    parameters.clear();
    parameters.write("tag_01", "sqrt");
    mObjects[9] = new FrameLib_Expand<FrameLib_Tag>(context, &parameters, mProxy, 1);
    mObjects[9]->addConnection(Connection(mObjects[8], 0), 0);

    parameters.clear();
    parameters.write("window", "hann");
    parameters.write("compensate", "linear");
    mObjects[10] = new FrameLib_Expand<FrameLib_Window>(context, &parameters, mProxy, 1);
    mObjects[10]->addConnection(Connection(mObjects[7], 0), 0);
    mObjects[10]->addConnection(Connection(mObjects[9], 0), 1);

    double fl_11_vector_0[] = { 65536 };
    parameters.clear();
    parameters.write("maxlength", fl_11_vector_0, 1);
    mObjects[11] = new FrameLib_Expand<FrameLib_FFT>(context, &parameters, mProxy, 1);
    mObjects[11]->addConnection(Connection(mObjects[10], 0), 0);

    parameters.clear();
    mObjects[12] = new FrameLib_Expand<FrameLib_BinaryOp<Binary_Functor<&atan2> > >(context, &parameters, mProxy, 1);
    mObjects[12]->addConnection(Connection(mObjects[11], 1), 0);
    mObjects[12]->addConnection(Connection(mObjects[11], 0), 1);

    parameters.clear();
    mObjects[13] = new FrameLib_Expand<FrameLib_FrameDelta>(context, &parameters, mProxy, 1);
    mObjects[13]->addConnection(Connection(mObjects[12], 0), 0);

    parameters.clear();
    mObjects[14] = new FrameLib_Expand<FrameLib_BinaryOp<Binary_Functor<&hypot> > >(context, &parameters, mProxy, 1);
    mObjects[14]->addConnection(Connection(mObjects[11], 0), 0);
    mObjects[14]->addConnection(Connection(mObjects[11], 1), 1);

    parameters.clear();
    parameters.write("mode", "input");
    mObjects[15] = new FrameLib_Expand<FrameLib_Random>(context, &parameters, mProxy, 1);
    mObjects[15]->addConnection(Connection(mObjects[14], 0), 0);

    parameters.clear();
    mObjects[16] = new FrameLib_Expand<FrameLib_BinaryOp<std::equal_to<double> > >(context, &parameters, mProxy, 1);
    double fl_16_inputs_1[] = { 0 };
    mObjects[16]->setFixedInput(1, fl_16_inputs_1 , 1);
    mObjects[16]->addConnection(Connection(mObjects[14], 0), 0);

    parameters.clear();
    mObjects[17] = new FrameLib_Expand<FrameLib_BinaryOp<std::multiplies<double> > >(context, &parameters, mProxy, 1);
    mObjects[17]->addConnection(Connection(mObjects[16], 0), 0);
    mObjects[17]->addConnection(Connection(mObjects[15], 0), 1);

    parameters.clear();
    parameters.write("expr", "in1 * 2 * pi");
    mObjects[18] = new FrameLib_Expand<FrameLib_Expression>(context, &parameters, mProxy, 1);
    mObjects[18]->addConnection(Connection(mObjects[17], 0), 0);

    parameters.clear();
    mObjects[19] = new FrameLib_Expand<FrameLib_BinaryOp<std::plus<double> > >(context, &parameters, mProxy, 1);
    mObjects[19]->addConnection(Connection(mObjects[18], 0), 0);
    mObjects[19]->addConnection(Connection(mObjects[13], 0), 1);

    parameters.clear();
    mObjects[20] = new FrameLib_Expand<FrameLib_UnaryOp<Unary_Functor<&cos> > >(context, &parameters, mProxy, 1);
    mObjects[20]->addConnection(Connection(mObjects[19], 0), 0);

    double fl_21_vector_0[] = { 1 };
    parameters.clear();
    parameters.write("outputs", fl_21_vector_0, 1);
    mObjects[21] = new FrameLib_Unpack(context, &parameters, mProxy, 1);
    mObjects[21]->addConnection(Connection(mObjects[11], 1), 0);

    parameters.clear();
    mObjects[22] = new FrameLib_Expand<FrameLib_Now>(context, &parameters, mProxy, 1);
    mObjects[22]->addConnection(Connection(mObjects[21], 0), 0);

    parameters.clear();
    mObjects[23] = new FrameLib_Expand<FrameLib_BinaryOp<std::equal_to<double> > >(context, &parameters, mProxy, 1);
    double fl_23_inputs_1[] = { 0 };
    mObjects[23]->setFixedInput(1, fl_23_inputs_1 , 1);
    mObjects[23]->addConnection(Connection(mObjects[22], 0), 0);

    parameters.clear();
    mObjects[24] = new FrameLib_Expand<FrameLib_Register>(context, &parameters, mProxy, 1);
    mObjects[24]->addConnection(Connection(mObjects[21], 0), 0);
    mObjects[24]->addConnection(Connection(mObjects[2], 0), 1);

    parameters.clear();
    mObjects[25] = new FrameLib_Expand<FrameLib_FrameDelta>(context, &parameters, mProxy, 1);
    mObjects[25]->addConnection(Connection(mObjects[24], 0), 0);

    parameters.clear();
    mObjects[26] = new FrameLib_Expand<FrameLib_Register>(context, &parameters, mProxy, 1);
    mObjects[26]->addConnection(Connection(mObjects[21], 0), 0);
    mObjects[26]->addConnection(Connection(mObjects[1], 0), 1);

    parameters.clear();
    mObjects[27] = new FrameLib_Expand<FrameLib_FrameDelta>(context, &parameters, mProxy, 1);
    mObjects[27]->addConnection(Connection(mObjects[26], 0), 0);

    parameters.clear();
    mObjects[28] = new FrameLib_Expand<FrameLib_BinaryOp<std::logical_or<double> > >(context, &parameters, mProxy, 1);
    mObjects[28]->addConnection(Connection(mObjects[25], 0), 0);
    mObjects[28]->addConnection(Connection(mObjects[27], 0), 1);

    parameters.clear();
    mObjects[29] = new FrameLib_Expand<FrameLib_BinaryOp<std::logical_or<double> > >(context, &parameters, mProxy, 1);
    mObjects[29]->addConnection(Connection(mObjects[28], 0), 0);
    mObjects[29]->addConnection(Connection(mObjects[23], 0), 1);

    parameters.clear();
    parameters.write("tag_01", "input");
    mObjects[30] = new FrameLib_Expand<FrameLib_Tag>(context, &parameters, mProxy, 1);
    mObjects[30]->addConnection(Connection(mObjects[29], 0), 0);

    parameters.clear();
    mObjects[31] = new FrameLib_Expand<FrameLib_Select>(context, &parameters, mProxy, 1);
    mObjects[31]->addConnection(Connection(mObjects[21], 0), 0);
    mObjects[31]->addConnection(Connection(mObjects[30], 0), 2);

    parameters.clear();
    parameters.write("mode", "input");
    mObjects[32] = new FrameLib_Expand<FrameLib_Uniform>(context, &parameters, mProxy, 1);
    mObjects[32]->addConnection(Connection(mObjects[31], 0), 0);

    parameters.clear();
    parameters.write("mode", "input");
    parameters.write("scale", "normalised");
    mObjects[33] = new FrameLib_Expand<FrameLib_Ramp>(context, &parameters, mProxy, 1);
    mObjects[33]->addConnection(Connection(mObjects[32], 0), 0);

    parameters.clear();
    mObjects[34] = new FrameLib_Expand<FrameLib_Register>(context, &parameters, mProxy, 1);
    double fl_34_inputs_1[] = { 40 };
    mObjects[34]->setFixedInput(1, fl_34_inputs_1 , 1);
    mObjects[34]->addConnection(Connection(mObjects[33], 0), 0);

    parameters.clear();
    parameters.write("mode", "freq->halfnorm");
    mObjects[35] = new FrameLib_Expand<FrameLib_SampleRate>(context, &parameters, mProxy, 1);
    mObjects[35]->addConnection(Connection(mObjects[34], 0), 0);

    parameters.clear();
    mObjects[36] = new FrameLib_Expand<FrameLib_Register>(context, &parameters, mProxy, 1);
    double fl_36_inputs_1[] = { 40 };
    mObjects[36]->setFixedInput(1, fl_36_inputs_1 , 1);
    mObjects[36]->addConnection(Connection(mObjects[33], 0), 0);

    parameters.clear();
    parameters.write("mode", "freq->halfnorm");
    mObjects[37] = new FrameLib_Expand<FrameLib_SampleRate>(context, &parameters, mProxy, 1);
    mObjects[37]->addConnection(Connection(mObjects[36], 0), 0);

    parameters.clear();
    parameters.write("tag_01", "inlo");
    parameters.write("tag_02", "outlo");
    mObjects[38] = new FrameLib_Expand<FrameLib_Tag>(context, &parameters, mProxy, 1);
    mObjects[38]->addConnection(Connection(mObjects[37], 0), 0);
    mObjects[38]->addConnection(Connection(mObjects[35], 0), 1);

    double fl_39_vector_1[] = { 0.002000 };
    double fl_39_vector_2[] = { 0.600000 };
    double fl_39_vector_3[] = { 0 };
    double fl_39_vector_4[] = { 1 };
    double fl_39_vector_5[] = { 1 };
    parameters.clear();
    parameters.write("mode", "log");
    parameters.write("inlo", fl_39_vector_1, 1);
    parameters.write("inhi", fl_39_vector_2, 1);
    parameters.write("outlo", fl_39_vector_3, 1);
    parameters.write("outhi", fl_39_vector_4, 1);
    parameters.write("clip", fl_39_vector_5, 1);
    mObjects[39] = new FrameLib_Expand<FrameLib_Map>(context, &parameters, mProxy, 1);
    mObjects[39]->addConnection(Connection(mObjects[33], 0), 0);
    mObjects[39]->addConnection(Connection(mObjects[38], 0), 1);

    double fl_40_vector_0[] = { 64 };
    parameters.clear();
    parameters.write("interval", fl_40_vector_0, 1);
    mObjects[40] = new FrameLib_Expand<FrameLib_Interval>(context, &parameters, mProxy, 1);

    parameters.clear();
    parameters.write("mode", "params");
    mObjects[41] = new FrameLib_Expand<FrameLib_FromHost>(context, &parameters, mProxy, 1);
    mObjects[41]->addConnection(Connection(mObjects[40], 0), 0);

    parameters.clear();
    mObjects[42] = new FrameLib_Expand<FrameLib_Random>(context, &parameters, mProxy, 1);
    mObjects[42]->addConnection(Connection(mObjects[40], 0), 0);

    double fl_43_vector_1[] = { 0 };
    double fl_43_vector_2[] = { 1 };
    double fl_43_vector_3[] = { 200 };
    double fl_43_vector_4[] = { 600 };
    parameters.clear();
    parameters.write("mode", "exp");
    parameters.write("inlo", fl_43_vector_1, 1);
    parameters.write("inhi", fl_43_vector_2, 1);
    parameters.write("outlo", fl_43_vector_3, 1);
    parameters.write("outhi", fl_43_vector_4, 1);
    mObjects[43] = new FrameLib_Expand<FrameLib_Map>(context, &parameters, mProxy, 1);
    mObjects[43]->addConnection(Connection(mObjects[42], 0), 0);
    mObjects[43]->addConnection(Connection(mObjects[41], 0), 1);

    parameters.clear();
    parameters.write("tag_01", "interval");
    mObjects[44] = new FrameLib_Expand<FrameLib_Tag>(context, &parameters, mProxy, 1);
    mObjects[44]->addConnection(Connection(mObjects[43], 0), 0);

    parameters.clear();
    parameters.write("units", "ms");
    mObjects[45] = new FrameLib_Expand<FrameLib_Interval>(context, &parameters, mProxy, 1);
    mObjects[45]->addConnection(Connection(mObjects[44], 0), 0);

    parameters.clear();
    mObjects[46] = new FrameLib_Expand<FrameLib_Register>(context, &parameters, mProxy, 1);
    mObjects[46]->addConnection(Connection(mObjects[45], 0), 0);
    mObjects[46]->addConnection(Connection(mObjects[43], 0), 1);

    parameters.clear();
    mObjects[47] = new FrameLib_Expand<FrameLib_Register>(context, &parameters, mProxy, 1);
    mObjects[47]->addConnection(Connection(mObjects[32], 0), 0);
    mObjects[47]->addConnection(Connection(mObjects[3], 0), 1);

    parameters.clear();
    parameters.write("mode", "samples->seconds");
    mObjects[48] = new FrameLib_Expand<FrameLib_SampleRate>(context, &parameters, mProxy, 1);
    mObjects[48]->addConnection(Connection(mObjects[47], 0), 0);

    parameters.clear();
    mObjects[49] = new FrameLib_Expand<FrameLib_FromHost>(context, &parameters, mProxy, 1);
    mObjects[49]->addConnection(Connection(mObjects[11], 1), 0);

    parameters.clear();
    parameters.write("expr", "round(in2 / (in1 * 1000)) + 1");
    mObjects[50] = new FrameLib_Expand<FrameLib_Expression>(context, &parameters, mProxy, 1);
    mObjects[50]->addConnection(Connection(mObjects[48], 0), 0);
    mObjects[50]->addConnection(Connection(mObjects[49], 0), 1);

    parameters.clear();
    parameters.write("expr", "round(2 / in1) + 1");
    mObjects[51] = new FrameLib_Expand<FrameLib_Expression>(context, &parameters, mProxy, 1);
    mObjects[51]->addConnection(Connection(mObjects[48], 0), 0);

    parameters.clear();
    parameters.write("tag_01", "max_frames");
    parameters.write("tag_02", "num_frames");
    mObjects[52] = new FrameLib_Expand<FrameLib_Tag>(context, &parameters, mProxy, 1);
    mObjects[52]->addConnection(Connection(mObjects[51], 0), 0);
    mObjects[52]->addConnection(Connection(mObjects[50], 0), 1);

    double fl_53_vector_0[] = { 100 };
    double fl_53_vector_1[] = { 20 };
    parameters.clear();
    parameters.write("max_frames", fl_53_vector_0, 1);
    parameters.write("num_frames", fl_53_vector_1, 1);
    mObjects[53] = new FrameLib_Expand<FrameLib_TimeMean>(context, &parameters, mProxy, 1);
    mObjects[53]->addConnection(Connection(mObjects[20], 0), 0);
    mObjects[53]->addConnection(Connection(mObjects[52], 0), 1);

    parameters.clear();
    mObjects[54] = new FrameLib_Expand<FrameLib_BinaryOp<std::multiplies<double> > >(context, &parameters, mProxy, 1);
    mObjects[54]->addConnection(Connection(mObjects[53], 0), 0);
    mObjects[54]->addConnection(Connection(mObjects[53], 0), 1);

    parameters.clear();
    mObjects[55] = new FrameLib_Expand<FrameLib_UnaryOp<Unary_Functor<&sin> > >(context, &parameters, mProxy, 1);
    mObjects[55]->addConnection(Connection(mObjects[19], 0), 0);

    double fl_56_vector_0[] = { 100 };
    double fl_56_vector_1[] = { 20 };
    parameters.clear();
    parameters.write("max_frames", fl_56_vector_0, 1);
    parameters.write("num_frames", fl_56_vector_1, 1);
    mObjects[56] = new FrameLib_Expand<FrameLib_TimeMean>(context, &parameters, mProxy, 1);
    mObjects[56]->addConnection(Connection(mObjects[55], 0), 0);
    mObjects[56]->addConnection(Connection(mObjects[52], 0), 1);

    parameters.clear();
    mObjects[57] = new FrameLib_Expand<FrameLib_BinaryOp<std::multiplies<double> > >(context, &parameters, mProxy, 1);
    mObjects[57]->addConnection(Connection(mObjects[56], 0), 0);
    mObjects[57]->addConnection(Connection(mObjects[56], 0), 1);

    parameters.clear();
    mObjects[58] = new FrameLib_Expand<FrameLib_BinaryOp<std::plus<double> > >(context, &parameters, mProxy, 1);
    mObjects[58]->addConnection(Connection(mObjects[57], 0), 0);
    mObjects[58]->addConnection(Connection(mObjects[54], 0), 1);

    parameters.clear();
    parameters.write("expr", "max(in1, exp(-4*pi*pi))");
    mObjects[59] = new FrameLib_Expand<FrameLib_Expression>(context, &parameters, mProxy, 1);
    mObjects[59]->addConnection(Connection(mObjects[58], 0), 0);

    parameters.clear();
    mObjects[60] = new FrameLib_Expand<FrameLib_UnaryOp<Unary_Functor<&log> > >(context, &parameters, mProxy, 1);
    mObjects[60]->addConnection(Connection(mObjects[59], 0), 0);

    parameters.clear();
    mObjects[61] = new FrameLib_Expand<FrameLib_BinaryOp<std::multiplies<double> > >(context, &parameters, mProxy, 1);
    double fl_61_inputs_1[] = { -1 };
    mObjects[61]->setFixedInput(1, fl_61_inputs_1 , 1);
    mObjects[61]->addConnection(Connection(mObjects[60], 0), 0);

    parameters.clear();
    mObjects[62] = new FrameLib_Expand<FrameLib_BinaryOp<Binary_Functor<&fmax> > >(context, &parameters, mProxy, 1);
    double fl_62_inputs_1[] = { 0 };
    mObjects[62]->setFixedInput(1, fl_62_inputs_1 , 1);
    mObjects[62]->addConnection(Connection(mObjects[61], 0), 0);

    parameters.clear();
    mObjects[63] = new FrameLib_Expand<FrameLib_UnaryOp<Unary_Functor<&sqrt> > >(context, &parameters, mProxy, 1);
    mObjects[63]->addConnection(Connection(mObjects[62], 0), 0);

    double fl_64_vector_0[] = { 100 };
    double fl_64_vector_1[] = { 20 };
    parameters.clear();
    parameters.write("max_frames", fl_64_vector_0, 1);
    parameters.write("num_frames", fl_64_vector_1, 1);
    mObjects[64] = new FrameLib_Expand<FrameLib_TimeMean>(context, &parameters, mProxy, 1);
    mObjects[64]->addConnection(Connection(mObjects[14], 0), 0);
    mObjects[64]->addConnection(Connection(mObjects[52], 0), 1);

    double fl_65_vector_0[] = { 100 };
    double fl_65_vector_1[] = { 20 };
    parameters.clear();
    parameters.write("max_frames", fl_65_vector_0, 1);
    parameters.write("num_frames", fl_65_vector_1, 1);
    mObjects[65] = new FrameLib_Expand<FrameLib_TimeStdDev>(context, &parameters, mProxy, 1);
    mObjects[65]->addConnection(Connection(mObjects[14], 0), 0);
    mObjects[65]->addConnection(Connection(mObjects[52], 0), 1);

    parameters.clear();
    mObjects[66] = new FrameLib_Expand<FrameLib_BinaryOp<Binary_Functor<&atan2> > >(context, &parameters, mProxy, 1);
    mObjects[66]->addConnection(Connection(mObjects[56], 0), 0);
    mObjects[66]->addConnection(Connection(mObjects[53], 0), 1);

    double fl_67_vector_0[] = { 4 };
    parameters.clear();
    parameters.write("inputs", fl_67_vector_0, 1);
    mObjects[67] = new FrameLib_Pack(context, &parameters, mProxy, 1);
    mObjects[67]->addConnection(Connection(mObjects[64], 0), 0);
    mObjects[67]->addConnection(Connection(mObjects[65], 0), 1);
    mObjects[67]->addConnection(Connection(mObjects[66], 0), 2);
    mObjects[67]->addConnection(Connection(mObjects[63], 0), 3);

    parameters.clear();
    mObjects[68] = new FrameLib_Expand<FrameLib_FromHost>(context, &parameters, mProxy, 1);
    mObjects[68]->addConnection(Connection(mObjects[67], 0), 0);

    parameters.clear();
    mObjects[69] = new FrameLib_Expand<FrameLib_BinaryOp<Binary_Functor<&fmax> > >(context, &parameters, mProxy, 1);
    double fl_69_inputs_1[] = { 0.010000 };
    mObjects[69]->setFixedInput(1, fl_69_inputs_1 , 1);
    mObjects[69]->addConnection(Connection(mObjects[68], 0), 0);

    parameters.clear();
    mObjects[70] = new FrameLib_Expand<FrameLib_AudioTrigger>(context, &parameters, mProxy, 1);

    double fl_71_vector_0[] = { 2 };
    parameters.clear();
    parameters.write("num_ins", fl_71_vector_0, 1);
    parameters.write("mode", "high");
    mObjects[71] = new FrameLib_Expand<FrameLib_Prioritise>(context, &parameters, mProxy, 1);
    mObjects[71]->addConnection(Connection(mObjects[70], 0), 0);
    mObjects[71]->addConnection(Connection(mObjects[32], 0), 1);

    parameters.clear();
    parameters.write("units", "ms");
    mObjects[72] = new FrameLib_Expand<FrameLib_Timer>(context, &parameters, mProxy, 8);
    mObjects[72]->addConnection(Connection(mObjects[71], 0), 0);
    mObjects[72]->addConnection(Connection(mObjects[67], 0), 1);

    parameters.clear();
    mObjects[73] = new FrameLib_Expand<FrameLib_BinaryOp<std::divides<double> > >(context, &parameters, mProxy, 1);
    mObjects[73]->addConnection(Connection(mObjects[72], 0), 0);
    mObjects[73]->addConnection(Connection(mObjects[69], 0), 1);

    parameters.clear();
    mObjects[74] = new FrameLib_Expand<FrameLib_TernaryOp<Ternary_Functor<&FrameLib_Ternary_Ops::clip<double>> > >(context, &parameters, mProxy, 1);
    double fl_74_inputs_1[] = { 0 };
    double fl_74_inputs_2[] = { 1 };
    mObjects[74]->setFixedInput(1, fl_74_inputs_1 , 1);
    mObjects[74]->setFixedInput(2, fl_74_inputs_2 , 1);
    mObjects[74]->addConnection(Connection(mObjects[73], 0), 0);

    parameters.clear();
    parameters.write("name", "last");
    mObjects[75] = new FrameLib_Expand<FrameLib_Recall>(context, &parameters, mProxy, 8);
    mObjects[75]->addConnection(Connection(mObjects[70], 0), 0);

    double fl_76_vector_0[] = { 6 };
    parameters.clear();
    parameters.write("inputs", fl_76_vector_0, 1);
    mObjects[76] = new FrameLib_Pack(context, &parameters, mProxy, 1);
    mObjects[76]->addConnection(Connection(mObjects[32], 0), 0);
    mObjects[76]->addConnection(Connection(mObjects[32], 0), 1);
    mObjects[76]->addConnection(Connection(mObjects[32], 0), 2);
    mObjects[76]->addConnection(Connection(mObjects[32], 0), 3);
    mObjects[76]->addConnection(Connection(mObjects[32], 0), 4);
    mObjects[76]->addConnection(Connection(mObjects[32], 0), 5);

    double fl_77_vector_0[] = { 2 };
    parameters.clear();
    parameters.write("inputs", fl_77_vector_0, 1);
    mObjects[77] = new FrameLib_Pack(context, &parameters, mProxy, 1);
    mObjects[77]->addConnection(Connection(mObjects[32], 0), 0);
    mObjects[77]->addConnection(Connection(mObjects[32], 0), 1);

    parameters.clear();
    parameters.write("mode", "input");
    mObjects[78] = new FrameLib_Expand<FrameLib_Random>(context, &parameters, mProxy, 1);
    mObjects[78]->addConnection(Connection(mObjects[77], 0), 0);

    parameters.clear();
    parameters.write("expr", "in1 * 2 * pi");
    mObjects[79] = new FrameLib_Expand<FrameLib_Expression>(context, &parameters, mProxy, 1);
    mObjects[79]->addConnection(Connection(mObjects[78], 0), 0);

    parameters.clear();
    mObjects[80] = new FrameLib_Pack(context, &parameters, mProxy, 1);
    mObjects[80]->addConnection(Connection(mObjects[76], 0), 0);
    mObjects[80]->addConnection(Connection(mObjects[79], 0), 1);

    parameters.clear();
    mObjects[81] = new FrameLib_Expand<FrameLib_Register>(context, &parameters, mProxy, 1);
    mObjects[81]->addConnection(Connection(mObjects[70], 0), 0);
    mObjects[81]->addConnection(Connection(mObjects[67], 0), 1);

    double fl_82_vector_0[] = { 1 };
    parameters.clear();
    parameters.write("outputs", fl_82_vector_0, 1);
    mObjects[82] = new FrameLib_Unpack(context, &parameters, mProxy, 1);
    mObjects[82]->addConnection(Connection(mObjects[81], 0), 0);

    parameters.clear();
    mObjects[83] = new FrameLib_Expand<FrameLib_Random>(context, &parameters, mProxy, 1);
    mObjects[83]->addConnection(Connection(mObjects[82], 0), 0);

    parameters.clear();
    mObjects[84] = new FrameLib_Expand<FrameLib_FromHost>(context, &parameters, mProxy, 1);
    mObjects[84]->addConnection(Connection(mObjects[82], 0), 0);

    double fl_85_vector_0[] = { 4 };
    double fl_85_vector_1[] = { 1 };
    parameters.clear();
    parameters.write("num_outs", fl_85_vector_0, 1);
    parameters.write("size", fl_85_vector_1, 1);
    mObjects[85] = new FrameLib_Expand<FrameLib_Chop>(context, &parameters, mProxy, 1);
    mObjects[85]->addConnection(Connection(mObjects[84], 0), 0);

    parameters.clear();
    parameters.write("tag_01", "outlo");
    parameters.write("tag_02", "outhi");
    mObjects[86] = new FrameLib_Expand<FrameLib_Tag>(context, &parameters, mProxy, 1);
    mObjects[86]->addConnection(Connection(mObjects[85], 0), 0);
    mObjects[86]->addConnection(Connection(mObjects[85], 1), 1);

    parameters.clear();
    mObjects[87] = new FrameLib_Expand<FrameLib_Random>(context, &parameters, mProxy, 1);
    mObjects[87]->addConnection(Connection(mObjects[82], 0), 0);

    double fl_88_vector_1[] = { 0 };
    double fl_88_vector_2[] = { 1 };
    double fl_88_vector_3[] = { 0.500000 };
    double fl_88_vector_4[] = { 0.500000 };
    parameters.clear();
    parameters.write("mode", "linear");
    parameters.write("inlo", fl_88_vector_1, 1);
    parameters.write("inhi", fl_88_vector_2, 1);
    parameters.write("outlo", fl_88_vector_3, 1);
    parameters.write("outhi", fl_88_vector_4, 1);
    mObjects[88] = new FrameLib_Expand<FrameLib_Map>(context, &parameters, mProxy, 1);
    mObjects[88]->addConnection(Connection(mObjects[87], 0), 0);
    mObjects[88]->addConnection(Connection(mObjects[86], 0), 1);

    parameters.clear();
    parameters.write("tag_01", "outlo");
    parameters.write("tag_02", "outhi");
    mObjects[89] = new FrameLib_Expand<FrameLib_Tag>(context, &parameters, mProxy, 1);
    mObjects[89]->addConnection(Connection(mObjects[85], 2), 0);
    mObjects[89]->addConnection(Connection(mObjects[85], 3), 1);

    double fl_90_vector_1[] = { 0 };
    double fl_90_vector_2[] = { 1 };
    double fl_90_vector_3[] = { 0.500000 };
    double fl_90_vector_4[] = { 0.500000 };
    parameters.clear();
    parameters.write("mode", "linear");
    parameters.write("inlo", fl_90_vector_1, 1);
    parameters.write("inhi", fl_90_vector_2, 1);
    parameters.write("outlo", fl_90_vector_3, 1);
    parameters.write("outhi", fl_90_vector_4, 1);
    mObjects[90] = new FrameLib_Expand<FrameLib_Map>(context, &parameters, mProxy, 1);
    mObjects[90]->addConnection(Connection(mObjects[83], 0), 0);
    mObjects[90]->addConnection(Connection(mObjects[89], 0), 1);

    parameters.clear();
    mObjects[91] = new FrameLib_Expand<FrameLib_Register>(context, &parameters, mProxy, 1);
    double fl_91_inputs_1[] = { 0.010000 };
    mObjects[91]->setFixedInput(1, fl_91_inputs_1 , 1);
    mObjects[91]->addConnection(Connection(mObjects[90], 0), 0);

    parameters.clear();
    mObjects[92] = new FrameLib_Expand<FrameLib_BinaryOp<std::plus<double> > >(context, &parameters, mProxy, 1);
    mObjects[92]->addConnection(Connection(mObjects[88], 0), 0);
    mObjects[92]->addConnection(Connection(mObjects[90], 0), 1);

    parameters.clear();
    mObjects[93] = new FrameLib_Expand<FrameLib_BinaryOp<std::plus<double> > >(context, &parameters, mProxy, 1);
    mObjects[93]->addConnection(Connection(mObjects[92], 0), 0);
    mObjects[93]->addConnection(Connection(mObjects[91], 0), 1);

    parameters.clear();
    parameters.write("tag_01", "inlo");
    parameters.write("tag_02", "inhi");
    mObjects[94] = new FrameLib_Expand<FrameLib_Tag>(context, &parameters, mProxy, 1);
    mObjects[94]->addConnection(Connection(mObjects[92], 0), 0);
    mObjects[94]->addConnection(Connection(mObjects[93], 0), 1);

    parameters.clear();
    parameters.write("mode", "input");
    parameters.write("scale", "normalised");
    mObjects[95] = new FrameLib_Expand<FrameLib_Ramp>(context, &parameters, mProxy, 1);
    mObjects[95]->addConnection(Connection(mObjects[32], 0), 0);

    parameters.clear();
    parameters.write("mode", "halfnorm->freq");
    mObjects[96] = new FrameLib_Expand<FrameLib_SampleRate>(context, &parameters, mProxy, 1);
    mObjects[96]->addConnection(Connection(mObjects[95], 0), 0);

    double fl_97_vector_1[] = { 40 };
    double fl_97_vector_2[] = { 16000 };
    double fl_97_vector_3[] = { 0 };
    double fl_97_vector_4[] = { 1 };
    double fl_97_vector_5[] = { 1 };
    parameters.clear();
    parameters.write("mode", "log");
    parameters.write("inlo", fl_97_vector_1, 1);
    parameters.write("inhi", fl_97_vector_2, 1);
    parameters.write("outlo", fl_97_vector_3, 1);
    parameters.write("outhi", fl_97_vector_4, 1);
    parameters.write("clip", fl_97_vector_5, 1);
    mObjects[97] = new FrameLib_Expand<FrameLib_Map>(context, &parameters, mProxy, 1);
    mObjects[97]->addConnection(Connection(mObjects[96], 0), 0);

    parameters.clear();
    mObjects[98] = new FrameLib_Expand<FrameLib_Register>(context, &parameters, mProxy, 1);
    mObjects[98]->addConnection(Connection(mObjects[82], 0), 0);
    mObjects[98]->addConnection(Connection(mObjects[97], 0), 1);

    double fl_99_vector_1[] = { 35 };
    double fl_99_vector_2[] = { 45 };
    double fl_99_vector_3[] = { 1 };
    double fl_99_vector_4[] = { 0 };
    double fl_99_vector_5[] = { 1 };
    parameters.clear();
    parameters.write("mode", "linear");
    parameters.write("inlo", fl_99_vector_1, 1);
    parameters.write("inhi", fl_99_vector_2, 1);
    parameters.write("outlo", fl_99_vector_3, 1);
    parameters.write("outhi", fl_99_vector_4, 1);
    parameters.write("clip", fl_99_vector_5, 1);
    mObjects[99] = new FrameLib_Expand<FrameLib_Map>(context, &parameters, mProxy, 1);
    mObjects[99]->addConnection(Connection(mObjects[98], 0), 0);
    mObjects[99]->addConnection(Connection(mObjects[94], 0), 1);

    parameters.clear();
    mObjects[100] = new FrameLib_Expand<FrameLib_BinaryOp<std::minus<double> > >(context, &parameters, mProxy, 1);
    mObjects[100]->addConnection(Connection(mObjects[88], 0), 0);
    mObjects[100]->addConnection(Connection(mObjects[90], 0), 1);

    parameters.clear();
    mObjects[101] = new FrameLib_Expand<FrameLib_BinaryOp<std::minus<double> > >(context, &parameters, mProxy, 1);
    mObjects[101]->addConnection(Connection(mObjects[100], 0), 0);
    mObjects[101]->addConnection(Connection(mObjects[91], 0), 1);

    parameters.clear();
    parameters.write("tag_01", "inlo");
    parameters.write("tag_02", "inhi");
    mObjects[102] = new FrameLib_Expand<FrameLib_Tag>(context, &parameters, mProxy, 1);
    mObjects[102]->addConnection(Connection(mObjects[101], 0), 0);
    mObjects[102]->addConnection(Connection(mObjects[100], 0), 1);

    double fl_103_vector_1[] = { 3 };
    double fl_103_vector_2[] = { 15 };
    double fl_103_vector_3[] = { 0 };
    double fl_103_vector_4[] = { 1 };
    double fl_103_vector_5[] = { 1 };
    parameters.clear();
    parameters.write("mode", "linear");
    parameters.write("inlo", fl_103_vector_1, 1);
    parameters.write("inhi", fl_103_vector_2, 1);
    parameters.write("outlo", fl_103_vector_3, 1);
    parameters.write("outhi", fl_103_vector_4, 1);
    parameters.write("clip", fl_103_vector_5, 1);
    mObjects[103] = new FrameLib_Expand<FrameLib_Map>(context, &parameters, mProxy, 1);
    mObjects[103]->addConnection(Connection(mObjects[98], 0), 0);
    mObjects[103]->addConnection(Connection(mObjects[102], 0), 1);

    parameters.clear();
    mObjects[104] = new FrameLib_Expand<FrameLib_BinaryOp<Binary_Functor<&fmin> > >(context, &parameters, mProxy, 1);
    mObjects[104]->addConnection(Connection(mObjects[103], 0), 0);
    mObjects[104]->addConnection(Connection(mObjects[99], 0), 1);

    parameters.clear();
    parameters.write("name", "freeze");
    mObjects[105] = new FrameLib_Expand<FrameLib_Recall>(context, &parameters, mProxy, 1);
    mObjects[105]->addConnection(Connection(mObjects[81], 0), 0);

    double fl_106_vector_1[] = { 1 };
    parameters.clear();
    parameters.write("expr", "in1 + in3 * (in2 - in1) ");
    parameters.write("trigger_ins", fl_106_vector_1, 1);
    mObjects[106] = new FrameLib_Expand<FrameLib_Expression>(context, &parameters, mProxy, 1);
    mObjects[106]->addConnection(Connection(mObjects[105], 0), 0);
    mObjects[106]->addConnection(Connection(mObjects[81], 0), 1);
    mObjects[106]->addConnection(Connection(mObjects[104], 0), 2);

    double fl_107_vector_0[] = { 2 };
    parameters.clear();
    parameters.write("num_ins", fl_107_vector_0, 1);
    parameters.write("mode", "high");
    mObjects[107] = new FrameLib_Expand<FrameLib_Prioritise>(context, &parameters, mProxy, 1);
    mObjects[107]->addConnection(Connection(mObjects[106], 0), 0);
    mObjects[107]->addConnection(Connection(mObjects[80], 0), 1);

    parameters.clear();
    parameters.write("name", "freeze");
    mObjects[108] = new FrameLib_Expand<FrameLib_Store>(context, &parameters, mProxy, 8);
    mObjects[108]->addConnection(Connection(mObjects[107], 0), 0);

    parameters.clear();
    parameters.write("name", "freeze");
    mObjects[109] = new FrameLib_Expand<FrameLib_Recall>(context, &parameters, mProxy, 8);
    mObjects[109]->addConnection(Connection(mObjects[67], 0), 0);
    mObjects[109]->addOrderingConnection(Connection(mObjects[108], 0));

    double fl_110_vector_0[] = { 2 };
    parameters.clear();
    parameters.write("num_ins", fl_110_vector_0, 1);
    parameters.write("mode", "high");
    mObjects[110] = new FrameLib_Expand<FrameLib_Prioritise>(context, &parameters, mProxy, 1);
    mObjects[110]->addConnection(Connection(mObjects[75], 0), 0);
    mObjects[110]->addConnection(Connection(mObjects[80], 0), 1);

    parameters.clear();
    parameters.write("name", "freezeOld");
    mObjects[111] = new FrameLib_Expand<FrameLib_Store>(context, &parameters, mProxy, 8);
    mObjects[111]->addConnection(Connection(mObjects[110], 0), 0);

    parameters.clear();
    parameters.write("name", "freezeOld");
    mObjects[112] = new FrameLib_Expand<FrameLib_Recall>(context, &parameters, mProxy, 8);
    mObjects[112]->addConnection(Connection(mObjects[67], 0), 0);
    mObjects[112]->addOrderingConnection(Connection(mObjects[111], 0));

    double fl_113_vector_1[] = { 1 };
    parameters.clear();
    parameters.write("expr", "in1+in3*(in2-in1) ");
    parameters.write("trigger_ins", fl_113_vector_1, 1);
    mObjects[113] = new FrameLib_Expand<FrameLib_Expression>(context, &parameters, mProxy, 1);
    mObjects[113]->addConnection(Connection(mObjects[112], 0), 0);
    mObjects[113]->addConnection(Connection(mObjects[109], 0), 1);
    mObjects[113]->addConnection(Connection(mObjects[74], 0), 2);

    parameters.clear();
    parameters.write("name", "last");
    mObjects[114] = new FrameLib_Expand<FrameLib_Store>(context, &parameters, mProxy, 1);
    mObjects[114]->addConnection(Connection(mObjects[113], 0), 0);

    double fl_115_vector_0[] = { 8 };
    parameters.clear();
    parameters.write("outputs", fl_115_vector_0, 1);
    mObjects[115] = new FrameLib_Unpack(context, &parameters, mProxy, 1);
    mObjects[115]->addConnection(Connection(mObjects[113], 0), 0);

    parameters.clear();
    mObjects[116] = new FrameLib_Pack(context, &parameters, mProxy, 1);
    mObjects[116]->addConnection(Connection(mObjects[115], 0), 0);
    mObjects[116]->addConnection(Connection(mObjects[115], 1), 1);

    parameters.clear();
    mObjects[117] = new FrameLib_Pack(context, &parameters, mProxy, 1);
    mObjects[117]->addConnection(Connection(mObjects[115], 2), 0);
    mObjects[117]->addConnection(Connection(mObjects[115], 3), 1);

    parameters.clear();
    parameters.write("mode", "input");
    mObjects[118] = new FrameLib_Expand<FrameLib_Gaussian>(context, &parameters, mProxy, 1);
    mObjects[118]->addConnection(Connection(mObjects[116], 0), 0);
    mObjects[118]->addConnection(Connection(mObjects[117], 0), 1);

    parameters.clear();
    mObjects[119] = new FrameLib_Pack(context, &parameters, mProxy, 1);
    mObjects[119]->addConnection(Connection(mObjects[115], 4), 0);
    mObjects[119]->addConnection(Connection(mObjects[115], 5), 1);

    parameters.clear();
    mObjects[120] = new FrameLib_Pack(context, &parameters, mProxy, 1);
    mObjects[120]->addConnection(Connection(mObjects[115], 6), 0);
    mObjects[120]->addConnection(Connection(mObjects[115], 7), 1);

    parameters.clear();
    parameters.write("mode", "input");
    mObjects[121] = new FrameLib_Expand<FrameLib_Gaussian>(context, &parameters, mProxy, 1);
    mObjects[121]->addConnection(Connection(mObjects[119], 0), 0);
    mObjects[121]->addConnection(Connection(mObjects[120], 0), 1);

    parameters.clear();
    parameters.write("name", "phases");
    mObjects[122] = new FrameLib_Expand<FrameLib_Recall>(context, &parameters, mProxy, 1);
    mObjects[122]->addConnection(Connection(mObjects[121], 0), 0);

    parameters.clear();
    mObjects[123] = new FrameLib_Expand<FrameLib_Prioritise>(context, &parameters, mProxy, 1);
    mObjects[123]->addConnection(Connection(mObjects[32], 0), 0);
    mObjects[123]->addConnection(Connection(mObjects[122], 0), 1);

    parameters.clear();
    mObjects[124] = new FrameLib_Expand<FrameLib_BinaryOp<std::plus<double> > >(context, &parameters, mProxy, 1);
    mObjects[124]->addConnection(Connection(mObjects[121], 0), 0);
    mObjects[124]->addConnection(Connection(mObjects[123], 0), 1);

    parameters.clear();
    parameters.write("expr", "wrap(in1, -pi, pi)");
    mObjects[125] = new FrameLib_Expand<FrameLib_Expression>(context, &parameters, mProxy, 1);
    mObjects[125]->addConnection(Connection(mObjects[124], 0), 0);

    parameters.clear();
    parameters.write("name", "phases");
    mObjects[126] = new FrameLib_Expand<FrameLib_Store>(context, &parameters, mProxy, 1);
    mObjects[126]->addConnection(Connection(mObjects[125], 0), 0);

    parameters.clear();
    mObjects[127] = new FrameLib_Expand<FrameLib_UnaryOp<Unary_Functor<&sin> > >(context, &parameters, mProxy, 1);
    mObjects[127]->addConnection(Connection(mObjects[124], 0), 0);

    parameters.clear();
    mObjects[128] = new FrameLib_Expand<FrameLib_BinaryOp<std::multiplies<double> > >(context, &parameters, mProxy, 1);
    mObjects[128]->addConnection(Connection(mObjects[118], 0), 0);
    mObjects[128]->addConnection(Connection(mObjects[127], 0), 1);

    double fl_129_vector_0[] = { 1 };
    parameters.clear();
    parameters.write("outputs", fl_129_vector_0, 1);
    mObjects[129] = new FrameLib_Unpack(context, &parameters, mProxy, 1);
    mObjects[129]->addConnection(Connection(mObjects[128], 0), 0);

    parameters.clear();
    parameters.write("units", "ms");
    mObjects[130] = new FrameLib_Expand<FrameLib_Timer>(context, &parameters, mProxy, 1);
    mObjects[130]->addConnection(Connection(mObjects[46], 0), 0);
    mObjects[130]->addConnection(Connection(mObjects[129], 0), 1);

    parameters.clear();
    parameters.write("trigger_ins", "left");
    mObjects[131] = new FrameLib_Expand<FrameLib_BinaryOp<std::divides<double> > >(context, &parameters, mProxy, 1);
    mObjects[131]->addConnection(Connection(mObjects[130], 0), 0);
    mObjects[131]->addConnection(Connection(mObjects[46], 0), 1);

    parameters.clear();
    mObjects[132] = new FrameLib_Expand<FrameLib_BinaryOp<Binary_Functor<&pow> > >(context, &parameters, mProxy, 1);
    double fl_132_inputs_1[] = { 0.600000 };
    mObjects[132]->setFixedInput(1, fl_132_inputs_1 , 1);
    mObjects[132]->addConnection(Connection(mObjects[131], 0), 0);

    parameters.clear();
    parameters.write("mode", "params");
    mObjects[133] = new FrameLib_Expand<FrameLib_FromHost>(context, &parameters, mProxy, 1);
    mObjects[133]->addConnection(Connection(mObjects[45], 0), 0);

    double fl_134_vector_1[] = { 1 };
    double fl_134_vector_2[] = { 45 };
    parameters.clear();
    parameters.write("mode", "requested");
    parameters.write("stddev", fl_134_vector_1, 1);
    parameters.write("length", fl_134_vector_2, 1);
    mObjects[134] = new FrameLib_Expand<FrameLib_Gaussian>(context, &parameters, mProxy, 1);
    mObjects[134]->addConnection(Connection(mObjects[45], 0), 0);
    mObjects[134]->addConnection(Connection(mObjects[133], 0), 2);

    parameters.clear();
    parameters.write("mode", "input");
    parameters.write("scale", "normalised");
    mObjects[135] = new FrameLib_Expand<FrameLib_Ramp>(context, &parameters, mProxy, 1);
    mObjects[135]->addConnection(Connection(mObjects[134], 0), 0);

    parameters.clear();
    parameters.write("mode", "params");
    mObjects[136] = new FrameLib_Expand<FrameLib_FromHost>(context, &parameters, mProxy, 1);
    mObjects[136]->addConnection(Connection(mObjects[45], 0), 0);

    double fl_137_vector_1[] = { 0 };
    double fl_137_vector_2[] = { 1 };
    double fl_137_vector_3[] = { 10 };
    double fl_137_vector_4[] = { 2 };
    parameters.clear();
    parameters.write("mode", "linear");
    parameters.write("inlo", fl_137_vector_1, 1);
    parameters.write("inhi", fl_137_vector_2, 1);
    parameters.write("outlo", fl_137_vector_3, 1);
    parameters.write("outhi", fl_137_vector_4, 1);
    mObjects[137] = new FrameLib_Expand<FrameLib_Map>(context, &parameters, mProxy, 1);
    mObjects[137]->addConnection(Connection(mObjects[135], 0), 0);
    mObjects[137]->addConnection(Connection(mObjects[136], 0), 1);

    parameters.clear();
    mObjects[138] = new FrameLib_Expand<FrameLib_TernaryOp<Ternary_Functor<&FrameLib_Ternary_Ops::clip<double>> > >(context, &parameters, mProxy, 1);
    double fl_138_inputs_1[] = { -1 };
    double fl_138_inputs_2[] = { 1 };
    mObjects[138]->setFixedInput(1, fl_138_inputs_1 , 1);
    mObjects[138]->setFixedInput(2, fl_138_inputs_2 , 1);
    mObjects[138]->addConnection(Connection(mObjects[134], 0), 0);

    parameters.clear();
    mObjects[139] = new FrameLib_Expand<FrameLib_BinaryOp<std::multiplies<double> > >(context, &parameters, mProxy, 1);
    mObjects[139]->addConnection(Connection(mObjects[138], 0), 0);
    mObjects[139]->addConnection(Connection(mObjects[137], 0), 1);

    parameters.clear();
    mObjects[140] = new FrameLib_Expand<FrameLib_Vector<&statLength<double const*>, (FrameLib_Vector_EmptyMode)4> >(context, &parameters, mProxy, 1);
    mObjects[140]->addConnection(Connection(mObjects[138], 0), 0);

    parameters.clear();
    mObjects[141] = new FrameLib_Expand<FrameLib_BinaryOp<std::minus<double> > >(context, &parameters, mProxy, 1);
    double fl_141_inputs_1[] = { 1 };
    mObjects[141]->setFixedInput(1, fl_141_inputs_1 , 1);
    mObjects[141]->addConnection(Connection(mObjects[140], 0), 0);

    parameters.clear();
    mObjects[142] = new FrameLib_Expand<FrameLib_BinaryOp<std::multiplies<double> > >(context, &parameters, mProxy, 1);
    mObjects[142]->addConnection(Connection(mObjects[39], 0), 0);
    mObjects[142]->addConnection(Connection(mObjects[141], 0), 1);

    parameters.clear();
    parameters.write("mode", "clip");
    mObjects[143] = new FrameLib_Expand<FrameLib_Lookup>(context, &parameters, mProxy, 1);
    mObjects[143]->addConnection(Connection(mObjects[142], 0), 0);
    mObjects[143]->addConnection(Connection(mObjects[139], 0), 1);

    parameters.clear();
    mObjects[144] = new FrameLib_Expand<FrameLib_Register>(context, &parameters, mProxy, 1);
    mObjects[144]->addConnection(Connection(mObjects[129], 0), 0);
    mObjects[144]->addConnection(Connection(mObjects[143], 0), 1);

    parameters.clear();
    parameters.write("name", "eq");
    mObjects[145] = new FrameLib_Expand<FrameLib_Recall>(context, &parameters, mProxy, 1);
    mObjects[145]->addConnection(Connection(mObjects[143], 0), 0);

    parameters.clear();
    mObjects[146] = new FrameLib_Expand<FrameLib_Prioritise>(context, &parameters, mProxy, 1);
    mObjects[146]->addConnection(Connection(mObjects[32], 0), 0);
    mObjects[146]->addConnection(Connection(mObjects[145], 0), 1);

    parameters.clear();
    mObjects[147] = new FrameLib_Expand<FrameLib_Register>(context, &parameters, mProxy, 1);
    mObjects[147]->addConnection(Connection(mObjects[129], 0), 0);
    mObjects[147]->addConnection(Connection(mObjects[146], 0), 1);

    double fl_148_vector_1[] = { 1, 0, 0 };
    parameters.clear();
    parameters.write("expr", "in1 + in3 * (in2 - in1) ");
    parameters.write("trigger_ins", fl_148_vector_1, 3);
    mObjects[148] = new FrameLib_Expand<FrameLib_Expression>(context, &parameters, mProxy, 1);
    mObjects[148]->addConnection(Connection(mObjects[147], 0), 0);
    mObjects[148]->addConnection(Connection(mObjects[144], 0), 1);
    mObjects[148]->addConnection(Connection(mObjects[132], 0), 2);

    parameters.clear();
    parameters.write("name", "eq");
    mObjects[149] = new FrameLib_Expand<FrameLib_Store>(context, &parameters, mProxy, 1);
    mObjects[149]->addConnection(Connection(mObjects[148], 0), 0);

    parameters.clear();
    parameters.write("mode", "db->amp");
    mObjects[150] = new FrameLib_Expand<FrameLib_Convert>(context, &parameters, mProxy, 1);
    mObjects[150]->addConnection(Connection(mObjects[148], 0), 0);

    parameters.clear();
    mObjects[151] = new FrameLib_Expand<FrameLib_BinaryOp<std::multiplies<double> > >(context, &parameters, mProxy, 1);
    mObjects[151]->addConnection(Connection(mObjects[128], 0), 0);
    mObjects[151]->addConnection(Connection(mObjects[150], 0), 1);

    parameters.clear();
    mObjects[152] = new FrameLib_Expand<FrameLib_UnaryOp<Unary_Functor<&cos> > >(context, &parameters, mProxy, 1);
    mObjects[152]->addConnection(Connection(mObjects[124], 0), 0);

    parameters.clear();
    mObjects[153] = new FrameLib_Expand<FrameLib_BinaryOp<std::multiplies<double> > >(context, &parameters, mProxy, 1);
    mObjects[153]->addConnection(Connection(mObjects[118], 0), 0);
    mObjects[153]->addConnection(Connection(mObjects[152], 0), 1);

    parameters.clear();
    mObjects[154] = new FrameLib_Expand<FrameLib_BinaryOp<std::multiplies<double> > >(context, &parameters, mProxy, 1);
    mObjects[154]->addConnection(Connection(mObjects[153], 0), 0);
    mObjects[154]->addConnection(Connection(mObjects[150], 0), 1);

    double fl_155_vector_0[] = { 65536 };
    parameters.clear();
    parameters.write("maxlength", fl_155_vector_0, 1);
    mObjects[155] = new FrameLib_Expand<FrameLib_iFFT>(context, &parameters, mProxy, 1);
    mObjects[155]->addConnection(Connection(mObjects[154], 0), 0);
    mObjects[155]->addConnection(Connection(mObjects[151], 0), 1);

    parameters.clear();
    mObjects[156] = new FrameLib_Expand<FrameLib_Register>(context, &parameters, mProxy, 1);
    mObjects[156]->addConnection(Connection(mObjects[32], 0), 0);
    mObjects[156]->addConnection(Connection(mObjects[1], 0), 1);

    parameters.clear();
    mObjects[157] = new FrameLib_Expand<FrameLib_BinaryOp<std::equal_to<double> > >(context, &parameters, mProxy, 1);
    double fl_157_inputs_1[] = { 2 };
    mObjects[157]->setFixedInput(1, fl_157_inputs_1 , 1);
    mObjects[157]->addConnection(Connection(mObjects[156], 0), 0);

    parameters.clear();
    parameters.write("tag_01", "sqrt");
    mObjects[158] = new FrameLib_Expand<FrameLib_Tag>(context, &parameters, mProxy, 1);
    mObjects[158]->addConnection(Connection(mObjects[157], 0), 0);

    parameters.clear();
    parameters.write("window", "hann");
    parameters.write("compensate", "powoverlin");
    mObjects[159] = new FrameLib_Expand<FrameLib_Window>(context, &parameters, mProxy, 1);
    mObjects[159]->addConnection(Connection(mObjects[155], 0), 0);
    mObjects[159]->addConnection(Connection(mObjects[158], 0), 1);

    parameters.clear();
    mObjects[160] = new FrameLib_Expand<FrameLib_BinaryOp<std::divides<double> > >(context, &parameters, mProxy, 1);
    double fl_160_inputs_0[] = { 1 };
    mObjects[160]->setFixedInput(0, fl_160_inputs_0 , 1);
    mObjects[160]->addConnection(Connection(mObjects[156], 0), 1);

    parameters.clear();
    parameters.write("trigger_ins", "right");
    mObjects[161] = new FrameLib_Expand<FrameLib_BinaryOp<std::multiplies<double> > >(context, &parameters, mProxy, 1);
    mObjects[161]->addConnection(Connection(mObjects[160], 0), 0);
    mObjects[161]->addConnection(Connection(mObjects[159], 0), 1);

    parameters.clear();
    mObjects[162] = new FrameLib_Expand<FrameLib_Sink>(context, &parameters, mProxy, 2);
    mObjects[162]->addConnection(Connection(mObjects[161], 0), 0);

    for (auto it = mObjects.begin(); it != mObjects.end(); it++)
    {
        (*it)->autoOrderingConnections();

        if ((*it)->handlesAudio())
            mAudioObjects.push_back(*it);

        mNumAudioIns += (*it)->getNumAudioIns();
        mNumAudioOuts += (*it)->getNumAudioOuts();
    }
}

Freeze::~Freeze()
{
    for (auto it = mObjects.begin(); it != mObjects.end(); it++)
        delete *it;

    mObjects.clear();
    mAudioObjects.clear();
    delete mProxy;
    FrameLib_Global::release(&mGlobal);
}

void Freeze::reset(double samplerate, unsigned long maxvectorsize)
{
    for (auto it = mObjects.begin(); it != mObjects.end(); it++)
        (*it)->reset(samplerate, maxvectorsize);
}

void Freeze::process(double **inputs, double **outputs, unsigned long blockSize)
{
    for (auto it = mAudioObjects.begin(); it != mAudioObjects.end(); it++)
    {
        (*it)->blockUpdate(inputs, outputs, blockSize);

        inputs += (*it)->getNumAudioIns();
        outputs += (*it)->getNumAudioOuts();
    }
}