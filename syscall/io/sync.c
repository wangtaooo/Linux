/*
 * =====================================================================================
 *
 *       Filename:  sync.c
 *
 *    Description: 传统ＵＮＩＸ系统内核设有缓冲区高速缓存或页高速缓存，大多数磁盘ＩＯ都过程缓冲区进行．
 *              　　延迟写:
 *                      当我们写入文件，内核将数据复制到缓冲区，排入队列，晚些时候写入磁盘. 
 *                      
 *                      当内核要重用缓冲区来存放其他磁盘块数据，将所有延迟写数据写入磁盘
 *                      保证缓冲区和磁盘内容一致性，提供三个函数
 *
 *        Version:  1.0
 *        Created:  06/23/2018 10:07:37 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hang Cao (Melvin), caohang103215@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <unistd.h>

int main(){
    /* 
     * 1.void sync(void); 缓冲区排入队列，准备写入磁盘
     * 将所有修改过的块缓冲区排入队列，然后返回，并不等待实际写磁盘操作结束.
     *  */

    /*
     * 称为update系统守护进程周期性调用(一般30ｓ)sync函数．保证定期冲洗内核缓冲区.
     */

    /* 
     * 2.int fdatasync(int fd);　FreeBSD不支持
     *  */

    /*
     * 3.fsync函数
     * int fsync(int fd);只对文件fd有效，等待写磁盘操作结束才返回．
     * fsync用于数据库这样的应用程序，修保证修改过的程序写入磁盘上
     */
}

