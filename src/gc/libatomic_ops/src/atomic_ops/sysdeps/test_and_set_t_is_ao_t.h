/*
 * Copyright (c) 2004 Hewlett-Packard Development Company, L.P.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*
 * These are common definitions for architectures on which test_and_set
 * operates on pointer-sized quantities, the "clear" value contains
 * all zeroes, and the "set" value contains only one lowest bit set.
 * This can be used if test_and_set is synthesized from compare_and_swap.
 */
typedef enum {MK_AO_TS_clear = 0, MK_AO_TS_set = 1} MK_AO_TS_val;
#define MK_AO_TS_VAL_t MK_AO_TS_val
#define MK_AO_TS_CLEAR MK_AO_TS_clear
#define MK_AO_TS_SET MK_AO_TS_set

#define MK_AO_TS_t MK_AO_t

#define MK_AO_MK_AO_TS_T 1
