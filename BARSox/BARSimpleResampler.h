#ifndef BARSIMPLERESAMPLER_H
#define BARSIMPLERESAMPLER_H

#include <vector>

template<typename T>
class BARSimpleResampler
{
    public:
        BARSimpleResampler() {
        }

        static void resample(std::vector<T>& vec, float currentRate, float desiredRate, bool stereo=false) {
            if (currentRate > desiredRate) {
                downsample(vec, currentRate, desiredRate, stereo);
            } else if (currentRate < desiredRate) {
                upsample(vec, currentRate, desiredRate, stereo);
            }
        }

        static void upsample(std::vector<T>& vec, float currentRate, float desiredRate, bool stereo=false) {
            if (currentRate < desiredRate) {
                unsigned int i=0, jb=0, d=stereo ? 2 : 1;
                //unsigned int ja=0, k=0;
                //T c=0;

                unsigned int vecSize = vec.size();
                float rateRatio = desiredRate/currentRate;

                std::vector<T> vec_orig(vec);

                vec.clear();
                if (!stereo) {
                    vec.resize((unsigned int)(rateRatio*vecSize), 0);
                } else {
                    unsigned int size = rateRatio*vecSize;
                    vec.resize(size - size%d);
                }

                vec[0] = vec_orig[0];
                if (stereo) {
                    vec[1] = vec_orig[1];
                }

                for (i = d; i < vecSize; i+= d) {
                    //ja = jb;
                    jb = i*rateRatio;
                    if (stereo) {
                        jb -= jb%d;
                    }

                    vec[jb] = vec_orig[i];
                    if (stereo) {
                        vec[jb+1] = vec_orig[i+1];
                    }

                    //c = d*(vec[jb] - vec[ja])/(jb - ja);

                    //It looks too simple to insert zeros but it is less noisy than using linear interpolation.

                    /*for (k=ja+d; k<jb; k+=d) {
                        //vec[k] = vec[k-d] + c;
                        if (stereo) {
                            //vec[k+1] = vec[k-d+1] + c;
                        }
                    }*/
                }
            }
        }

        static void downsample(std::vector<T>& vec, float currentRate, float desiredRate, bool stereo = false) {
            if (currentRate > desiredRate) {
                unsigned int i=0, j=0, d = stereo ? 2 : 1;

                unsigned int vecSize = vec.size();
                float rateRatio = desiredRate/currentRate;

                std::vector<T> vec_orig(vec);

                vec.clear();
                if (!stereo) {
                    vec.resize((unsigned int)(rateRatio*vecSize), 0);
                } else {
                    unsigned int size = rateRatio*vecSize;
                    vec.resize(size + size%d);
                }

                vec[0] = vec_orig[0];
                if (stereo) {
                    vec[1] = vec_orig[1];
                }

                for (j = d; j < vec.size(); j+= d) {
                    i = j/rateRatio;
                    if (stereo) {
                        i -= i%d;
                    }

                    vec[j] = vec_orig[i];

                    if (stereo) {
                        vec[j+1] = vec_orig[i+1];
                    }
                }

            }
        }
};

#endif // BARSIMPLERESAMPLER_H
