/*
 * Copyright (c) 2013-2019 Huawei Technologies Co., Ltd. All rights reserved.
 * Copyright (c) 2020-2021 Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 * of conditions and the following disclaimer in the documentation and/or other materials
 * provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific prior written
 * permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "It_posix_mem.h"

/* *
 * @test IT_POSIX_MEMALIGN_003
 * -@tspec posix_memalign Function test
 * -@ttitle The alignment argument was a power of two
 * -@tprecon dynamic memory function open
 * -@tbrief
 * -#alignment == 4,8,16,32,64
 * -@texpect
 * -#return EINVAL
 * -#return EINVAL
 * -@tprior 1
 * -@tauto TRUE
 * -@tremark
 */
static UINT32 Testcase(VOID)
{
    int ret;
    size_t align = sizeof(UINTPTR);
    size_t size = 0x100;
    void *p = nullptr;

    for (align = sizeof(UINTPTR); align <= 64; align <<= 1) { // 64, alignment
        ret = posix_memalign(&p, align, size);
        ICUNIT_ASSERT_EQUAL(ret, 0, ret);
        ICUNIT_ASSERT_NOT_EQUAL(p, nullptr, p);

        free(p);
    }

    return 0;
}

VOID ItPosixMem003(void)
{
    TEST_ADD_CASE("IT_POSIX_MEM_003", Testcase, TEST_POSIX, TEST_MEM, TEST_LEVEL0, TEST_FUNCTION);
}
