/*
 * =====================================================================================
 *
 *       Filename:  damo.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  03/16/2026 10:03:27 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  storm-1614
 *   Organization:
 *
 * =====================================================================================
 */
#include <iostream>
#include <print>

#define fn(x)                                                                                                          \
    do                                                                                                                 \
    {                                                                                                                  \
    } while (0)

int main(int argc, char *argv[])
{
    char * const name = "chen";
    name[3] = 'a';  // 段错误
    const a = 1;
}
