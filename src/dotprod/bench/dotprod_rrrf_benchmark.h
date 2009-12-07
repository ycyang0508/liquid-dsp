/*
 * Copyright (c) 2007, 2009 Joseph Gaeddert
 * Copyright (c) 2007, 2009 Virginia Polytechnic Institute & State University
 *
 * This file is part of liquid.
 *
 * liquid is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * liquid is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with liquid.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __LIQUID_DOTPROD_BENCHMARK_H__
#define __LIQUID_DOTPROD_BENCHMARK_H__

#include <sys/resource.h>
#include "liquid.h"

// Helper function to keep code base small
void dotprod_rrrf_bench(
    struct rusage *_start,
    struct rusage *_finish,
    unsigned long int *_num_iterations,
    unsigned int _n)
{
    float x[_n], h[_n], y;
    unsigned int i;
    for (i=0; i<_n; i++) {
        x[i] = 1.0f;
        h[i] = 1.0f;
    }

    // start trials
    *_num_iterations *= 256;
    *_num_iterations /= _n;
    getrusage(RUSAGE_SELF, _start);
    for (i=0; i<(*_num_iterations); i++) {
        dotprod_rrrf_run(x,h,_n,&y);
        dotprod_rrrf_run(x,h,_n,&y);
        dotprod_rrrf_run(x,h,_n,&y);
        dotprod_rrrf_run(x,h,_n,&y);
    }
    getrusage(RUSAGE_SELF, _finish);
    *_num_iterations *= 4;

}

#define dotprod_rrrf_BENCHMARK_API(N)       \
(   struct rusage *_start,              \
    struct rusage *_finish,             \
    unsigned long int *_num_iterations) \
{ dotprod_rrrf_bench(_start, _finish, _num_iterations, N); }

void benchmark_dotprod_rrrf_4       dotprod_rrrf_BENCHMARK_API(4)
void benchmark_dotprod_rrrf_16      dotprod_rrrf_BENCHMARK_API(16)
void benchmark_dotprod_rrrf_64      dotprod_rrrf_BENCHMARK_API(64)
void benchmark_dotprod_rrrf_256     dotprod_rrrf_BENCHMARK_API(256)

#endif // __LIQUID_DOTPROD_BENCHMARK_H__

