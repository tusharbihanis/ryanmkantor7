/*
 * Copyright (c) 2013-2019 Huawei Technologies Co., Ltd. All rights reserved.
 * Copyright (c) 2020-2021 Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without specific prior written
 *    permission.
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

#include "It_vfs_jffs.h"

static UINT32 Testcase(VOID)
{
    INT32 fd = -1;
    INT32 fd1 = -1;
    INT32 ret;
    CHAR *pret = NULL;
    CHAR pathname[50] = { JFFS_PATH_NAME0 };
    CHAR buf[30] = "";
    struct dirent *ptr = NULL;
    INT32 offset, offset1, offset2, offset3, offset4;

    ret = mkdir(pathname, HIGHEST_AUTHORITY);
    ICUNIT_GOTO_EQUAL(ret, 0, ret, EXIT);

    ret = chdir(pathname);
    ICUNIT_GOTO_EQUAL(ret, 0, ret, EXIT);
    pret = getcwd(buf, 30); // 30 means name length
    ICUNIT_GOTO_NOT_EQUAL(pret, NULL, pret, EXIT);
    ICUNIT_GOTO_STRING_EQUAL(buf, pathname, buf, EXIT);

    (void)strcat_s(pathname, sizeof(pathname), "/0test");
    ret = mkdir(pathname, HIGHEST_AUTHORITY);
    ICUNIT_GOTO_EQUAL(ret, 0, ret, EXIT1);

    ret = chdir(pathname);
    ICUNIT_GOTO_EQUAL(ret, 0, ret, EXIT1);
    pret = getcwd(buf, 30); // 30 means name length
    ICUNIT_GOTO_NOT_EQUAL(pret, NULL, pret, EXIT1);
    ICUNIT_GOTO_STRING_EQUAL(buf, pathname, buf, EXIT1);

    JffsStrcat2(pathname, "/0file", sizeof(pathname));
    fd = open(pathname, O_NONBLOCK | O_CREAT | O_RDWR, HIGHEST_AUTHORITY);
    ICUNIT_GOTO_NOT_EQUAL(fd, -1, fd, EXIT2);

    JffsStrcat2(pathname, "/2test", sizeof(pathname));
    ret = mkdir(pathname, HIGHEST_AUTHORITY);
    ICUNIT_GOTO_EQUAL(ret, 0, ret, EXIT3);

    ret = chdir(pathname);
    ICUNIT_GOTO_EQUAL(ret, 0, ret, EXIT3);
    pret = getcwd(buf, 30); // 30 means name length
    ICUNIT_GOTO_NOT_EQUAL(pret, NULL, pret, EXIT3);
    ICUNIT_GOTO_STRING_EQUAL(buf, pathname, buf, EXIT3);

    (void)strcat_s(pathname, sizeof(pathname), "/1file");
    fd1 = open(pathname, O_NONBLOCK | O_CREAT | O_RDWR, HIGHEST_AUTHORITY);
    ICUNIT_GOTO_NOT_EQUAL(fd, -1, fd, EXIT4);

    JffsStrcat2(pathname, "/1test", sizeof(pathname));
    ret = mkdir(pathname, HIGHEST_AUTHORITY);
    ICUNIT_GOTO_EQUAL(ret, 0, ret, EXIT5);

    ret = chdir(pathname);
    ICUNIT_GOTO_EQUAL(ret, 0, ret, EXIT5);
    pret = getcwd(buf, 30); // 30 means name length
    ICUNIT_GOTO_NOT_EQUAL(pret, NULL, pret, EXIT5);
    ICUNIT_GOTO_STRING_EQUAL(buf, pathname, buf, EXIT5);

    ret = chdir("/storage");
    ICUNIT_GOTO_EQUAL(ret, 0, ret, EXIT5);
    pret = getcwd(buf, 30); // 30 means name length
    ICUNIT_GOTO_NOT_EQUAL(pret, NULL, pret, EXIT5);
    ICUNIT_GOTO_STRING_EQUAL(buf, "/storage", buf, EXIT5);

EXIT5:
    JffsStrcat2(pathname, "/1test", sizeof(pathname));
    rmdir(pathname);
EXIT4:
    JffsStrcat2(pathname, "/2test/1file", sizeof(pathname));
    close(fd1);
    remove(pathname);
EXIT3:
    JffsStrcat2(pathname, "/2test", sizeof(pathname));
    rmdir(pathname);
EXIT2:
    JffsStrcat2(pathname, "/0file", sizeof(pathname));
    close(fd);
    remove(pathname);
EXIT1:
    JffsStrcat2(pathname, "/0test", sizeof(pathname));
    rmdir(pathname);
EXIT:
    rmdir(JFFS_PATH_NAME0);
    return JFFS_NO_ERROR;
}


VOID ItFsJffs006(VOID)
{
    TEST_ADD_CASE("IT_FS_JFFS_006", Testcase, TEST_VFS, TEST_JFFS, TEST_LEVEL2, TEST_FUNCTION);
}

