
#include "Freeze.h"
#include "FrameLib_Objects.h"

Freeze::Freeze(FrameLib_Proxy *proxy) : mNumAudioIns(0), mNumAudioOuts(0), mProxy(proxy)
{
    using Connection = FrameLib_Object<FrameLib_Multistream>::Connection;

    FrameLib_Global::get(&mGlobal, FrameLib_Thread::defaultPriorities());
    FrameLib_Context context(mGlobal, this);
    FrameLib_Parameters::AutoSerial parameters;

    mObjects.resize(85);

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
    parameters.write("units", "ms");
    mObjects[34] = new FrameLib_Expand<FrameLib_Timer>(context, &parameters, mProxy, 8);
    mObjects[34]->addConnection(Connection(mObjects[32], 0), 0);
    mObjects[34]->addConnection(Connection(mObjects[31], 0), 1);

    parameters.clear();
    mObjects[35] = new FrameLib_Expand<FrameLib_BinaryOp<std::__1::divides<double> > >(context, &parameters, mProxy, 1);
    mObjects[35]->addConnection(Connection(mObjects[34], 0), 0);
    mObjects[35]->addConnection(Connection(mObjects[33], 0), 1);

    parameters.clear();
    mObjects[36] = new FrameLib_Expand<FrameLib_TernaryOp<Ternary_Functor<&FrameLib_Ternary_Ops::clip<double>> > >(context, &parameters, mProxy, 1);
    double fl_36_inputs_1[] = { 0 };
    double fl_36_inputs_2[] = { 1 };
    mObjects[36]->setFixedInput(1, fl_36_inputs_1 , 1);
    mObjects[36]->setFixedInput(2, fl_36_inputs_2 , 1);
    mObjects[36]->addConnection(Connection(mObjects[35], 0), 0);

    parameters.clear();
    parameters.write("name", "last");
    mObjects[37] = new FrameLib_Expand<FrameLib_Recall>(context, &parameters, mProxy, 8);
    mObjects[37]->addConnection(Connection(mObjects[32], 0), 0);

    parameters.clear();
    parameters.write("name", "freezeOld");
    mObjects[38] = new FrameLib_Expand<FrameLib_Store>(context, &parameters, mProxy, 8);
    mObjects[38]->addConnection(Connection(mObjects[37], 0), 0);

    parameters.clear();
    parameters.write("name", "freezeOld");
    mObjects[39] = new FrameLib_Expand<FrameLib_Recall>(context, &parameters, mProxy, 8);
    mObjects[39]->addConnection(Connection(mObjects[31], 0), 0);
    mObjects[39]->addOrderingConnection(Connection(mObjects[38], 0));

    parameters.clear();
    mObjects[40] = new FrameLib_Expand<FrameLib_Vector<&statLength<double const*>, (FrameLib_Vector_EmptyMode)4> >(context, &parameters, mProxy, 1);
    mObjects[40]->addConnection(Connection(mObjects[39], 0), 0);

    parameters.clear();
    mObjects[41] = new FrameLib_Expand<FrameLib_Vector<&statLength<double const*>, (FrameLib_Vector_EmptyMode)4> >(context, &parameters, mProxy, 1);
    mObjects[41]->addConnection(Connection(mObjects[31], 0), 0);

    parameters.clear();
    parameters.write("expr", "(in1 != in2) + 1");
    mObjects[42] = new FrameLib_Expand<FrameLib_Expression>(context, &parameters, mProxy, 1);
    mObjects[42]->addConnection(Connection(mObjects[40], 0), 0);
    mObjects[42]->addConnection(Connection(mObjects[41], 0), 1);

    parameters.clear();
    parameters.write("tag_01", "input");
    mObjects[43] = new FrameLib_Expand<FrameLib_Tag>(context, &parameters, mProxy, 1);
    mObjects[43]->addConnection(Connection(mObjects[42], 0), 0);

    parameters.clear();
    parameters.write("mode", "input");
    mObjects[44] = new FrameLib_Expand<FrameLib_Uniform>(context, &parameters, mProxy, 1);
    mObjects[44]->addConnection(Connection(mObjects[31], 0), 0);

    parameters.clear();
    mObjects[45] = new FrameLib_Expand<FrameLib_Select>(context, &parameters, mProxy, 1);
    mObjects[45]->addConnection(Connection(mObjects[39], 0), 0);
    mObjects[45]->addConnection(Connection(mObjects[44], 0), 1);
    mObjects[45]->addConnection(Connection(mObjects[43], 0), 2);

    parameters.clear();
    mObjects[46] = new FrameLib_Expand<FrameLib_Register>(context, &parameters, mProxy, 1);
    mObjects[46]->addConnection(Connection(mObjects[32], 0), 0);
    mObjects[46]->addConnection(Connection(mObjects[31], 0), 1);

    parameters.clear();
    parameters.write("name", "freeze");
    mObjects[47] = new FrameLib_Expand<FrameLib_Store>(context, &parameters, mProxy, 8);
    mObjects[47]->addConnection(Connection(mObjects[46], 0), 0);

    parameters.clear();
    parameters.write("name", "freeze");
    mObjects[48] = new FrameLib_Expand<FrameLib_Recall>(context, &parameters, mProxy, 8);
    mObjects[48]->addConnection(Connection(mObjects[31], 0), 0);
    mObjects[48]->addOrderingConnection(Connection(mObjects[47], 0));

    parameters.clear();
    mObjects[49] = new FrameLib_Expand<FrameLib_Vector<&statLength<double const*>, (FrameLib_Vector_EmptyMode)4> >(context, &parameters, mProxy, 1);
    mObjects[49]->addConnection(Connection(mObjects[48], 0), 0);

    parameters.clear();
    mObjects[50] = new FrameLib_Expand<FrameLib_Vector<&statLength<double const*>, (FrameLib_Vector_EmptyMode)4> >(context, &parameters, mProxy, 1);
    mObjects[50]->addConnection(Connection(mObjects[31], 0), 0);

    parameters.clear();
    parameters.write("expr", "(in1 != in2) + 1");
    mObjects[51] = new FrameLib_Expand<FrameLib_Expression>(context, &parameters, mProxy, 1);
    mObjects[51]->addConnection(Connection(mObjects[49], 0), 0);
    mObjects[51]->addConnection(Connection(mObjects[50], 0), 1);

    parameters.clear();
    parameters.write("tag_01", "input");
    mObjects[52] = new FrameLib_Expand<FrameLib_Tag>(context, &parameters, mProxy, 1);
    mObjects[52]->addConnection(Connection(mObjects[51], 0), 0);

    parameters.clear();
    parameters.write("mode", "input");
    mObjects[53] = new FrameLib_Expand<FrameLib_Uniform>(context, &parameters, mProxy, 1);
    mObjects[53]->addConnection(Connection(mObjects[31], 0), 0);

    parameters.clear();
    mObjects[54] = new FrameLib_Expand<FrameLib_Select>(context, &parameters, mProxy, 1);
    mObjects[54]->addConnection(Connection(mObjects[48], 0), 0);
    mObjects[54]->addConnection(Connection(mObjects[53], 0), 1);
    mObjects[54]->addConnection(Connection(mObjects[52], 0), 2);

    double fl_55_vector_1[] = { 1 };
    parameters.clear();
    parameters.write("expr", "in1+in3*(in2-in1) ");
    parameters.write("trigger_ins", fl_55_vector_1, 1);
    mObjects[55] = new FrameLib_Expand<FrameLib_Expression>(context, &parameters, mProxy, 1);
    mObjects[55]->addConnection(Connection(mObjects[45], 0), 0);
    mObjects[55]->addConnection(Connection(mObjects[54], 0), 1);
    mObjects[55]->addConnection(Connection(mObjects[36], 0), 2);

    parameters.clear();
    parameters.write("name", "last");
    mObjects[56] = new FrameLib_Expand<FrameLib_Store>(context, &parameters, mProxy, 1);
    mObjects[56]->addConnection(Connection(mObjects[55], 0), 0);

    double fl_57_vector_0[] = { 8 };
    parameters.clear();
    parameters.write("outputs", fl_57_vector_0, 1);
    mObjects[57] = new FrameLib_Unpack(context, &parameters, mProxy, 1);
    mObjects[57]->addConnection(Connection(mObjects[55], 0), 0);

    parameters.clear();
    mObjects[58] = new FrameLib_Pack(context, &parameters, mProxy, 1);
    mObjects[58]->addConnection(Connection(mObjects[57], 0), 0);
    mObjects[58]->addConnection(Connection(mObjects[57], 1), 1);

    parameters.clear();
    mObjects[59] = new FrameLib_Pack(context, &parameters, mProxy, 1);
    mObjects[59]->addConnection(Connection(mObjects[57], 2), 0);
    mObjects[59]->addConnection(Connection(mObjects[57], 3), 1);

    parameters.clear();
    parameters.write("mode", "input");
    mObjects[60] = new FrameLib_Expand<FrameLib_Gaussian>(context, &parameters, mProxy, 1);
    mObjects[60]->addConnection(Connection(mObjects[58], 0), 0);
    mObjects[60]->addConnection(Connection(mObjects[59], 0), 1);

    parameters.clear();
    mObjects[61] = new FrameLib_Pack(context, &parameters, mProxy, 1);
    mObjects[61]->addConnection(Connection(mObjects[57], 4), 0);
    mObjects[61]->addConnection(Connection(mObjects[57], 5), 1);

    parameters.clear();
    mObjects[62] = new FrameLib_Pack(context, &parameters, mProxy, 1);
    mObjects[62]->addConnection(Connection(mObjects[57], 6), 0);
    mObjects[62]->addConnection(Connection(mObjects[57], 7), 1);

    parameters.clear();
    parameters.write("mode", "input");
    mObjects[63] = new FrameLib_Expand<FrameLib_Gaussian>(context, &parameters, mProxy, 1);
    mObjects[63]->addConnection(Connection(mObjects[61], 0), 0);
    mObjects[63]->addConnection(Connection(mObjects[62], 0), 1);

    parameters.clear();
    mObjects[64] = new FrameLib_Expand<FrameLib_Vector<&statLength<double const*>, (FrameLib_Vector_EmptyMode)4> >(context, &parameters, mProxy, 1);
    mObjects[64]->addConnection(Connection(mObjects[63], 0), 0);

    parameters.clear();
    parameters.write("tag_01", "split");
    mObjects[65] = new FrameLib_Expand<FrameLib_Tag>(context, &parameters, mProxy, 1);
    mObjects[65]->addConnection(Connection(mObjects[64], 0), 0);

    parameters.clear();
    parameters.write("name", "phases");
    mObjects[66] = new FrameLib_Expand<FrameLib_Recall>(context, &parameters, mProxy, 1);
    mObjects[66]->addConnection(Connection(mObjects[63], 0), 0);

    parameters.clear();
    mObjects[67] = new FrameLib_Expand<FrameLib_Vector<&statLength<double const*>, (FrameLib_Vector_EmptyMode)4> >(context, &parameters, mProxy, 1);
    mObjects[67]->addConnection(Connection(mObjects[66], 0), 0);

    parameters.clear();
    mObjects[68] = new FrameLib_Expand<FrameLib_BinaryOp<std::__1::equal_to<double> > >(context, &parameters, mProxy, 1);
    mObjects[68]->addConnection(Connection(mObjects[67], 0), 0);
    mObjects[68]->addConnection(Connection(mObjects[64], 0), 1);

    parameters.clear();
    parameters.write("mismatch", "pad_in");
    mObjects[69] = new FrameLib_Expand<FrameLib_BinaryOp<std::__1::plus<double> > >(context, &parameters, mProxy, 1);
    double fl_69_inputs_1[] = { 0 };
    mObjects[69]->setFixedInput(1, fl_69_inputs_1 , 1);
    mObjects[69]->addConnection(Connection(mObjects[66], 0), 0);

    double fl_70_vector_0[] = { 1 };
    parameters.clear();
    parameters.write("split", fl_70_vector_0, 1);
    mObjects[70] = new FrameLib_Expand<FrameLib_Split>(context, &parameters, mProxy, 1);
    mObjects[70]->addConnection(Connection(mObjects[69], 0), 0);
    mObjects[70]->addConnection(Connection(mObjects[65], 0), 1);

    parameters.clear();
    parameters.write("expr", "in1 + in3 * in2");
    mObjects[71] = new FrameLib_Expand<FrameLib_Expression>(context, &parameters, mProxy, 1);
    mObjects[71]->addConnection(Connection(mObjects[63], 0), 0);
    mObjects[71]->addConnection(Connection(mObjects[70], 0), 1);
    mObjects[71]->addConnection(Connection(mObjects[68], 0), 2);

    parameters.clear();
    parameters.write("expr", "wrap(in1, -pi, pi)");
    mObjects[72] = new FrameLib_Expand<FrameLib_Expression>(context, &parameters, mProxy, 1);
    mObjects[72]->addConnection(Connection(mObjects[71], 0), 0);

    parameters.clear();
    parameters.write("name", "phases");
    mObjects[73] = new FrameLib_Expand<FrameLib_Store>(context, &parameters, mProxy, 1);
    mObjects[73]->addConnection(Connection(mObjects[72], 0), 0);

    parameters.clear();
    mObjects[74] = new FrameLib_Expand<FrameLib_UnaryOp<Unary_Functor<&sin> > >(context, &parameters, mProxy, 1);
    mObjects[74]->addConnection(Connection(mObjects[71], 0), 0);

    parameters.clear();
    mObjects[75] = new FrameLib_Expand<FrameLib_BinaryOp<std::__1::multiplies<double> > >(context, &parameters, mProxy, 1);
    mObjects[75]->addConnection(Connection(mObjects[60], 0), 0);
    mObjects[75]->addConnection(Connection(mObjects[74], 0), 1);

    parameters.clear();
    mObjects[76] = new FrameLib_Expand<FrameLib_UnaryOp<Unary_Functor<&cos> > >(context, &parameters, mProxy, 1);
    mObjects[76]->addConnection(Connection(mObjects[71], 0), 0);

    parameters.clear();
    mObjects[77] = new FrameLib_Expand<FrameLib_BinaryOp<std::__1::multiplies<double> > >(context, &parameters, mProxy, 1);
    mObjects[77]->addConnection(Connection(mObjects[60], 0), 0);
    mObjects[77]->addConnection(Connection(mObjects[76], 0), 1);

    double fl_78_vector_0[] = { 65536 };
    parameters.clear();
    parameters.write("maxlength", fl_78_vector_0, 1);
    mObjects[78] = new FrameLib_Expand<FrameLib_iFFT>(context, &parameters, mProxy, 1);
    mObjects[78]->addConnection(Connection(mObjects[77], 0), 0);
    mObjects[78]->addConnection(Connection(mObjects[75], 0), 1);

    parameters.clear();
    mObjects[79] = new FrameLib_Expand<FrameLib_BinaryOp<std::__1::equal_to<double> > >(context, &parameters, mProxy, 1);
    double fl_79_inputs_1[] = { 2 };
    mObjects[79]->setFixedInput(1, fl_79_inputs_1 , 1);
    mObjects[79]->addConnection(Connection(mObjects[1], 0), 0);

    parameters.clear();
    parameters.write("tag_01", "sqrt");
    mObjects[80] = new FrameLib_Expand<FrameLib_Tag>(context, &parameters, mProxy, 1);
    mObjects[80]->addConnection(Connection(mObjects[79], 0), 0);

    parameters.clear();
    parameters.write("window", "hann");
    parameters.write("compensate", "powoverlin");
    mObjects[81] = new FrameLib_Expand<FrameLib_Window>(context, &parameters, mProxy, 1);
    mObjects[81]->addConnection(Connection(mObjects[78], 0), 0);
    mObjects[81]->addConnection(Connection(mObjects[80], 0), 1);

    parameters.clear();
    mObjects[82] = new FrameLib_Expand<FrameLib_BinaryOp<std::__1::divides<double> > >(context, &parameters, mProxy, 1);
    double fl_82_inputs_0[] = { 1 };
    mObjects[82]->setFixedInput(0, fl_82_inputs_0 , 1);
    mObjects[82]->addConnection(Connection(mObjects[1], 0), 1);

    parameters.clear();
    parameters.write("trigger_ins", "right");
    mObjects[83] = new FrameLib_Expand<FrameLib_BinaryOp<std::__1::multiplies<double> > >(context, &parameters, mProxy, 1);
    mObjects[83]->addConnection(Connection(mObjects[82], 0), 0);
    mObjects[83]->addConnection(Connection(mObjects[81], 0), 1);

    parameters.clear();
    mObjects[84] = new FrameLib_Expand<FrameLib_Sink>(context, &parameters, mProxy, 2);
    mObjects[84]->addConnection(Connection(mObjects[83], 0), 0);

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