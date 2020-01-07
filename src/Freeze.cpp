
#include "Freeze.h"
#include "FrameLib_Objects.h"

Freeze::Freeze(FrameLib_Proxy *proxy) : mGlobal(nullptr), mNumAudioIns(0), mNumAudioOuts(0), mProxy(proxy)
{
    using Connection = FrameLib_Object<FrameLib_Multistream>::Connection;

    FrameLib_Global::get(&mGlobal, FrameLib_Thread::defaultPriorities());
    FrameLib_Context context(mGlobal, this);
    FrameLib_Parameters::AutoSerial parameters;

    mObjects.resize(139);

    double fl_0_vector_0[] = { 8 };
    parameters.clear();
    parameters.write("interval", fl_0_vector_0, 1);
    mObjects[0] = new FrameLib_Expand<FrameLib_Interval>(context, &parameters, mProxy, 1);

    parameters.clear();
    mObjects[1] = new FrameLib_Expand<FrameLib_FromHost>(context, &parameters, mProxy, 1);
    mObjects[1]->addConnection(Connection(mObjects[0], 0), 0);

    parameters.clear();
    mObjects[2] = new FrameLib_Expand<FrameLib_BinaryOp<std::__1::equal_to<double> > >(context, &parameters, mProxy, 1);
    double fl_2_inputs_1[] = { 2 };
    mObjects[2]->setFixedInput(1, fl_2_inputs_1 , 1);
    mObjects[2]->addConnection(Connection(mObjects[1], 0), 0);

    parameters.clear();
    parameters.write("tag_01", "sqrt");
    mObjects[3] = new FrameLib_Expand<FrameLib_Tag>(context, &parameters, mProxy, 1);
    mObjects[3]->addConnection(Connection(mObjects[2], 0), 0);

    parameters.clear();
    mObjects[4] = new FrameLib_Expand<FrameLib_FromHost>(context, &parameters, mProxy, 1);
    mObjects[4]->addConnection(Connection(mObjects[0], 0), 0);

    parameters.clear();
    mObjects[5] = new FrameLib_Expand<FrameLib_BinaryOp<std::__1::divides<double> > >(context, &parameters, mProxy, 1);
    mObjects[5]->addConnection(Connection(mObjects[4], 0), 0);
    mObjects[5]->addConnection(Connection(mObjects[1], 0), 1);

    parameters.clear();
    parameters.write("tag_01", "interval");
    mObjects[6] = new FrameLib_Expand<FrameLib_Tag>(context, &parameters, mProxy, 1);
    mObjects[6]->addConnection(Connection(mObjects[5], 0), 0);

    double fl_7_vector_0[] = { 512 };
    parameters.clear();
    parameters.write("interval", fl_7_vector_0, 1);
    mObjects[7] = new FrameLib_Expand<FrameLib_Interval>(context, &parameters, mProxy, 1);
    mObjects[7]->addConnection(Connection(mObjects[6], 0), 0);

    parameters.clear();
    parameters.write("tag_01", "length");
    mObjects[8] = new FrameLib_Expand<FrameLib_Tag>(context, &parameters, mProxy, 1);
    mObjects[8]->addConnection(Connection(mObjects[4], 0), 0);

    double fl_9_vector_0[] = { 65536 };
    double fl_9_vector_1[] = { 4096 };
    parameters.clear();
    parameters.write("buffer_size", fl_9_vector_0, 1);
    parameters.write("length", fl_9_vector_1, 1);
    mObjects[9] = new FrameLib_Expand<FrameLib_Source>(context, &parameters, mProxy, 2);
    mObjects[9]->addConnection(Connection(mObjects[7], 0), 0);
    mObjects[9]->addConnection(Connection(mObjects[8], 0), 1);

    parameters.clear();
    parameters.write("window", "hann");
    parameters.write("compensate", "linear");
    mObjects[10] = new FrameLib_Expand<FrameLib_Window>(context, &parameters, mProxy, 1);
    mObjects[10]->addConnection(Connection(mObjects[9], 0), 0);
    mObjects[10]->addConnection(Connection(mObjects[3], 0), 1);

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
    mObjects[14] = new FrameLib_Expand<FrameLib_UnaryOp<Unary_Functor<&cos> > >(context, &parameters, mProxy, 1);
    mObjects[14]->addConnection(Connection(mObjects[13], 0), 0);

    parameters.clear();
    parameters.write("mode", "params");
    mObjects[15] = new FrameLib_Expand<FrameLib_FromHost>(context, &parameters, mProxy, 1);
    mObjects[15]->addConnection(Connection(mObjects[11], 1), 0);

    double fl_16_vector_0[] = { 100 };
    double fl_16_vector_1[] = { 20 };
    parameters.clear();
    parameters.write("max_frames", fl_16_vector_0, 1);
    parameters.write("num_frames", fl_16_vector_1, 1);
    mObjects[16] = new FrameLib_Expand<FrameLib_TimeMean>(context, &parameters, mProxy, 1);
    mObjects[16]->addConnection(Connection(mObjects[14], 0), 0);
    mObjects[16]->addConnection(Connection(mObjects[15], 0), 1);

    parameters.clear();
    mObjects[17] = new FrameLib_Expand<FrameLib_BinaryOp<std::__1::multiplies<double> > >(context, &parameters, mProxy, 1);
    mObjects[17]->addConnection(Connection(mObjects[16], 0), 0);
    mObjects[17]->addConnection(Connection(mObjects[16], 0), 1);

    parameters.clear();
    mObjects[18] = new FrameLib_Expand<FrameLib_UnaryOp<Unary_Functor<&sin> > >(context, &parameters, mProxy, 1);
    mObjects[18]->addConnection(Connection(mObjects[13], 0), 0);

    double fl_19_vector_0[] = { 100 };
    double fl_19_vector_1[] = { 20 };
    parameters.clear();
    parameters.write("max_frames", fl_19_vector_0, 1);
    parameters.write("num_frames", fl_19_vector_1, 1);
    mObjects[19] = new FrameLib_Expand<FrameLib_TimeMean>(context, &parameters, mProxy, 1);
    mObjects[19]->addConnection(Connection(mObjects[18], 0), 0);
    mObjects[19]->addConnection(Connection(mObjects[15], 0), 1);

    parameters.clear();
    mObjects[20] = new FrameLib_Expand<FrameLib_BinaryOp<std::__1::multiplies<double> > >(context, &parameters, mProxy, 1);
    mObjects[20]->addConnection(Connection(mObjects[19], 0), 0);
    mObjects[20]->addConnection(Connection(mObjects[19], 0), 1);

    parameters.clear();
    mObjects[21] = new FrameLib_Expand<FrameLib_BinaryOp<std::__1::plus<double> > >(context, &parameters, mProxy, 1);
    mObjects[21]->addConnection(Connection(mObjects[20], 0), 0);
    mObjects[21]->addConnection(Connection(mObjects[17], 0), 1);

    parameters.clear();
    parameters.write("expr", "max(in1, exp(-4*pi*pi))");
    mObjects[22] = new FrameLib_Expand<FrameLib_Expression>(context, &parameters, mProxy, 1);
    mObjects[22]->addConnection(Connection(mObjects[21], 0), 0);

    parameters.clear();
    mObjects[23] = new FrameLib_Expand<FrameLib_UnaryOp<Unary_Functor<&log> > >(context, &parameters, mProxy, 1);
    mObjects[23]->addConnection(Connection(mObjects[22], 0), 0);

    parameters.clear();
    mObjects[24] = new FrameLib_Expand<FrameLib_BinaryOp<std::__1::multiplies<double> > >(context, &parameters, mProxy, 1);
    double fl_24_inputs_1[] = { -1 };
    mObjects[24]->setFixedInput(1, fl_24_inputs_1 , 1);
    mObjects[24]->addConnection(Connection(mObjects[23], 0), 0);

    parameters.clear();
    mObjects[25] = new FrameLib_Expand<FrameLib_BinaryOp<Binary_Functor<&fmax> > >(context, &parameters, mProxy, 1);
    double fl_25_inputs_1[] = { 0 };
    mObjects[25]->setFixedInput(1, fl_25_inputs_1 , 1);
    mObjects[25]->addConnection(Connection(mObjects[24], 0), 0);

    parameters.clear();
    mObjects[26] = new FrameLib_Expand<FrameLib_UnaryOp<Unary_Functor<&sqrt> > >(context, &parameters, mProxy, 1);
    mObjects[26]->addConnection(Connection(mObjects[25], 0), 0);

    parameters.clear();
    mObjects[27] = new FrameLib_Expand<FrameLib_BinaryOp<Binary_Functor<&hypot> > >(context, &parameters, mProxy, 1);
    mObjects[27]->addConnection(Connection(mObjects[11], 0), 0);
    mObjects[27]->addConnection(Connection(mObjects[11], 1), 1);

    double fl_28_vector_0[] = { 100 };
    double fl_28_vector_1[] = { 20 };
    parameters.clear();
    parameters.write("max_frames", fl_28_vector_0, 1);
    parameters.write("num_frames", fl_28_vector_1, 1);
    mObjects[28] = new FrameLib_Expand<FrameLib_TimeStdDev>(context, &parameters, mProxy, 1);
    mObjects[28]->addConnection(Connection(mObjects[27], 0), 0);
    mObjects[28]->addConnection(Connection(mObjects[15], 0), 1);

    double fl_29_vector_0[] = { 100 };
    double fl_29_vector_1[] = { 20 };
    parameters.clear();
    parameters.write("max_frames", fl_29_vector_0, 1);
    parameters.write("num_frames", fl_29_vector_1, 1);
    mObjects[29] = new FrameLib_Expand<FrameLib_TimeMean>(context, &parameters, mProxy, 1);
    mObjects[29]->addConnection(Connection(mObjects[27], 0), 0);
    mObjects[29]->addConnection(Connection(mObjects[15], 0), 1);

    parameters.clear();
    mObjects[30] = new FrameLib_Expand<FrameLib_BinaryOp<Binary_Functor<&atan2> > >(context, &parameters, mProxy, 1);
    mObjects[30]->addConnection(Connection(mObjects[19], 0), 0);
    mObjects[30]->addConnection(Connection(mObjects[16], 0), 1);

    double fl_31_vector_0[] = { 4 };
    parameters.clear();
    parameters.write("inputs", fl_31_vector_0, 1);
    mObjects[31] = new FrameLib_Pack(context, &parameters, mProxy, 1);
    mObjects[31]->addConnection(Connection(mObjects[29], 0), 0);
    mObjects[31]->addConnection(Connection(mObjects[28], 0), 1);
    mObjects[31]->addConnection(Connection(mObjects[30], 0), 2);
    mObjects[31]->addConnection(Connection(mObjects[26], 0), 3);

    parameters.clear();
    mObjects[32] = new FrameLib_Expand<FrameLib_AudioTrigger>(context, &parameters, mProxy, 1);

    parameters.clear();
    mObjects[33] = new FrameLib_Expand<FrameLib_FromHost>(context, &parameters, mProxy, 1);
    mObjects[33]->addConnection(Connection(mObjects[32], 0), 0);

    parameters.clear();
    mObjects[34] = new FrameLib_Expand<FrameLib_BinaryOp<Binary_Functor<&fmax> > >(context, &parameters, mProxy, 1);
    double fl_34_inputs_1[] = { 0.010000 };
    mObjects[34]->setFixedInput(1, fl_34_inputs_1 , 1);
    mObjects[34]->addConnection(Connection(mObjects[33], 0), 0);

    parameters.clear();
    parameters.write("units", "ms");
    mObjects[35] = new FrameLib_Expand<FrameLib_Timer>(context, &parameters, mProxy, 8);
    mObjects[35]->addConnection(Connection(mObjects[32], 0), 0);
    mObjects[35]->addConnection(Connection(mObjects[31], 0), 1);

    parameters.clear();
    mObjects[36] = new FrameLib_Expand<FrameLib_BinaryOp<std::__1::divides<double> > >(context, &parameters, mProxy, 1);
    mObjects[36]->addConnection(Connection(mObjects[35], 0), 0);
    mObjects[36]->addConnection(Connection(mObjects[34], 0), 1);

    parameters.clear();
    mObjects[37] = new FrameLib_Expand<FrameLib_TernaryOp<Ternary_Functor<&FrameLib_Ternary_Ops::clip<double>> > >(context, &parameters, mProxy, 1);
    double fl_37_inputs_1[] = { 0 };
    double fl_37_inputs_2[] = { 1 };
    mObjects[37]->setFixedInput(1, fl_37_inputs_1 , 1);
    mObjects[37]->setFixedInput(2, fl_37_inputs_2 , 1);
    mObjects[37]->addConnection(Connection(mObjects[36], 0), 0);

    parameters.clear();
    parameters.write("name", "last");
    mObjects[38] = new FrameLib_Expand<FrameLib_Recall>(context, &parameters, mProxy, 8);
    mObjects[38]->addConnection(Connection(mObjects[32], 0), 0);

    parameters.clear();
    parameters.write("name", "freezeOld");
    mObjects[39] = new FrameLib_Expand<FrameLib_Store>(context, &parameters, mProxy, 8);
    mObjects[39]->addConnection(Connection(mObjects[38], 0), 0);

    parameters.clear();
    parameters.write("name", "freezeOld");
    mObjects[40] = new FrameLib_Expand<FrameLib_Recall>(context, &parameters, mProxy, 8);
    mObjects[40]->addConnection(Connection(mObjects[31], 0), 0);
    mObjects[40]->addOrderingConnection(Connection(mObjects[39], 0));

    parameters.clear();
    mObjects[41] = new FrameLib_Expand<FrameLib_Vector<&statLength<double const*>, (FrameLib_Vector_EmptyMode)4> >(context, &parameters, mProxy, 1);
    mObjects[41]->addConnection(Connection(mObjects[40], 0), 0);

    parameters.clear();
    mObjects[42] = new FrameLib_Expand<FrameLib_Vector<&statLength<double const*>, (FrameLib_Vector_EmptyMode)4> >(context, &parameters, mProxy, 1);
    mObjects[42]->addConnection(Connection(mObjects[31], 0), 0);

    parameters.clear();
    parameters.write("expr", "(in1 != in2) + 1");
    mObjects[43] = new FrameLib_Expand<FrameLib_Expression>(context, &parameters, mProxy, 1);
    mObjects[43]->addConnection(Connection(mObjects[41], 0), 0);
    mObjects[43]->addConnection(Connection(mObjects[42], 0), 1);

    parameters.clear();
    parameters.write("tag_01", "input");
    mObjects[44] = new FrameLib_Expand<FrameLib_Tag>(context, &parameters, mProxy, 1);
    mObjects[44]->addConnection(Connection(mObjects[43], 0), 0);

    parameters.clear();
    parameters.write("mode", "input");
    mObjects[45] = new FrameLib_Expand<FrameLib_Uniform>(context, &parameters, mProxy, 1);
    mObjects[45]->addConnection(Connection(mObjects[31], 0), 0);

    parameters.clear();
    mObjects[46] = new FrameLib_Expand<FrameLib_Select>(context, &parameters, mProxy, 1);
    mObjects[46]->addConnection(Connection(mObjects[40], 0), 0);
    mObjects[46]->addConnection(Connection(mObjects[45], 0), 1);
    mObjects[46]->addConnection(Connection(mObjects[44], 0), 2);

    parameters.clear();
    mObjects[47] = new FrameLib_Expand<FrameLib_Register>(context, &parameters, mProxy, 1);
    mObjects[47]->addConnection(Connection(mObjects[32], 0), 0);
    mObjects[47]->addConnection(Connection(mObjects[31], 0), 1);

    parameters.clear();
    parameters.write("name", "freeze");
    mObjects[48] = new FrameLib_Expand<FrameLib_Store>(context, &parameters, mProxy, 8);
    mObjects[48]->addConnection(Connection(mObjects[47], 0), 0);

    parameters.clear();
    parameters.write("name", "freeze");
    mObjects[49] = new FrameLib_Expand<FrameLib_Recall>(context, &parameters, mProxy, 8);
    mObjects[49]->addConnection(Connection(mObjects[31], 0), 0);
    mObjects[49]->addOrderingConnection(Connection(mObjects[48], 0));

    parameters.clear();
    mObjects[50] = new FrameLib_Expand<FrameLib_Vector<&statLength<double const*>, (FrameLib_Vector_EmptyMode)4> >(context, &parameters, mProxy, 1);
    mObjects[50]->addConnection(Connection(mObjects[49], 0), 0);

    parameters.clear();
    mObjects[51] = new FrameLib_Expand<FrameLib_Vector<&statLength<double const*>, (FrameLib_Vector_EmptyMode)4> >(context, &parameters, mProxy, 1);
    mObjects[51]->addConnection(Connection(mObjects[31], 0), 0);

    parameters.clear();
    parameters.write("expr", "(in1 != in2) + 1");
    mObjects[52] = new FrameLib_Expand<FrameLib_Expression>(context, &parameters, mProxy, 1);
    mObjects[52]->addConnection(Connection(mObjects[50], 0), 0);
    mObjects[52]->addConnection(Connection(mObjects[51], 0), 1);

    parameters.clear();
    parameters.write("tag_01", "input");
    mObjects[53] = new FrameLib_Expand<FrameLib_Tag>(context, &parameters, mProxy, 1);
    mObjects[53]->addConnection(Connection(mObjects[52], 0), 0);

    parameters.clear();
    parameters.write("mode", "input");
    mObjects[54] = new FrameLib_Expand<FrameLib_Uniform>(context, &parameters, mProxy, 1);
    mObjects[54]->addConnection(Connection(mObjects[31], 0), 0);

    parameters.clear();
    mObjects[55] = new FrameLib_Expand<FrameLib_Select>(context, &parameters, mProxy, 1);
    mObjects[55]->addConnection(Connection(mObjects[49], 0), 0);
    mObjects[55]->addConnection(Connection(mObjects[54], 0), 1);
    mObjects[55]->addConnection(Connection(mObjects[53], 0), 2);

    double fl_56_vector_1[] = { 1 };
    parameters.clear();
    parameters.write("expr", "in1+in3*(in2-in1) ");
    parameters.write("trigger_ins", fl_56_vector_1, 1);
    mObjects[56] = new FrameLib_Expand<FrameLib_Expression>(context, &parameters, mProxy, 1);
    mObjects[56]->addConnection(Connection(mObjects[46], 0), 0);
    mObjects[56]->addConnection(Connection(mObjects[55], 0), 1);
    mObjects[56]->addConnection(Connection(mObjects[37], 0), 2);

    parameters.clear();
    parameters.write("name", "last");
    mObjects[57] = new FrameLib_Expand<FrameLib_Store>(context, &parameters, mProxy, 1);
    mObjects[57]->addConnection(Connection(mObjects[56], 0), 0);

    double fl_58_vector_0[] = { 8 };
    parameters.clear();
    parameters.write("outputs", fl_58_vector_0, 1);
    mObjects[58] = new FrameLib_Unpack(context, &parameters, mProxy, 1);
    mObjects[58]->addConnection(Connection(mObjects[56], 0), 0);

    parameters.clear();
    mObjects[59] = new FrameLib_Pack(context, &parameters, mProxy, 1);
    mObjects[59]->addConnection(Connection(mObjects[58], 0), 0);
    mObjects[59]->addConnection(Connection(mObjects[58], 1), 1);

    parameters.clear();
    mObjects[60] = new FrameLib_Pack(context, &parameters, mProxy, 1);
    mObjects[60]->addConnection(Connection(mObjects[58], 2), 0);
    mObjects[60]->addConnection(Connection(mObjects[58], 3), 1);

    parameters.clear();
    parameters.write("mode", "input");
    mObjects[61] = new FrameLib_Expand<FrameLib_Gaussian>(context, &parameters, mProxy, 1);
    mObjects[61]->addConnection(Connection(mObjects[59], 0), 0);
    mObjects[61]->addConnection(Connection(mObjects[60], 0), 1);

    parameters.clear();
    mObjects[62] = new FrameLib_Pack(context, &parameters, mProxy, 1);
    mObjects[62]->addConnection(Connection(mObjects[58], 4), 0);
    mObjects[62]->addConnection(Connection(mObjects[58], 5), 1);

    parameters.clear();
    mObjects[63] = new FrameLib_Pack(context, &parameters, mProxy, 1);
    mObjects[63]->addConnection(Connection(mObjects[58], 6), 0);
    mObjects[63]->addConnection(Connection(mObjects[58], 7), 1);

    parameters.clear();
    parameters.write("mode", "input");
    mObjects[64] = new FrameLib_Expand<FrameLib_Gaussian>(context, &parameters, mProxy, 1);
    mObjects[64]->addConnection(Connection(mObjects[62], 0), 0);
    mObjects[64]->addConnection(Connection(mObjects[63], 0), 1);

    parameters.clear();
    mObjects[65] = new FrameLib_Expand<FrameLib_Vector<&statLength<double const*>, (FrameLib_Vector_EmptyMode)4> >(context, &parameters, mProxy, 1);
    mObjects[65]->addConnection(Connection(mObjects[64], 0), 0);

    parameters.clear();
    parameters.write("tag_01", "split");
    mObjects[66] = new FrameLib_Expand<FrameLib_Tag>(context, &parameters, mProxy, 1);
    mObjects[66]->addConnection(Connection(mObjects[65], 0), 0);

    parameters.clear();
    parameters.write("name", "phases");
    mObjects[67] = new FrameLib_Expand<FrameLib_Recall>(context, &parameters, mProxy, 1);
    mObjects[67]->addConnection(Connection(mObjects[64], 0), 0);

    parameters.clear();
    mObjects[68] = new FrameLib_Expand<FrameLib_Vector<&statLength<double const*>, (FrameLib_Vector_EmptyMode)4> >(context, &parameters, mProxy, 1);
    mObjects[68]->addConnection(Connection(mObjects[67], 0), 0);

    parameters.clear();
    mObjects[69] = new FrameLib_Expand<FrameLib_BinaryOp<std::__1::equal_to<double> > >(context, &parameters, mProxy, 1);
    mObjects[69]->addConnection(Connection(mObjects[68], 0), 0);
    mObjects[69]->addConnection(Connection(mObjects[65], 0), 1);

    parameters.clear();
    parameters.write("mismatch", "pad_in");
    mObjects[70] = new FrameLib_Expand<FrameLib_BinaryOp<std::__1::plus<double> > >(context, &parameters, mProxy, 1);
    double fl_70_inputs_1[] = { 0 };
    mObjects[70]->setFixedInput(1, fl_70_inputs_1 , 1);
    mObjects[70]->addConnection(Connection(mObjects[67], 0), 0);

    double fl_71_vector_0[] = { 1 };
    parameters.clear();
    parameters.write("split", fl_71_vector_0, 1);
    mObjects[71] = new FrameLib_Expand<FrameLib_Split>(context, &parameters, mProxy, 1);
    mObjects[71]->addConnection(Connection(mObjects[70], 0), 0);
    mObjects[71]->addConnection(Connection(mObjects[66], 0), 1);

    parameters.clear();
    parameters.write("expr", "in1 + in3 * in2");
    mObjects[72] = new FrameLib_Expand<FrameLib_Expression>(context, &parameters, mProxy, 1);
    mObjects[72]->addConnection(Connection(mObjects[64], 0), 0);
    mObjects[72]->addConnection(Connection(mObjects[71], 0), 1);
    mObjects[72]->addConnection(Connection(mObjects[69], 0), 2);

    parameters.clear();
    parameters.write("expr", "wrap(in1, -pi, pi)");
    mObjects[73] = new FrameLib_Expand<FrameLib_Expression>(context, &parameters, mProxy, 1);
    mObjects[73]->addConnection(Connection(mObjects[72], 0), 0);

    parameters.clear();
    parameters.write("name", "phases");
    mObjects[74] = new FrameLib_Expand<FrameLib_Store>(context, &parameters, mProxy, 1);
    mObjects[74]->addConnection(Connection(mObjects[73], 0), 0);

    parameters.clear();
    mObjects[75] = new FrameLib_Expand<FrameLib_UnaryOp<Unary_Functor<&sin> > >(context, &parameters, mProxy, 1);
    mObjects[75]->addConnection(Connection(mObjects[72], 0), 0);

    parameters.clear();
    mObjects[76] = new FrameLib_Expand<FrameLib_BinaryOp<std::__1::multiplies<double> > >(context, &parameters, mProxy, 1);
    mObjects[76]->addConnection(Connection(mObjects[61], 0), 0);
    mObjects[76]->addConnection(Connection(mObjects[75], 0), 1);

    double fl_77_vector_0[] = { 1 };
    parameters.clear();
    parameters.write("outputs", fl_77_vector_0, 1);
    mObjects[77] = new FrameLib_Unpack(context, &parameters, mProxy, 1);
    mObjects[77]->addConnection(Connection(mObjects[76], 0), 0);

    double fl_78_vector_0[] = { 64 };
    parameters.clear();
    parameters.write("interval", fl_78_vector_0, 1);
    mObjects[78] = new FrameLib_Expand<FrameLib_Interval>(context, &parameters, mProxy, 1);

    parameters.clear();
    parameters.write("mode", "params");
    mObjects[79] = new FrameLib_Expand<FrameLib_FromHost>(context, &parameters, mProxy, 1);
    mObjects[79]->addConnection(Connection(mObjects[78], 0), 0);

    parameters.clear();
    mObjects[80] = new FrameLib_Expand<FrameLib_Random>(context, &parameters, mProxy, 1);
    mObjects[80]->addConnection(Connection(mObjects[78], 0), 0);

    double fl_81_vector_1[] = { 0 };
    double fl_81_vector_2[] = { 1 };
    double fl_81_vector_3[] = { 200 };
    double fl_81_vector_4[] = { 600 };
    parameters.clear();
    parameters.write("mode", "exp");
    parameters.write("inlo", fl_81_vector_1, 1);
    parameters.write("inhi", fl_81_vector_2, 1);
    parameters.write("outlo", fl_81_vector_3, 1);
    parameters.write("outhi", fl_81_vector_4, 1);
    mObjects[81] = new FrameLib_Expand<FrameLib_Map>(context, &parameters, mProxy, 1);
    mObjects[81]->addConnection(Connection(mObjects[80], 0), 0);
    mObjects[81]->addConnection(Connection(mObjects[79], 0), 1);

    parameters.clear();
    parameters.write("tag_01", "interval");
    mObjects[82] = new FrameLib_Expand<FrameLib_Tag>(context, &parameters, mProxy, 1);
    mObjects[82]->addConnection(Connection(mObjects[81], 0), 0);

    parameters.clear();
    parameters.write("units", "ms");
    mObjects[83] = new FrameLib_Expand<FrameLib_Interval>(context, &parameters, mProxy, 1);
    mObjects[83]->addConnection(Connection(mObjects[82], 0), 0);

    parameters.clear();
    mObjects[84] = new FrameLib_Expand<FrameLib_Register>(context, &parameters, mProxy, 1);
    mObjects[84]->addConnection(Connection(mObjects[83], 0), 0);
    mObjects[84]->addConnection(Connection(mObjects[81], 0), 1);

    parameters.clear();
    parameters.write("units", "ms");
    mObjects[85] = new FrameLib_Expand<FrameLib_Timer>(context, &parameters, mProxy, 1);
    mObjects[85]->addConnection(Connection(mObjects[84], 0), 0);
    mObjects[85]->addConnection(Connection(mObjects[77], 0), 1);

    parameters.clear();
    parameters.write("trigger_ins", "left");
    mObjects[86] = new FrameLib_Expand<FrameLib_BinaryOp<std::__1::divides<double> > >(context, &parameters, mProxy, 1);
    mObjects[86]->addConnection(Connection(mObjects[85], 0), 0);
    mObjects[86]->addConnection(Connection(mObjects[84], 0), 1);

    parameters.clear();
    mObjects[87] = new FrameLib_Expand<FrameLib_BinaryOp<Binary_Functor<&pow> > >(context, &parameters, mProxy, 1);
    double fl_87_inputs_1[] = { 0.600000 };
    mObjects[87]->setFixedInput(1, fl_87_inputs_1 , 1);
    mObjects[87]->addConnection(Connection(mObjects[86], 0), 0);

    parameters.clear();
    mObjects[88] = new FrameLib_Expand<FrameLib_Vector<&statLength<double const*>, (FrameLib_Vector_EmptyMode)4> >(context, &parameters, mProxy, 1);
    mObjects[88]->addConnection(Connection(mObjects[77], 0), 0);

    parameters.clear();
    mObjects[89] = new FrameLib_Expand<FrameLib_Once>(context, &parameters, mProxy, 1);

    parameters.clear();
    mObjects[90] = new FrameLib_Expand<FrameLib_Register>(context, &parameters, mProxy, 1);
    double fl_90_inputs_1[] = { 0 };
    mObjects[90]->setFixedInput(1, fl_90_inputs_1 , 1);
    mObjects[90]->addConnection(Connection(mObjects[89], 0), 0);

    parameters.clear();
    parameters.write("name", "length");
    mObjects[91] = new FrameLib_Expand<FrameLib_Store>(context, &parameters, mProxy, 1);
    mObjects[91]->addConnection(Connection(mObjects[90], 0), 0);

    parameters.clear();
    parameters.write("name", "length");
    mObjects[92] = new FrameLib_Expand<FrameLib_Recall>(context, &parameters, mProxy, 1);
    mObjects[92]->addConnection(Connection(mObjects[77], 0), 0);
    mObjects[92]->addOrderingConnection(Connection(mObjects[91], 0));

    parameters.clear();
    mObjects[93] = new FrameLib_Expand<FrameLib_BinaryOp<std::__1::not_equal_to<double> > >(context, &parameters, mProxy, 1);
    mObjects[93]->addConnection(Connection(mObjects[88], 0), 0);
    mObjects[93]->addConnection(Connection(mObjects[92], 0), 1);

    parameters.clear();
    parameters.write("tag_01", "input");
    mObjects[94] = new FrameLib_Expand<FrameLib_Tag>(context, &parameters, mProxy, 1);
    mObjects[94]->addConnection(Connection(mObjects[93], 0), 0);

    double fl_95_vector_0[] = { 2 };
    parameters.clear();
    parameters.write("num_ins", fl_95_vector_0, 1);
    mObjects[95] = new FrameLib_Expand<FrameLib_Select>(context, &parameters, mProxy, 1);
    mObjects[95]->addConnection(Connection(mObjects[77], 0), 0);
    mObjects[95]->addConnection(Connection(mObjects[94], 0), 2);

    parameters.clear();
    parameters.write("mode", "input");
    parameters.write("scale", "normalised");
    mObjects[96] = new FrameLib_Expand<FrameLib_Ramp>(context, &parameters, mProxy, 1);
    mObjects[96]->addConnection(Connection(mObjects[95], 0), 0);

    parameters.clear();
    mObjects[97] = new FrameLib_Expand<FrameLib_Register>(context, &parameters, mProxy, 1);
    double fl_97_inputs_1[] = { 40 };
    mObjects[97]->setFixedInput(1, fl_97_inputs_1 , 1);
    mObjects[97]->addConnection(Connection(mObjects[96], 0), 0);

    parameters.clear();
    parameters.write("mode", "freq->halfnorm");
    mObjects[98] = new FrameLib_Expand<FrameLib_SampleRate>(context, &parameters, mProxy, 1);
    mObjects[98]->addConnection(Connection(mObjects[97], 0), 0);

    parameters.clear();
    mObjects[99] = new FrameLib_Expand<FrameLib_Register>(context, &parameters, mProxy, 1);
    double fl_99_inputs_1[] = { 40 };
    mObjects[99]->setFixedInput(1, fl_99_inputs_1 , 1);
    mObjects[99]->addConnection(Connection(mObjects[96], 0), 0);

    parameters.clear();
    parameters.write("mode", "freq->halfnorm");
    mObjects[100] = new FrameLib_Expand<FrameLib_SampleRate>(context, &parameters, mProxy, 1);
    mObjects[100]->addConnection(Connection(mObjects[99], 0), 0);

    parameters.clear();
    parameters.write("tag_01", "inlo");
    parameters.write("tag_02", "outlo");
    mObjects[101] = new FrameLib_Expand<FrameLib_Tag>(context, &parameters, mProxy, 1);
    mObjects[101]->addConnection(Connection(mObjects[100], 0), 0);
    mObjects[101]->addConnection(Connection(mObjects[98], 0), 1);

    double fl_102_vector_1[] = { 0.002000 };
    double fl_102_vector_2[] = { 0.600000 };
    double fl_102_vector_3[] = { 0 };
    double fl_102_vector_4[] = { 1 };
    double fl_102_vector_5[] = { 1 };
    parameters.clear();
    parameters.write("mode", "log");
    parameters.write("inlo", fl_102_vector_1, 1);
    parameters.write("inhi", fl_102_vector_2, 1);
    parameters.write("outlo", fl_102_vector_3, 1);
    parameters.write("outhi", fl_102_vector_4, 1);
    parameters.write("clip", fl_102_vector_5, 1);
    mObjects[102] = new FrameLib_Expand<FrameLib_Map>(context, &parameters, mProxy, 1);
    mObjects[102]->addConnection(Connection(mObjects[96], 0), 0);
    mObjects[102]->addConnection(Connection(mObjects[101], 0), 1);

    parameters.clear();
    mObjects[103] = new FrameLib_Expand<FrameLib_Vector<&statLength<double const*>, (FrameLib_Vector_EmptyMode)4> >(context, &parameters, mProxy, 1);
    mObjects[103]->addConnection(Connection(mObjects[102], 0), 0);

    parameters.clear();
    parameters.write("name", "length");
    mObjects[104] = new FrameLib_Expand<FrameLib_Store>(context, &parameters, mProxy, 1);
    mObjects[104]->addConnection(Connection(mObjects[103], 0), 0);

    parameters.clear();
    parameters.write("mode", "params");
    mObjects[105] = new FrameLib_Expand<FrameLib_FromHost>(context, &parameters, mProxy, 1);
    mObjects[105]->addConnection(Connection(mObjects[83], 0), 0);

    double fl_106_vector_1[] = { 1 };
    double fl_106_vector_2[] = { 45 };
    parameters.clear();
    parameters.write("mode", "requested");
    parameters.write("stddev", fl_106_vector_1, 1);
    parameters.write("length", fl_106_vector_2, 1);
    mObjects[106] = new FrameLib_Expand<FrameLib_Gaussian>(context, &parameters, mProxy, 1);
    mObjects[106]->addConnection(Connection(mObjects[83], 0), 0);
    mObjects[106]->addConnection(Connection(mObjects[105], 0), 2);

    parameters.clear();
    parameters.write("mode", "input");
    parameters.write("scale", "normalised");
    mObjects[107] = new FrameLib_Expand<FrameLib_Ramp>(context, &parameters, mProxy, 1);
    mObjects[107]->addConnection(Connection(mObjects[106], 0), 0);

    parameters.clear();
    parameters.write("mode", "params");
    mObjects[108] = new FrameLib_Expand<FrameLib_FromHost>(context, &parameters, mProxy, 1);
    mObjects[108]->addConnection(Connection(mObjects[107], 0), 0);

    double fl_109_vector_1[] = { 0 };
    double fl_109_vector_2[] = { 1 };
    double fl_109_vector_3[] = { 10 };
    double fl_109_vector_4[] = { 2 };
    parameters.clear();
    parameters.write("mode", "linear");
    parameters.write("inlo", fl_109_vector_1, 1);
    parameters.write("inhi", fl_109_vector_2, 1);
    parameters.write("outlo", fl_109_vector_3, 1);
    parameters.write("outhi", fl_109_vector_4, 1);
    mObjects[109] = new FrameLib_Expand<FrameLib_Map>(context, &parameters, mProxy, 1);
    mObjects[109]->addConnection(Connection(mObjects[107], 0), 0);
    mObjects[109]->addConnection(Connection(mObjects[108], 0), 1);

    parameters.clear();
    mObjects[110] = new FrameLib_Expand<FrameLib_TernaryOp<Ternary_Functor<&FrameLib_Ternary_Ops::clip<double>> > >(context, &parameters, mProxy, 1);
    double fl_110_inputs_1[] = { -1 };
    double fl_110_inputs_2[] = { 1 };
    mObjects[110]->setFixedInput(1, fl_110_inputs_1 , 1);
    mObjects[110]->setFixedInput(2, fl_110_inputs_2 , 1);
    mObjects[110]->addConnection(Connection(mObjects[106], 0), 0);

    parameters.clear();
    mObjects[111] = new FrameLib_Expand<FrameLib_BinaryOp<std::__1::multiplies<double> > >(context, &parameters, mProxy, 1);
    mObjects[111]->addConnection(Connection(mObjects[110], 0), 0);
    mObjects[111]->addConnection(Connection(mObjects[109], 0), 1);

    parameters.clear();
    mObjects[112] = new FrameLib_Expand<FrameLib_Vector<&statLength<double const*>, (FrameLib_Vector_EmptyMode)4> >(context, &parameters, mProxy, 1);
    mObjects[112]->addConnection(Connection(mObjects[110], 0), 0);

    parameters.clear();
    mObjects[113] = new FrameLib_Expand<FrameLib_BinaryOp<std::__1::minus<double> > >(context, &parameters, mProxy, 1);
    double fl_113_inputs_1[] = { 1 };
    mObjects[113]->setFixedInput(1, fl_113_inputs_1 , 1);
    mObjects[113]->addConnection(Connection(mObjects[112], 0), 0);

    parameters.clear();
    mObjects[114] = new FrameLib_Expand<FrameLib_BinaryOp<std::__1::multiplies<double> > >(context, &parameters, mProxy, 1);
    mObjects[114]->addConnection(Connection(mObjects[102], 0), 0);
    mObjects[114]->addConnection(Connection(mObjects[113], 0), 1);

    parameters.clear();
    parameters.write("mode", "clip");
    mObjects[115] = new FrameLib_Expand<FrameLib_Lookup>(context, &parameters, mProxy, 1);
    mObjects[115]->addConnection(Connection(mObjects[114], 0), 0);
    mObjects[115]->addConnection(Connection(mObjects[111], 0), 1);

    parameters.clear();
    mObjects[116] = new FrameLib_Expand<FrameLib_Register>(context, &parameters, mProxy, 1);
    mObjects[116]->addConnection(Connection(mObjects[77], 0), 0);
    mObjects[116]->addConnection(Connection(mObjects[115], 0), 1);

    parameters.clear();
    parameters.write("name", "eq");
    mObjects[117] = new FrameLib_Expand<FrameLib_Recall>(context, &parameters, mProxy, 1);
    mObjects[117]->addConnection(Connection(mObjects[115], 0), 0);

    parameters.clear();
    mObjects[118] = new FrameLib_Expand<FrameLib_Vector<&statLength<double const*>, (FrameLib_Vector_EmptyMode)4> >(context, &parameters, mProxy, 1);
    mObjects[118]->addConnection(Connection(mObjects[117], 0), 0);

    parameters.clear();
    mObjects[119] = new FrameLib_Expand<FrameLib_Vector<&statLength<double const*>, (FrameLib_Vector_EmptyMode)4> >(context, &parameters, mProxy, 1);
    mObjects[119]->addConnection(Connection(mObjects[77], 0), 0);

    parameters.clear();
    parameters.write("expr", "(in1 != in2) + 1");
    mObjects[120] = new FrameLib_Expand<FrameLib_Expression>(context, &parameters, mProxy, 1);
    mObjects[120]->addConnection(Connection(mObjects[118], 0), 0);
    mObjects[120]->addConnection(Connection(mObjects[119], 0), 1);

    parameters.clear();
    parameters.write("tag_01", "input");
    mObjects[121] = new FrameLib_Expand<FrameLib_Tag>(context, &parameters, mProxy, 1);
    mObjects[121]->addConnection(Connection(mObjects[120], 0), 0);

    parameters.clear();
    parameters.write("mode", "input");
    mObjects[122] = new FrameLib_Expand<FrameLib_Uniform>(context, &parameters, mProxy, 1);
    mObjects[122]->addConnection(Connection(mObjects[77], 0), 0);

    parameters.clear();
    mObjects[123] = new FrameLib_Expand<FrameLib_Select>(context, &parameters, mProxy, 1);
    mObjects[123]->addConnection(Connection(mObjects[117], 0), 0);
    mObjects[123]->addConnection(Connection(mObjects[122], 0), 1);
    mObjects[123]->addConnection(Connection(mObjects[121], 0), 2);

    parameters.clear();
    mObjects[124] = new FrameLib_Expand<FrameLib_Register>(context, &parameters, mProxy, 1);
    mObjects[124]->addConnection(Connection(mObjects[77], 0), 0);
    mObjects[124]->addConnection(Connection(mObjects[123], 0), 1);

    double fl_125_vector_1[] = { 1, 0, 0 };
    parameters.clear();
    parameters.write("expr", "in1 + in3 * (in2 - in1) ");
    parameters.write("trigger_ins", fl_125_vector_1, 3);
    mObjects[125] = new FrameLib_Expand<FrameLib_Expression>(context, &parameters, mProxy, 1);
    mObjects[125]->addConnection(Connection(mObjects[124], 0), 0);
    mObjects[125]->addConnection(Connection(mObjects[116], 0), 1);
    mObjects[125]->addConnection(Connection(mObjects[87], 0), 2);

    parameters.clear();
    parameters.write("name", "eq");
    mObjects[126] = new FrameLib_Expand<FrameLib_Store>(context, &parameters, mProxy, 1);
    mObjects[126]->addConnection(Connection(mObjects[125], 0), 0);

    parameters.clear();
    parameters.write("mode", "db->amp");
    mObjects[127] = new FrameLib_Expand<FrameLib_Convert>(context, &parameters, mProxy, 1);
    mObjects[127]->addConnection(Connection(mObjects[125], 0), 0);

    parameters.clear();
    mObjects[128] = new FrameLib_Expand<FrameLib_BinaryOp<std::__1::multiplies<double> > >(context, &parameters, mProxy, 1);
    mObjects[128]->addConnection(Connection(mObjects[76], 0), 0);
    mObjects[128]->addConnection(Connection(mObjects[127], 0), 1);

    parameters.clear();
    mObjects[129] = new FrameLib_Expand<FrameLib_UnaryOp<Unary_Functor<&cos> > >(context, &parameters, mProxy, 1);
    mObjects[129]->addConnection(Connection(mObjects[72], 0), 0);

    parameters.clear();
    mObjects[130] = new FrameLib_Expand<FrameLib_BinaryOp<std::__1::multiplies<double> > >(context, &parameters, mProxy, 1);
    mObjects[130]->addConnection(Connection(mObjects[61], 0), 0);
    mObjects[130]->addConnection(Connection(mObjects[129], 0), 1);

    parameters.clear();
    mObjects[131] = new FrameLib_Expand<FrameLib_BinaryOp<std::__1::multiplies<double> > >(context, &parameters, mProxy, 1);
    mObjects[131]->addConnection(Connection(mObjects[130], 0), 0);
    mObjects[131]->addConnection(Connection(mObjects[127], 0), 1);

    double fl_132_vector_0[] = { 65536 };
    parameters.clear();
    parameters.write("maxlength", fl_132_vector_0, 1);
    mObjects[132] = new FrameLib_Expand<FrameLib_iFFT>(context, &parameters, mProxy, 1);
    mObjects[132]->addConnection(Connection(mObjects[131], 0), 0);
    mObjects[132]->addConnection(Connection(mObjects[128], 0), 1);

    parameters.clear();
    mObjects[133] = new FrameLib_Expand<FrameLib_BinaryOp<std::__1::equal_to<double> > >(context, &parameters, mProxy, 1);
    double fl_133_inputs_1[] = { 2 };
    mObjects[133]->setFixedInput(1, fl_133_inputs_1 , 1);
    mObjects[133]->addConnection(Connection(mObjects[1], 0), 0);

    parameters.clear();
    parameters.write("tag_01", "sqrt");
    mObjects[134] = new FrameLib_Expand<FrameLib_Tag>(context, &parameters, mProxy, 1);
    mObjects[134]->addConnection(Connection(mObjects[133], 0), 0);

    parameters.clear();
    parameters.write("window", "hann");
    parameters.write("compensate", "powoverlin");
    mObjects[135] = new FrameLib_Expand<FrameLib_Window>(context, &parameters, mProxy, 1);
    mObjects[135]->addConnection(Connection(mObjects[132], 0), 0);
    mObjects[135]->addConnection(Connection(mObjects[134], 0), 1);

    parameters.clear();
    mObjects[136] = new FrameLib_Expand<FrameLib_BinaryOp<std::__1::divides<double> > >(context, &parameters, mProxy, 1);
    double fl_136_inputs_0[] = { 1 };
    mObjects[136]->setFixedInput(0, fl_136_inputs_0 , 1);
    mObjects[136]->addConnection(Connection(mObjects[1], 0), 1);

    parameters.clear();
    parameters.write("trigger_ins", "right");
    mObjects[137] = new FrameLib_Expand<FrameLib_BinaryOp<std::__1::multiplies<double> > >(context, &parameters, mProxy, 1);
    mObjects[137]->addConnection(Connection(mObjects[136], 0), 0);
    mObjects[137]->addConnection(Connection(mObjects[135], 0), 1);

    parameters.clear();
    mObjects[138] = new FrameLib_Expand<FrameLib_Sink>(context, &parameters, mProxy, 2);
    mObjects[138]->addConnection(Connection(mObjects[137], 0), 0);

    for (auto it = mObjects.begin(); it != mObjects.end(); it++)
    {
        if ((*it)->getType() == kScheduler || (*it)->getNumAudioChans())//if ((*it)->handlesAudio())
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