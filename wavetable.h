#ifndef WAVETABLE_H
#define WAVETABLE_H

#include <vector>

#define NUM_NOTES 108
#define MIDDLE_A_INDEX 48

using namespace std;

class WaveTable {
    public:
        WaveTable();
        ~WaveTable();
        double triangle(double phase, double freq);
        double square(double phase, double freq);
        double sawtooth(double phase, double freq);
        double sine(double phase, double freq);
        static double getSample(double phase, double freq, double **table);
        void buildTriangle();
        void buildSquare();
        void buildSawtooth();
        double sawtoothFunction(double phase, double f);
        double squareFunction(double phase, double f);
        double triangleFunction(double phase, double f);
    private:
        static double debugSample1(double cursor, double period, double **table, int closest);
        static double debugSample2(double cursor, double period, double **table, int closest);
        static double debugSample3(double cursor, double period, double **table, int closest);
        static double debugSample4(double cursor, double period, double **table, int closest, double amountLeft);
        static double debugSample5(double cursor, double period, double **table, int closest, double amountLeft);
        static double debugSample6(double cursor, double period, double **table, int closest, double amountLeft);
        double *triangleTable[NUM_NOTES];
        double *squareTable[NUM_NOTES];
        double *sawtoothTable[NUM_NOTES];
};

#endif
