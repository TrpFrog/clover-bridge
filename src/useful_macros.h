#ifndef CLOVER_BRIDGE_USEFUL_MACROS_H
#define CLOVER_BRIDGE_USEFUL_MACROS_H

#include <iostream>

#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
    #include <OpenGL/OpenGL.h>
    #include <GLUT/GLUT.h>
#else
    #include <GL/glut.h>
#endif

// iterator
#define ALL(obj) (obj).begin(), (obj).end()
#define rALL(obj) (obj).rbegin(), (obj).rend()

// loop
#define REP(i, n) for (int i = 0; i < (int)(n); i++)
#define rREP(i, n) for (int i = (int)(n) - 1; i >= 0; i--)
#define REPS(i, n, m) for (int i = (int)(n); i < (int)(m); i++)
#define rREPS(i, n, m) for (int i = (int)(m) - 1; i >= (int)(n); i--)

// debug
#define dbgarr(a) {for(auto _e:(a)){std::cerr << _e << " ";} std::cerr << std::endl;}
#define debug(x) std::cerr << #x << ": " << x << std::endl
#define debugarr(a) {std::cerr << #a << ": "; dbgarr(a);}

// math
#define mod(a, m) (((a) % (m) + (m)) % (m))
#define fmodp(a, m) fmod(fmod((a), (m)) + (m), (m))
#define scale(v, l1, r1, l2, r2) (l2 + ((r2) - (l2)) / ((r1) - (l1)) * (v - l1))

#endif //CLOVER_BRIDGE_USEFUL_MACROS_H
