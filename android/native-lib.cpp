#include <jni.h>
#include <opencv2/opencv.hpp>

extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_example_MainActivity_processFrame(JNIEnv *env, jobject thiz,
                                           jbyteArray input, jint w, jint h) {

    jbyte* ptr = env->GetByteArrayElements(input, 0);

    cv::Mat rgba(h, w, CV_8UC4, (unsigned char*)ptr);
    cv::Mat gray, edges, out;

    cv::cvtColor(rgba, gray, cv::COLOR_RGBA2GRAY);
    cv::Canny(gray, edges, 80, 160);
    cv::cvtColor(edges, out, cv::COLOR_GRAY2RGBA);

    jbyteArray output = env->NewByteArray(out.total() * 4);
    env->SetByteArrayRegion(output, 0, out.total()*4, (jbyte*)out.data);

    env->ReleaseByteArrayElements(input, ptr, JNI_ABORT);
    return output;
}
